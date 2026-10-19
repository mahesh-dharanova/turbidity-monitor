/*
  turbidity-monitor — Phase 1 sensor node
  Board:  Arduino Uno R4 WiFi
  Sensor: KIE-TS-300B turbidity module

  This file is an orchestrator only: setup()/loop() wire the modules together.
  All logic lives in sensor.*, filter.*, health.*, calibration.*, reporting.*
  (see architecture.md). Full pipeline wiring lands in Chunk 7 (see plan.md).

  Chunk 2 (current): only sensor.* is real. loop() prints its raw output
  directly so it can be verified on hardware — this direct print is replaced
  by the filter -> health -> calibration -> reporting chain in Chunk 7.
*/

#include <Arduino.h>
#include "config.h"
#include "sensor.h"

void setup() {
  Serial.begin(115200);
  sensorInit();
}

void loop() {
  static uint32_t nextReportMs = 0;
  const uint32_t now = millis();
  if (now < nextReportMs) return;
  nextReportMs = now + REPORT_INTERVAL_MS;

  const SensorReading reading = sensorRead();
  Serial.print(F("{\"ms\":"));
  Serial.print(now);
  Serial.print(F(",\"raw\":"));
  Serial.print(reading.rawAdc);
  Serial.print(F(",\"v\":"));
  Serial.print(reading.volts, 3);
  Serial.println(F("}"));
}
