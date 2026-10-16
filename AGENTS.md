# AGENTS.md

Rules for any agent working in this repo (Claude Code, Codex, OpenCode with a local model,
others). Work here may switch agents mid-task: everything needed to continue lives in this
repo, never in an agent's private memory. `CLAUDE.md` in this repo just points here.

turbidity-monitor is a single Arduino Uno R4 WiFi sensor node (KIE-TS-300B turbidity module).
Phase 1 scope: filtered, health-checked, calibration-flagged readings over serial only — no
networking, logging, or dashboard. See `plan.md` for the full roadmap and `architecture.md`
for why the code is split the way it is.

## If you are a small model (1.5B to 3B, 16k context)
- One chunk per session. Read only `current_state.md` and the one module you're touching.
- Copy an existing module's pattern (e.g. a new pure-logic module: copy `filter.h`/`filter.cpp`
  and its test) instead of inventing a new shape.
- Unsure? Stop and say exactly what you do not understand. Never guess a fix.

## Where the truth lives
- Progress: `git log --oneline -15`, then `current_state.md`.
- Roadmap: `plan.md` (stable; only changes on a real scope decision).
- Design/module boundaries: `architecture.md` (stable; only changes on a real design decision).
- Hardware-in-loop results: `docs/TEST_LOG.md` (dated entries, never overwritten).
- Do not create HANDOFF or status files. Continuity is `current_state.md` + the commits.

## Module boundary (the one rule that matters most here)
`firmware/turbidity_monitor/turbidity_monitor.ino` is an orchestrator ONLY: `setup()`/`loop()`
calling into modules, no logic of its own. Every module is one concern:
- `sensor.*` — the only module allowed to touch `Arduino.h` / `analogRead()`.
- `filter.*`, `health.*`, `calibration.*`, `reporting.*` — plain C++, no `Arduino.h`, so they
  compile and run as real unit tests on the host with `g++` (`tests/run_tests.sh`).
- `health` (is the sensor behaving plausibly?) and `calibration` (do we trust the NTU
  mapping?) are separate signals. Never merge them or infer one from the other — a sensor can
  be healthy but uncalibrated, or calibrated but currently out of range.

## Commands (repo root)
- Host unit tests (fast, no hardware): `tests/run_tests.sh`
- Compile for the board (no upload): `scripts/compile.sh`
- Upload (board connected): `scripts/upload.sh /dev/ttyACMx`
- Monitor: `arduino-cli monitor -p /dev/ttyACMx --config baudrate=115200`

## Chunk protocol
1. Say the goal and how you will verify it, in two lines.
2. Bug: write the failing test first. Feature: its test comes in the same chunk.
3. Smallest change that works, in the style of the surrounding code. No drive-by edits.
4. Verify: `tests/run_tests.sh` for pure modules; `scripts/compile.sh` always; hardware
   session + `docs/TEST_LOG.md` entry for anything touching `sensor.*` or the `.ino`.
5. Update `current_state.md` in the same commit: what's done, what's next.
6. Commit after every verified chunk (message = what changed, how verified, what's open).
   Pushing needs the user's explicit go-ahead the first time a remote exists.

## Never
- Secrets in files (not applicable yet — no networking in Phase 1, but keep it true when
  Phase 2 adds WiFi).
- Hardcoded machine values (paths, usernames). Pin numbers and board constants belong in
  `config.h` as named constants, not scattered literals.
- Claiming a calibrated reading without real reference data. Phase 1 output is always
  tagged `"calibrated":false` until Phase 2 supplies fitted calibration points.
- Weakening or deleting a test to get green. If a host test fails, the module is wrong.
- `git push`, `reset`, `rebase`, force anything, without the user's explicit approval.

## Too big or risky for a small model: stop and say so
Any change to the calibration curve's shape (not just its constants), ADC resolution
assumptions, anything that would make `sensor.*` do more than read and convert, and anything
needing hardware you don't have physical access to verify.

## Hard-won facts
- Uno R4 WiFi's exact usable ADC resolution was unverified at project start (datasheet
  claims up to 14-bit); confirmed value goes in `architecture.md` once Chunk 2 is done.
- No manufacturer datasheet found for "KIE-TS-300B ver-2.0_12227k" specifically; Phase 1
  treats the closely related TS-300B public specs (5 V, 0–4.5 V analog out, <500 ms response)
  as the working assumption, to be corrected against the physical module's observed behavior.
