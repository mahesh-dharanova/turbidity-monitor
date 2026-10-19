# Plan

Roadmap broken into chunks. Edit only on a real scope decision.

## Goals

- Phase 1: a modular, tested Arduino Uno R4 WiFi sensor node that reports filtered,
  health-checked turbidity readings from the KIE-TS-300B over serial.
- Phase 2: real calibration once reference turbidity standards exist.

## Phase 1 — sensor node (current)

1. [x] Scaffold — repo structure, docs, stub modules, git init.
   Verified: `scripts/compile.sh` succeeds on the empty orchestrator.
2. [x] Sensor module — wire the KIE-TS-300B (5V/GND/A0), implement `sensor.cpp`
   (raw ADC read + voltage), confirm the Uno R4 WiFi's real ADC resolution on hardware.
   Verified: upload + monitor, dry/distilled/lemon/turbid-solution readings logged in
   `docs/TEST_LOG.md`.
3. [ ] Filter module — windowed average + median-of-5 smoothing.
   Verified: `tests/run_tests.sh` covers flat input, single-spike rejection, ramp response.
4. [ ] Health module — range / stuck-value / warm-up checks, independent of calibration.
   Verified: one unit test per fault condition.
5. [ ] Calibration module — voltage→approximate-NTU, always flagged `UNCALIBRATED` in
   Phase 1 (no reference solutions yet).
   Verified: unit tests against known vendor-typical voltage points; a test asserting the
   uncalibrated flag is always set.
6. [ ] Reporting module — JSON line builder.
   Verified: unit tests on formatting and edge values.
7. [ ] Orchestrator wiring — `.ino` calls sensor → filter → health → calibration →
   reporting → `Serial.println`, once per second.
   Verified: compile + upload + monitor, dry and in-water session logged.
8. [ ] Integration pass — full host test suite + fresh hardware session together,
   `current_state.md` matches reality, first tag marking Phase 1 complete.

## Phase 2 — real calibration (not started)

- Collect reference turbidity standards (formazin/NTU solutions or equivalent known samples).
- Replace the `UNCALIBRATED` curve in `calibration.cpp` with fitted reference points.
- Re-verify against the host tests and a fresh hardware session.
- Only after this: consider whether logging or a dashboard (next phases) are worth building.
