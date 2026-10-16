/*
  turbidity-monitor — Phase 1 sensor node
  Board:  Arduino Uno R4 WiFi
  Sensor: KIE-TS-300B turbidity module

  This file is an orchestrator only: setup()/loop() wire the modules together.
  All logic lives in sensor.*, filter.*, health.*, calibration.*, reporting.*
  (see architecture.md). Module wiring lands in Chunk 7 (see plan.md) — this
  is the Chunk 1 scaffold, so setup()/loop() are intentionally minimal.
*/

#include <Arduino.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
}
