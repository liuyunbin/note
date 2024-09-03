#ifndef TINYNET_CHANNEL_H_
#define TINYNET_CHANNEL_H_

#include <functional>

namespace TinyNet {

class EventLoop;

class Channel {
  Channel(           const Channel&) = delete;
  Channel& operator=(const Channel&) = delete;

 public:
  using EventCallback = std::function<void()>;
  
  Channel(EventLoop* loop, int fd);

  void handleEvent();

  void setReadCallback( const EventCallback& cb);
  void setWriteCallback(const EventCallback& cb);
  void setErrorCallback(const EventCallback& cb);

  EventLoop* getLoop() const;
  int          getFd() const;

  uint32_t getEvents() const;
  void     setEvents(uint32_t events);
  
  void setEventsRead();
  void setEventsNoRead();
  void setEventsWrite();
  void setEventsNoWrite();
  void setEventsNone();

  bool isEventsRead()    const;
  bool isEventsNoRead()  const;
  bool isEventsWrite()   const;
  bool isEventsNoWrite() const;
  bool isEventsNone()    const;

  uint32_t getRevents() const;
  void     setRevents(uint32_t revents);

  void add();
  void remove();
  void update();

 private:
  
  EventLoop*  loop_;
  const int     fd_;
  uint32_t  events_;
  uint32_t revents_;

  EventCallback  read_callback_;
  EventCallback write_callback_;
  EventCallback error_callback_;
};

} // namespace TinyNet

#endif
