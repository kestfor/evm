#include <iostream>
#include <random>
#include <fstream>
#include <string.h>
#include <intrin.h>
#include <limits.h>
using namespace std;


void directArrayFill(int *array, const int len) {
    for (int i = 0; i < len - 1; i++) {
        array[i] = i + 1;
    }
    array[len - 1] = 0;
}

void reverseArrayFill(int *array, const int len) {
    for (int i = len - 1; i > 0; i--) {
        array[i] = i - 1;
    }
    array[0] = len - 1;
}

void randomArrayFill(int *array, const int len) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,len - 1);
    memset(array, -1, sizeof(int) * len);
    int tmp;
    while ((tmp = dist(rng)) == 0) {
        continue;
    }
    array[0] = tmp;
    int next = tmp;
    for (int i = 0; i < len - 2; i++) {
        tmp = dist(rng);
        for (int j = 0; j < len; j++) {
            const int ind = (tmp + j) % len;
            if (array[ind] == -1 && next != ind) {
                array[next] = ind;
                tmp = ind;
                break;
            }
        }
        next = tmp;
    }
    array[next] = 0;
}

void arrayTraversal(const int *array, const int len, const int numberOfTraversals) {
    for (int k = 0, i = 0; i < len * numberOfTraversals; i++) {
        k = array[k];
    }
}

int main() {
    const int nMin = 256; // 1кб
    const int nMax = 256 * 1024 * 8; // 64мб
    ofstream file("data.txt");
    int *array = new int[nMax];
    const int k = 100;
    for (int n = nMin; n <= nMax; n += 256 * 256) { //шаг 256 кб
        uint64_t start = 0, end = 0;
        directArrayFill(array, n);
        uint64_t t = LONG_LONG_MAX;
        for (int j = 0; j < 1; j++) {
            arrayTraversal(array, n, 1); // прогрев кэша
            start = __rdtsc();
            arrayTraversal(array, n, k);
            end = __rdtsc();
            t = std::min(t, end - start);
        }
        file << "N = " << n << " прямой обход: " << (t) / (k * n) << " тактов\n";
        reverseArrayFill(array, n);
        t = LONG_LONG_MAX;
        for (int j = 0; j < 1; j++) {
            arrayTraversal(array, n, 1); // прогрев кэша
            start = __rdtsc();
            arrayTraversal(array, n, k);
            end = __rdtsc();
            t = std::min(t, end - start);
        }
        file << "N = " << n << " обратный обход: " << (t) / (k * n) << " тактов\n";
        randomArrayFill(array, n);
        t = LONG_LONG_MAX;
        for (int j = 0; j < 1; j++) {
            arrayTraversal(array, n, 1); // прогрев кэша
            start = __rdtsc();
            arrayTraversal(array, n, k);
            end = __rdtsc();
            t = std::min(t, end - start);
        }
        file << "N = " << n << " случайный обход: " << (t) / (k * n) << " тактов\n";
    }
    delete array;
}