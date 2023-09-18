#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

double algorithm(int n) {
    double res = 0;
    for (int i = 0; i <= n; i++) {
        res += pow(-1, i) / (2 * i + 1);
    }
    return res * 4;
};

int main() {
    system("sync");
    int n = 1500000000;
    int amount_of_tests = 5;
    struct timespec start, end;
    double res;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for (int i = 0; i < amount_of_tests; i++) {
        res = algorithm(n);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    printf("Time taken: %lf sec.\nres: %lf\n", (end.tv_sec-start.tv_sec + 0.000000001 * (end.tv_nsec-start.tv_nsec)) / amount_of_tests, res);
}