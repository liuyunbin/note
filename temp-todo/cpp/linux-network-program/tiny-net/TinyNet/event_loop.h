#ifndef TINYNET_EVENT_LOOP_H_
#define TINYNET_EVENT_LOOP_H_

#include <TinyNet/channel.h>
#include <TinyNet/epoller.h>

#include <atomic>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

namespace TinyNet {

class EventLoop {
  EventLoop(           const EventLoop&) = delete;
  EventLoop& operator=(const EventLoop&) = delete; 

 public:
  using Functor = std::function<void()>;

   EventLoop();
  ~EventLoop();

  void loop();

  void quit();

  void    addChannel(Channel*);
  void updateChannel(Channel*);
  void removeChannel(Channel*);

  bool isInLoopThread() const;

  void runInLoop(const Functor& f);

  void queueInLoop(const Functor& f);

 private:

  Epoller           epoller_;
  std::thread::id thread_id_;

  std::atomic<bool> quit_;

  int     wakeup_fd_;
  Channel wakeup_channel_;

  void handleWakeupRead();
  void wakeup();

  void doPendingFunctors();

  std::mutex           mutex_;
  std::atomic<bool>    calling_pending_functors_;
  std::vector<Functor> pending_functors_;

};

} // namespace TinyNet

#endif
