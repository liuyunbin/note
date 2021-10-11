
#include <TinyNet/epoller.h>

#include <unistd.h>

#include <iostream>

namespace TinyNet {

Epoller::Epoller(std::vector<struct epoll_event>::size_type init_events_size)
  : epollfd_(::epoll_create1(EPOLL_CLOEXEC)),
     events_(init_events_size) {
}

Epoller::~Epoller() { ::close(epollfd_); }

void Epoller::poll() {
  int n = ::epoll_wait(epollfd_, events_.data(), static_cast<int>(events_.size()), -1);

  for (int i = 0; i < n; ++i) {
    Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
    channel->setRevents(events_[i].events);
    channel->handleEvent();
  }

  if (n == static_cast<int>(events_.size()))
    events_.resize(events_.size()*2);
}

void Epoller::addChannel(   Channel* channel) { update(EPOLL_CTL_ADD, channel); }
void Epoller::updateChannel(Channel* channel) { update(EPOLL_CTL_MOD, channel); }
void Epoller::removeChannel(Channel* channel) { update(EPOLL_CTL_DEL, channel); }

void Epoller::update(int operation, Channel* channel) {
  struct epoll_event event;
  event.events = channel->getEvents();
  event.data.ptr = channel;
  int fd = channel->getFd();
  ::epoll_ctl(epollfd_, operation, fd, &event);
}

} // namespace TinyNet
