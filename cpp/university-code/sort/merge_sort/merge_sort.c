#include "merge_sort.h"

void swap(void* x, void* y, size_t size) {
    void* temp = malloc(size);
    if (temp == NULL) {
        fputs("malloc error\n", stdout);
        return ;
    }
    memcpy(temp,    x, size);
    memcpy(   x,    y, size);
    memcpy(   y, temp, size);
    free(temp);
}

void merge_sort(void* st, size_t st_len, size_t size, int compare(const void*, const void*)) {
    if (st_len <= 1)
        return ;
    int len_left   = st_len >> 1;
    int len_right  = st_len - len_left;
    void *st_left  = st;
    void *st_right = st + len_left * size;

    merge_sort(st_left,  len_left,  size, compare);
    merge_sort(st_right, len_right, size, compare);

    void* st_temp = malloc(st_len * size);
    if (st_temp == NULL) {
        fputs("malloc error\n", stdout);
        return ;
    }
    size_t i, j, k;
    for (i = j = k = 0; i < len_left && j < len_right; ++k) {
        if (compare(st_left + i * size, st_right + j * size) < 0) {
            memcpy(st_temp + k * size, st_left  + i * size, size);
            ++i;
        }
        else {
            memcpy(st_temp + k * size, st_right + j * size, size);
            ++j;
        }
    }
    if (i < len_left)
        memcpy(st_temp + k * size, st_left  + i * size, size * (len_left  - i));
    else
        memcpy(st_temp + k * size, st_right + j * size, size * (len_right - j));
    memcpy(st, st_temp, size * st_len);
    free(st_temp);
}

