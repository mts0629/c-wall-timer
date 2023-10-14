# libcwt (c-wall-timer)

Library to measure an "Wall time" (elapsed real time) in the program.

## Requirement

- gcc
    - Compiled under C11 for `struct timespec`.
- GNU Make
- GNU Binutils (GNU ar)

## Build

Build static library (`libcwt.a`):

```sh
# build/release/libcwt.a
$ make
# or
$ make static
```

Build shared library (`libcwt.so`):

```sh
# build/release/libcwt.so
$ make shared
```

Debug build (`libcwtd.***`):

```sh
# build/debug/libcwtd.a
$ make DEBUG=yes

# build/debug/libcwtd.so
$ make shared DEBUG=yes
```

Build sample programs:

```sh
# build/release/sample/*
$ make sample
```

## Usage

### Measure wall time

```c
// Create a timer object
cwt_timer timer;

// Start the timer
cwt_start(&timer);

// Some processing
// ...

// Stop the timer
cwt_stop(&timer);

// Get wall time between start and stop, in millisecond
printf("Elapsed: %f[ms]\n", cwt_get_time(&timer, CWT_MILLISECONDS);
```

Get wall time of target processing automatically with `CWT_TIMER_BLOCK()`.

```c
// Variable to store wall time
double time;

CWT_TIMER_BLOCK(
    time,
    CWT_MILLISECONDS, // Time scale
    {
        // Some processing
        // ...
    }
);

printf("Elapsed: %f[ms]\n", time);
```

The target processing is executed in a block scope (`{ ... }`), therefore variables used after the processing should be declared before this macro.

### Measure lap time

```c
// Create a lap timer object, with
cwt_lap_timer timer = CWT_LAP_TIMER_INIT(10);

// Start the timer
cwt_lap_start(&timer);

for (int i = 0; i < 10; i++) {
    // Some processing
    // ...

    // Record lap time
    cwt_lap_record(&timer);
}

for (int i = 0; i < 10; i++) {
    // Get i-th lap time
    printf("Elapsed: %f[ms]\n", cwt_get_lap_time(&timer, i, CWT_MILLISECONDS));
}
```

## License

MIT License
