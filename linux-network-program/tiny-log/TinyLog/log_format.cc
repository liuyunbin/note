
#include <TinyLog/log_format.h>

namespace TinyLog {

const char* LogFormat::data() const { return data_; }

LogStream& operator<<(LogStream& os, const LogFormat& fmt) {
  return os << fmt.data();
}

} // namespace TinyLog
