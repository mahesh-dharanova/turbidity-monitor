#!/usr/bin/env bash
# Uploads the firmware to a connected Arduino Uno R4 WiFi.
# Usage: scripts/upload.sh <port>   (run 'arduino-cli board list' to find it)
set -euo pipefail
cd "$(dirname "$0")/.."

PORT="${1:-}"
if [ -z "$PORT" ]; then
    echo "Usage: $0 <port>  (e.g. /dev/ttyACM0 — run 'arduino-cli board list' to find it)" >&2
    exit 1
fi

arduino-cli upload -p "$PORT" --fqbn arduino:renesas_uno:unor4wifi --verify firmware/turbidity_monitor
