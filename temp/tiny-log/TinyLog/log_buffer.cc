
#include <TinyLog/log_buffer.h>

#include <cstring>

namespace TinyLog {

LogBuffer::LogBuffer() : len_(0) {}
LogBuffer::LogBuffer(const LogBuffer& other) : len_(other.size()) {
    std::memcpy(buf_, other.data(), other.size());
}

LogBuffer& LogBuffer::operator=(const LogBuffer& other) {
    len_ = other.size();
    std::memcpy(buf_, other.data(), other.size());
    return *this;
}

void LogBuffer::append(const char* str, std::size_t len) {
    if (available_size() >= len) {
        std::memcpy(buf_ + len_, str, len);
        len_ += len;
    }
}

void LogBuffer::append(const char* str) { append(str, std::strlen(str)); }

const char* LogBuffer::data() const { return buf_; }
std::size_t LogBuffer::size() const { return len_; }
std::size_t LogBuffer::max_size() const { return sizeof(buf_); }
std::size_t LogBuffer::available_size() const { return max_size() - size(); }

void LogBuffer::clear() { len_ = 0; }

}  // namespace TinyLog
