
#include "sudoku.h"

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

bool read_all(int sock, char *buf, int len) {

  while (len > 0) {
    int ret = read(sock, buf, len);
    if (ret == 0) {
      return false;
    }
    if (ret < 0) {
      perror("read");
      return false;
    }
    buf += ret;
    len -= ret;
  }
  return true;
}

void signal_handle(int sig) {
  switch (sig) {
  case SIGCHLD:
    printf("catch SIGCHLD\n");
    while (waitpid(-1, NULL, WNOHANG) > 0) { // 避免僵尸进程
      ;
    }
    break;
  case SIGPIPE:
    printf("catch SIGPIPE, ignore\n");
    break;
  default:
    printf("catch unknown signal, ignore\n");
    break;
  }
}

void set_signal() {
  struct sigaction act;
  act.sa_handler = signal_handle;
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_RESTART;
  sigaction(SIGCHLD, &act, NULL);
  sigaction(SIGPIPE, &act, NULL);
}

void server_handle_client(int con_socket) {
  // 设置发送超时，处理客户端只发送，不接收的情况
  struct timeval tv = {10, 0};
  setsockopt(con_socket, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

  int val = 1;
  setsockopt(con_socket, SOL_SOCKET, SO_KEEPALIVE, &val,
             sizeof(val)); // 设置 TCP 保活机制

  // 为求处理简单化，发送和接收的数据大小都为 81 个字符
  for (;;) {
    char buf[81];
    bool ret = read_all(con_socket, buf, 81);

    if (ret == false)
      break;

    if (solve_sudoku(buf) == false) {
      snprintf(buf, sizeof(buf), "此数独无解");
    }

    if (write(con_socket, buf, 81) != 81) {
      perror("write");
      break;
    }
  }
}

int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf("usage: %s port\n", argv[0]);
    return -1;
  }

  uint16_t server_port = atoi(argv[1]);

  if (server_port <= 0) {
    printf("usage: %s port\n", argv[0]);
    return -1;
  }

  printf("server port = %d\n", server_port);

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

  printf("server start\n");
  printf("accept...\n");

  for (;;) {

    int con_socket = accept(listen_socket, NULL, NULL);
    if (con_socket == -1) {
      perror("accept");
      exit(-1);
    }

    switch (fork()) {
    case -1:
      perror("fork");
      exit(-1);
    case 0:
      // 子进程
      close(listen_socket);
      printf("new client\n");
      server_handle_client(con_socket);
      printf("client quit\n");
      close(con_socket);
      exit(0);
    default:
      // 父进程
      close(con_socket);
    }
  }

  printf("server quit\n");

  return 0;
}

