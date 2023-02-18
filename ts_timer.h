/**
 * @file ts_timer.h
 * @brief Timer utilities for C11 timespec struct
*/
#ifndef TS_TIMER_H
#define TS_TIMER_H

#include <time.h>

/**
 * @brief Get a timespec value
 *
 * @param[out] ts timespec struct to store current time
*/
static inline void ts_get(struct timespec *ts) {
    timespec_get(ts, TIME_UTC);
}

/**
 * @brief Add 2 timespec values: sum = ts1 + ts2
 *
 * @param[out] sum Sum of 2 timespec values
 * @param[in] ts1 Addend 1
 * @param[in] ts2 Addend 2
*/
static inline void ts_add(struct timespec *sum, const struct timespec *ts1, const struct timespec *ts2) {
    sum->tv_sec  = ts1->tv_sec  + ts2->tv_sec;
    sum->tv_nsec = ts1->tv_nsec + ts2->tv_nsec;
    if (sum->tv_nsec > 1000000000) {
        sum->tv_sec++;
        sum->tv_nsec -= 1000000000;
    }
}

/**
 * @brief Subtract 2 timespec values: diff = ts1 - ts2
 *
 * @param[out] sum Difference of 2 timespec values
 * @param[in] ts1 Minuend
 * @param[in] ts2 Subtrahend
*/
static inline void ts_sub(struct timespec *diff, const struct timespec *ts1, const struct timespec *ts2) {
    diff->tv_sec  = ts1->tv_sec  - ts2->tv_sec;
    diff->tv_nsec = ts1->tv_nsec - ts2->tv_nsec;
    if (diff->tv_nsec < 0) {
        diff->tv_sec--;
        diff->tv_nsec += 1000000000;
    }
}

/**
 * @brief Accumulate timespec value: sum = sum + ts
 *
 * @param[out] sum Accumulated time
 * @param[in] ts Timespec value
*/
static inline void ts_accum(struct timespec *sum, const struct timespec *ts) {
    ts_add(sum, sum, ts);
}

/**
 * @brief Get a difference of 2 timespec values: diff = end - start
 *
 * @param[out] diff Difference of time from the start to the end
 * @param[in] start Start time
 * @param[in] end End time
*/
static inline void ts_get_diff(struct timespec *diff, const struct timespec *start, const struct timespec *end) {
    ts_sub(diff, end, start);
}

/**
 * @brief Get an average time of n from the total
 *
 * @param[out] avg Average time
 * @param[in] total Total time
 * @param[in] n Number of iterations
*/
static inline void ts_get_avg(struct timespec *avg, const struct timespec *total, const int n) {
    long nsec = total->tv_sec * 1000000000 + total->tv_nsec;
    nsec /= n;
    avg->tv_sec  = nsec / 1000000000;
    avg->tv_nsec = nsec - avg->tv_sec;
}

/**
 * @enum TimeScale
 * @brief Time scale for displaying timespec value
*/
enum TimeScale {
    TIME_SCALE_S,   //!< Second
    TIME_SCALE_MS,  //!< Millisecond
    TIME_SCALE_US,  //!< Microsecond
    TIME_SCALE_NS   //!< Nanosecond
};

/**
 * @brief Get a time from the timespec value with a specified time scale
 *
 * @param[in] ts timespec value
 * @param[in] scale Time scale
 * @return Time value with the specified time scale
*/
static inline double ts_get_time_as(const struct timespec *ts, const enum TimeScale scale) {
    if (scale == TIME_SCALE_S) {
        return ts->tv_sec + ts->tv_nsec * (1 / 1e9);
    } else if (scale == TIME_SCALE_MS) {
        return ts->tv_sec * 1e3 + ts->tv_nsec * (1 / 1e6);
    } else if (scale == TIME_SCALE_US) {
        return ts->tv_sec * 1e6 + ts->tv_nsec * (1 / 1e3);
    }
    // TIME_SCALE_NS
    return ts->tv_sec * 1e9 + ts->tv_nsec;
}

#endif // TS_TIMER_H
