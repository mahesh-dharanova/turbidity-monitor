#include "calibration.h"

TurbidityEstimate calibrationEstimate(float filteredVolts) {
    (void)filteredVolts;
    // TODO(Chunk 5): vendor-typical approximate curve, always flagged
    // uncalibrated until Phase 2 supplies real reference points.
    return TurbidityEstimate{ 0.0f, false };
}
