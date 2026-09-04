#ifndef TINYNET_TCP_CONNECTION_H_
#define TINYNET_TCP_CONNECTION_H_

#include <TinyNet/buffer.h>
#include <TinyNet/channel.h>
#include <TinyNet/event_loop.h>
#include <TinyNet/inet_address.h>

#include <cstdio>
#include <functional>
#include <memory>
#include <string>

namespace TinyNet {

class TcpConnection;

using ConnectionCallBack = std::function<void(const std::shared_ptr<TcpConnection>&)>;
using       ReadCallBack = std::function<void(const std::shared_ptr<TcpConnection>&, std::string)>;
using      CloseCallBack = std::function<void(const std::shared_ptr<TcpConnection>&)>;

class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
 public:
  TcpConnection(           const TcpConnection&) = delete;
  TcpConnection& operator=(const TcpConnection&) = delete;

   TcpConnection(EventLoop* loop, int socket);
  ~TcpConnection();

  const InetAddress& getPeerAddress() const;
  const InetAddress& getSockAddress() const;

  EventLoop* getLoop() const;

  void connectEstablished();

  void setConnectionCallBack(const ConnectionCallBack&);
  void setReadCallBack(      const       ReadCallBack&);
  void setCloseCallBack(     const      CloseCallBack&);

  void handleRead();
  void handleWrite();
  void handleClose();

  void connectDestroy();

  void shutdown();

  void send(const        char* st);
  void send(const        char* st, std::size_t n);
  void send(const std::string& st);

  void sendInLoop(const std::string& st);
  void sendInLoop(const char* st, std::size_t n);

 private:

  enum State { kDisconnected, kConnecting, kConnected, kDisconnecting };

  void setState(State s);

  State        state_;

  EventLoop*    loop_;
  Channel    channel_;
  int         socket_;

  ConnectionCallBack connection_call_back_;
        ReadCallBack       read_call_back_;
       CloseCallBack      close_call_back_;

  Buffer  input_buffer_;
  Buffer output_buffer_;

  void shutdownInLoop();

  InetAddress peer_addr_;
  InetAddress sock_addr_;
};

} // namespace TinyNet

#endif
