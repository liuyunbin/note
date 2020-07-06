
#include <TinyNet/listen_socket.h>

#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>

namespace TinyNet {

ListenSocket::ListenSocket(const InetAddress& addr) {
  listen_socket_ = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
  
  int optval = 1;
  ::setsockopt(listen_socket_, SOL_SOCKET, SO_REUSEADDR, &optval, static_cast<socklen_t>(sizeof(optval)));
  ::setsockopt(listen_socket_, SOL_SOCKET, SO_REUSEPORT, &optval, static_cast<socklen_t>(sizeof(optval)));
  ::setsockopt(listen_socket_, IPPROTO_TCP, TCP_NODELAY, &optval, static_cast<socklen_t>(sizeof(optval)));
  ::setsockopt(listen_socket_, SOL_SOCKET, SO_KEEPALIVE, &optval, static_cast<socklen_t>(sizeof(optval)));
  
  ::bind(listen_socket_, reinterpret_cast<const struct sockaddr*>(addr.data()), static_cast<socklen_t>(sizeof(struct sockaddr_in)));
}

void ListenSocket::listen() {
  ::listen(listen_socket_, SOMAXCONN);
}

int ListenSocket::accept() {
  return ::accept4(listen_socket_, NULL, NULL, SOCK_NONBLOCK | SOCK_CLOEXEC);
}

int ListenSocket::getFd() {
  return listen_socket_;
}

ListenSocket::~ListenSocket() {
  ::close(listen_socket_);
}

} // namespace TinyNet
