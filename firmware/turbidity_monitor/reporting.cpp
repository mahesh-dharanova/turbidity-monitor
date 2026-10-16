#include "reporting.h"

size_t formatReport(char *buf, size_t bufLen, uint32_t nowMs,
                     const SensorReading &reading, float filteredVolts,
                     HealthStatus health, const TurbidityEstimate &estimate) {
    (void)nowMs;
    (void)reading;
    (void)filteredVolts;
    (void)health;
    (void)estimate;
    // TODO(Chunk 6): JSON line builder, unit-tested on the host.
    if (bufLen == 0) return 0;
    buf[0] = '\0';
    return 0;
}
