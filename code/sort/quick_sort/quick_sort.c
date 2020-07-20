#include "quick_sort.h"

void swap(void* x, void* y, size_t size) {
	void* temp=malloc(size);
	if (temp == NULL) {
		fputs("malloc error\n", stdout);
		return ;
	}
	memcpy(temp,    x, size);
	memcpy(   x,    y, size);
	memcpy(   y, temp, size);
	free(temp);
}

void quick_sort(void* st, size_t st_len, size_t size, int compare(const void*, const void*)) {
	while (st_len > 1) {
		size_t j = 0;
		for (size_t i = 1; i < st_len; ++i) {
			if (compare(st, st + i * size) > 0) {
				++j;
				swap(st + i * size, st + j * size, size);
			}
		}
		swap(st, st + j * size, size);
		quick_sort(st + (j + 1) * size, st_len - j - 1, size, compare);
		st_len = j;
	}
}

