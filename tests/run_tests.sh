#!/usr/bin/env bash
# Host-side unit tests for the pure logic modules (filter, health,
# calibration, reporting). No framework dependency: plain g++ + <cassert>.
# sensor.cpp is excluded on purpose — it depends on Arduino.h and can only be
# verified on the physical board (see docs/TEST_LOG.md).
set -euo pipefail
cd "$(dirname "$0")"

FW_DIR="../firmware/turbidity_monitor"
BUILD_DIR=".build"
mkdir -p "$BUILD_DIR"

MODULES=(filter health calibration reporting)
status=0

for mod in "${MODULES[@]}"; do
    echo "== $mod =="
    g++ -std=c++17 -Wall -Wextra -I "$FW_DIR" \
        "test_${mod}.cpp" "$FW_DIR/${mod}.cpp" \
        -o "$BUILD_DIR/test_${mod}"
    if "$BUILD_DIR/test_${mod}"; then
        echo "PASS: $mod"
    else
        echo "FAIL: $mod"
        status=1
    fi
done

exit $status
