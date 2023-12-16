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

int main() {
    long n = 150000000;
    struct timespec start, end;
    double res;
    res = algorithm(n);
    printf("%lf", res);
}