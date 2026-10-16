#pragma once
#include <cstdint>

// The only module allowed to touch Arduino.h / analogRead() — see AGENTS.md.

struct SensorReading {
    uint32_t rawAdc;
    float    volts;
};

// Configures the analog pin and ADC resolution. Call once from setup().
void sensorInit();

// Averages SAMPLE_WINDOW_US worth of analog reads. Implemented in Chunk 2.
SensorReading sensorRead();
