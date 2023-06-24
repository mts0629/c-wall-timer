#include <stdio.h>
#include <unistd.h>

#include "cwt.h"

int main(void) {
    cwt_timer timer;

    // Start
    cwt_start(&timer);

    // Some procesing
    sleep(1);

    // Stop
    cwt_stop(&timer);

    // Get elapsed time in millisecond
    printf("%f[ms]\n", cwt_get_time(&timer, CWT_TIMESCALE_MS));

    return 0;
}
