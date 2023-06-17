#ifndef TINYLOG_TIME_STAMP_H_
#define TINYLOG_TIME_STAMP_H_

#include <cstdint>
#include <ctime>

namespace TinyLog {

class TimeStamp {
 public:
  TimeStamp(           const TimeStamp& other) = default;
  TimeStamp& operator=(const TimeStamp& other) = default;

  TimeStamp();

  std::time_t   getSeconds()      const;
  std::uint64_t getMicroSeconds() const;

  const char* data() const;
 
 private:
  std::uint64_t micro_seconds_;
};

bool operator< (const TimeStamp& lhs, const TimeStamp& rhs);
bool operator<=(const TimeStamp& lhs, const TimeStamp& rhs);
bool operator> (const TimeStamp& lhs, const TimeStamp& rhs);
bool operator>=(const TimeStamp& lhs, const TimeStamp& rhs);
bool operator==(const TimeStamp& lhs, const TimeStamp& rhs);
bool operator!=(const TimeStamp& lhs, const TimeStamp& rhs);

} // namespace TinyLog

#endif
