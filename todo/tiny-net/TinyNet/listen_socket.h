
#ifndef TINYNET_LISTEN_SOCKET_H_
#define TINYNET_LISTEN_SOCKET_H_

#include <TinyNet/inet_address.h>

#include <netinet/in.h>
#include <stdint.h>

namespace TinyNet {

class ListenSocket {
 public:
  ListenSocket(           const ListenSocket&) = delete;
  ListenSocket& operator=(const ListenSocket&) = delete;

  ListenSocket(const InetAddress& addr);
  void listen();
  int  accept();

  int getFd();
  ~ListenSocket();

 private:
  int listen_socket_;
};

} // namespace TinyNet

#endif
