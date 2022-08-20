
#include "is_void.h"

#include <type_traits>

#include <gtest/gtest.h>

TEST(test_type_traits, test_is_void) {
  EXPECT_EQ(std::is_void<void>::value, liuyunbin::is_void<void>::value);
  EXPECT_EQ(std::is_void<const void>::value,
            liuyunbin::is_void<const void>::value);
  EXPECT_EQ(std::is_void<volatile void>::value,
            liuyunbin::is_void<volatile void>::value);
  EXPECT_EQ(std::is_void<const volatile void>::value,
            liuyunbin::is_void<const volatile void>::value);

  EXPECT_EQ(std::is_void<char>::value, liuyunbin::is_void<char>::value);
  EXPECT_EQ(std::is_void<signed char>::value,
            liuyunbin::is_void<signed char>::value);
  EXPECT_EQ(std::is_void<unsigned char>::value,
            liuyunbin::is_void<unsigned char>::value);

  EXPECT_EQ(std::is_void<short>::value, liuyunbin::is_void<short>::value);
  EXPECT_EQ(std::is_void<unsigned short>::value,
            liuyunbin::is_void<unsigned short>::value);

  EXPECT_EQ(std::is_void<int>::value, liuyunbin::is_void<int>::value);
  EXPECT_EQ(std::is_void<unsigned int>::value,
            liuyunbin::is_void<unsigned int>::value);

  EXPECT_EQ(std::is_void<long>::value, liuyunbin::is_void<long>::value);
  EXPECT_EQ(std::is_void<unsigned long>::value,
            liuyunbin::is_void<unsigned long>::value);

  EXPECT_EQ(std::is_void<long long>::value,
            liuyunbin::is_void<long long>::value);
  EXPECT_EQ(std::is_void<unsigned long long>::value,
            liuyunbin::is_void<unsigned long long>::value);

  EXPECT_EQ(std::is_void<float>::value, liuyunbin::is_void<float>::value);
  EXPECT_EQ(std::is_void<double>::value, liuyunbin::is_void<double>::value);
  EXPECT_EQ(std::is_void<long double>::value,
            liuyunbin::is_void<long double>::value);
}
