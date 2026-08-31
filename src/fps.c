#include "fps.h"
#include "sys.h"
#include "core.h"

int fps_iterate_counters(long long *start_tick, long long *end_tick) {
    *end_tick = get_time_mus();
    int fps = ceil_f((float)MUS_PER_SEC / (*end_tick - *start_tick));
    *start_tick = get_time_mus();
    return fps;
}