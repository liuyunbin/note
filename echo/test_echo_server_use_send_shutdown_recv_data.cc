
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("usage: %s ip port send_count(Mib)\n", argv[0]);
        return -1;
    }

    const char* server_ip = argv[1];
    uint16_t server_port = atoi(argv[2]);
    int count = atoi(argv[3]);

    if (server_port <= 0 || count <= 0) {
        printf("usage: %s ip port send_count\n", argv[0]);
        return -1;
    }

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    int ret = inet_pton(AF_INET, server_ip, &server_addr.sin_addr);
    if (ret != 1) {
        perror("");
        return -1;
    }

    int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    printf("try connect %s:%d\n", server_ip, server_port);
    ret = connect(client_socket, (struct sockaddr*)(&server_addr),
                  sizeof server_addr);
    if (ret == -1) {
        perror("connect faile");
        return -1;
    }
    printf("connect success\n");

    char buf[1024];
    int send_count = 0;
    int read_count = 0;
    for (int i = 0; i != count; ++i)  // Mib
        for (int j = 0; j != 1024; ++j) {
            ssize_t ret = write(client_socket, buf, sizeof(buf));
            if (ret == -1) {
                perror("error");
                exit(-1);
            }
            send_count += ret;
        }

    printf("send: %d\n", send_count);
    printf("shutdown WRITE\n");
    shutdown(client_socket, SHUT_WR);
    for (;;) {
        ssize_t ret = read(client_socket, buf, sizeof(buf) - 1);
        if (ret == -1) {
            perror("error");
            exit(-1);
        }
        if (ret == 0) break;
        read_count += ret;
    }
    printf("read: %d\n\n", read_count);

    return 0;
}
