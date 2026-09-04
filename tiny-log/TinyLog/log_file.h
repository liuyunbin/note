#ifndef TINYLOG_LOG_FILE_H_
#define TINYLOG_LOG_FILE_H_

#include <TinyLog/log_append_file.h>
#include <TinyLog/time_stamp.h>

#include <ctime>
#include <memory>
#include <string>

namespace TinyLog {

class LogFile {
  LogFile(           const LogFile&) = delete;
  LogFile& operator=(const LogFile&) = delete;

 public:
  LogFile(std::string file_name, std::size_t roll_size, std::time_t flush_interval = 3);
  
  void append(const char* logline, std::size_t len);
  void flush();
  void rollFile(const TimeStamp& val = TimeStamp());

 private:

  const std::string                file_name_;
  const std::size_t                roll_size_;
  const std::time_t           flush_interval_;

  std::time_t               start_of_period_;
  std::time_t                     last_roll_;
  std::time_t                    last_flush_;
  std::unique_ptr<LogAppendFile>       file_;

  constexpr static std::time_t kRollPerSeconds = 60*60*24;
};

} // namespace TinyLog

#endif
