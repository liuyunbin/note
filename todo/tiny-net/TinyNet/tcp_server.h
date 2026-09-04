#ifndef TINYNET_TCP_SERVER_H_
#define TINYNET_TCP_SERVER_H_

#include <TinyNet/acceptor.h>
#include <TinyNet/event_loop.h>
#include <TinyNet/event_loop_thread_pool.h>
#include <TinyNet/tcp_connection.h>

#include <cstdio>
#include <unordered_set>

namespace TinyNet {

class TcpServer {
 public:
  TcpServer(           const TcpServer&) = delete;
  TcpServer& operator=(const TcpServer&) = delete;

   TcpServer(EventLoop* loop, const InetAddress& addr);

  void start();

  void setConnectionCallBack(const ConnectionCallBack&);
  void setReadCallBack(      const       ReadCallBack&);

private:
  EventLoop*     loop_;
  Acceptor   acceptor_;

  EventLoopThreadPool loop_thread_pool_;

  ConnectionCallBack connection_call_back_;
        ReadCallBack       read_call_back_;

  std::unordered_set<std::shared_ptr<TcpConnection>> connections_;

  void newConnection(int socket);
  void removeConnection(const std::shared_ptr<TcpConnection>& con);
};

} // namespace TinyNet

#endif
