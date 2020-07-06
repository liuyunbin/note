
#include <TinyNet/buffer.h>

#include <sys/uio.h>

#include <cstring>
#include <algorithm>

namespace TinyNet {

Buffer::Buffer(std::size_t initialSize)
  : buffer_(kCheapPrepend + initialSize),
    reader_index_(kCheapPrepend),
    writer_index_(kCheapPrepend) {
}

std::string Buffer::read() {
  std::string result(buffer_.begin() + static_cast<std::ptrdiff_t>(reader_index_),
                     buffer_.begin() + static_cast<std::ptrdiff_t>(writer_index_));
  reader_index_ = kCheapPrepend;
  writer_index_ = kCheapPrepend;
  return result;
}

char*       Buffer::data() { return buffer_.data() + static_cast<std::ptrdiff_t>(reader_index_); }
std::size_t Buffer::size() { return static_cast<std::ptrdiff_t>(writer_index_) - static_cast<std::ptrdiff_t>(reader_index_); }
void        Buffer::read(std::size_t n) { reader_index_ += n; }

void Buffer::append_head(const std::string& str) {
  append_head(str.data(), str.size());
}

void Buffer::append_head(const char* data) {
  append_head(data, std::strlen(data));
}

void Buffer::append_head(const char* data, std::size_t len) {
  std::copy(data, data + len, buffer_.begin() + static_cast<std::ptrdiff_t>(reader_index_ - len));
  reader_index_ -= len;
}

void Buffer::append(const std::string& str) {
  append(str.data(), str.size());
}

void Buffer::append(const char* data) {
  append(data, std::strlen(data));
}

void Buffer::append(const char* data, std::size_t len) {
  if (buffer_.size() - writer_index_ < len)
    buffer_.resize(writer_index_ + len);
  std::copy(data, data + len, buffer_.begin() + static_cast<std::ptrdiff_t>(writer_index_));
  writer_index_ += len;
}

ssize_t Buffer::readFd(int fd) {
  char buf[65536];
  struct iovec vec[2];
  vec[0].iov_base = buffer_.data() + writer_index_;
  vec[0].iov_len  = buffer_.size() - writer_index_;
  vec[1].iov_base = buf;
  vec[1].iov_len = sizeof(buf);
  const ssize_t n = ::readv(fd, vec, 2);
  if (static_cast<std::size_t>(n) <= buffer_.size() - writer_index_) {
    writer_index_ += static_cast<std::size_t>(n);
  }
  else {
    auto k = static_cast<std::size_t>(n) - (buffer_.size() - writer_index_);
    writer_index_ = buffer_.size();
    append(buf, k);
  }
  return n;
}

} // namespace TinyNet
