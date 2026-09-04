
#include <TinyNet/acceptor.h>

#include <utility>

namespace TinyNet {

Acceptor::Acceptor(EventLoop* loop, const InetAddress& addr)
    : listenning_(false),
      listen_socket_(addr),
      channel_(loop, listen_socket_.getFd()) {}

Acceptor::~Acceptor() {
    if (listenning_) channel_.remove();
}

void Acceptor::setConnectionCallback(const ConnectionCallback& cb) {
    connection_callback_ = cb;
}

void Acceptor::listen() {
    channel_.setEventsRead();
    channel_.setReadCallback(std::bind(&Acceptor::handleRead, this));
    channel_.add();
    listenning_ = true;
    listen_socket_.listen();
}

void Acceptor::handleRead() {
    int connfd = listen_socket_.accept();
    if (connfd != -1) connection_callback_(connfd);
}

}  // namespace TinyNet
