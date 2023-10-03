#include <math.h>
#include <stdio.h>

float algorithm(int n) {
    float res = 0;
    int i;
    for (i = 0; i <= n; i++) {
        float p = pow(-1, i);
        int tmp = 2 * i + 1;
        float d = p / tmp;
        res += d;
    }
    return res * 4;
};

int main() {
    int n = 10000;
    float res = algorithm(n);
    printf("%f", res);
}
