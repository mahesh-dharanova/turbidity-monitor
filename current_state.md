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

- Chunk 2 (sensor): complete. Wired VCC→5V, GND→GND, OUT→A0 on `/dev/ttyACM0`. `sensor.cpp`
  real (windowed ADC average + volts conversion), hardware-verified across four conditions
  in the same session: dry air (~3.082V) and three liquids. Distilled water (~3.575V) and
  lemon water (~3.48V) both read higher and tighter than dry air, as expected for clearer
  liquids; a turbid powdered solution read noisy (~3.00–3.13V, never settling) with a mean
  that happens to land back near the dry-air baseline — variance, not mean, is what
  separates it. 14-bit ADC resolution confirmed active (raw values up to ~11717, ruling out
  10/12-bit clipping). See `docs/TEST_LOG.md` for the full dated entry.

## Next

- Chunk 3: filter module — windowed average + median-of-5 smoothing. Pure logic, no
  hardware session strictly required (host tests via `tests/run_tests.sh`).

## Open questions / blockers

- No manufacturer datasheet for "KIE-TS-300B ver-2.0_12227k" — working from the public
  TS-300B spec; Chunk 2's observed behavior (clear > turbid in mean voltage) is consistent
  with it, but the full voltage-to-NTU curve is still unverified.
- No turbidity calibration reference solutions yet — Phase 1 stays in `UNCALIBRATED` mode.
- Turbid sample's persistent high-frequency noise (not just its mean voltage) may be a
  useful signal later — not acted on in Phase 1, see `docs/TEST_LOG.md`'s open items.
