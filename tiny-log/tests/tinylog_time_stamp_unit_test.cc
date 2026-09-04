
#include <TinyLog/time_stamp.h>
#include <gtest/gtest.h>

#include <iostream>

namespace {

TEST(TimeStampTest, constructor) {
    TinyLog::TimeStamp t1;
    TinyLog::TimeStamp t2(t1);
    EXPECT_TRUE(t1 == t2);
}

TEST(TimeStampTest, assignment) {
    TinyLog::TimeStamp t1;
    TinyLog::TimeStamp t2;
    t2 = t1;
    EXPECT_TRUE(t1 == t2);
    EXPECT_FALSE(t1 != t2);
    EXPECT_FALSE(t1 < t2);
    EXPECT_TRUE(t1 <= t2);
    EXPECT_FALSE(t1 > t2);
    EXPECT_TRUE(t1 >= t2);
}

TEST(TimeStampTest, data) {
    TinyLog::TimeStamp t1;
    std::cout << t1.data() << std::endl;
}

}  // namespace
