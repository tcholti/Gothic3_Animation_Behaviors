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
    DOCS / "COLLABORATION_RULES.md",
    DOCS / "KNOWLEDGE_MAINTENANCE.md",
    DOCS / "KNOWLEDGE_REGISTRY.md",
    DOCS / "PROJECT_OPERATING_PROCEDURES.md",
    DOCS / "PROJECT_PIPELINE.md",
    DOCS / "WORK_IMPLEMENTATION_PROTOCOL.md",
    DOCS / "FEATURE_DEVELOPMENT_METHOD.md",
    ROOT / "research" / "README.md",
]

# The ordinary docs/ root is deliberately curated. A genuinely new permanent
# authority/reference is allowed, but adding it must be a deliberate lifecycle
# change that updates this allowlist and KNOWLEDGE_REGISTRY together.
ALLOWED_DOC_ROOT_FILES = {
    "ANIMATION_CATALOG.md",
    "ANIMATION_INDEX.md",
    "ANIMATION_RULES.md",
    "BETWEEN_CHATS.md",
    "COLLABORATION_RULES.md",
    "COLLISION_CLEANUP_CALLSITE_MAP.md",
    "COLLISION_DIAGNOSTICS.md",
    "COLLISION_LIFECYCLE.md",
    "COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md",
    "COLLISION_REFERENCE.md",
    "COLLISION_TEST_PLAN.md",
    "DESIGN.md",
    "ENGINEERING_GUIDE.md",
    "EVIDENCE_INDEX.md",
    "EVIDENCE_LEDGER_309_ONWARD.md",
    "EVIDENCE_PATH_MIGRATIONS.md",
    "FEATURE_DEVELOPMENT_METHOD.md",
    "GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md",
    "KNOWLEDGE_MAINTENANCE.md",
    "KNOWLEDGE_REGISTRY.md",
    "LOCAL_WORKSTATION_PATHS.md",
    "PROJECT_OPERATING_PROCEDURES.md",
    "PROJECT_PIPELINE.md",
    "PROJECT_SCOPE_CONTEXT.md",
    "README.md",
    "SESSION_ENTRYPOINT.md",
    "SOURCE_HOOK_GUIDE.md",
    "WORK_IMPLEMENTATION_PROTOCOL.md",
}

TEMP_ROOT_PATTERN = re.compile(
    r"(?:_PROBE|_TASK|_CORRECTION|_IMPLEMENTATION|_REFACTOR)\.md$",
    re.IGNORECASE,
)
ACTIVE_LEDGER_PATTERN = re.compile(r"EVIDENCE_LEDGER_\d+_ONWARD\.md$")
MD_LINK_PATTERN = re.compile(r"\[[^\]]*\]\(([^)]+\.md(?:#[^)]+)?)\)")

FORBIDDEN_CURRENT_REFERENCES = {
    "COLLISION_LIFECYCLE_PLAN.md": "COLLISION_LIFECYCLE.md",
    "COLLISION_LOGGER_PLAN.md": "COLLISION_DIAGNOSTICS.md",
    "COLLISION_ARCHITECTURE_REDESIGN_PLAN.md": "current architecture/reference or archived provenance",
}

CURRENT_STATE_MAX_BYTES = {
    "SESSION_ENTRYPOINT.md": 8 * 1024,
    "BETWEEN_CHATS.md": 4 * 1024,
}


def read(path: Path) -> str:
    return path.read_text(encoding="utf-8")


def current_markdown_files() -> list[Path]:
    return [
        p
        for p in DOCS.rglob("*.md")
        if ARCHIVE not in p.parents
    ]


def main() -> int:
    errors: list[str] = []
    warnings: list[str] = []

    for required in [
        DOCS,
        ARCHIVE,
        ARCHIVE / "investigations",
        ARCHIVE / "evidence",
        DOCS / "decisions",
        ACTIVE_WORK,
    ]:
        if not required.exists():
            errors.append(f"missing required lifecycle path: {required.relative_to(ROOT)}")

    root_md = sorted(p for p in DOCS.glob("*.md") if p.is_file())
    unexpected_root = sorted(
        p.name for p in root_md if p.name not in ALLOWED_DOC_ROOT_FILES
    )
    missing_root = sorted(
        name for name in ALLOWED_DOC_ROOT_FILES if not (DOCS / name).exists()
    )
    if unexpected_root:
        errors.append(
            "unregistered Markdown file(s) in docs/ root: "
            + ", ".join(unexpected_root)
            + "; classify as current authority/reference or move to docs/work/active/"
        )
    if missing_root:
        errors.append(
            "registered current docs missing from docs/ root: " + ", ".join(missing_root)
        )

    root_ledgers = sorted(p for p in DOCS.glob("EVIDENCE_LEDGER*.md") if p.is_file())
    active_ledgers = [p for p in root_ledgers if ACTIVE_LEDGER_PATTERN.fullmatch(p.name)]
    if len(root_ledgers) != 1 or len(active_ledgers) != 1:
        errors.append(
            "docs/ must contain exactly one active evidence ledger named "
            "EVIDENCE_LEDGER_<start>_ONWARD.md; closed volumes belong in docs/archive/evidence/"
        )
    elif active_ledgers[0].stat().st_size > 64 * 1024:
        warnings.append(
            f"active ledger is {active_ledgers[0].stat().st_size} bytes; rotate it before it becomes routine context burden"
        )

    bad_root = sorted(p.name for p in root_md if TEMP_ROOT_PATTERN.search(p.name))
    if bad_root:
        errors.append(
            "temporary lifecycle documents found in docs/ root: " + ", ".join(bad_root)
        )

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
            errors.append(f"required lifecycle-routing file missing: {p.relative_to(ROOT)}")
            continue
        if ROUTE_MARKER not in read(p):
            errors.append(
                f"knowledge-lifecycle route marker missing: {p.relative_to(ROOT)}"
            )

    for name, max_bytes in CURRENT_STATE_MAX_BYTES.items():
        p = DOCS / name
        if p.exists() and p.stat().st_size > max_bytes:
            errors.append(
                f"current-state pointer too large: {p.relative_to(ROOT)} "
                f"({p.stat().st_size} bytes > {max_bytes}); promote durable content and compress the pointer"
            )

    evidence_index = DOCS / "EVIDENCE_INDEX.md"
    if evidence_index.exists() and evidence_index.stat().st_size > 20 * 1024:
        warnings.append(
            "EVIDENCE_INDEX.md exceeds 20 KiB; prefer routing compression over narrative growth"
        )

    collision_reference = DOCS / "COLLISION_REFERENCE.md"
    if collision_reference.exists() and collision_reference.stat().st_size > 24 * 1024:
        warnings.append(
            "COLLISION_REFERENCE.md exceeds 24 KiB; consider splitting by stable subject rather than creating a monolith"
        )

    current_docs = current_markdown_files()
    for p in current_docs:
        text = read(p)
        for old_name, replacement in FORBIDDEN_CURRENT_REFERENCES.items():
            if old_name in text:
                errors.append(
                    f"stale current-document reference in {p.relative_to(ROOT)}: "
                    f"{old_name} -> use {replacement}"
                )

    # Validate ordinary/current Markdown links. Archive documents are provenance
    # and may retain historical paths deliberately.
    scan_roots = [ROOT / "README.md", ROOT / "research" / "README.md"] + current_docs
    seen: set[Path] = set()
    for p in scan_roots:
        if p in seen:
            continue
        seen.add(p)
        text = read(p)
        for raw_target in MD_LINK_PATTERN.findall(text):
            target = raw_target.split("#", 1)[0]
            if not target or "://" in target or target.startswith("mailto:"):
                continue
            resolved = (p.parent / target).resolve()
            try:
                resolved.relative_to(ROOT.resolve())
            except ValueError:
                errors.append(
                    f"Markdown link escapes repository: {p.relative_to(ROOT)} -> {target}"
                )
                continue
            if not resolved.exists():
                errors.append(
                    f"broken Markdown link: {p.relative_to(ROOT)} -> {target}"
                )

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
