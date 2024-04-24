
#include <arpa/inet.h>
#include <fcntl.h>
#include <limits.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>

int send_data(int fd, int n) {
    struct timeval t1;
    gettimeofday(&t1, NULL);

    char buf[1024];

    for (int i = 0; i != n; ++i)         // 1024 MiB
        for (int j = 0; j != 1024; ++j)  // 1024 KiB
            if (sizeof(buf) != write(fd, buf, sizeof(buf))) {
                perror("");
                return -1;
            }

    struct timeval t2;
    gettimeofday(&t2, NULL);

    float send_sum = n;
    float send_tim =
        t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) / 1000000.0;

    std::cout << "总共发送：" << send_sum << " MiB " << std::endl;
    std::cout << "总共耗时：" << send_tim << " s   " << std::endl;
    std::cout << "平均速度：" << send_sum / send_tim << " MiB/s " << std::endl;

    return 0;
}

int main(int argc, char *argv[]) {
    const char *server_ip = "192.168.1.107";
    uint16_t server_port = 6666;

    const char *client_ip = "192.168.0.100";
    uint16_t client_port = 0;

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    struct sockaddr_in client_addr;
    bzero(&client_addr, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(client_port);
    inet_pton(AF_INET, client_ip, &client_addr.sin_addr);

    int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    std::cout << "client try to bind " << client_ip << ":" << client_port
              << std::endl;
    int ret =
        bind(client_socket, reinterpret_cast<struct sockaddr *>(&client_addr),
             static_cast<socklen_t>(sizeof client_addr));
    if (ret == -1)
        perror("bind error");
    else
        std::cout << "bind success" << std::endl;
    std::cout << "client try to connect " << server_ip << ":" << server_port
              << std::endl;
    ret = connect(client_socket,
                  reinterpret_cast<struct sockaddr *>(&server_addr),
                  static_cast<socklen_t>(sizeof server_addr));
    if (ret == -1)
        perror("connect error");
    else
        std::cout << "connect success" << std::endl;

    send_data(client_socket, 100 * 1024);

    return 0;
}
