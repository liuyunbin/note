
#ifndef TINYNET_INET_ADDRESS_H_
#define TINYNET_INET_ADDRESS_H_

#include <stdint.h>
#include <netinet/in.h>

#include <string>

namespace TinyNet {

class InetAddress {
 public:
   InetAddress(           const InetAddress&) = default;
   InetAddress& operator=(const InetAddress&) = default;

  explicit InetAddress(uint16_t port = 0, bool loopbackOnly = false);
           InetAddress(const char* ip, uint16_t port);
           InetAddress(const sockaddr_in& addr);

  std::string toString() const;

        struct sockaddr_in* data();
  const struct sockaddr_in* data() const;
  
 private:
  struct sockaddr_in addr_;
};

}  // namespace TinyNet

#endif
