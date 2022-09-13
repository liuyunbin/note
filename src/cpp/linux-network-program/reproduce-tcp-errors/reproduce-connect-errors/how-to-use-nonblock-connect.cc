#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>

int main(int argc, char* argv[]) {

  const char* server_ip   = "192.0.0.1";
  uint16_t    server_port = 6666;

  int client_socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP); // 非阻塞 socket

  struct sockaddr_in server_addr;
  bzero(&server_addr, sizeof server_addr);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port   = htons(server_port);
  inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

  std::cout << "try to connect " << server_ip << ":" << server_port << std::endl;
  int ret = connect(client_socket, reinterpret_cast<struct sockaddr*>(&server_addr),
              static_cast<socklen_t>(sizeof server_addr));
  if (ret == 0) {
    std::cout << "connect succcess" << std::endl;
    return 0;
  }
  if (errno != EINPROGRESS) {
    std::cout << "connect error" << std::endl;
    return -1;
  }
  int fd = epoll_create(1);
  struct epoll_event event;
  event.events = EPOLLOUT;
  epoll_ctl(fd, EPOLL_CTL_ADD, client_socket, &event);
  ret = epoll_wait(fd, &event, 1, -1);
  if (ret == 1 && (event.events & EPOLLOUT)) {
    int err;
    socklen_t err_len = sizeof(err);
    if (getsockopt(client_socket, SOL_SOCKET, SO_ERROR, &err, &err_len) < 0 ||
        err != 0)
      std::cout << "connect error: " << std::endl;
    else
      std::cout << "connect success" << std::endl;
  }
  return 0;
}

