#ifndef QUICK_SORT_H_
#define QUICK_SORT_H_ 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quick_sort(void* st, size_t st_len, size_t size, int compare(const void*, const void*));

#endif
