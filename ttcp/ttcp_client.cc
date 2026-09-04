
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iomanip>
#include <iostream>

char buf[100 * 1024 * 1024];

void read_all(int sock, char *buf, int len) {
    while (len > 0) {
        int ret = read(sock, buf, len);
        if (ret <= 0) {
            perror("read");
            exit(-1);
        }
        buf += ret;
        len -= ret;
    }
}

void do_write_and_read_data(int sock, int number, int length) {
    int32_t net_number = htonl(number);
    if (write(sock, &net_number, 4) != 4) {
        perror("write");
        exit(-1);
    }

    int32_t net_length = htonl(length);
    if (write(sock, &net_length, 4) != 4) {
        perror("write");
        exit(-1);
    }

    for (int i = 0; i < number; ++i) {
        if (write(sock, &net_length, 4) != 4) {
            perror("write");
            exit(-1);
        }

        if (write(sock, buf, length) != length) {
            perror("");
            exit(-1);
        }

        read_all(sock, buf, 4);

        int32_t read_net_length = *(int32_t *)buf;

        if (read_net_length != net_length) {
            printf("格式错误\n");
            exit(-1);
        }
    }
}

void do_ttcp(const char *server_ip,
             uint16_t    server_port,
             int         number,
             int         length) {
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port   = htons(server_port);
    int ret = inet_pton(AF_INET, server_ip, &server_addr.sin_addr);
    if (ret == -1) {
        perror("IP 错误");
        exit(-1);
    }

    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1) {
        perror("socket");
        exit(-1);
    }

    printf("尝试连接 %s:%d...\n", server_ip, server_port);

    ret = connect(sock, (struct sockaddr *)(&server_addr), sizeof server_addr);
    if (ret == -1) {
        perror("连接失败");
        exit(-1);
    }

    printf("连接成功\n");

    struct timeval t1;
    gettimeofday(&t1, NULL);

    printf("发送数据中...\n");
    do_write_and_read_data(sock, number, length);

    struct timeval t2;
    gettimeofday(&t2, NULL);

    double send_sum = 1.0 * length * number;
    double send_tim =
        t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) / 1000000.0;

    std::cout << std::fixed;
    if (send_sum < 1024)
        std::cout << "总共发送：" << send_sum << " B 数据" << std::endl;
    else if (send_sum < 1024 * 1024)
        std::cout << "总共发送：" << send_sum / 1024 << " KiB 数据"
                  << std::endl;
    else if (send_sum < 1024 * 1024 * 1024)
        std::cout << "总共发送：" << send_sum / 1024 / 1024 << " MiB 数据"
                  << std::endl;
    else
        std::cout << "总共发送：" << send_sum / 1024 / 1024 / 1024
                  << " GiB 数据" << std::endl;

    std::cout << std::endl;
    std::cout << "总共发送    ：" << number << " 条数据" << std::endl;

    if (length < 1024)
        std::cout << "每条数据长为：" << length << " B" << std::endl;
    else if (length < 1024 * 1024)
        std::cout << "每条数据长为：" << length / 1024.0 << " KiB" << std::endl;
    else if (length < 1024 * 1024 * 1024)
        std::cout << "每条数据长为：" << length / 1024.0 / 1024 << " MiB"
                  << std::endl;
    else
        std::cout << "每条数据长为：" << length / 1024.0 / 1024 / 1024 << " GiB"
                  << std::endl;

    std::cout << std::endl;
    std::cout << "总共耗时：" << send_tim << " s   " << std::endl;

    double speed = send_sum / send_tim;

    if (speed < 1024)
        std::cout << "平均速度：" << speed << " B/s " << std::endl;
    else if (speed < 1024 * 1024)
        std::cout << "平均速度：" << speed / 1024 << " KiB/s " << std::endl;
    else if (speed < 1024 * 1024 * 1024)
        std::cout << "平均速度：" << speed / 1024 / 1024 << " MiB/s "
                  << std::endl;
    else
        std::cout << "平均速度：" << speed / 1024 / 1024 / 1024 << " GiB/s "
                  << std::endl;

    double speed_qps = number / send_tim;
    if (speed_qps < 1024)
        std::cout << "平均 QPS：" << speed_qps << " QPS " << std::endl;
    else if (speed_qps < 1024 * 1024)
        std::cout << "平均 QPS：" << speed_qps / 1024 << " KQPS " << std::endl;
    else if (speed_qps < 1024 * 1024 * 1024)
        std::cout << "平均 QPS：" << speed_qps / 1024 / 1024 << " MQPS "
                  << std::endl;
    else
        std::cout << "平均 QPS：" << speed_qps / 1024 / 1024 / 1024 << " GQPS "
                  << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("使用说明: %s IP地址 端口号 发送的数目 每次发送的大小\n",
               argv[0]);
        return -1;
    }

    const char *server_ip   = argv[1];
    uint16_t    server_port = atoi(argv[2]);
    int32_t     number      = atoi(argv[3]);
    int32_t     length      = atoi(argv[4]);

    if (server_port <= 0 || number <= 0 || length <= 0) {
        printf("使用说明: %s IP地址 端口号 发送的数目 每次发送的大小\n",
               argv[0]);
        return -1;
    }

    if (length > static_cast<int32_t>(sizeof(buf))) {
        printf("每次发送的数据太大，数据最大为：%lu MB\n",
               sizeof(buf) / 1024 / 1024);
        exit(-1);
    }

    do_ttcp(server_ip, server_port, number, length);

    return 0;
}
