
#include <TinyLog/log_strerror.h>
#include <TinyLog/logging.h>
#include <TinyLog/time_stamp.h>

#include <cstdlib>
#include <cstring>

namespace TinyLog {

Logging::Logging(const char* file_name, int line, Logger::LogLevel level,
                 const char* func)
    : level_(level) {
    static const char* LogLevelName[] = {"TRACE", "DEBUG", "INFO ",
                                         "WARN ", "ERROR", "FATAL"};

    stream_ << TimeStamp().data() << " " << LogLevelName[level] << " "
            << file_name << ":" << line << " " << func << " ";
}

Logging::~Logging() {
    if (errno != 0) stream_ << log_strerror();
    stream_ << "\n";
    Logger::getLogOutput()(stream_.data(), stream_.size());
    if (level_ == Logger::FATAL) {
        Logger::getLogFlush()();
        std::abort();
    }
}

LogStream& Logging::stream() { return stream_; }

}  // namespace TinyLog
