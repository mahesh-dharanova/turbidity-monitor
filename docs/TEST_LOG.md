# Test Log

Dated hardware-in-loop verification entries. Never edit a past entry — append a new one.

## 2026-10-16 — Chunk 1 scaffold

- `scripts/compile.sh` succeeds against `arduino:renesas_uno:unor4wifi` with the empty
  orchestrator (`Serial.begin()` only) and all stub modules compiled alongside it.
- `tests/run_tests.sh` passes (asserts stub placeholder behavior only — not real logic).
- No hardware connected yet; no sensor wiring performed.

## 2026-10-19 — Chunk 2: sensor wired and hardware-verified

- Wired KIE-TS-300B: VCC→5V, GND→GND, OUT→A0. Board: `/dev/ttyACM0` (Arduino Uno R4 WiFi,
  confirmed via `arduino-cli board list`).
- `sensor.cpp` implemented for real (windowed ADC average over `SAMPLE_WINDOW_US`,
  raw-to-volts conversion at 14-bit/`ADC_VREF_VOLTS`). `.ino` prints raw sensor output
  directly (`{"ms":...,"raw":...,"v":...}`), same pattern as the sibling `ph-monitor`/
  `water-level-monitor` Chunk 2 sessions.
- `scripts/compile.sh` succeeded (20% flash, 20% SRAM) and upload succeeded on first try.
- Four conditions captured in one continuous session, probe rinsed and dried between each:

| Condition | Volts (settled) | Raw ADC (14-bit) | Noise |
|---|---|---|---|
| Dry (air baseline) | ~3.081–3.082 | ~10096–10098 | tight, <0.001V |
| Distilled water | ~3.574–3.576 | ~11710–11717 | tight, ~0.002V |
| Lemon water | ~3.48 | ~11392–11426 | slight, ~0.01V |
| Powdered solution (turbid) | ~3.00–3.13 | ~9840–10247 | high, ~0.05–0.1V, non-settling |

- Directionally clean: clearer liquids read a higher, tighter voltage than dry air; the
  turbid powdered-solution sample's *mean* voltage happens to land back near the dry-air
  baseline, but it never settles — it keeps jittering ±0.05–0.1V for as long as it was
  observed (confirmed persistent across two separate 10–15s captures, not a dip transient).
  Mean voltage alone would NOT separate "dry" from "turbid" here; variance does. Worth
  carrying into `health`/`filter` design (Chunk 3/4) rather than assuming a single scalar
  voltage tells the whole story.
- Confirms 14-bit `analogReadResolution()` is genuinely active: raw values reached ~11717,
  which rules out silent 10-bit (max 1023) or 12-bit (max 4095) clipping.
- Confirms wiring (VCC/GND/OUT) is correct and `sensor.cpp`'s real ADC read works end to end.

### Open items carried forward

- No manufacturer datasheet for "KIE-TS-300B ver-2.0_12227k" still found; behavior observed
  here (clear > turbid in mean voltage, turbid shows elevated noise) is consistent with the
  public TS-300B family spec used as the working assumption, but the module's full
  voltage-to-NTU curve remains unverified — Phase 2 scope once real NTU reference standards
  exist (see `plan.md`).
- No reference turbidity standards (known-NTU solutions) used this session — the three
  liquids/solution tested confirm the sensor responds distinctly and directionally to
  clarity, not an actual NTU value.
- Settling time not independently measured per condition this session (unlike `ph-monitor`'s
  25–60s figures) — worth timing in a future session if `health`'s warm-up check needs it.
- The turbid sample's persistent high-frequency noise, not just its mean, may be a useful
  `health`/plausibility signal later — noted here, not acted on in Phase 1 (see
  `architecture.md`'s house rule: health and calibration stay independent signals; this is a
  design question for a future chunk, not something to merge in now).
