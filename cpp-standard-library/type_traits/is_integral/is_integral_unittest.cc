
#include "is_integral.h"

#include <gtest/gtest.h>

#include <type_traits>

TEST(test_type_traits, test_is_integral) {
    EXPECT_EQ(std::is_integral<void>::value,
              liuyunbin::is_integral<void>::value);
    EXPECT_EQ(std::is_integral<const void>::value,
              liuyunbin::is_integral<const void>::value);
    EXPECT_EQ(std::is_integral<volatile void>::value,
              liuyunbin::is_integral<volatile void>::value);
    EXPECT_EQ(std::is_integral<const volatile void>::value,
              liuyunbin::is_integral<const volatile void>::value);

    EXPECT_EQ(std::is_integral<char>::value,
              liuyunbin::is_integral<char>::value);
    EXPECT_EQ(std::is_integral<signed char>::value,
              liuyunbin::is_integral<signed char>::value);
    EXPECT_EQ(std::is_integral<unsigned char>::value,
              liuyunbin::is_integral<unsigned char>::value);

    EXPECT_EQ(std::is_integral<short>::value,
              liuyunbin::is_integral<short>::value);
    EXPECT_EQ(std::is_integral<unsigned short>::value,
              liuyunbin::is_integral<unsigned short>::value);

    EXPECT_EQ(std::is_integral<int>::value, liuyunbin::is_integral<int>::value);
    EXPECT_EQ(std::is_integral<unsigned int>::value,
              liuyunbin::is_integral<unsigned int>::value);

    EXPECT_EQ(std::is_integral<long>::value,
              liuyunbin::is_integral<long>::value);
    EXPECT_EQ(std::is_integral<unsigned long>::value,
              liuyunbin::is_integral<unsigned long>::value);

    EXPECT_EQ(std::is_integral<long long>::value,
              liuyunbin::is_integral<long long>::value);
    EXPECT_EQ(std::is_integral<unsigned long long>::value,
              liuyunbin::is_integral<unsigned long long>::value);

    EXPECT_EQ(std::is_integral<float>::value,
              liuyunbin::is_integral<float>::value);
    EXPECT_EQ(std::is_integral<double>::value,
              liuyunbin::is_integral<double>::value);
    EXPECT_EQ(std::is_integral<long double>::value,
              liuyunbin::is_integral<long double>::value);

    EXPECT_EQ(std::is_integral<const int>::value,
              liuyunbin::is_integral<const int>::value);
}
