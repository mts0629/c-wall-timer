#ifndef CWT_H
#define CWT_H

#include <time.h>

typedef struct cwt_timer {
    struct timespec start;
    struct timespec end;
} cwt_timer;

typedef struct cwt_rap_timer {
    int rap_count;
    struct timespec* rap;
} cwt_rap_timer;

#define CWT_RAP_TIMER_INIT(n_rap) { \
    .rap_count = 0, \
    .rap = (struct timespec[(n_rap) + 1]){ \
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

#define CWT_TIMER_BLOCK(time, scale, ...) { \
    cwt_timer t; \
    cwt_start(&t); \
    __VA_ARGS__; \
    cwt_stop(&t); \
    (time) = cwt_get_time(&t, (scale)); \
}

void cwt_rap_start(cwt_rap_timer* timer);

void cwt_rap_record(cwt_rap_timer* timer);

double cwt_get_rap_time(cwt_rap_timer* timer, const int rap_index, const cwt_scale scale);

#endif // CWT_H
