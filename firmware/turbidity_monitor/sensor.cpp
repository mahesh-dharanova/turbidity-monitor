#include "sensor.h"
#include "config.h"
#include <Arduino.h>

namespace {
constexpr uint8_t SENSOR_ANALOG_PIN = A0;
}

void sensorInit() {
    analogReadResolution(ADC_RESOLUTION_BITS);
    pinMode(SENSOR_ANALOG_PIN, INPUT);
}

SensorReading sensorRead() {
    // TODO(Chunk 2): windowed average over SAMPLE_WINDOW_US, verified against
    // the physical KIE-TS-300B on hardware. Stub returns a zeroed reading so
    // the pipeline compiles end to end before the sensor is wired.
    return SensorReading{ 0, 0.0f };
}
