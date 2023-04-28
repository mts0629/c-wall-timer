#ifndef TM_H
#define TM_H

#include <time.h>

struct timespec tm_get_diff(const struct timespec *start, const struct timespec *end) {
    time_t sec = end->tv_sec - start->tv_sec;
    long nsec = end->tv_nsec - start->tv_nsec;
    if (nsec < 0) {
        sec--;
        nsec += 1000000000;
    }
    return (struct timespec){ .tv_sec = sec, .tv_nsec = nsec };
}

typedef enum TimeScale {
    TIMESCALE_S,
    TIMESCALE_MS,
    TIMESCALE_US,
    TIMESCALE_NS
} TimeScale;

double tm_convert_timescale(const struct timespec *time, const TimeScale scale) {
    if (scale == TIMESCALE_S) {
        return time->tv_sec + time->tv_nsec / 1e9;
    } else if (scale == TIMESCALE_MS) {
        return time->tv_sec * 1e3 + time->tv_nsec / 1e6;
    } else if (scale == TIMESCALE_US) {
        return time->tv_sec * 1e6 + time->tv_nsec / 1e3;
    }
    // TIME_SCALE_NS
    return time->tv_sec * 1e9 + time->tv_nsec;
}

typedef struct tm_span {
    struct timespec start;
    struct timespec end;
} tm_span;

static inline void tm_start(tm_span *span) {
    timespec_get(&span->start, TIME_UTC);
}

static inline void tm_end(tm_span *span) {
    timespec_get(&span->end, TIME_UTC);
}

static inline struct timespec tm_get_span(const tm_span *span) {
    return tm_get_diff(&span->start, &span->end);
}

static inline double tm_get_span_timescale(const tm_span *span, const TimeScale scale) {
    struct timespec elapsed = tm_get_span(span);
    return tm_convert_timescale(&elapsed, scale);
}

#endif // TM_H
