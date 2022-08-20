
#include <TinyNet/tcp_server.h>

namespace TinyNet {

TcpServer::TcpServer(EventLoop* loop, const InetAddress& addr) 
  :             loop_(loop), 
            acceptor_(loop, addr),
    loop_thread_pool_(loop) {

  using namespace std::placeholders;
  acceptor_.setConnectionCallback(std::bind(&TcpServer::newConnection, this, _1));
}

void TcpServer::start() {
  acceptor_.listen();
}

void TcpServer::setConnectionCallBack(const ConnectionCallBack& cb) { connection_call_back_ = cb; }
void TcpServer::setReadCallBack(      const       ReadCallBack& cb) {       read_call_back_ = cb; }

void TcpServer::newConnection(int socket) {
  EventLoop* loop = loop_thread_pool_.getNextLoop();
  std::shared_ptr<TcpConnection> con(new TcpConnection(loop, socket));
  connections_.insert(con);
  con->setConnectionCallBack(connection_call_back_);
  con->setReadCallBack(read_call_back_);
  using namespace std::placeholders;
  con->setCloseCallBack(std::bind(&TcpServer::removeConnection, this, _1));
  loop->runInLoop(std::bind(&TcpConnection::connectEstablished, con));
}

void TcpServer::removeConnection(const std::shared_ptr<TcpConnection>& con) {
  connections_.erase(con);
  auto io_loop = con->getLoop();
  io_loop->queueInLoop(std::bind(&TcpConnection::connectDestroy, con));
}

} // namespace TinyNet
