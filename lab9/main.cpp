#include <cstdint>
#include <iostream>
#include <fstream>
#include <intrin.h>
using namespace std;

void fillArray(int *array, int amountBanks, int offsetEl, int blockElementsAmount) {
    for (int j = 0; j < amountBanks - 1; j++) {
        int *start = array + j * offsetEl;
        for (int i = 0; i < blockElementsAmount; i++) {
            start[i] = i + (offsetEl * (j + 1));
        }
    }
    for (int i = 0; i < blockElementsAmount; i++) {
        array[i + offsetEl * (amountBanks - 1)] = i + 1;
    }
    array[offsetEl * (amountBanks - 1) + blockElementsAmount - 1] = 0;
}

void arrayTraversal(int *array, int len, int amount) {
    for (int k = 0, i = 0; i < len * amount; i++) {
        k = array[k];
    }
}

typedef unsigned long long ull;

inline ull rdtsc() {
    unsigned int lo, hi;
    asm volatile ( "rdtsc\n" : "=a" (lo), "=d" (hi) );
    return ((ull)hi << 32) | lo;
}

int main() {
    int *array = new int[256 * 1024 * 32 * 16]; //32 блока по 16мб
    int size = 256 * 128; //128 кб
    int offset = 256 * 1024 * 16;//16мб
    ofstream file("data.txt");
    for (int n = 1; n < 33; n++) {
        fillArray(array, n, offset, size/n);
        ull t = LONG_LONG_MAX;
        for (int i = 0; i < 50; i++) {
            ull start = __rdtsc();
            arrayTraversal(array, size, 10000);
            ull end = __rdtsc();
            t = std::min(end - start, t);
        }
        file << n << ',' <<(t) / 10000 / size << endl;
    }
    delete array;
}