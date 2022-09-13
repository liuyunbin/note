
#include <TinyNet/channel.h>
#include <TinyNet/event_loop.h>

#include <sys/epoll.h>

namespace TinyNet {

Channel::Channel(EventLoop* loop, int fd) : loop_(loop), fd_(fd), events_(0), revents_(0) {}

void Channel::setReadCallback( const EventCallback& cb) {  read_callback_ = cb; }
void Channel::setWriteCallback(const EventCallback& cb) { write_callback_ = cb; }
void Channel::setErrorCallback(const EventCallback& cb) { error_callback_ = cb; }

EventLoop* Channel::getLoop() const { return loop_; }
int        Channel::getFd()   const { return   fd_; }

uint32_t Channel::getEvents() const          { return    events_; }
void     Channel::setEvents(uint32_t events) { events_ = events;  }

void Channel::setEventsRead()    { events_ |=  EPOLLIN;  }
void Channel::setEventsWrite()   { events_ |=  EPOLLOUT; }
void Channel::setEventsNoRead()  { events_ &= ~EPOLLIN;  }
void Channel::setEventsNoWrite() { events_ &= ~EPOLLOUT; }
void Channel::setEventsNone()    { events_  =         0; }

bool Channel::isEventsRead()    const { return   events_&EPOLLIN;        }
bool Channel::isEventsNoRead()  const { return  (events_&EPOLLIN)  == 0; }
bool Channel::isEventsWrite()   const { return   events_&EPOLLOUT;       }
bool Channel::isEventsNoWrite() const { return  (events_&EPOLLOUT) == 0; }
bool Channel::isEventsNone()    const { return   events_           == 0; }

uint32_t Channel::getRevents() const           { return     revents_; }
void     Channel::setRevents(uint32_t revents) { revents_ = revents;  }
  
void Channel::add()    { loop_->addChannel(this);    }
void Channel::update() { loop_->updateChannel(this); }
void Channel::remove() { loop_->removeChannel(this); }

void Channel::handleEvent() {
  if (revents_&EPOLLERR)
    if (error_callback_)
      error_callback_();
  if (revents_&EPOLLIN)
    if (read_callback_)
      read_callback_();
  if (revents_&EPOLLOUT)
    if (write_callback_)
      write_callback_();
}

} // namespace TinyNet
