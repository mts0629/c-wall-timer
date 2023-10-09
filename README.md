# c-wall-timer

## Description

"Wall time" (elapsed real time) measurement on C language

## Requirements

- GCC
    - `-std=c11`: `struct timespec` is used.
- GNU Make
- GNU Binutils (ar)

## Build

Build static library `libcwt.a` in `build/release` by `make` or `make static`.

```sh
$ make
gcc -Wall -Wextra -Wpedantic -std=c11 -I./src -O2 -c src/cwt.c -o build/release/src/cwt.o
ar rc build/release/libcwt.a build/release/src/cwt.o
```

Build shared library `libcwt.so` in `build/release` by `make shared`.

```sh
$ make shared
gcc -Wall -Wextra -Wpedantic -std=c11 -I./src -O2 -c src/cwt.c -o build/release/src/cwt.o
gcc -Wall -Wextra -Wpedantic -std=c11 -I./src -O2 -shared -fPIC build/release/src/cwt.o -o build/release/libcwt.so
```

A library with debug information (`libcwt.***`) can be built with option `DEBUG=yes` (e.g. `make shared DEBUG=yes`) in `build/debug`.

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

Sample programs in `sample` can be built in `build/release/sample` by `make sample`.
