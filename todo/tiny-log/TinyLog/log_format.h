#ifndef TINYLOG_LOG_FORMAT_H_
#define TINYLOG_LOG_FORMAT_H_

#include <TinyLog/log_stream.h>

namespace TinyLog {

class LogFormat {
 public:
  LogFormat           (const LogFormat&) = delete;
  LogFormat& operator=(const LogFormat&) = delete;

  template <typename T>
  LogFormat(const char* fmt, T v);

  const char* data() const;

 private:
  char data_[32];
};

LogStream& operator<<(LogStream& os, const LogFormat& fmt);

template <typename T>
LogFormat::LogFormat(const char* fmt, T v) {
  std::snprintf(data_, sizeof(data_), fmt, v);
}

} // namespace TinyLog

#endif
