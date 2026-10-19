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
    uint64_t sum = 0;
    uint32_t n = 0;
    const uint32_t start = micros();
    while ((uint32_t)(micros() - start) < SAMPLE_WINDOW_US) {
        sum += analogRead(SENSOR_ANALOG_PIN);
        n++;
    }
    const uint32_t maxCount = (1UL << ADC_RESOLUTION_BITS) - 1;
    const uint32_t rawAvg = (n > 0) ? (uint32_t)(sum / n) : 0;
    const float volts = (float)rawAvg * ADC_VREF_VOLTS / (float)maxCount;
    return SensorReading{ rawAvg, volts };
}
