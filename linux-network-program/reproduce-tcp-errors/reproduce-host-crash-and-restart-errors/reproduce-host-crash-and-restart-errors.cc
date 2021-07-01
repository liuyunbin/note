#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>

void signal_handle(int sig) { std::cout << "catch SIGPIPE" << std::endl; }

void set_signal() { signal(SIGPIPE, signal_handle); }

int main(int argc, char* argv[]) {

  set_signal();

  const char* server_ip   = "192.168.1.100";
  uint16_t    server_port = 6666;

  const char* client_ip   = "192.168.1.200";
  uint16_t    client_port = 0;

  std::cout << "sudo ip addr add 192.168.1.100/8 dev enp2s0" << std::endl;
  system("sudo ip addr add 192.168.1.100/8 dev enp2s0");
  
  std::cout << "sudo ip addr add 192.168.1.200/8 dev enp2s0" << std::endl;
  system("sudo ip addr add 192.168.1.200/8 dev enp2s0");
  
  struct sockaddr_in server_addr;
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port   = htons(server_port);
  inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

  struct sockaddr_in client_addr;
  bzero(&client_addr, sizeof(client_addr));
  client_addr.sin_family = AF_INET;
  client_addr.sin_port   = htons(client_port);
  inet_pton(AF_INET, client_ip, &client_addr.sin_addr);

  int listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  int opt = 1;
  setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  std::cout << "server try to bind " << server_ip << ":" << server_port << std::endl;
  int ret = bind(listen_socket, reinterpret_cast<struct sockaddr*>(&server_addr),
             static_cast<socklen_t>(sizeof server_addr));
  if (ret == -1)
    perror("bind error");
  else
    std::cout << "bind success" << std::endl;
  listen(listen_socket, 5);
  std::cout << "server listen..." << std::endl;

  int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  std::cout << "client try to bind " << client_ip << ":" << client_port << std::endl;
  ret = bind(client_socket, reinterpret_cast<struct sockaddr*>(&client_addr),
             static_cast<socklen_t>(sizeof client_addr));
  if (ret == -1)
    perror("bind error");
  else
    std::cout << "bind success" << std::endl;
  std::cout << "client try to connect " << server_ip << ":" << server_port << std::endl;
  ret = connect(client_socket, reinterpret_cast<struct sockaddr*>(&server_addr),
                static_cast<socklen_t>(sizeof server_addr));
  if (ret == -1)
    perror("connect error");
  else
    std::cout << "connect success" << std::endl;

  int con_socket = accept(listen_socket, NULL, NULL);
  std::cout << "new client come" << std::endl;

  std::cout << "sudo ip addr del 192.168.1.100/8 dev enp2s0" << std::endl;
  system("sudo ip addr del 192.168.1.100/8 dev enp2s0");
 
  close(con_socket);
  std::cout << "close server con_socket" << std::endl;

  close(listen_socket);
  std::cout << "close server listen socket" << std::endl;

  std::cout << "sudo ip addr add 192.168.1.100/8 dev enp2s0";
  system("sudo ip addr add 192.168.1.100/8 dev enp2s0");
  
  char ch;
  std::cout << "client: try write..." << std::endl;
  if (write(client_socket, &ch, sizeof(ch)) == -1)
    std::cout << "client: write error" << std::endl;

  std::cout << "client: try read..." << std::endl;
  if (read(client_socket, &ch, sizeof(ch)) == -1)
    std::cout << "client: read error" << std::endl;

  std::cout << "client: try write again..." << std::endl;
  if (write(client_socket, &ch, sizeof(ch)) == -1)
    std::cout << "client: write error" << std::endl;

  close(client_socket);
  std::cout << "close client listen socket" << std::endl;

  std::cout << "sudo ip addr del 192.168.1.100/8 dev enp2s0" << std::endl;
  system("sudo ip addr del 192.168.1.100/8 dev enp2s0");

  std::cout << "sudo ip addr del 192.168.1.200/8 dev enp2s0" << std::endl;
  system("sudo ip addr del 192.168.1.200/8 dev enp2s0");
 
  return 0;
}
