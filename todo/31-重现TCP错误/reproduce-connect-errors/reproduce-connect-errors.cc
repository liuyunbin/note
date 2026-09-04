#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>

void test_connect(const char* server_ip, uint16_t server_port) {
    int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    std::cout << "try connect " << server_ip << ":" << server_port << std::endl;
    int ret =
        connect(client_socket, reinterpret_cast<struct sockaddr*>(&server_addr),
                static_cast<socklen_t>(sizeof server_addr));
    if (ret == -1)
        perror("connect error");
    else
        std::cout << "connect success" << std::endl;
    close(client_socket);
}

int main(int argc, char* argv[]) {
    test_connect("127.0.0.1", 6666);

    test_connect("172.20.10.100", 6666);

    test_connect("192.168.1.100", 6666);

    return 0;
}
