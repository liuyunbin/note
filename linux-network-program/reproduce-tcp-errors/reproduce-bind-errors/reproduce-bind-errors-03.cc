
#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>

int main(int argc, char* argv[]) {

  const char* server_ip   = "127.0.0.1";
  uint16_t    server_port = 6667;

  struct sockaddr_in server_addr;
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port   = htons(server_port);
  inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

  int listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  std::cout << "server try to bind " << server_ip << ":" << server_port << std::endl;
  int ret = bind(listen_socket, reinterpret_cast<struct sockaddr*>(&server_addr),
            static_cast<socklen_t>(sizeof server_addr));
  if (ret == -1)
    perror("bind error");
  else
    std::cout << "bind success" << std::endl;
  listen(listen_socket, 5);
  std::cout << "server listen..." << std::endl;

  listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  std::cout << "new server try to bind " << server_ip << ":" << server_port << std::endl;
  ret = bind(listen_socket, reinterpret_cast<struct sockaddr*>(&server_addr),
             static_cast<socklen_t>(sizeof server_addr));
  if (ret == -1)
    perror("bind error");
  else
    std::cout << "bind success" << std::endl;

  return 0;
}
