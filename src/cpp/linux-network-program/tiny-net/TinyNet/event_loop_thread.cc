
#include <TinyNet/event_loop_thread.h>

namespace TinyNet {

EventLoopThread::EventLoopThread() : loop_(NULL) {}

EventLoopThread::~EventLoopThread() {
    if (loop_ != NULL) {
        loop_->quit();
        thread_.join();
    }
}

EventLoop* EventLoopThread::start() {
    thread_ = std::thread(&EventLoopThread::threadFunc, this);
    {
        std::unique_lock<std::mutex> lock(mutex_);
        while (loop_ == NULL) cond_.wait(lock);
    }
    return loop_;
}

void EventLoopThread::threadFunc() {
    EventLoop loop;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        loop_ = &loop;
        cond_.notify_one();
    }
    loop.loop();
    loop_ = NULL;
}

}  // namespace TinyNet
