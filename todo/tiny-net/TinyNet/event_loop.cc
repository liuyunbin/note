
#include <TinyNet/event_loop.h>
#include <sys/eventfd.h>
#include <unistd.h>

namespace TinyNet {

EventLoop::EventLoop()
    : thread_id_(std::this_thread::get_id()),
      quit_(false),
      wakeup_fd_(::eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK)),
      wakeup_channel_(this, wakeup_fd_),
      calling_pending_functors_(false) {
    wakeup_channel_.setReadCallback(
        std::bind(&EventLoop::handleWakeupRead, this));
    wakeup_channel_.setEventsRead();
    wakeup_channel_.add();
}

EventLoop::~EventLoop() { ::close(wakeup_fd_); }

void EventLoop::loop() {
    while (quit_ == false) {
        epoller_.poll();
        doPendingFunctors();
    }
}

void EventLoop::handleWakeupRead() {
    uint64_t data;
    ::eventfd_read(wakeup_fd_, &data);
}

void EventLoop::wakeup() {
    uint64_t data = 1;
    ::eventfd_write(wakeup_fd_, data);
}

void EventLoop::runInLoop(const Functor& f) {
    if (isInLoopThread())
        f();
    else
        queueInLoop(f);
}

void EventLoop::queueInLoop(const Functor& f) {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        pending_functors_.push_back(f);
    }
    if (!isInLoopThread() || calling_pending_functors_) wakeup();
}

void EventLoop::doPendingFunctors() {
    calling_pending_functors_ = true;
    std::vector<Functor> temp;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        using std::swap;
        swap(temp, pending_functors_);
    }
    for (auto& val : temp) val();
    calling_pending_functors_ = false;
}

void EventLoop::quit() {
    quit_ = true;
    if (!isInLoopThread()) wakeup();
}

void EventLoop::addChannel(Channel* channel) { epoller_.addChannel(channel); }
void EventLoop::updateChannel(Channel* channel) {
    epoller_.updateChannel(channel);
}
void EventLoop::removeChannel(Channel* channel) {
    epoller_.removeChannel(channel);
}

bool EventLoop::isInLoopThread() const {
    return thread_id_ == std::this_thread::get_id();
}

}  // namespace TinyNet
