#ifndef CWT_H
#define CWT_H

#include <time.h>

typedef struct cwt_timer {
    struct timespec start;
    struct timespec end;
} cwt_timer;

typedef enum cwt_timescale {
    CWT_TIMESCALE_S,
    CWT_TIMESCALE_MS,
    CWT_TIMESCALE_US,
    CWT_TIMESCALE_NS
} cwt_timescale;

typedef struct cwt_timer cwt_timer;

void cwt_start(cwt_timer* timer);

void cwt_stop(cwt_timer* timer);

double cwt_get_time(const cwt_timer* timer, const cwt_timescale scale);

#endif // CWT_H
