/**
 * @file cwt.h
 * @brief Wall timer
*/
#ifndef CWT_H
#define CWT_H

#include <time.h>

/**
 * @brief Timer object
*/
typedef struct cwt_timer {
    struct timespec start; //!< Start time
    struct timespec end; //!< End time
} cwt_timer;

/**
 * @brief Lap timer object
*/
typedef struct cwt_lap_timer {
    int lap_count; //!< Current lap count
    struct timespec* laps; //!< Lap times
} cwt_lap_timer;

/**
 * @brief Initialize a lap timer with specified max lap count
*/
#define CWT_LAP_TIMER_INIT(max_lap_count) { \
    .lap_count = 0, \
    .laps = (struct timespec[(max_lap_count) + 1]){ \
        { 0, 0 }, \
    } \
}

/**
 * @brief Timescale for the elapsed time
*/
typedef enum cwt_scale {
    CWT_SECONDS, //!< Seconds
    CWT_MILLISECONDS, //!< Milliseconds
    CWT_MICROSECONDS, //!< Microseconds
    CWT_NANOSECONDS //!< Nanoseconds
} cwt_scale;

/**
 * @brief Start the timer
 * @param[out] timer Timer object
*/
void cwt_start(cwt_timer* timer);

/**
 * @brief Stop the timer
 * @param[out] timer Timer object
*/
void cwt_stop(cwt_timer* timer);

/**
 * @brief Get elapsed time
 * @param[in] timer Timer object
 * @param[in] scale Timescale
 * @return Elapsed time in specified timescale
*/
double cwt_get_time(const cwt_timer* timer, const cwt_scale scale);

/**
 * @brief Get elapsed time for processing of specified codes
 * @note Multi-line codes must be surrounded by curly blace `{}`
*/
#define CWT_TIMER_BLOCK(time, scale, codes){ \
    cwt_timer t_; \
    cwt_start(&t_); \
    codes; \
    cwt_stop(&t_); \
    (time) = cwt_get_time(&t_, (scale)); \
}

/**
 * @brief Start the lap timer
 * @param[out] timer Lap timer object
*/
void cwt_lap_start(cwt_lap_timer* timer);

/**
 * @brief Record the current lap time
 * @param[out] timer Lap timer object
 * @note The number of recording be within the max lap count of the timer object
*/
void cwt_lap_record(cwt_lap_timer* timer);

/**
 * @brief Get elapsed time of the specified lap
 * @param[in] timer Timer object
 * @param[in] lap_index Lap index
 * @param[in] scale Timescale
 * @return Elapsed time of the lap in specified timescale
*/
double cwt_get_lap_time(cwt_lap_timer* timer, const int lap_index, const cwt_scale scale);

#endif // CWT_H
