#include "heap_sort.h"

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

void max_heap(void* st, size_t st_len, size_t size,
              int compare(const void*, const void*), int k) {
    void* key = malloc(size);
    if (key == NULL) {
        fputs("malloc error\n", stdout);
        return;
    }
    memcpy(key, st + k * size, size);
    while (1) {
        size_t large = k * 2 + 1;
        if (large >= st_len) break;
        if (large + 1 < st_len &&
            compare(st + (large + 1) * size, st + large * size) > 0)
            ++large;
        if (compare(st + large * size, key) <= 0) break;
        memcpy(st + k * size, st + large * size, size);
        k = large;
    }
    memcpy(st + k * size, key, size);
    free(key);
}

void heap_sort(void* st, size_t st_len, size_t size,
               int compare(void const*, const void*)) {
    if (st_len <= 1) return;
    for (size_t k = st_len / 2 - 1; k != -1; --k)
        max_heap(st, st_len, size, compare, k);
    size_t left_len = st_len;
    while (--left_len > 0) {
        swap(st, st + left_len * size, size);
        max_heap(st, left_len, size, compare, 0);
    }
}
