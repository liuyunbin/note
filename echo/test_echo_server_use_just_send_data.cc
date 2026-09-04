
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("usage: %s ip port\n", argv[0]);
        return -1;
    }

    const char* server_ip = argv[1];
    uint16_t server_port = atoi(argv[2]);

    if (server_port <= 0) {
        printf("usage: %s ip port\n", argv[0]);
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

    printf("try connect %s:%d ...\n", server_ip, server_port);

    ret = connect(client_socket, (struct sockaddr*)(&server_addr),
                  sizeof server_addr);
    if (ret != 0) {
        perror("connect error");
        return -1;
    }
    printf("connect success");

    char buf[1024];
    int send_count = 0;
    for (;;) {
        ret = write(client_socket, buf, sizeof(buf));
        if (ret == -1) {
            perror("error");
            exit(-1);
        }
        send_count += ret;

        if (send_count < 1024)
            printf("send: %d\n", send_count);
        else if (send_count < 1024 * 1024)
            printf("send: %fk\n", send_count / 1024.0);
        else if (send_count < 1024 * 1024 * 1024)
            printf("send: %fM\n", send_count / 1024.0 / 1024.0);
    }
    return 0;
}
