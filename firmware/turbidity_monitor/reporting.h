#pragma once
#include <cstddef>
#include <cstdint>
#include "sensor.h"
#include "health.h"
#include "calibration.h"

// Formats one report line into buf (JSON, no trailing newline). Returns the
// number of characters written, or 0 if it didn't fit / isn't implemented yet.
size_t formatReport(char *buf, size_t bufLen, uint32_t nowMs,
                     const SensorReading &reading, float filteredVolts,
                     HealthStatus health, const TurbidityEstimate &estimate);
