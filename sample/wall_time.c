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

    // Get elapsed time of processing in specified block
    double ms;
    CWT_TIMER_BLOCK(ms, CWT_MILLISECONDS,
        {
            int a = 0;
            for (int i = 0; i < 1000; i++) {
                for (int j = 0; j < 10000; j++) {
                    a += j;
                }
            }
        }
    );
    printf("Elapsed: %f[ms]\n", ms);

    return 0;
}
