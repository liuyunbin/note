
#include <TinyLog/log_stream.h>

namespace TinyLog {

LogStream& LogStream::operator<<(bool value) {
    return append(value ? "true" : "false");
}
LogStream& LogStream::operator<<(char value) { return append(&value, 1); }

LogStream& LogStream::operator<<(short value) {
    char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "%hd", value);
    return append(buffer);
}

LogStream& LogStream::operator<<(unsigned short value) {
    char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "%hu", value);
    return append(buffer);
}

LogStream& LogStream::operator<<(int value) {
    char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "%d", value);
    return append(buffer);
}

LogStream& LogStream::operator<<(unsigned int value) {
    char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "%u", value);
    return append(buffer);
}

LogStream& LogStream::operator<<(long value) {
    char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "%ld", value);
    return append(buffer);
}

LogStream& LogStream::operator<<(unsigned long value) {
    char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "%lu", value);
    return append(buffer);
}

LogStream& LogStream::operator<<(long long value) {
    char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "%lld", value);
    return append(buffer);
}

LogStream& LogStream::operator<<(unsigned long long value) {
    char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "%llu", value);
    return append(buffer);
}

LogStream& LogStream::operator<<(float value) {
    char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "%f", value);
    return append(buffer);
}

LogStream& LogStream::operator<<(double value) {
    char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "%f", value);
    return append(buffer);
}

LogStream& LogStream::operator<<(long double value) {
    char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "%Lf", value);
    return append(buffer);
}

LogStream& LogStream::operator<<(const void* str) {
    char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "%p", str);
    return append(buffer);
}

LogStream& LogStream::operator<<(const char* str) { return append(str); }

LogStream& LogStream::operator<<(const std::string& str) {
    return append(str.data(), str.size());
}

LogStream& LogStream::append(const char* str, std::size_t len) {
    log_buffer_.append(str, len);
    return *this;
}

LogStream& LogStream::append(const char* str) {
    log_buffer_.append(str);
    return *this;
}

const char* LogStream::data() const { return log_buffer_.data(); }
std::size_t LogStream::size() const { return log_buffer_.size(); }

}  // namespace TinyLog
