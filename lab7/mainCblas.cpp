#include <chrono>
#include <iostream>
#include <string.h>
#include <limits.h>
#include <cblas.h>
using namespace std;

void mult(float *multiplicand, float *multiplier, float*product, const int n) {
    cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans, n, n, n, 1.0, multiplicand, n, multiplier, n, 0.0, product, n);
}

void div(float *source, float *res, const float k, const int n) {
    for (int i = 0; i < n; i++) {
        const int tmp = i * n;
        for (int j = 0; j < n; j++) {
            res[tmp + j] = source[tmp + j] / k;
        }
    }
}

float max1(float *matr, const int n) {
    float max1 = INT_MIN;
    for (int i = 0; i < n; i++) {
        float sum = 0;
        float *a = matr + i * n;
        for (int j = 0; j < n; j++) {
            sum += a[j];
        }
        max1 = std::max(sum, max1);
    }
    return max1;
}

float max2(float *matr, const int n) {
    float max2 = INT_MIN;
    for (int j = 0; j < n; j++) {
        float sum = 0;
        for (int i = 0; i < n; i++) {
            sum += matr[i*n + j];
        }
        max2 = std::max(sum, max2);
    }
    return max2;
}

void sub(float *minuend, float*subtrahend, float *difference, const int n) {
    for (int i = 0; i < n; i++) {
        const int tmp = i * n;
        for (int j = 0; j < n; j++) {
            difference[tmp + j] = minuend[tmp + j] - subtrahend[tmp + j];
        }
    }
}

void add(float *addendum1, float *addendum2, float *sum, const int n) {
    for (int i = 0; i < n; i++) {
        const int tmp = i * n;
        for (int j = 0; j < n; j++) {
            sum[tmp + j] = addendum1[tmp + j] + addendum2[tmp + j];
        }
    }
}

void transposition(float *source, float *res, const int n) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i * n + j] = source[j * n + i];
        }
    }
}

void identityMatrInit(float *matr, const int n) {
    memset(matr, 0, sizeof(float) * n * n);
    for (int i = 0; i < n; i++) {
        matr[i * n + i] = 1;
    }
}

void func(float *source, float *res, const int n, const int m) {
    float *b = new float[n * n];
    float *sourceTransp = new float[n * n];
    float *identityMatr = new float[n * n];
    float *r = new float[n * n];
    float *tmp = new float[n * n];
    transposition(source, sourceTransp, n);
    div(sourceTransp, b, max1(source, n) * max2(source, n), n);
    identityMatrInit(identityMatr, n);
    mult(b, source, tmp, n);
    sub(identityMatr, tmp, r, n);
    memset(res, 0, sizeof(float) * n * n);
    add(res, identityMatr, res, n);
    add(res, r, res, n);
    float *rPow = tmp;
    tmp = sourceTransp;
    memcpy(rPow, r, sizeof(float) * n * n);
    for (int i = 2; i < m; i++) {
        mult(r, rPow, tmp, n);
        memcpy(rPow, tmp, sizeof(float) * n * n);
        add(res, rPow, res, n);
    }
    mult(res, b, tmp, n);
    memcpy(res, tmp, sizeof(float) * n * n);
    delete r;
    delete rPow;
    delete b;
    delete tmp;
    delete identityMatr;
}

int main() {
    constexpr int n = 2048;
    float *a = new float[n * n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                a[i * n + j] = 2;
            } else {
                a[i * n + j] = 1;
            }
        }
    }
    float *aInverse = new float[n * n];
    timespec start_process{};
    timespec end_process{};
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_process);
    std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
    func();
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_process);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "\nTime difference = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() /  ((end_process.tv_sec - start_process.tv_sec) +  1.0e-9 * (end_process.tv_nsec - start_process.tv_nsec))<< std::endl;
    delete a;
    delete aInverse;
}