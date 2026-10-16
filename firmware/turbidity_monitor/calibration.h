#pragma once

// Maps a filtered sensor voltage to an NTU estimate. Phase 1 has no reference
// data, so `calibrated` is always false — see architecture.md "UNCALIBRATED
// mode" and docs/CALIBRATION_PROCEDURE.md for Phase 2.
struct TurbidityEstimate {
    float ntu;
    bool  calibrated;
};

TurbidityEstimate calibrationEstimate(float filteredVolts);
