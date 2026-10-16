# turbidity-monitor

Water turbidity sensor node: Arduino Uno R4 WiFi + KIE-TS-300B turbidity module.

## Overview

Phase 1 is a sensor node only: reads the KIE-TS-300B analog output, filters it, runs basic
health checks, and reports a calibrated-or-flagged-uncalibrated turbidity value as one JSON
line per second over serial. No networking, logging, or dashboard in this phase — see
`plan.md` for what comes after.

## Goals

- Phase 1: correct, modular, tested serial readings from the sensor.
- Phase 2: real calibration once reference turbidity standards are available.

## Technology

- Arduino Uno R4 WiFi (`arduino:renesas_uno:unor4wifi`), Arduino core, C++.
- `arduino-cli` for compile/upload.
- Plain `g++` for host-side unit tests of the pure logic modules (no framework dependency).

## Setup

See `docs/HARDWARE_WIRING.md` for wiring and `scripts/compile.sh` / `scripts/upload.sh` for
the build workflow.

## Usage

Upload `firmware/turbidity_monitor/turbidity_monitor.ino`, open a serial monitor at 115200
baud. One JSON line per second.

## Development

Read `AGENTS.md` first — it's the authoritative, agent-agnostic rulebook for this repo.

## Testing

`tests/run_tests.sh` runs the host-side unit tests for the pure logic modules
(`filter`, `health`, `calibration`, `reporting`). Hardware-in-loop verification is recorded
in `docs/TEST_LOG.md`.

## Configuration

No secrets in Phase 1 (no networking). `.env.example` is omitted until Phase 2 needs one.

## Documentation

- `plan.md` — roadmap and chunks.
- `architecture.md` — module boundaries and design decisions.
- `current_state.md` — what's done, what's next (updated per verified chunk).
- `docs/` — hardware wiring, calibration procedure, test log.
