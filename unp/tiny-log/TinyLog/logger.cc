
#include <TinyLog/logger.h>

#include <cstdio>

namespace TinyLog {

void Logger::defaultOutput(const char* msg, std::size_t len) {
    std::fwrite(msg, 1, len, stdout);
}
void Logger::defaultFlush() { std::fflush(stdout); }

Logger::LogLevel Logger::getLogLevel() { return log_level_; }
Logger::OutputFunc Logger::getLogOutput() { return log_output_; }
Logger::FlushFunc Logger::getLogFlush() { return log_flush_; }

void Logger::setLogLevel(LogLevel log_level) { log_level_ = log_level; }
void Logger::setLogOutput(OutputFunc log_output) { log_output_ = log_output; }
void Logger::setLogFlush(FlushFunc log_flush) { log_flush_ = log_flush; }

Logger::LogLevel Logger::log_level_ = Logger::INFO;
Logger::OutputFunc Logger::log_output_ = Logger::defaultOutput;
Logger::FlushFunc Logger::log_flush_ = Logger::defaultFlush;

}  // namespace TinyLog
