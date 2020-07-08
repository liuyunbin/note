
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
  
  printf("new client\n");

  // 设置发送超时，处理客户端只发送，不接收的情况
  struct timeval tv = {10, 0};
  setsockopt(con_socket, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
  
  int val = 1;
  setsockopt(con_socket, SOL_SOCKET, SO_KEEPALIVE, &val, sizeof(val)); // 设置 TCP 保活机制
  
  char buf[1024];
  for (;;) {
    ssize_t read_len = read(con_socket, buf, sizeof buf);
    if (read_len == 0) {
      printf("client quit\n");
      return;
    }
    if (read_len < 0) {
      perror("client quit");
      return;
    }
    if (write(con_socket, buf, read_len) != read_len) {
      perror("client quit");
      return;
    }
  }
}

void server(uint16_t server_port) {

  printf("server port = %d\n", server_port);

  const char* server_ip = "0.0.0.0";

  struct sockaddr_in server_addr;
  bzero(&server_addr, sizeof server_addr);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port   = htons(server_port);
  inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

  int listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (listen_socket == -1) {
    perror("socket");
    exit(-1);
  }

  int opt = 1;
  setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  setsockopt(listen_socket, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
  
  int ret = bind(listen_socket, (struct sockaddr*)(&server_addr), sizeof server_addr);
  if (ret == -1) {
    perror("bind");
    exit(-1);
  }

  ret = listen(listen_socket, 5);
  if (ret == -1) {
    perror("listen");
    exit(-1);
  }

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
      server_handle_client(con_socket);
      close(con_socket);
      exit(0);
    default:
      // 父进程
      close(con_socket);
      break;
    }
  }
}

int main(int argc, char *argv[]) {

  set_signal();

  if (argc < 2) {
    printf("usage: %s port\n", argv[0]);
    return -1;
  }

  uint16_t server_port = atoi(argv[1]);

  if (server_port <= 0) {
    printf("usage: %s port\n", argv[0]);
    return -1;
  }

  server(server_port);

  return 0;
}

