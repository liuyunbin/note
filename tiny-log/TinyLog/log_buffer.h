
#ifndef TINYLOG_LOG_BUFFER_H_
#define TINYLOG_LOG_BUFFER_H_

#include <cstddef>

namespace TinyLog {

class LogBuffer {
 public:
  LogBuffer();
  LogBuffer(const LogBuffer&);

  LogBuffer& operator=(const LogBuffer&);
  
  void append(const char* str);
  void append(const char* str, std::size_t len);

  const char*           data() const;
  std::size_t           size() const;
  std::size_t       max_size() const;
  std::size_t available_size() const;

  void clear();

 private:
  char        buf_[4 * 1024];
  std::size_t len_;
};

} // namespace TinyLog

#endif
