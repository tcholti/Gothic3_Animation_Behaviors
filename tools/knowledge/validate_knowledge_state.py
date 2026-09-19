#!/usr/bin/env python3
"""Validate Gothic3_Animation_Behaviors documentation lifecycle invariants."""

from __future__ import annotations

import html
import re
from pathlib import Path
from urllib.parse import unquote

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
EXPLICIT_HTML_ID_PATTERN = re.compile(
    r"<(?:a|span)\b[^>]*\bid\s*=\s*['\"]([^'\"]+)['\"][^>]*>",
    re.IGNORECASE,
)
ATX_HEADING_PATTERN = re.compile(r"^ {0,3}#{1,6}\s+(.+?)\s*$")
SETEXT_HEADING_PATTERN = re.compile(r"^ {0,3}(?:=+|-+)\s*$")
FENCED_CODE_BOUNDARY_PATTERN = re.compile(r"^ {0,3}(?:`{3,}|~{3,})")
NUMERIC_SECTION_ROUTE_PATTERN = re.compile(
    r"(?P<target>(?:[A-Za-z0-9_.-]+/)*[A-Za-z0-9_.-]+\.md)"
    r"`?\s+§(?P<section>\d+(?:\.\d+)*)\b"
)

FORBIDDEN_CURRENT_REFERENCES = {
    "COLLISION_LIFECYCLE_PLAN.md": "COLLISION_LIFECYCLE.md",
    "COLLISION_LOGGER_PLAN.md": "COLLISION_DIAGNOSTICS.md",
    "COLLISION_ARCHITECTURE_REDESIGN_PLAN.md": "current architecture/reference or archived provenance",
}

CURRENT_STATE_MAX_BYTES = {
    "SESSION_ENTRYPOINT.md": 8 * 1024,
    "BETWEEN_CHATS.md": 4 * 1024,
}

# Semantic route invariants protect the high-value rules that are easiest for a
# later cleanup/review to accidentally make ambiguous while still passing
# structural checks.
REQUIRED_SNIPPETS = {
    ROOT / "README.md": [
        "canonical front door",
        "If the previous Chat failed, hit max context, or became unusable",
    ],
    DOCS / "README.md": [
        "root `README.md` **Start Here** → `SESSION_ENTRYPOINT.md`",
        "Previous Chat died before handoff; what now?",
    ],
    DOCS / "SESSION_ENTRYPOINT.md": [
        "Repository startup begins at root `README.md` **Start Here**",
    ],
    DOCS / "BETWEEN_CHATS.md": [
        "start at root `README.md`",
    ],
    DOCS / "COLLABORATION_RULES.md": [
        "discoverable first hop is always root `README.md` **Start Here**",
    ],
    DOCS / "KNOWLEDGE_MAINTENANCE.md": [
        "Current reference tells us what we know.",
        "Closed temporary work and closed ledger volumes are archived.",
    ],
}

CLOSED_LEDGER_REF_PATTERN = re.compile(
    r"EVIDENCE_LEDGER_(?!309_ONWARD\.md)(?:STEP_B|\d+_ONWARD)\.md"
)


def read(path: Path) -> str:
    return path.read_text(encoding="utf-8")


def current_markdown_files() -> list[Path]:
    return [
        p
        for p in DOCS.rglob("*.md")
        if ARCHIVE not in p.parents
    ]


def strip_inline_markdown(text: str) -> str:
    text = re.sub(r"!\[([^\]]*)\]\([^)]+\)", r"\1", text)
    text = re.sub(r"\[([^\]]+)\]\([^)]+\)", r"\1", text)
    text = re.sub(r"<[^>]+>", "", text)
    return html.unescape(text)


def markdown_prose_text(text: str) -> str:
    prose_lines: list[str] = []
    inside_fence = False
    for line in text.splitlines():
        if FENCED_CODE_BOUNDARY_PATTERN.match(line):
            inside_fence = not inside_fence
            prose_lines.append("")
            continue
        prose_lines.append("" if inside_fence else line)
    return "\n".join(prose_lines)


def normalize_heading_anchor(heading: str) -> str:
    heading = strip_inline_markdown(heading)
    heading = re.sub(r"\s+#+\s*$", "", heading).strip().lower()
    return "".join(
        "-" if char.isspace() else char
        for char in heading
        if char.isalnum() or char in {"_", "-"} or char.isspace()
    )


def markdown_anchors(text: str) -> set[str]:
    text = markdown_prose_text(text)
    anchors = {
        html.unescape(match)
        for match in EXPLICIT_HTML_ID_PATTERN.findall(text)
    }
    heading_counts: dict[str, int] = {}
    lines = text.splitlines()

    heading_texts: list[str] = []
    for index, line in enumerate(lines):
        atx_match = ATX_HEADING_PATTERN.match(line)
        if atx_match:
            heading_texts.append(atx_match.group(1))
            continue
        if index > 0 and SETEXT_HEADING_PATTERN.match(line) and lines[index - 1].strip():
            heading_texts.append(lines[index - 1].strip())

    for heading in heading_texts:
        base = normalize_heading_anchor(heading)
        if not base:
            continue
        duplicate_index = heading_counts.get(base, 0)
        anchor = base if duplicate_index == 0 else f"{base}-{duplicate_index}"
        anchors.add(anchor)
        heading_counts[base] = duplicate_index + 1

    return anchors


def markdown_section_numbers(text: str) -> set[str]:
    text = markdown_prose_text(text)
    sections: set[str] = set()
    for line in text.splitlines():
        heading_match = ATX_HEADING_PATTERN.match(line)
        if not heading_match:
            continue
        heading = strip_inline_markdown(heading_match.group(1))
        section_match = re.match(r"^(\d+(?:\.\d+)*)\b", heading.strip())
        if section_match:
            sections.add(section_match.group(1))
    return sections


def numeric_route_text(text: str) -> str:
    # A complete route inside one code span is treated as a literal/example.
    # Filename-only code spans remain eligible when the following §N is prose.
    text = markdown_prose_text(text)
    return re.sub(
        r"`([^`\n]+)`",
        lambda match: "" if "§" in match.group(1) else match.group(1),
        text,
    )


def resolve_numeric_route(source: Path, target: str) -> Path | None:
    relative_candidate = (source.parent / target).resolve()
    root_candidate = (ROOT / target).resolve()
    for candidate in (relative_candidate, root_candidate):
        try:
            candidate.relative_to(ROOT.resolve())
        except ValueError:
            continue
        if candidate.exists():
            return candidate
    return None


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

    registry = DOCS / "KNOWLEDGE_REGISTRY.md"
    if registry.exists():
        registry_text = read(registry)
        missing_registry_routes = []
        for name in sorted(ALLOWED_DOC_ROOT_FILES):
            registry_token = (
                "`docs/README.md`" if name == "README.md" else f"`{name}`"
            )
            if registry_token not in registry_text:
                missing_registry_routes.append(name)
        if missing_registry_routes:
            errors.append(
                "docs-root allowlist file(s) lack a KNOWLEDGE_REGISTRY.md route: "
                + ", ".join(missing_registry_routes)
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
        session_text = read(DOCS / "SESSION_ENTRYPOINT.md") if (DOCS / "SESSION_ENTRYPOINT.md").exists() else ""
        between_text = read(DOCS / "BETWEEN_CHATS.md") if (DOCS / "BETWEEN_CHATS.md").exists() else ""
        current_state_text = session_text + "\n" + between_text

        for p in sorted(ACTIVE_WORK.glob("*.md")):
            if p.name == "README.md":
                continue
            if "**Status:** ACTIVE" not in read(p):
                errors.append(
                    f"active temporary document lacks '**Status:** ACTIVE': {p.relative_to(ROOT)}"
                )
            if p.name not in current_state_text:
                errors.append(
                    f"orphan active temporary document is not routed by SESSION_ENTRYPOINT.md "
                    f"or BETWEEN_CHATS.md: {p.relative_to(ROOT)}"
                )

    for p in ROUTE_FILES:
        if not p.exists():
            errors.append(f"required lifecycle-routing file missing: {p.relative_to(ROOT)}")
            continue
        if ROUTE_MARKER not in read(p):
            errors.append(
                f"knowledge-lifecycle route marker missing: {p.relative_to(ROOT)}"
            )

    for p, snippets in REQUIRED_SNIPPETS.items():
        if not p.exists():
            errors.append(f"semantic-route file missing: {p.relative_to(ROOT)}")
            continue
        text = read(p)
        for snippet in snippets:
            if snippet not in text:
                errors.append(
                    f"required semantic lifecycle/startup rule missing from "
                    f"{p.relative_to(ROOT)}: {snippet}"
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

    if evidence_index.exists():
        index_text = read(evidence_index)
        archive_evidence = ARCHIVE / "evidence"
        archived_ledgers = sorted(
            p for p in archive_evidence.glob("EVIDENCE_LEDGER*.md") if p.is_file()
        )
        for p in archived_ledgers:
            if p.name not in index_text:
                errors.append(
                    f"archived evidence ledger is not routed by EVIDENCE_INDEX.md: "
                    f"{p.relative_to(ROOT)}"
                )
        if len(active_ledgers) == 1 and active_ledgers[0].name not in index_text:
            errors.append(
                "active evidence ledger is not routed by EVIDENCE_INDEX.md: "
                + active_ledgers[0].name
            )

    collision_reference = DOCS / "COLLISION_REFERENCE.md"
    if collision_reference.exists() and collision_reference.stat().st_size > 24 * 1024:
        warnings.append(
            "COLLISION_REFERENCE.md exceeds 24 KiB; consider splitting by stable subject rather than creating a monolith"
        )

    current_docs = current_markdown_files()
    permitted_current_markdown_dirs = {
        DOCS.resolve(),
        (DOCS / "decisions").resolve(),
        ACTIVE_WORK.resolve(),
    }
    unexpected_current_locations = sorted(
        p.relative_to(ROOT)
        for p in current_docs
        if p.parent.resolve() not in permitted_current_markdown_dirs
    )
    if unexpected_current_locations:
        errors.append(
            "current Markdown file(s) found outside permitted docs/, docs/decisions/, "
            "or docs/work/active/ topology: "
            + ", ".join(str(p) for p in unexpected_current_locations)
        )

    for p in current_docs:
        text = read(p)
        for old_name, replacement in FORBIDDEN_CURRENT_REFERENCES.items():
            if old_name in text:
                errors.append(
                    f"stale current-document reference in {p.relative_to(ROOT)}: "
                    f"{old_name} -> use {replacement}"
                )

        # Closed ledger filenames belong behind EVIDENCE_INDEX routing. Current
        # technical/reference/procedure documents should cite EV IDs, not bind
        # themselves directly to old storage volumes. The index and migration
        # map are the intentional exceptions.
        if p.name not in {"EVIDENCE_INDEX.md", "EVIDENCE_PATH_MIGRATIONS.md"}:
            match = CLOSED_LEDGER_REF_PATTERN.search(text)
            if match:
                errors.append(
                    f"direct closed-ledger filename reference in current document "
                    f"{p.relative_to(ROOT)}: {match.group(0)}; cite EV IDs and route "
                    f"storage through EVIDENCE_INDEX.md"
                )

    # Validate ordinary/current Markdown links. Archive documents are provenance
    # and may retain historical paths deliberately.
    scan_roots = [ROOT / "README.md", ROOT / "research" / "README.md"] + current_docs
    seen: set[Path] = set()
    anchor_cache: dict[Path, set[str]] = {}
    section_cache: dict[Path, set[str]] = {}
    for p in scan_roots:
        if p in seen:
            continue
        seen.add(p)
        text = read(p)
        for raw_target in MD_LINK_PATTERN.findall(text):
            target, separator, raw_fragment = raw_target.partition("#")
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
                continue
            if separator:
                fragment = unquote(raw_fragment)
                anchors = anchor_cache.setdefault(
                    resolved, markdown_anchors(read(resolved))
                )
                if fragment not in anchors:
                    errors.append(
                        f"broken Markdown fragment: {p.relative_to(ROOT)} -> "
                        f"{target}#{raw_fragment}"
                    )

        for match in NUMERIC_SECTION_ROUTE_PATTERN.finditer(
            numeric_route_text(text)
        ):
            target = match.group("target")
            section = match.group("section")
            resolved = resolve_numeric_route(p, target)
            if resolved is None:
                errors.append(
                    f"broken numeric section route: {p.relative_to(ROOT)} -> "
                    f"{target} §{section} (target file not found)"
                )
                continue
            sections = section_cache.setdefault(
                resolved, markdown_section_numbers(read(resolved))
            )
            if section not in sections:
                errors.append(
                    f"broken numeric section route: {p.relative_to(ROOT)} -> "
                    f"{target} §{section}"
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
