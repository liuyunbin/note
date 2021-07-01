#ifndef TINYLOG_LOGGER_H_
#define TINYLOG_LOGGER_H_

#include <cstddef>
#include <functional>

namespace TinyLog {

class Logger {
 public:
  Logger()                         = delete;
  Logger(           const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;

  using OutputFunc = std::function<void(const char*, std::size_t)>;
  using  FlushFunc = std::function<void()>;

  enum LogLevel { TRACE, DEBUG, INFO, WARN, ERROR, FATAL };
  
  static void defaultOutput(const char* msg, std::size_t len);

  static void defaultFlush();

  static   LogLevel getLogLevel();
  static OutputFunc getLogOutput();
  static  FlushFunc getLogFlush();

  static void setLogLevel(   LogLevel log_level);
  static void setLogOutput(OutputFunc log_output);
  static void setLogFlush(  FlushFunc log_flush);

 private:
  static   LogLevel log_level_;
  static OutputFunc log_output_;
  static  FlushFunc log_flush_;
};

} // namespace TinyLog

#endif
