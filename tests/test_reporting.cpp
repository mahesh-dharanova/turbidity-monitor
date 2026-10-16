#include "reporting.h"
#include <cassert>

int main() {
    char buf[128];
    const SensorReading reading{ 0, 0.0f };
    const TurbidityEstimate estimate{ 0.0f, false };
    const size_t written = formatReport(buf, sizeof(buf), 0, reading, 0.0f,
                                         HealthStatus::WarmingUp, estimate);
    // Chunk 1 stub writes nothing. Rewritten in Chunk 6.
    assert(written == 0);
    return 0;
}
