#include <stdio.h>
#include <unistd.h>

#include "cwt.h"

int main(void) {
    cwt_timer timer;

    cwt_start(&timer);

    // Some procesing
    sleep(1);

    cwt_stop(&timer);

    // Get elapsed time in millisecond
    printf("Elapsed: %f[ms]\n", cwt_get_time(&timer, CWT_MILLISECONDS));

    return 0;
}
