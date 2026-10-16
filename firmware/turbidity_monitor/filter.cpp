#include "filter.h"

TurbidityFilter::TurbidityFilter() {}

float TurbidityFilter::update(float rawSample) {
    // TODO(Chunk 3): median-of-FILTER_WINDOW_SIZE + exponential smoothing.
    // Stub passes the raw sample through unchanged.
    return rawSample;
}
