
#ifndef TINLOG_LOG_APPEND_FILE_H_
#define TINLOG_LOG_APPEND_FILE_H_

#include <cstddef>
#include <string>

namespace TinyLog {

class LogAppendFile {
  LogAppendFile(           const LogAppendFile&) = delete;
  LogAppendFile& operator=(const LogAppendFile&) = delete;

 public:
  explicit LogAppendFile(const std::string& filename);
  explicit LogAppendFile(const char*        filename);

  ~LogAppendFile();

  void append(const      char*   str, std::size_t len);
  void append(const      char*   str);
  void append(const std::string& str);

  void flush();

  std::size_t size() const;

 private:

  FILE*        fp_;
  std::size_t len_;
};

} // namespace TinyLog

#endif
