# Current State

Updated once per chunk, right after it is built and verified.
This is a pointer into git history for the next agent, not a duplicate of it.

## Done

- Chunk 1 (scaffold): repo structure, `AGENTS.md`/`README.md`/`plan.md`/`architecture.md`,
  stub modules (`sensor`, `filter`, `health`, `calibration`, `reporting`) with signatures
  only, `tests/run_tests.sh` harness, `scripts/compile.sh`/`upload.sh`, doc stubs. Verified:
  `scripts/compile.sh` compiles the empty orchestrator against
  `arduino:renesas_uno:unor4wifi`; `tests/run_tests.sh` runs (no real assertions yet since
  modules are stubs).

## Next

- Chunk 2: wire the KIE-TS-300B to the board, implement `sensor.cpp`, confirm real ADC
  resolution on hardware, log a dry/in-water session in `docs/TEST_LOG.md`.

## Open questions / blockers

- No manufacturer datasheet for "KIE-TS-300B ver-2.0_12227k" — working from the public
  TS-300B spec until the physical module is wired and its actual behavior observed.
- No turbidity calibration reference solutions yet — Phase 1 stays in `UNCALIBRATED` mode.
