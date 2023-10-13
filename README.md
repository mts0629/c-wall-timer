# c-wall-timer

## Description

"Wall time" (elapsed real time) measurement on C language

## Requirements

- gcc
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

## Usage

### Measure elapsed time

Start/stop the timer by `cwt_start()`/`cwt_stop()` and get elapsed time by `cwt_get_time()` in specified timescale.
- 4 types of timescales: seconds, milliseconds, microseconds, nanoseconds
- `cwt_get_time()` needs calculation, therefore it's better to call it after the processing.

```c
cwt_timer timer;

cwt_start(&timer);

// Some processing
// ...

cwt_stop(&timer);

printf("Elapsed: %f[ms]\n", cwt_get_time(&timer, CWT_MILLISECONDS);
```

Elapsed time of specified processing can be get automatically by `CWT_TIMER_BLOCK()`.
- Tokens decleared in the processing cannot be referred later because of using block scope.

```c
double time;

CWT_TIMER_BLOCK(
    time,
    CWT_MILLISECONDS,
    {
        // Some processing
        // ...
    }
);

printf("Elapsed: %f[ms]\n", time);
```

### Measure lap time

Initialize a lap timer object by `CWT_LAP_TIMER_INIT` with the max count of the laps.

Start measurement of lap time by `cwt_lap_start()`, and measure lap time by `cwt_lap_record()`.

Elapsed time of the specified lap can be get by `cwt_get_lap_time()`.

```c
cwt_lap_timer timer = CWT_LAP_TIMER_INIT(10);

cwt_lap_start(&timer);

for (int i = 0; i < 10; i++) {
    // Some processing
    // ...
    cwt_lap_record(&timer);
}

for (int i = 0; i < 10; i++) {
    printf("Elapsed: %f[ms]\n", cwt_get_lap_time(&timer, i, CWT_MILLISECONDS));
}
```

Sample programs in `sample` can be built in `build/release/sample` by `make sample`.
