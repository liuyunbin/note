
#include <TinyNet/event_loop_thread_pool.h>

namespace TinyNet {

EventLoopThreadPool::EventLoopThreadPool(EventLoop* base_loop, int num_threads_)
    : base_loop_(base_loop), next_(0) {
    for (int i = 0; i < num_threads_; ++i) {
        EventLoopThread* t = new EventLoopThread();
        threads_.push_back(std::unique_ptr<EventLoopThread>(t));
        loops_.push_back(t->start());
    }
}

EventLoop* EventLoopThreadPool::getNextLoop() {
    EventLoop* loop = base_loop_;

    if (!loops_.empty()) {
        loop = loops_[next_++];
        if (next_ == loops_.size()) next_ = 0;
    }
    return loop;
}

}  // namespace TinyNet
