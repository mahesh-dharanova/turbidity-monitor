#include "health.h"

HealthMonitor::HealthMonitor() {}

HealthStatus HealthMonitor::check(float filteredVolts, uint32_t nowMs) {
    (void)filteredVolts;
    (void)nowMs;
    // TODO(Chunk 4): range / stuck-value / warm-up checks.
    return HealthStatus::WarmingUp;
}
