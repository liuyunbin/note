#ifndef TINYLOG_LOGGING_H_
#define TINYLOG_LOGGING_H_

#include <TinyLog/log_format.h>
#include <TinyLog/log_stream.h>
#include <TinyLog/logger.h>

namespace TinyLog {

class Logging {
 public:
  Logging(           const Logging&) = delete;
  Logging& operator=(const Logging&) = delete;

  Logging(const char* file_name, int line, Logger::LogLevel level, const char* func);
  
  ~Logging();

  LogStream& stream();
  
 private:
  LogStream        stream_;
  Logger::LogLevel  level_;
};

#define LOG_TRACE if (TinyLog::Logger::getLogLevel() <= TinyLog::Logger::TRACE) \
                      TinyLog::Logging(__FILE__, __LINE__, TinyLog::Logger::TRACE, __func__).stream()
#define LOG_DEBUG if (TinyLog::Logger::getLogLevel() <= TinyLog::Logger::DEBUG) \
                      TinyLog::Logging(__FILE__, __LINE__, TinyLog::Logger::DEBUG, __func__).stream()
#define LOG_INFO  if (TinyLog::Logger::getLogLevel() <= TinyLog::Logger::INFO)  \
                      TinyLog::Logging(__FILE__, __LINE__, TinyLog::Logger::INFO,  __func__).stream()
#define LOG_WARN      TinyLog::Logging(__FILE__, __LINE__, TinyLog::Logger::WARN,  __func__).stream()
#define LOG_ERROR     TinyLog::Logging(__FILE__, __LINE__, TinyLog::Logger::ERROR, __func__).stream()
#define LOG_FATAL     TinyLog::Logging(__FILE__, __LINE__, TinyLog::Logger::FATAL, __func__).stream()

#define LOG_FORMAT TinyNet::LogFormat

} // namespace TinyLog

#endif
