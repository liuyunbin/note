
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>

#include <pthread.h>

#include "noncopyable.h"

#include <stdio.h>

void f(int client) {
    char buf[1024];

    snprintf(buf, sizeof(buf), "HTTP/1.0\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "lyb");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "<HTML><HEAD><TITLE>I'am liuyunbin.\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "</TITLE></HEAD>\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "<BODY><P>Hello, everyone.\r\n");
    send(client, buf, strlen(buf), 0);
    snprintf(buf, sizeof(buf), "</BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}

int main() {
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    bzero(reinterpret_cast<void*>(&addr), sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(80);
    bind(listen_fd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr));
    listen(listen_fd, 1);
    for (;;) {
        int connected_fd = accept(listen_fd, NULL, NULL);
        f(connected_fd);
        close(connected_fd);
    }
    return 0;
}
