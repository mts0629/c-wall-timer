# timespec_utils

## Description

Time measurement on C language

## Requirement

- GCC
    - `-std=c11`: `struct timespec` is used.
- GNU Make

## TODO

- Prepare macro API to reduce penalty of function call.

## Sample

```c
#include "tm.h"

void sample(void) {
     tm_span span; 
     tm_start(&span); // Start 
  
     // Process to be measured
  
     tm_stop(&span); // Stop
  
     // Get elapsed time in milliseconds 
     printf("%f[ms]\n", tm_get_span_timescale(&span, TIMESCALE_MS));
}
```
