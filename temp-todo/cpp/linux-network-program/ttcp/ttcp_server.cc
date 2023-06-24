
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("使用说明: %s 端口号\n", argv[0]);
        return -1;
    }

    uint16_t server_port = atoi(argv[1]);

    if (server_port <= 0) {
        printf("使用说明: %s 端口号\n", argv[0]);
        return -1;
    }

    printf("服务器端口号为 %d\n", server_port);

    const char *server_ip = "0.0.0.0";

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    int ret = inet_pton(AF_INET, server_ip, &server_addr.sin_addr);
    if (ret == -1) {
        perror("inet_pton");
        exit(-1);
    }

    int listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listen_socket == -1) {
        perror("socket");
        exit(-1);
    }

    int opt = 1;
    setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    setsockopt(listen_socket, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));

    ret = bind(listen_socket, (struct sockaddr *)(&server_addr),
               sizeof server_addr);
    if (ret == -1) {
        perror("bind");
        exit(-1);
    }

    ret = listen(listen_socket, 5);
    if (ret == -1) {
        perror("listen");
        exit(-1);
    }

    printf("ttcp 服务器启动\n");

    for (;;) {
        printf("等待客户中...\n");
        int con_socket = accept(listen_socket, NULL, NULL);
        if (con_socket == -1) {
            perror("accept");
            exit(-1);
        }

        printf("新客户来到\n");

        read_all(con_socket, buf, 8);

        int32_t net_number = *(int32_t *)buf;
        int32_t host_number = ntohl(net_number);
        int32_t net_length = *(int32_t *)(buf + 4);
        int32_t host_length = ntohl(net_length);

        if (host_length > static_cast<int32_t>(sizeof(buf))) {
            printf("每次发送的数据太大，数据最大为：%lu MB\n",
                   sizeof(buf) / 1024 / 1024);
            exit(-1);
        }

        printf("客户端将发送 %d 个数据包, 每个数据包的数据长度为 %d\n",
               host_number, host_length);
        for (int i = 0; i < host_number; ++i) {
            read_all(con_socket, buf, 4);

            int32_t read_net_length = *(int32_t *)buf;

            if (read_net_length != net_length) {
                printf("格式错误\n");
                exit(-1);
            }

            read_all(con_socket, buf, host_length);

            if (write(con_socket, &net_length, 4) != 4) {
                perror("");
                exit(-1);
            }
        }
        close(con_socket);
        printf("关闭客户端\n\n");
    }
    printf("服务器退出\n");

    return 0;
}
