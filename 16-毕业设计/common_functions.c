#include "common_functions.h"

int Accept(int connection, void* cliaddr, socklen_t* addrlen) {
    int n;
    if ((n = accept(connection, (struct sockaddr*)cliaddr, addrlen)) == -1)
        error_exit(-1, "accpt error");
    return n;
}

int Bind(int connection, const struct sockaddr* servaddr, socklen_t addrlen) {
    if (bind(connection, servaddr, addrlen) == -1) error_exit(-1, "bind error");
    return 0;
}

char* Fgets(char* st, int n, FILE* p) {
    if (fgets(st, n, p) == NULL) error_exit(-1, "fgets error");
    if (st[n = (strlen(st) - 1)] == '\n') st[n] = '\0';
    return st;
}

int Connect(int connection, const struct sockaddr* servaddr,
            socklen_t addrlen) {
    if (connect(connection, servaddr, addrlen) == -1)
        error_exit(-1, "connect error");
    return 0;
}

void error_exit(int connection, const char* st) {
    if (connection < 0)
        perror(st);
    else
        Write(connection, st);
    exit(1);
}

int Inet_pton(int family, const char* str, void* addr) {
    if (inet_pton(family, str, addr) <= 0) error_exit(-1, "error argc");
    return 1;
}

int Listen(int connection, int backlog) {
    if (listen(connection, backlog) == -1) error_exit(-1, "listen error");
    return 0;
}

int Read(int connection, void* buf, size_t nbytes) {
    int n;

    memset(buf, '\0', nbytes);
    if ((n = read(connection, buf, nbytes)) == -1)
        error_exit(-1, "read errror");

    return n;
}

int Socket(int family, int type, int proctol) {
    int n;

    if ((n = socket(family, type, proctol)) == -1)
        error_exit(-1, "socket error");
    return n;
}

int Write(int connection, const char* buf) {
    int i, len, n;

    len = n = strlen(buf);
    while (n > 0 && (i = write(connection, buf, n)) > 0) {
        n -= i;
        buf += i;
    }
    if (i < 0) error_exit(-1, "write error");

    return len;
}
