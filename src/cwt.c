#include "cwt.h"

static inline struct timespec get_diff_timespec(const struct timespec* start, const struct timespec* end) {
    time_t sec = end->tv_sec - start->tv_sec;
    long nsec = end->tv_nsec - start->tv_nsec;
    if (nsec < 0) {
        sec--;
        nsec += 1000000000;
    }
    return (struct timespec){ .tv_sec = sec, .tv_nsec = nsec };
}

void cwt_start(cwt_timer* timer) {
    timespec_get(&timer->start, TIME_UTC);
}

void cwt_stop(cwt_timer* timer) {
    timespec_get(&timer->end, TIME_UTC);
}

static inline double convert_timescale(const struct timespec* time, const cwt_timescale scale) {
    if (scale == CWT_TIMESCALE_S) {
        return time->tv_sec + time->tv_nsec / 1e9;
    } else if (scale == CWT_TIMESCALE_MS) {
        return time->tv_sec * 1e3 + time->tv_nsec / 1e6;
    } else if (scale == CWT_TIMESCALE_US) {
        return time->tv_sec * 1e6 + time->tv_nsec / 1e3;
    }
    // CWT_TIME_SCALE_NS
    return time->tv_sec * 1e9 + time->tv_nsec;
}

double cwt_get_time(const cwt_timer* timer, const cwt_timescale scale) {
    struct timespec elapsed = get_diff_timespec(&timer->start, &timer->end);
    return convert_timescale(&elapsed, scale);
}
