
#include <TinyNet/inet_address.h>

#include <arpa/inet.h>
#include <strings.h>

#include <cstdio>

namespace TinyNet {

InetAddress::InetAddress(const sockaddr_in& addr) : addr_(addr) {
}

InetAddress::InetAddress(const char* ip, uint16_t port) {
  ::bzero(&addr_, sizeof(addr_));
  addr_.sin_family = AF_INET;
  addr_.sin_port   = ::htons(port);
  ::inet_pton(AF_INET, ip, &addr_.sin_addr);
}

InetAddress::InetAddress(uint16_t port, bool loopbackOnly) {
  uint32_t ip = loopbackOnly ? INADDR_LOOPBACK : INADDR_ANY;
  ::bzero(&addr_, sizeof(addr_));
  addr_.sin_family      = AF_INET;
  addr_.sin_port        = ::htons(port);
  addr_.sin_addr.s_addr = ::htonl(ip);
}

std::string InetAddress::toString() const {
  char buf[32];
  ::inet_ntop(AF_INET, &addr_.sin_addr, buf, static_cast<socklen_t>(sizeof(buf)));
  std::string st = "ip: ";
  st += buf;
  uint16_t port = ::ntohs(addr_.sin_port);
  std::snprintf(buf, sizeof(buf), " port: %u ", port);
  return st + buf;
}

      struct sockaddr_in* InetAddress::data()       { return &addr_; }
const struct sockaddr_in* InetAddress::data() const { return &addr_; }

} // namespace TinyNet
