
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

#include <vector>

void read_all(int sock, char *buf, int len) {

  while (len > 0) {
    int ret = read(sock, buf, len);
    if (ret <= 0) {
      perror("read");
      exit(-1);
    }
    buf += ret;
    len -= ret;
  }
}

int main(int argc, char *argv[]) {

  if (argc < 5) {
    printf("usage: %s ip port client_number send_number\n", argv[0]);
    return -1;
  }

  const char *server_ip = argv[1];
  uint16_t server_port = atoi(argv[2]);
  int32_t client_number = atoi(argv[3]);
  int32_t send_number = atoi(argv[4]);

  if (server_port <= 0 || client_number <= 0 || send_number <= 0) {
    printf("usage: %s ip port clinet_number send_number\n", argv[0]);
    return -1;
  }

  struct sockaddr_in server_addr;
  bzero(&server_addr, sizeof server_addr);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(server_port);
  int ret = inet_pton(AF_INET, server_ip, &server_addr.sin_addr);
  if (ret == -1) {
    perror("inet_pton");
    exit(-1);
  }

  std::vector<int> sock(client_number, 0);

  for (int i = 0; i < client_number; ++i) {
    sock[i] = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock[i] == -1) {
      perror("socket");
      exit(-1);
    }

    printf("try connect %s:%d...\n", server_ip, server_port);

    ret =
        connect(sock[i], (struct sockaddr *)(&server_addr), sizeof server_addr);
    if (ret == -1) {
      perror("connect fail");
      exit(-1);
    }

    printf("connect success\n");
  }

  struct timeval t1;
  gettimeofday(&t1, NULL);

  for (int i = 0; i < client_number; ++i) {
    for (int j = 0; j < send_number; ++j) {
      if (write(sock[i], test_data, 81) != 81) {
        perror("write");
        exit(-1);
      }
    }
  }

  for (int i = 0; i < client_number; ++i) {
    for (int j = 0; j < send_number; ++j) {
      char buf[81];
      read_all(sock[i], buf, 81);
    }
    close(sock[i]);
  }

  struct timeval t2;
  gettimeofday(&t2, NULL);

  double test_tm =
      t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) / 1000000.0;

  int test_all_number = client_number * send_number;

  printf("总共测试 %d 个客户端\n", client_number);
  printf("每个客户端发送 %d 个数独\n", send_number);
  printf("总共发送 %d 个数独\n", test_all_number);
  printf("总共耗时 %f 秒\n", test_tm);
  printf("平均每秒处理 %d 个数独\n", (int)(test_all_number / test_tm));
  printf("平均每个数独需要 %f 微秒\n", test_tm * 1000 * 1000 / test_all_number);

  return 0;
}

