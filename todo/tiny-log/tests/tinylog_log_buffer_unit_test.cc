
#include <TinyLog/log_buffer.h>
#include <gtest/gtest.h>

#include <iostream>
#include <string>

namespace {

TEST(LogBufferTest, append) {
    TinyLog::LogBuffer st;
    st.append("123");
    EXPECT_TRUE(std::string(st.data(), st.size()) == std::string("123"));
    st.clear();
    st.append("123456", 3);
    EXPECT_TRUE(std::string(st.data(), st.size()) == std::string("123"));
}

}  // namespace
