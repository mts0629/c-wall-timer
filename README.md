# c-wall-timer

## Description

"Wall time" (elapsed real time) measurement on C language

## Requirements

- GCC
    - `-std=c11`: `struct timespec` is used.
- GNU Make

## Build

Library `libcwt.a` is built in `build/release/` by `make`.

```sh
$ make
gcc -Wall -Wextra -Wpedantic -std=c11 -I./src -O2 -c src/cwt.c -o build/release/src/cwt.o
ar rc build/release/libcwt.a build/release/src/cwt.o
```

Debug build: `libcwtd.a` is built in `./build/debug` by `make DEBUG=yes`.

## Sample

Measure wall time of target processing and print it by ms order.

```c
#include "cwt.h"

void sample(void) {
    cwt_timer timer;

    // Start
    cwt_start(&timer);

    // Some procesing
    sleep(1);

    // Stop
    cwt_stop(&timer);

    // Get elapsed time in millisecond
    printf("%f[ms]\n", cwt_get_time(&span, CWT_TIMESCALE_MS));
}
```

Sample programs in `sample/` can be built into `build/sample` by `make sample`.
