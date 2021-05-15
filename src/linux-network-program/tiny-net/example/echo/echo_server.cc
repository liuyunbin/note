
#include <TinyNet/tcp_server.h>

#include <iostream>
#include <string>

void connection(const std::shared_ptr<TinyNet::TcpConnection>& con) {
  std::cout << "new connection: " << con->getPeerAddress().toString() << std::endl;
}

void readCallback(const std::shared_ptr<TinyNet::TcpConnection>& con, std::string st) {
  std::cout << st;
  con->send(st.data(), st.size());
}

int main() {
  TinyNet::InetAddress addr(7);

  TinyNet::EventLoop loop;

  TinyNet::TcpServer server(&loop, addr);

  server.setConnectionCallBack(connection);
  server.setReadCallBack(readCallback);

  server.start();
  loop.loop();
  
  return 0;
}
