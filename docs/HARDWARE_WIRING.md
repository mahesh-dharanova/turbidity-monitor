# Hardware Wiring

## Board

Arduino Uno R4 WiFi (`arduino:renesas_uno:unor4wifi`). ADC reference 5V.

## Sensor

KIE-TS-300B ver-2.0_12227k turbidity module. No manufacturer datasheet was found; wiring
below follows the public TS-300B spec (5V, analog out 0–4.5V, <500ms response, XH2.54
connector) until confirmed against the physical module in Chunk 2.

| Module pin | Uno R4 WiFi pin | Notes |
|---|---|---|
| VCC | 5V | |
| GND | GND | |
| OUT (analog) | A0 | |

## Logic-level check

Module and board both run their analog I/O at 5V — no level-shifting needed as currently
understood. Flag immediately if the physical module turns out to be 3.3V-only (per
`Embedded/CLAUDE.md`'s standing rule to proactively flag voltage mismatches).

## To confirm in Chunk 2

- [ ] Physical pin labels on the module match this table (some TS-300B variants expose a
      4th digital-threshold pin — unused here either way, but note if present).
- [ ] Observed dry (in-air) voltage and in-water voltage, recorded in `TEST_LOG.md`.
- [ ] Actual ADC resolution returned by `analogReadResolution()` on this board.
