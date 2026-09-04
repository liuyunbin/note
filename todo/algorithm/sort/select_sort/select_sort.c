#include "select_sort.h"

void swap(void* x, void* y, size_t size) {
    void* temp = malloc(size);
    if (temp == NULL) {
        fputs("malloc error.\n", stdout);
        return;
    }
    memcpy(temp, x, size);
    memcpy(x, y, size);
    memcpy(y, temp, size);
    free(temp);
}

void select_sort(void* st, size_t st_len, size_t size,
                 int compare(const void*, const void*)) {
    if (st_len <= 1) return;
    for (size_t i = 0; i < st_len; ++i) {
        size_t k = i;
        for (size_t j = i + 1; j < st_len; ++j)
            if (compare(st + k * size, st + j * size) > 0) k = j;
        if (i != k) swap(st + k * size, st + i * size, size);
    }
}
