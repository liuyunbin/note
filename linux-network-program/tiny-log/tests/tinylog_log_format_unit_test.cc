
#include <TinyLog/log_format.h>

#include <gtest/gtest.h>

#include <string>

namespace {

TEST(LogFormatTest, construct) {
  TinyLog::LogFormat os("test: %d", 100);
  EXPECT_TRUE(std::string(os.data()) == std::string("test: 100"));
}

}  // namespace
