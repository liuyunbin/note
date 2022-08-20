
#include <TinyLog/logging_async.h>

#include <TinyLog/logger.h>

#include <chrono>
#include <functional>
#include <utility>

namespace TinyLog {

LoggingAsync::LoggingAsync(std::string file_name, std::size_t roll_size, std::time_t flush_interval)
  : log_file_(std::move(file_name), roll_size, flush_interval),
    running_(false),
    current_buffer_(new LogBuffer),
       next_buffer_(new LogBuffer) {
}

LoggingAsync::~LoggingAsync() {
  stop();
}

void LoggingAsync::start() {
  using namespace std::placeholders;
  running_ = true;
  Logger::setLogOutput(std::bind(&LoggingAsync::append, this, _1, _2));
  Logger::setLogFlush( std::bind(&LoggingAsync::flush,  this));
   thread_ = std::thread(&LoggingAsync::thread_func, this);
}

void LoggingAsync::stop() {
  if (running_) {
    running_ = false;
       cond_.notify_one();
     thread_.join();
  }
}

void LoggingAsync::append(const char* logline, std::size_t len) {
  if (running_ == false)
    return ;
  std::lock_guard<std::mutex> lock(mutex_);
  if (current_buffer_->available_size() >= len) {
    current_buffer_->append(logline, len);
    return ;
  }
  buffers_.push_back(std::move(current_buffer_));

  if (next_buffer_)
    current_buffer_ = std::move(next_buffer_);
  else
    current_buffer_.reset(new LogBuffer);
  current_buffer_->append(logline, len);
  cond_.notify_one();
}

void LoggingAsync::flush() {
  stop();
}

void LoggingAsync::thread_func() {
  decltype(current_buffer_) new_buffer1(new LogBuffer);
  decltype(   next_buffer_) new_buffer2(new LogBuffer);
  
  decltype(buffers_) buffers_temp;

  while (running_) {
    {
      std::unique_lock<std::mutex> lock(mutex_);
      if (buffers_.empty())
        cond_.wait(lock);
      buffers_.push_back(std::move(current_buffer_));
      current_buffer_ = std::move(new_buffer1);
      using std::swap;
      swap(buffers_temp, buffers_);
      if (!next_buffer_)
        next_buffer_ = std::move(new_buffer2);
    }

    for (const auto& val : buffers_temp)
      log_file_.append(val->data(), val->size());

    if (!new_buffer1) {
      new_buffer1 = std::move(buffers_temp.back());
      buffers_temp.pop_back();
      new_buffer1->clear();
    }

    if (!new_buffer2) {
      new_buffer2 = std::move(buffers_temp.back());
      buffers_temp.pop_back();
      new_buffer2->clear();
    }
    buffers_temp.clear();
  }
  {
    std::lock_guard<std::mutex> lock(mutex_);
    buffers_.push_back(std::move(current_buffer_));
    for (const auto& val : buffers_)
      log_file_.append(val->data(), val->size());
  }
}

} // namespace TinyLog
