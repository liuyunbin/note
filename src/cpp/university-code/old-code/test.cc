
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>

int main() {
    struct timeval t1;
    gettimeofday(&t1, NULL);

    const char *file_name = "test";

    int N = 1024;
    int fd = open(file_name, O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("");
        return -1;
    }

    char buf[1024];

    for (int i = 0; i != N; ++i)         // 1024 MiB
        for (int j = 0; j != 1024; ++j)  // 1024 KiB
            if (sizeof(buf) != write(fd, buf, sizeof(buf))) {
                perror("");
                return -1;
            }

    close(fd);

    struct timeval t2;
    gettimeofday(&t2, NULL);

    float send_sum = N;
    float send_tim =
        t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) / 1000000.0;

    std::cout << "总共发送：" << send_sum << " MiB " << std::endl;
    std::cout << "总共耗时：" << send_tim << " s   " << std::endl;
    std::cout << "平均速度：" << send_sum / send_tim << " MiB/s " << std::endl;

    return 0;
}
