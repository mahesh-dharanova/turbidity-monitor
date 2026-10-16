#!/usr/bin/env bash
# Compiles the firmware against the Arduino Uno R4 WiFi. No upload.
set -euo pipefail
cd "$(dirname "$0")/.."

arduino-cli compile --fqbn arduino:renesas_uno:unor4wifi firmware/turbidity_monitor
