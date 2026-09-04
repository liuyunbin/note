
#ifndef TINYNET_EVENT_LOOP_THREAD_H_
#define TINYNET_EVENT_LOOP_THREAD_H_

#include <TinyNet/event_loop.h>

#include <condition_variable>
#include <mutex>
#include <thread>

namespace TinyNet {

class EventLoopThread {
 public:
  EventLoopThread(           const EventLoopThread&) = delete;
  EventLoopThread& operator=(const EventLoopThread&) = delete;

  EventLoopThread();
  ~EventLoopThread();
  EventLoop* start();

 private:
  void threadFunc();

  EventLoop*              loop_;
  std::thread           thread_;
  std::mutex             mutex_;
  std::condition_variable cond_;
};

} // namespace TinyNet

#endif
