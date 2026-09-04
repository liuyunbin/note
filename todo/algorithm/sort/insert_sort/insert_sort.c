#include "insert_sort.h"

void swap(void* x, void* y, size_t size) {
    void* temp = malloc(size);
    if (temp == NULL) {
        fputs("malloc error\n", stdout);
        return;
    }
    memcpy(temp, x, size);
    memcpy(x, y, size);
    memcpy(y, temp, size);
    free(temp);
}

void insert_sort(void* st, size_t st_len, size_t size,
                 int compare(const void*, const void*)) {
    if (st_len <= 1) return;
    void* temp = malloc(size);
    if (temp == NULL) {
        fputs("malloc error\n", stdout);
        return;
    }
    for (size_t i = 1; i < st_len; ++i) {
        memcpy(temp, st + i * size, size);
        size_t j = i;
        while (j > 0 && compare(st + (j - 1) * size, temp) > 0) {
            memcpy(st + j * size, st + (j - 1) * size, size);
            --j;
        }
        memcpy(st + j * size, temp, size);
    }
}
