#ifndef HEAP_SORT_H_
#define HEAP_SORT_H_ 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void heap_sort(void* st, size_t st_len, size_t size, int compare(void const*, const void*));

#endif

