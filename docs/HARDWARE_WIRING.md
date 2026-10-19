# Hardware Wiring

## Board

Arduino Uno R4 WiFi (`arduino:renesas_uno:unor4wifi`). ADC reference 5V.

## Sensor

KIE-TS-300B ver-2.0_12227k turbidity module. No manufacturer datasheet was found; wiring
below follows the public TS-300B spec (5V, analog out 0–4.5V, <500ms response, XH2.54
connector) — confirmed correct against the physical module in Chunk 2
(see `docs/TEST_LOG.md`'s 2026-10-19 entry).

| Module pin | Uno R4 WiFi pin | Notes |
|---|---|---|
| VCC | 5V | |
| GND | GND | |
| OUT (analog) | A0 | |

## Logic-level check

Module and board both run their analog I/O at 5V — no level-shifting needed as currently
understood. Flag immediately if the physical module turns out to be 3.3V-only (per
`Embedded/CLAUDE.md`'s standing rule to proactively flag voltage mismatches).

## Confirmed in Chunk 2 (see `docs/TEST_LOG.md`'s 2026-10-19 entry)

- [x] Physical module only exposes 3 pins (VCC, OUT, GND) — no 4th digital-threshold pin on
      this unit.
- [x] Observed dry (in-air) voltage and voltage across three liquids, recorded in
      `TEST_LOG.md`.
- [x] Actual ADC resolution returned by `analogReadResolution()` on this board: confirmed
      14-bit, active.
