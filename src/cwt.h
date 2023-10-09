#ifndef CWT_H
#define CWT_H

#include <time.h>

typedef struct cwt_timer {
    struct timespec start;
    struct timespec end;
} cwt_timer;

typedef enum cwt_scale {
    CWT_SECONDS,
    CWT_MILLISECONDS,
    CWT_MICROSECONDS,
    CWT_NANOSECONDS
} cwt_scale;

void cwt_start(cwt_timer* timer);

void cwt_stop(cwt_timer* timer);

double cwt_get_time(const cwt_timer* timer, const cwt_scale scale);

#endif // CWT_H
