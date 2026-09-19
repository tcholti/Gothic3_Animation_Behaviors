# Active Temporary Work

**Purpose:** Working area for temporary probes, bounded implementation contracts, audit tasks and other documents that exist only while a question is active.

Every temporary document here must declare:

```text
**Status:** ACTIVE
```

Closure is mandatory:

```text
question/result closes
-> evidence recorded
-> reusable facts promoted to current reference
-> architecture consequence promoted to owning architecture
-> significant rationale preserved in ADR when warranted
-> current-state pointers updated
-> temporary document moved to docs/archive/investigations/
```

A closed temporary document must not remain here merely because it may be useful later. Its history remains available from the archive and Git.
