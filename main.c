#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void bubble_sort(int *array, int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
}

int main() {
    int n;
    srand(time(NULL));
    scanf("%d", &n);
    int *array = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        array[i] = rand() % INT_MAX;
    }

    bubble_sort(array, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
}
