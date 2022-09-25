
#include <TinyLog/time_stamp.h>
#include <sys/time.h>
#include <time.h>

#include <cstdio>

namespace {

std::uint64_t kMicroSecondsPerSecond = 1000 * 1000;

}  // namespace

namespace TinyLog {

thread_local char buf[32];
thread_local std::time_t last_seconds;
TimeStamp::TimeStamp() {
    struct timeval current_time;
    ::gettimeofday(&current_time, NULL);
    micro_seconds_ = static_cast<std::uint64_t>(current_time.tv_sec) *
                         kMicroSecondsPerSecond +
                     current_time.tv_usec;

    auto seconds = getSeconds();

    if (seconds != last_seconds) {
        last_seconds = seconds;
        std::tm tm_time;
        ::localtime_r(&seconds, &tm_time);
        std::snprintf(buf, sizeof(buf), "%4d%02d%02d-%02d:%02d:%02d",
                      tm_time.tm_year + 1900, tm_time.tm_mon + 1,
                      tm_time.tm_mday, tm_time.tm_hour, tm_time.tm_min,
                      tm_time.tm_sec);
    }
    std::snprintf(buf + 18, sizeof(buf) - 18, "%06d",
                  static_cast<int>(micro_seconds_ % kMicroSecondsPerSecond));
}

std::time_t TimeStamp::getSeconds() const {
    return static_cast<std::time_t>(micro_seconds_ / kMicroSecondsPerSecond);
}
std::uint64_t TimeStamp::getMicroSeconds() const { return micro_seconds_; }

const char* TimeStamp::data() const { return buf; }

bool operator<(const TimeStamp& lhs, const TimeStamp& rhs) {
    return lhs.getMicroSeconds() < rhs.getMicroSeconds();
}
bool operator<=(const TimeStamp& lhs, const TimeStamp& rhs) {
    return lhs.getMicroSeconds() <= rhs.getMicroSeconds();
}
bool operator>(const TimeStamp& lhs, const TimeStamp& rhs) {
    return lhs.getMicroSeconds() > rhs.getMicroSeconds();
}
bool operator>=(const TimeStamp& lhs, const TimeStamp& rhs) {
    return lhs.getMicroSeconds() >= rhs.getMicroSeconds();
}
bool operator==(const TimeStamp& lhs, const TimeStamp& rhs) {
    return lhs.getMicroSeconds() == rhs.getMicroSeconds();
}
bool operator!=(const TimeStamp& lhs, const TimeStamp& rhs) {
    return lhs.getMicroSeconds() != rhs.getMicroSeconds();
}

}  // namespace TinyLog
