
#include <TinyLog/log_file.h>
#include <TinyLog/time_stamp.h>
#include <unistd.h>

#include <utility>

namespace TinyLog {

LogFile::LogFile(std::string file_name, std::size_t roll_size,
                 std::time_t flush_interval)
    : file_name_(std::move(file_name)),
      roll_size_(roll_size),
      flush_interval_(flush_interval),
      start_of_period_(0),
      last_roll_(0),
      last_flush_(0) {
    rollFile();
}

void LogFile::append(const char* logline, std::size_t len) {
    file_->append(logline, len);

    TimeStamp val;
    std::time_t seconds = val.getSeconds();
    if (seconds <= last_roll_) return;
    if (file_->size() >= roll_size_) {
        rollFile(val);
        return;
    }
    std::time_t this_period_ = seconds / kRollPerSeconds * kRollPerSeconds;
    if (this_period_ != start_of_period_) {
        rollFile(val);
        return;
    }
    if (seconds - last_flush_ > flush_interval_) {
        last_flush_ = seconds;
        flush();
    }
}

void LogFile::flush() { file_->flush(); }

void LogFile::rollFile(const TimeStamp& val) {
    std::time_t seconds = val.getSeconds();
    last_roll_ = seconds;
    last_flush_ = seconds;
    start_of_period_ = seconds / kRollPerSeconds * kRollPerSeconds;

    char buf_hostname[256];
    ::gethostname(buf_hostname, sizeof(buf_hostname));
    char buf[1024];
    std::snprintf(buf, sizeof buf, "%s.%s.%s.%d.log", file_name_.data(),
                  val.data(), buf_hostname, static_cast<int>(::getpid()));
    file_.reset(new LogAppendFile(buf));
}

}  // namespace TinyLog
