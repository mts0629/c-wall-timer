#ifndef CWT_H
#define CWT_H

#include <time.h>

typedef struct cwt_timer {
    struct timespec start;
    struct timespec end;
} cwt_timer;

typedef struct cwt_lap_timer {
    int lap_count;
    struct timespec* lap;
} cwt_lap_timer;

#define CWT_LAP_TIMER_INIT(max_lap_count) { \
    .lap_count = 0, \
    .lap = (struct timespec[(max_lap_count) + 1]){ \
        { 0, 0 }, \
    } \
}

typedef enum cwt_scale {
    CWT_SECONDS,
    CWT_MILLISECONDS,
    CWT_MICROSECONDS,
    CWT_NANOSECONDS
} cwt_scale;

void cwt_start(cwt_timer* timer);

void cwt_stop(cwt_timer* timer);

double cwt_get_time(const cwt_timer* timer, const cwt_scale scale);

#define CWT_TIMER_BLOCK(time, scale, proc){ \
    cwt_timer t_; \
    cwt_start(&t_); \
    proc; \
    cwt_stop(&t_); \
    (time) = cwt_get_time(&t_, (scale)); \
}

void cwt_lap_start(cwt_lap_timer* timer);

void cwt_lap_record(cwt_lap_timer* timer);

double cwt_get_lap_time(cwt_lap_timer* timer, const int lap_index, const cwt_scale scale);

#endif // CWT_H
