
#include <TinyLog/log_append_file.h>

#include <cstring>

namespace TinyLog {

LogAppendFile::LogAppendFile(const char* filename) : fp_(std::fopen(filename, "a")), len_(0) {
}

LogAppendFile::LogAppendFile(const std::string& filename) : LogAppendFile(filename.data()) {
}

LogAppendFile::~LogAppendFile() { std::fclose(fp_); }

void LogAppendFile::append(const char* str, std::size_t len) { len_ += std::fwrite(str, 1, len, fp_); }

void LogAppendFile::append(const char*        str) { append(str,  std::strlen(str)); }
void LogAppendFile::append(const std::string& str) { append(str.data(), str.size()); }

std::size_t LogAppendFile::size() const { return      len_; }
void        LogAppendFile::flush()      { std::fflush(fp_); }

} // namespace TinyLog

