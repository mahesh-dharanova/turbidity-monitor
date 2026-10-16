# Calibration Procedure (Phase 2)

Not started — no turbidity reference solutions on hand yet (see `current_state.md`).

## When reference solutions are available

1. Record the filtered voltage at each known NTU reference point (at least a 0 NTU / clear
   water point and one or more known-turbidity points).
2. Fit a curve (linear first; only go more complex if the data clearly needs it) and put the
   constants in `firmware/turbidity_monitor/calibration.cpp`.
3. Update `tests/test_calibration.cpp` to assert against the fitted points, and flip
   `calibrated` to `true` only once the fit is verified against a held-out sample (not one
   of the fitting points).
4. Record the fit and verification result in `TEST_LOG.md`.
