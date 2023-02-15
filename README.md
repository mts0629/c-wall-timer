# ctimer

C言語での `struct timespec` による時間計測

## Sample

行列積の時間を測定

```
$ gcc -std=c11 sample.c -o sample
$ ./sample
512x512 matmul time
[ 1] 454.140600[ms]
[ 2] 445.178600[ms]
[ 3] 439.113400[ms]
[ 4] 449.210200[ms]
[ 5] 490.854900[ms]
[ 6] 466.022800[ms]
[ 7] 461.624600[ms]
[ 8] 451.594600[ms]
[ 9] 440.771800[ms]
[10] 471.220900[ms]
Total: 4569.732400[ms]
```
