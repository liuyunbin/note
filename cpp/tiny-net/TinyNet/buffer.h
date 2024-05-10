
#ifndef TINYNET_BUFFER_H_
#define TINYNET_BUFFER_H_

#include <cstdio>

#include <string>
#include <vector>

namespace TinyNet {

class Buffer {
 public:
  static constexpr std::size_t kCheapPrepend = 8;

  explicit Buffer(std::size_t initialSize = 1024);

  std::string read();

  char*       data();
  std::size_t size();
  void read(std::size_t n);

  void append_head(const std::string& str);
  void append_head(const char* data);
  void append_head(const char* data, std::size_t len);

  void append(const std::string& str);
  void append(const char* data);
  void append(const char* data, std::size_t len);

  ssize_t readFd(int fd);

 private:
  std::vector<char> buffer_;
  std::size_t reader_index_;
  std::size_t writer_index_;
};

} // namespace TinyNet

#endif
