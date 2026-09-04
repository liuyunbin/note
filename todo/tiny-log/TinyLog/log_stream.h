#ifndef TINYLOG_LOG_STREAM_H_
#define TINYLOG_LOG_STREAM_H_

#include <TinyLog/log_buffer.h>

#include <string>

namespace TinyLog {

class LogStream {
 public:
  LogStream(            const LogStream&) = delete;
  LogStream& operator= (const LogStream&) = delete;

  LogStream() = default;

  LogStream& operator<<(         bool);
  LogStream& operator<<(         char);
  LogStream& operator<<(         short);
  LogStream& operator<<(unsigned short);
  LogStream& operator<<(         int);
  LogStream& operator<<(unsigned int);
  LogStream& operator<<(         long);
  LogStream& operator<<(unsigned long);
  LogStream& operator<<(         long long);
  LogStream& operator<<(unsigned long long);
  LogStream& operator<<(      float);
  LogStream& operator<<(     double);
  LogStream& operator<<(long double);
  LogStream& operator<<(const char*);
  LogStream& operator<<(const void*);
  LogStream& operator<<(const std::string&);
 
  LogStream& append(const char*);
  LogStream& append(const char*, std::size_t);
  
  const char* data() const;
  std::size_t size() const;

 private:
  LogBuffer log_buffer_;
};

} // namespace TinyLog

#endif
