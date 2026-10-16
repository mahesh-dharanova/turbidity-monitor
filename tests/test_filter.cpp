#include "filter.h"
#include <cassert>

int main() {
    TurbidityFilter filter;
    // Chunk 1 stub passes samples through unchanged. This assertion is
    // expected to be REWRITTEN in Chunk 3 once real smoothing lands.
    assert(filter.update(1.23f) == 1.23f);
    return 0;
}
