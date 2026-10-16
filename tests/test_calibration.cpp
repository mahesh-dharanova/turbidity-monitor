#include "calibration.h"
#include <cassert>

int main() {
    const TurbidityEstimate estimate = calibrationEstimate(2.5f);
    // Chunk 1 stub always reports uncalibrated. Rewritten with real curve
    // data in Chunk 5, but the uncalibrated-by-default assertion should
    // stay until Phase 2 supplies reference points.
    assert(estimate.calibrated == false);
    return 0;
}
