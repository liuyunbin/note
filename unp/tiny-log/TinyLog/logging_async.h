#ifndef TINYLOG_LOGGING_ASYNC_H_
#define TINYLOG_LOGGING_ASYNC_H_

#include <TinyLog/log_buffer.h>
#include <TinyLog/log_file.h>

#include <atomic>
#include <condition_variable>
#include <cstddef>
#include <cstdio>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace TinyLog {

class LoggingAsync {
  LoggingAsync(           const LoggingAsync&) = delete;
  LoggingAsync& operator=(const LoggingAsync&) = delete;

 public:

  LoggingAsync(std::string file_name, std::size_t roll_size, std::time_t flush_interval = 3);

  ~LoggingAsync();

  void append(const char* logline, std::size_t len);
  
  void start();

  void stop();

 private:

  void flush();
  void thread_func();

  LogFile log_file_;

  std::atomic<bool> running_;

  std::thread thread_;

  std::mutex              mutex_;
  std::condition_variable  cond_;

  std::unique_ptr<LogBuffer>             current_buffer_;
  std::unique_ptr<LogBuffer>                next_buffer_;
  std::vector<std::unique_ptr<LogBuffer>>       buffers_;
};

} // namespace TinyLog

#endif
