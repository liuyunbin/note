
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    bzero(reinterpret_cast<void*>(&addr), sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(21);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
    connect(fd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr));

    char st[100] = "12345";
    for (int i = 0; i != 10; ++i) {
        write(fd, st, 5);
        //       read(fd, st, 100);
        //     putchar(ch);
    }

    return 0;
}
