
#include <TinyNet/tcp_connection.h>

#include <sys/socket.h>
#include <unistd.h>

#include <cstring>

namespace TinyNet {

TcpConnection::TcpConnection(EventLoop* loop, int socket)
  :   state_(kConnecting),
       loop_(loop),
    channel_(loop_, socket),
     socket_(socket) {

  channel_.setReadCallback( std::bind(&TcpConnection::handleRead,  this));
  channel_.setWriteCallback(std::bind(&TcpConnection::handleWrite, this));
  channel_.setEventsRead();
  channel_.add();


  socklen_t len = sizeof(struct sockaddr_in);
  ::getpeername(socket, (struct sockaddr*)(peer_addr_.data()), &len);
  ::getsockname(socket, (struct sockaddr*)(peer_addr_.data()), &len);
}

const InetAddress& TcpConnection::getPeerAddress() const { return peer_addr_; }
const InetAddress& TcpConnection::getSockAddress() const { return sock_addr_; }

void TcpConnection::setState(State s) {
  state_ = s;
}

TcpConnection::~TcpConnection() {
  ::close(socket_);
}

EventLoop* TcpConnection::getLoop() const {
  return loop_;
}

void TcpConnection::handleRead() {
  auto n = input_buffer_.readFd(socket_);
  if (n > 0) {
    read_call_back_(shared_from_this(), input_buffer_.read());
  } else if (n == 0) {
    handleClose();
  }
}

void TcpConnection::handleWrite() {
  int n = ::write(socket_, output_buffer_.data(), output_buffer_.size());
  if (n <= 0)
    return ;
  output_buffer_.read(n);
  if (output_buffer_.size() == 0) {
    channel_.setEventsNoWrite();
    channel_.update();
    if (state_ == kDisconnecting)
      shutdownInLoop();
  }
}

void TcpConnection::handleClose() {
  channel_.remove();
  close_call_back_(shared_from_this());
}

void TcpConnection::connectDestroy() {
   setState(kDisconnected);
}

void TcpConnection::connectEstablished() {
  setState(kConnected);
  connection_call_back_(shared_from_this());
}

void TcpConnection::setConnectionCallBack(const ConnectionCallBack& cb) { connection_call_back_ = cb; }
void TcpConnection::setReadCallBack(      const       ReadCallBack& cb) {       read_call_back_ = cb; }
void TcpConnection::setCloseCallBack(     const      CloseCallBack& cb) {      close_call_back_ = cb; }

void TcpConnection::shutdown() {
  loop_->runInLoop(std::bind(&TcpConnection::shutdownInLoop, shared_from_this()));
}

void TcpConnection::shutdownInLoop() {
  setState(kDisconnecting);
  if (channel_.isEventsNoWrite())
    ::shutdown(socket_, SHUT_WR);
}

void TcpConnection::send(const        char* st)                { send(st,  std::strlen(st)); }
void TcpConnection::send(const std::string& st)                { send(st.data(), st.size()); }
void TcpConnection::send(const        char* st, std::size_t n) { 
  void (TcpConnection::*p)(const std::string&) = &TcpConnection::sendInLoop;
  loop_->runInLoop(std::bind(p, shared_from_this(), std::string(st, n)));
}

void TcpConnection::sendInLoop(const std::string& st) {
  sendInLoop(st.data(), st.size());
}

void TcpConnection::sendInLoop(const char* st, std::size_t n) {
  int len = 0;

  if (channel_.isEventsNoWrite()) {
    len = ::write(socket_, st, n);
    if (len < 0)
      return ;
    if (len == n)
      return ; 
  }

  output_buffer_.append(st + len, n - len);
  if (channel_.isEventsNoWrite()) {
    channel_.setEventsWrite();
    channel_.update();
  }
}

} // namespace TinyNet

