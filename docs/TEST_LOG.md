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

## 2026-10-19 — Powdered-solution follow-up: settling behavior investigation

User flagged the original powdered-solution reading (~3.00–3.13V) as untrustworthy; this
session re-dipped the same board/wiring multiple times to find out why, same day as Chunk 2.

- **2nd dip**: user added more powder + extra water to the cup, then immediately re-dipped
  (solution still actively mixing). Reading: **~2.41–2.66V**, noisy (~±0.1–0.2V), never
  settled across two 15s captures. Lower than the 1st dip's ~3.00–3.13V — consistent
  direction (more powder added = more turbid = lower voltage), not an error.
- **3rd dip**: same (now-modified) solution, no further changes, just rinsed and re-dipped a
  few minutes later. Reading: **~3.12–3.24V**, drifting upward over ~30s of observation, back
  near the 1st dip's range — NOT matching the 2nd dip taken on the same solution minutes
  earlier.
- **Conclusion**: this is sample behavior, not sensor or wiring flakiness. An unstirred
  powder suspension settles under gravity within minutes; the water near the probe clears
  as particles sink, so voltage drifts back up toward the clear-liquid range the longer the
  solution sits unstirred after mixing. A "turbid solution" reading is only meaningful
  relative to how recently and how well it was agitated — it is not a stable sample like
  distilled or lemon water.
- **Active-stirring test**: with the probe held in place and the solution continuously
  stirred, reading dropped and stabilized at **~2.81–2.95V**, noise tightening to ~±0.07V —
  tighter than any of the unstirred turbid readings (~±0.1–0.2V) and far tighter than the
  transient spike during the stirring motion itself (~0.48V spread as particles were first
  resuspended). This is the cleanest, most repeatable "actively turbid" reading captured so
  far.

### Open items carried forward

- Any future turbidity reading protocol (calibration or normal operation) needs to specify
  agitation state — e.g. "read N seconds after stirring stops" or "read while continuously
  stirred" — since the same cup can read anywhere from ~2.4V to ~3.2V depending purely on
  settling time, with no change in total powder/water content.
- Settling rate (voltage recovering from ~2.5V toward ~3.2V over tens of seconds to minutes)
  was observed qualitatively, not timed precisely — worth a dedicated timed-settling session
  before Phase 2 calibration locks in a measurement protocol.
- The active-stirring noise floor (~±0.07V) vs. unstirred noise (~±0.1–0.2V) is itself
  informative: stirring produces a *more* consistent high-turbidity reading than letting the
  sample settle partially, since partial settling is itself a moving target.
