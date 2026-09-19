#!/usr/bin/env python3
"""Validate Gothic3_Animation_Behaviors documentation lifecycle invariants."""

from __future__ import annotations

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
DOCS = ROOT / "docs"
ARCHIVE = DOCS / "archive"
ACTIVE_WORK = DOCS / "work" / "active"

ROUTE_MARKER = "KNOWLEDGE_LIFECYCLE_ROUTE"
ROUTE_FILES = [
    ROOT / "README.md",
    DOCS / "README.md",
    DOCS / "KNOWLEDGE_MAINTENANCE.md",
    DOCS / "KNOWLEDGE_REGISTRY.md",
    DOCS / "PROJECT_OPERATING_PROCEDURES.md",
    DOCS / "PROJECT_PIPELINE.md",
    DOCS / "WORK_IMPLEMENTATION_PROTOCOL.md",
    DOCS / "FEATURE_DEVELOPMENT_METHOD.md",
]

TEMP_ROOT_PATTERN = re.compile(
    r"(?:_PROBE|_TASK|_CORRECTION|_IMPLEMENTATION|_REFACTOR)\.md$",
    re.IGNORECASE,
)
ACTIVE_LEDGER_PATTERN = re.compile(r"EVIDENCE_LEDGER_\d+_ONWARD\.md$")
MD_LINK_PATTERN = re.compile(r"\[[^\]]*\]\(([^)]+\.md(?:#[^)]+)?)\)")


def read(path: Path) -> str:
    return path.read_text(encoding="utf-8")


def main() -> int:
    errors: list[str] = []
    warnings: list[str] = []

    for required in [DOCS, ARCHIVE, ARCHIVE / "investigations", ARCHIVE / "evidence", ACTIVE_WORK]:
        if not required.exists():
            errors.append(f"missing required lifecycle path: {required.relative_to(ROOT)}")

    root_ledgers = sorted(p for p in DOCS.glob("EVIDENCE_LEDGER*.md") if p.is_file())
    active_ledgers = [p for p in root_ledgers if ACTIVE_LEDGER_PATTERN.fullmatch(p.name)]
    if len(root_ledgers) != 1 or len(active_ledgers) != 1:
        errors.append(
            "docs/ must contain exactly one active evidence ledger named "
            "EVIDENCE_LEDGER_<start>_ONWARD.md; closed volumes belong in docs/archive/evidence/"
        )
    elif active_ledgers[0].stat().st_size > 64 * 1024:
        warnings.append(
            f"active ledger is {active_ledgers[0].stat().st_size} bytes; consider rotating it"
        )

    bad_root = sorted(p.name for p in DOCS.glob("*.md") if TEMP_ROOT_PATTERN.search(p.name))
    if bad_root:
        errors.append("temporary lifecycle documents found in docs/ root: " + ", ".join(bad_root))

    if ACTIVE_WORK.exists():
        for p in sorted(ACTIVE_WORK.glob("*.md")):
            if p.name == "README.md":
                continue
            if "**Status:** ACTIVE" not in read(p):
                errors.append(
                    f"active temporary document lacks '**Status:** ACTIVE': {p.relative_to(ROOT)}"
                )

    for p in ROUTE_FILES:
        if not p.exists():
            errors.append(f"required routing authority missing: {p.relative_to(ROOT)}")
            continue
        if ROUTE_MARKER not in read(p):
            errors.append(f"knowledge-lifecycle route marker missing: {p.relative_to(ROOT)}")

    scan_roots = [ROOT / "README.md"] + [
        p for p in DOCS.rglob("*.md") if ARCHIVE not in p.parents
    ]
    for p in scan_roots:
        text = read(p)
        for raw_target in MD_LINK_PATTERN.findall(text):
            target = raw_target.split("#", 1)[0]
            if not target or "://" in target or target.startswith("mailto:"):
                continue
            resolved = (p.parent / target).resolve()
            try:
                resolved.relative_to(ROOT.resolve())
            except ValueError:
                errors.append(f"Markdown link escapes repository: {p.relative_to(ROOT)} -> {target}")
                continue
            if not resolved.exists():
                errors.append(f"broken Markdown link: {p.relative_to(ROOT)} -> {target}")

    if warnings:
        print("Knowledge-state warnings:")
        for item in warnings:
            print(f"  WARN: {item}")

    if errors:
        print("Knowledge-state validation FAILED:")
        for item in errors:
            print(f"  ERROR: {item}")
        return 1

    print("Knowledge-state validation PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
