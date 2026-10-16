#include "health.h"
#include <cassert>

int main() {
    HealthMonitor monitor;
    // Chunk 1 stub always reports WarmingUp. Rewritten in Chunk 4.
    assert(monitor.check(2.5f, 0) == HealthStatus::WarmingUp);
    return 0;
}
