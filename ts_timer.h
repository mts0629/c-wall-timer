/**
 * ts_timer.h
 *
 * Timer operation with timespec struct
*/
#ifndef TS_TIMER_H
#define TS_TIMER_H

#include <time.h>

// Get a timespec value
static inline void ts_get(struct timespec *time) {
    timespec_get(time, TIME_UTC);
}

// Add 2 timespec values: sum = t1 - t2
static inline void ts_add(struct timespec *sum, const struct timespec *t1, const struct timespec *t2) {
    sum->tv_sec  = t1->tv_sec  + t2->tv_sec;
    sum->tv_nsec = t1->tv_nsec + t2->tv_nsec;
    if (sum->tv_nsec > 1e9) {
        sum->tv_sec++;
        sum->tv_nsec -= 1e9;
    }
}

// Subtract 2 timespec values: diff = t1 - t2
static inline void ts_sub(struct timespec *diff, const struct timespec *t1, const struct timespec *t2) {
    diff->tv_sec  = t1->tv_sec  - t2->tv_sec;
    diff->tv_nsec = t1->tv_nsec - t2->tv_nsec;
    if (diff->tv_nsec < 0) {
        diff->tv_sec--;
        diff->tv_nsec += 1e9;
    }
}

// Divide timespec value: div = ts / n
static inline void ts_div(struct timespec *div, const struct timespec *ts, const int n) {
    long nsec = ts->tv_sec * 1e9 + ts->tv_nsec;
    nsec /= n;
    div->tv_sec  = nsec / 1e9;
    div->tv_nsec = nsec - div->tv_sec;
}

// Time scale
enum TimeScale {
    TIME_SCALE_S,   // Second
    TIME_SCALE_MS,  // Milli second
    TIME_SCALE_US,  // Micro second
    TIME_SCALE_NS   // Nano second
};

// Get time from the timespec value with specified time scale
static inline double ts_get_time_as(const struct timespec *time, const enum TimeScale scale) {
    if (scale == TIME_SCALE_S) {
        return time->tv_sec + time->tv_nsec / 1e9;
    } else if (scale == TIME_SCALE_MS) {
        return time->tv_sec * 1e3 + time->tv_nsec / 1e6;
    } else if (scale == TIME_SCALE_US) {
        return time->tv_sec * 1e6 + time->tv_nsec / 1e3;
    }
    // TIME_SCALE_NS
    return time->tv_sec * 1e9 + time->tv_nsec;
}

// Accumulate timespec value: sum = sum + time
static inline void ts_accumulate(struct timespec *sum, const struct timespec *time) {
    ts_add(sum, sum, time);
}

// Get difference of 2 timespec values: diff = end - start
static inline void ts_get_diff(struct timespec *diff, const struct timespec *start, const struct timespec *end) {
    ts_sub(diff, end, start);
}

#endif // TS_TIMER_H
