#pragma once
#include <cstdint>

// Plausibility signal, independent of calibration — see AGENTS.md /
// architecture.md ("never merge health and calibration").
enum class HealthStatus {
    Ok,
    OutOfRange,
    Stuck,
    WarmingUp,
};

class HealthMonitor {
public:
    HealthMonitor();

    // Call once per report cycle with the current filtered voltage.
    HealthStatus check(float filteredVolts, uint32_t nowMs);
};
