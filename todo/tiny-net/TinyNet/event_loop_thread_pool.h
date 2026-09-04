
#ifndef TINYNET_EVENT_LOOP_THREAD_POOL_H_
#define TINYNET_EVENT_LOOP_THREAD_POOL_H_

#include <TinyNet/event_loop_thread.h>

#include <memory>
#include <vector>

namespace TinyNet {

class EventLoopThreadPool {
 public:
  EventLoopThreadPool(           const EventLoopThreadPool&) = delete;
  EventLoopThreadPool& operator=(const EventLoopThreadPool&) = delete;

  EventLoopThreadPool(EventLoop* base_loop, int num_threads = 4);
  EventLoop* getNextLoop();

 private:

  EventLoop*                                  base_loop_;
  int                                              next_;
  std::vector<std::unique_ptr<EventLoopThread>> threads_;
  std::vector<EventLoop*>                         loops_;
};

}

#endif
