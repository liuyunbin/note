
#ifndef TINYNET_ACCEPTOR_H_
#define TINYNET_ACCEPTOR_H_

#include <TinyNet/channel.h>
#include <TinyNet/event_loop.h>
#include <TinyNet/inet_address.h>
#include <TinyNet/listen_socket.h>

#include <atomic>
#include <functional>

namespace TinyNet {

class Acceptor {
  Acceptor(           const Acceptor&) = delete;
  Acceptor& operator=(const Acceptor&) = delete;

 public:
  using ConnectionCallback = std::function<void (int)>;

  Acceptor(EventLoop* loop, const InetAddress& addr);
  ~Acceptor();

  void setConnectionCallback(const ConnectionCallback& cb);

  void listen();

 private:
  void handleRead();

  std::atomic<bool>           listenning_;
  ListenSocket             listen_socket_;
  Channel                        channel_;
  ConnectionCallback connection_callback_;
};

} // namespace TinyNet

#endif
