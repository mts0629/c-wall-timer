/**
 * @file cwt.c
 * @brief Wall timer
*/
#include "cwt.h"

/**
 * @brief Calculate difference between two time points
 * @param[in] start Start time
 * @param[in] end End time
 * @return Difference time between the timepoints
*/
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

/**
 * @brief Convert time by specified timescale
 * @param[in] time Time
 * @param[in] scale Timescale
 * @return Time expression in specified timescale
*/
static inline double convert_by_timescale(const struct timespec* time, const cwt_scale scale) {
    if (scale == CWT_SECONDS) {
        return time->tv_sec + time->tv_nsec / 1e9;
    } else if (scale == CWT_MILLISECONDS) {
        return time->tv_sec * 1e3 + time->tv_nsec / 1e6;
    } else if (scale == CWT_MICROSECONDS) {
        return time->tv_sec * 1e6 + time->tv_nsec / 1e3;
    }
    // CWT_NANOSECONDS
    return time->tv_sec * 1e9 + time->tv_nsec;
}

double cwt_get_time(const cwt_timer* timer, const cwt_scale scale) {
    struct timespec elapsed = get_diff_timespec(&timer->start, &timer->end);
    return convert_by_timescale(&elapsed, scale);
}

void cwt_lap_start(cwt_lap_timer* timer) {
    timer->lap_count = 0;
    timespec_get(&timer->laps[timer->lap_count], TIME_UTC);
    timer->lap_count++;
}

void cwt_lap_record(cwt_lap_timer* timer) {
    timespec_get(&timer->laps[timer->lap_count], TIME_UTC);
    timer->lap_count++;
}

double cwt_get_lap_time(cwt_lap_timer* timer, const int lap_index, const cwt_scale scale) {
    struct timespec elapsed = get_diff_timespec(&timer->laps[lap_index], &timer->laps[lap_index + 1]);
    return convert_by_timescale(&elapsed, scale);
}
