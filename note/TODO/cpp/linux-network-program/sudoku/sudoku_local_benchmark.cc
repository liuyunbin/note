
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "sudoku.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("usage: %s test_count\n", argv[0]);
        return -1;
    }

    int test_count = atoi(argv[1]);

    if (test_count <= 0) {
        printf("usage: %s test_count\n", argv[0]);
        return -1;
    }

    struct timeval t1;
    gettimeofday(&t1, NULL);

    char buf[81];
    for (int i = 0; i != test_count; ++i) {
        for (int j = 0; j != 81; ++j) buf[j] = test_data[j];
        solve_sudoku(buf);
    }

    struct timeval t2;
    gettimeofday(&t2, NULL);

    double test_tm =
        t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) / 1000000.0;

    printf("总共测试 %d 个数独\n", test_count);
    printf("总共耗时 %f 秒\n", test_tm);
    printf("平均每秒处理 %d 个数独\n", (int)(test_count / test_tm));
    printf("平均每个数独需要 %f 微秒\n", test_tm * 1000 * 1000 / test_count);

    return 0;
}
