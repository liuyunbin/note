#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>

void signal_handle(int sig) { std::cout << "catch SIGPIPE" << std::endl; }

void set_signal() { signal(SIGPIPE, signal_handle); }

int main(int argc, char* argv[]) {
    set_signal();

    const char* server_ip = "127.0.0.1";
    uint16_t server_port = 6666;

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    int listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int opt = 1;
    setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    std::cout << "server try to bind " << server_ip << ":" << server_port
              << std::endl;
    int ret =
        bind(listen_socket, reinterpret_cast<struct sockaddr*>(&server_addr),
             static_cast<socklen_t>(sizeof server_addr));
    if (ret == -1)
        perror("bind error");
    else
        std::cout << "bind success" << std::endl;
    listen(listen_socket, 5);
    std::cout << "server listen..." << std::endl;

    int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    std::cout << "client try to connect " << server_ip << ":" << server_port
              << std::endl;
    ret =
        connect(client_socket, reinterpret_cast<struct sockaddr*>(&server_addr),
                static_cast<socklen_t>(sizeof server_addr));
    if (ret == -1)
        perror("connect error");
    else
        std::cout << "connect success" << std::endl;

    int con_socket = accept(listen_socket, NULL, NULL);
    std::cout << "new client come" << std::endl;
    close(con_socket);
    std::cout << "close server con_socket" << std::endl;
    close(listen_socket);
    std::cout << "close server listen socket" << std::endl;

    char ch;
    std::cout << "client: try read..." << std::endl;
    if (read(client_socket, &ch, sizeof(ch)) == 0)
        std::cout << "client: read EOF" << std::endl;
    std::cout << "client: try read again..." << std::endl;
    if (read(client_socket, &ch, sizeof(ch)) == 0)
        std::cout << "client: read EOF" << std::endl;
    for (;;) {
        std::cout << "client: try write..." << std::endl;
        if (write(client_socket, &ch, sizeof(ch)) == -1) {
            perror("client: write error");
            break;
        }
    }

    close(client_socket);
    std::cout << "close client listen socket" << std::endl;

    return 0;
}
