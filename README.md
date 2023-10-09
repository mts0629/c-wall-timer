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

Measure a wall time of target processing between `cwt_start()` and `cwt_stop()` and print the elapsed time in millisecond.

```c
#include "cwt.h"

void sample(void) {
    cwt_timer timer;

    cwt_start(&timer);

    // Some processing
    int a = 0;
    for (int i = 0; i < 10000; i++) {
        a += i;
    }

    cwt_stop(&timer);

    // Get elapsed time in millisecond
    printf("Elapsed: %f[ms]\n", cwt_get_time(&timer, CWT_MILLISECONDS));
}
```

Sample programs in `sample` can be built in `build/release/sample` by `make sample`.
