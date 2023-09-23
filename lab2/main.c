#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

double algorithm(long n) {
    double res = 0;
    for (long i = 0; i <= n; i++) {
        res += pow(-1, i) / (2 * i + 1);
    }
    return res * 4;
};

int main(int argv, char *argc[]) {
    int a = system("sync");
    char *vIn = argc[1];
    long n = strtol(vIn,NULL,10);
    printf("%ld\n", n);
    struct timespec start, end;
    double res;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    res = algorithm(n);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    printf("Time taken: %lf sec.\nres: %lf\n", (end.tv_sec-start.tv_sec + 0.000000001 * (end.tv_nsec-start.tv_nsec)), res);
}