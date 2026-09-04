
#ifndef TINYNET_EPOLLER_H_
#define TINYNET_EPOLLER_H_

#include <TinyNet/channel.h>

#include <sys/epoll.h>

#include <vector>

namespace TinyNet {

class Epoller {
  Epoller(           const Epoller&) = delete;
  Epoller& operator=(const Epoller&) = delete;

 public:
  explicit Epoller(std::vector<struct epoll_event>::size_type init_events_size = 16);
  ~Epoller();

  void poll();

  void addChannel(   Channel* channel);
  void updateChannel(Channel* channel);
  void removeChannel(Channel* channel);

 private:
  void update(int operation, Channel* channel);

  int epollfd_; 
  std::vector<struct epoll_event> events_;
};

} // namespace TinyNet

#endif
