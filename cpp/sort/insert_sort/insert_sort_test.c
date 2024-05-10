#include "insert_sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int compare(const void* x, const void* y) { return *(int*)x - *(int*)y; }

int main(void) {
    size_t array_len = 10;
    size_t array_test_len = 10;
    int* array = (int*)malloc(array_len * sizeof(int));
    int* array_test = (int*)malloc(array_test_len * sizeof(int));
    if (array == NULL || array_test == NULL) {
        fputs("malloc error\n", stdout);
        return -1;
    }
    srand((unsigned)time(NULL));
    for (size_t i = 0; i < array_len; ++i)
        array_test[i] = array[i] = rand() % 100;
    insert_sort(array, array_len, sizeof(int), compare);
    qsort(array_test, array_test_len, sizeof(int), compare);
    if (memcmp(array, array_test, sizeof(int) * array_len) != 0)
        fputs("insert_sort error\n", stdout);
    else
        fputs("insert_sort right\n", stdout);
    return 0;
}
