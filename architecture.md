# Architecture

Design and structure. Edit only on a real design decision.

## Overview

Single Arduino Uno R4 WiFi sensor node. `turbidity_monitor.ino` is an orchestrator only; all
logic lives in single-concern modules under `firmware/turbidity_monitor/`. The split exists
so everything that doesn't strictly need the Arduino runtime (`filter`, `health`,
`calibration`, `reporting`) can be unit-tested on the host with plain `g++` — no emulator, no
new toolchain dependency. Only `sensor.*` touches `Arduino.h`/`analogRead()` and can only be
verified on the physical board.

```
sensor.cpp  --raw ADC, voltage-->  filter.cpp  --smoothed voltage-->  health.cpp
                                                                           |
                                                                           v
                                                    calibration.cpp  --NTU (flagged)-->  reporting.cpp
                                                                                               |
                                                                                               v
                                                                                     Serial.println (JSON)
```

## Components

- **`sensor`** — reads the KIE-TS-300B analog pin, converts raw ADC counts to volts using
  the board's actual ADC resolution and reference voltage. The only module with hardware
  dependence.
- **`filter`** — windowed average (cancels AC mains flicker) + median-of-5 smoothing (drops
  single-sample spikes, e.g. a bubble). Pure function of a value stream.
- **`health`** — plausibility checks on the (filtered) voltage: out-of-range, stuck value,
  still warming up. Independent of calibration state by design (house rule, see below).
- **`calibration`** — maps voltage to an NTU estimate. In Phase 1 there is no reference data,
  so every reading is tagged `"calibrated":false` and uses a vendor-typical approximate
  curve. Phase 2 replaces the curve's constants once real reference solutions exist.
- **`reporting`** — builds the one-line JSON report into a fixed buffer. Pure formatting,
  no I/O; the `.ino` does the actual `Serial.println`.

## Key decisions

| Decision | Why | Date |
|---|---|---|
| Sensor node reports raw+filtered+flagged values only, no business logic | House rule in `Embedded/CLAUDE.md`: sensor nodes stay dumb, a future hub would own any decision-making | 2026-10-16 |
| `health` and `calibration` are separate modules/signals | House rule in `Embedded/CLAUDE.md`: never merge or infer one from the other | 2026-10-16 |
| Phase 1 ships explicit `UNCALIBRATED` mode instead of a guessed calibration | No reference turbidity standards on hand; a silently-wrong NTU number is worse than an honestly-flagged approximate one | 2026-10-16 |
| Host-side unit tests via plain `g++`, no framework | `filter`/`health`/`calibration`/`reporting` have zero Arduino dependency; g++ is already installed; avoids adding PlatformIO/Unity for no benefit | 2026-10-16 |
| Board: Arduino Uno R4 WiFi, FQBN `arduino:renesas_uno:unor4wifi` | User's hardware; WiFi unused in Phase 1 but available if a later phase needs it | 2026-10-16 |

## Open hardware questions (resolve during Chunk 2, don't assume)

- Exact ADC resolution the Uno R4 WiFi actually returns via `analogReadResolution()`
  (datasheet claims up to 14-bit).
- Exact pinout of the physical "KIE-TS-300B ver-2.0_12227k" module — no manufacturer
  datasheet was found; treating it as the public TS-300B spec (5V, 0–4.5V analog out) until
  confirmed against the real module.
