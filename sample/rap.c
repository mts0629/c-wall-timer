#include <stdio.h>
#include <unistd.h>

#include "cwt.h"

int main(void) {
    cwt_rap_timer timer = CWT_RAP_TIMER_INIT(10);

    cwt_rap_start(&timer);

    for (int i = 0; i < 10; i++) {
        // Some procesing
        int a = 0;
        for (int j = 0; j < 1000; j++) {
            for (int k = 0; k < 10000; k++) {
                a += j;
            }
        }
        cwt_rap_record(&timer);
    }

    // Get elapsed time in millisecond
    for (int i = 0; i < 10; i++) {
        printf("[%d] Elapsed: %f[ms]\n", i, cwt_get_rap_time(&timer, i, CWT_MILLISECONDS));
    }

    return 0;
}
