#include <math.h>
#include <stdio.h>

float algorithm(long n) {
    float res = 0;
    for (long i = 0; i <= n; i++) {
        float p = pow(-1, i);
        float tmp = 2 * i + 1;
        float d = p / tmp;
        res += d;
    }
    return res * 4;
};

int main() {
    long n = 10000;
    float res = algorithm(n);
    printf("%f", res);
}