
#include <TinyLog/log_stream.h>
#include <gtest/gtest.h>

#include <cstdint>
#include <iostream>
#include <limits>
#include <string>

namespace {

TEST(LogStreamTest, bool) {
    {
        TinyLog::LogStream os;
        os << true;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::string("true"));
    }
    {
        TinyLog::LogStream os;
        os << false;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::string("false"));
    }
}

TEST(LogStreamTest, char) {
    {
        char ch = std::numeric_limits<char>::min();
        TinyLog::LogStream os;
        os << ch;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::string(1, ch));
    }
    {
        char ch = 1;
        TinyLog::LogStream os;
        os << ch;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::string(1, ch));
    }
    {
        char ch = std::numeric_limits<char>::max();
        TinyLog::LogStream os;
        os << ch;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::string(1, ch));
    }
}

TEST(LogStreamTest, short) {
    {
        short value = std::numeric_limits<short>::min();
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
    {
        short value = 1;
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
    {
        short value = std::numeric_limits<short>::max();
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
}

TEST(LogStreamTest, unsigned_short) {
    {
        unsigned short value = std::numeric_limits<unsigned short>::min();
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
    {
        unsigned short value = 1;
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
    {
        unsigned short value = std::numeric_limits<unsigned short>::max();
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
}

TEST(LogStreamTest, int) {
    {
        int value = std::numeric_limits<int>::min();
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
    {
        int value = 1;
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
    {
        int value = std::numeric_limits<int>::max();
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
}

TEST(LogStreamTest, unsigned_int) {
    {
        unsigned int value = std::numeric_limits<unsigned int>::min();
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
    {
        unsigned int value = 1;
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
    {
        unsigned int value = std::numeric_limits<unsigned int>::max();
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
}

TEST(LogStreamTest, long) {
    {
        long value = std::numeric_limits<long>::min();
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
    {
        long value = 1;
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
    {
        long value = std::numeric_limits<long>::max();
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
}

TEST(LogStreamTest, unsigned_long) {
    {
        unsigned long value = std::numeric_limits<unsigned long>::min();
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
    {
        unsigned long value = 1;
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
    {
        unsigned long value = std::numeric_limits<unsigned long>::max();
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
}

TEST(LogStreamTest, long_long) {
    {
        long long value = std::numeric_limits<long long>::min();
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
    {
        long long value = 1;
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
    {
        long long value = std::numeric_limits<long long>::max();
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
}

TEST(LogStreamTest, unsigned_long_long) {
    {
        unsigned long long value =
            std::numeric_limits<unsigned long long>::min();
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
    {
        unsigned long long value = 1;
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
    {
        unsigned long long value =
            std::numeric_limits<unsigned long long>::max();
        TinyLog::LogStream os;
        os << value;
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
    }
}

TEST(LogStreamTest, float) {
    float value = 1.23;
    TinyLog::LogStream os;
    os << value;
    EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
}

TEST(LogStreamTest, double) {
    double value = 1.23;
    TinyLog::LogStream os;
    os << value;
    EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
}

TEST(LogStreamTest, long_double) {
    long double value = 1.23;
    TinyLog::LogStream os;
    os << value;
    EXPECT_TRUE(std::string(os.data(), os.size()) == std::to_string(value));
}

TEST(LogStreamTest, char_ptr) {
    const char* p = "china";
    TinyLog::LogStream os;
    os << p;
    EXPECT_TRUE(std::string(os.data(), os.size()) == std::string(p));
}

TEST(LogStreamTest, void_ptr) {
    TinyLog::LogStream os;
    char ch;
    void* p = &ch;
    os << p;
    char buf[32];
    std::snprintf(buf, sizeof buf, "%p", p);
    EXPECT_TRUE(std::string(os.data(), os.size()) == std::string(buf));
}

TEST(LogStreamTest, string) {
    std::string st("123");
    TinyLog::LogStream os;
    os << st;
    EXPECT_TRUE(std::string(os.data(), os.size()) == st);
}

TEST(LogStreamTest, append) {
    {
        const char* p = "123";
        TinyLog::LogStream os1;
        os1.append(p);
        EXPECT_TRUE(std::string(os1.data(), os1.size()) == std::string(p));
    }
    {
        const char* p = "123456";
        TinyLog::LogStream os;
        os.append(p, 3);
        EXPECT_TRUE(std::string(os.data(), os.size()) == std::string(p, 3));
    }
}

}  // namespace
