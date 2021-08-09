#include "utils.h"
#include <time.h>

float getUnixTime() {
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0)
        return (float)(ts.tv_sec & 0xFFFFF) + (float)(ts.tv_nsec) / 1.0e9;
    else return 0.0;
}
