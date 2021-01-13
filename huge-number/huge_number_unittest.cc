
#include "huge_number.h"

#include <gtest/gtest.h>

TEST(test_huge_number, test_check_digit_string_is_valid_and_format) {
  EXPECT_STREQ("-12", check_digit_string_is_valid_and_format("-12").data());
  EXPECT_STREQ("-12", check_digit_string_is_valid_and_format(" -12").data());
  EXPECT_STREQ("-12", check_digit_string_is_valid_and_format("   -12").data());

  EXPECT_STREQ("0", check_digit_string_is_valid_and_format("0").data());
  EXPECT_STREQ("0", check_digit_string_is_valid_and_format(" 0").data());
  EXPECT_STREQ("0", check_digit_string_is_valid_and_format("  0").data());
  EXPECT_STREQ("0", check_digit_string_is_valid_and_format("+0").data());
  EXPECT_STREQ("0", check_digit_string_is_valid_and_format(" +0").data());
  EXPECT_STREQ("0", check_digit_string_is_valid_and_format("  +0").data());
  EXPECT_STREQ("0", check_digit_string_is_valid_and_format("-0").data());
  EXPECT_STREQ("0", check_digit_string_is_valid_and_format(" -0").data());
  EXPECT_STREQ("0", check_digit_string_is_valid_and_format("  -0").data());

  EXPECT_STREQ("12", check_digit_string_is_valid_and_format("12").data());
  EXPECT_STREQ("12", check_digit_string_is_valid_and_format(" 12").data());
  EXPECT_STREQ("12", check_digit_string_is_valid_and_format("  12").data());
  EXPECT_STREQ("12", check_digit_string_is_valid_and_format("+12").data());
  EXPECT_STREQ("12", check_digit_string_is_valid_and_format(" +12").data());
  EXPECT_STREQ("12", check_digit_string_is_valid_and_format("  +12").data());
}

TEST(test_huge_number, test_compare_huge_number) {
  EXPECT_EQ(compare_huge_number("-123", "-1234"), 1);
  EXPECT_EQ(compare_huge_number("-123", "-123"), 0);
  EXPECT_EQ(compare_huge_number("-123", "-12"), -1);
  EXPECT_EQ(compare_huge_number("-123", "0"), -1);
  EXPECT_EQ(compare_huge_number("-123", "12"), -1);
  EXPECT_EQ(compare_huge_number("-123", "123"), -1);
  EXPECT_EQ(compare_huge_number("-123", "1234"), -1);

  EXPECT_EQ(compare_huge_number("0", "-123"), 1);
  EXPECT_EQ(compare_huge_number("0", "0"), 0);
  EXPECT_EQ(compare_huge_number("0", "123"), -1);

  EXPECT_EQ(compare_huge_number("123", "-1234"), 1);
  EXPECT_EQ(compare_huge_number("123", "-123"), 1);
  EXPECT_EQ(compare_huge_number("123", "-12"), 1);
  EXPECT_EQ(compare_huge_number("123", "0"), 1);
  EXPECT_EQ(compare_huge_number("123", "12"), 1);
  EXPECT_EQ(compare_huge_number("123", "123"), 0);
  EXPECT_EQ(compare_huge_number("123", "1234"), -1);
}

TEST(test_huge_number, test_add_huge_number) {
  EXPECT_STREQ(add_huge_number("-123", "-1234").data(), "-1357");
  EXPECT_STREQ(add_huge_number("-123", "-123").data(), "-246");
  EXPECT_STREQ(add_huge_number("-123", "-12").data(), "-135");
  EXPECT_STREQ(add_huge_number("-123", "0").data(), "-123");
  EXPECT_STREQ(add_huge_number("-123", "12").data(), "-111");
  EXPECT_STREQ(add_huge_number("-123", "123").data(), "0");
  EXPECT_STREQ(add_huge_number("-123", "1234").data(), "1111");
  EXPECT_STREQ(add_huge_number("0", "-123").data(), "-123");
  EXPECT_STREQ(add_huge_number("0", "0").data(), "0");
  EXPECT_STREQ(add_huge_number("0", "123").data(), "123");
  EXPECT_STREQ(add_huge_number("123", "-1234").data(), "-1111");
  EXPECT_STREQ(add_huge_number("123", "-123").data(), "0");
  EXPECT_STREQ(add_huge_number("123", "-12").data(), "111");
  EXPECT_STREQ(add_huge_number("123", "0").data(), "123");
  EXPECT_STREQ(add_huge_number("123", "123").data(), "246");
  EXPECT_STREQ(add_huge_number("123", "1234").data(), "1357");
  EXPECT_STREQ(
      add_huge_number("12345678901234567890", "12345678901234567890").data(),
      "24691357802469135780");
}

TEST(test_huge_number, test_sub_huge_number) {
  EXPECT_STREQ(sub_huge_number("-123", "-1234").data(), "1111");
  EXPECT_STREQ(sub_huge_number("-123", "-123").data(), "0");
  EXPECT_STREQ(sub_huge_number("-123", "-12").data(), "-111");
  EXPECT_STREQ(sub_huge_number("-123", "0").data(), "-123");
  EXPECT_STREQ(sub_huge_number("-123", "12").data(), "-135");
  EXPECT_STREQ(sub_huge_number("-123", "123").data(), "-246");
  EXPECT_STREQ(sub_huge_number("-123", "1234").data(), "-1357");
  EXPECT_STREQ(sub_huge_number("0", "-123").data(), "123");
  EXPECT_STREQ(sub_huge_number("0", "0").data(), "0");
  EXPECT_STREQ(sub_huge_number("0", "123").data(), "-123");
  EXPECT_STREQ(sub_huge_number("123", "-1234").data(), "1357");
  EXPECT_STREQ(sub_huge_number("123", "-123").data(), "246");
  EXPECT_STREQ(sub_huge_number("123", "-12").data(), "135");
  EXPECT_STREQ(sub_huge_number("123", "0").data(), "123");
  EXPECT_STREQ(sub_huge_number("123", "123").data(), "0");
  EXPECT_STREQ(sub_huge_number("123", "1234").data(), "-1111");
  EXPECT_STREQ(
      sub_huge_number("24691357802469135780", "12345678901234567890").data(),
      "12345678901234567890");
}

TEST(test_huge_number, test_mul_huge_number) {
  EXPECT_STREQ(mul_huge_number("-123", "-1234").data(), "151782");
  EXPECT_STREQ(mul_huge_number("-123", "-123").data(), "15129");
  EXPECT_STREQ(mul_huge_number("-123", "-12").data(), "1476");
  EXPECT_STREQ(mul_huge_number("-123", "0").data(), "0");
  EXPECT_STREQ(mul_huge_number("-123", "12").data(), "-1476");
  EXPECT_STREQ(mul_huge_number("-123", "123").data(), "-15129");
  EXPECT_STREQ(mul_huge_number("-123", "1234").data(), "-151782");
  EXPECT_STREQ(mul_huge_number("0", "-123").data(), "0");
  EXPECT_STREQ(mul_huge_number("0", "0").data(), "0");
  EXPECT_STREQ(mul_huge_number("0", "123").data(), "0");
  EXPECT_STREQ(mul_huge_number("123", "-1234").data(), "-151782");
  EXPECT_STREQ(mul_huge_number("123", "-123").data(), "-15129");
  EXPECT_STREQ(mul_huge_number("123", "-12").data(), "-1476");
  EXPECT_STREQ(mul_huge_number("123", "0").data(), "0");
  EXPECT_STREQ(mul_huge_number("123", "123").data(), "15129");
  EXPECT_STREQ(mul_huge_number("123", "1234").data(), "151782");
  EXPECT_STREQ(mul_huge_number("2", "12345678901234567890").data(),
               "24691357802469135780");
}

TEST(test_huge_number, test_div_huge_number) {
  EXPECT_STREQ(div_huge_number("-123", "-1234").data(), "0");
  EXPECT_STREQ(div_huge_number("-123", "-123").data(), "1");
  EXPECT_STREQ(div_huge_number("-123", "-12").data(), "10");
  EXPECT_STREQ(div_huge_number("-123", "12").data(), "-10");
  EXPECT_STREQ(div_huge_number("-123", "123").data(), "-1");
  EXPECT_STREQ(div_huge_number("-123", "1234").data(), "0");
  EXPECT_STREQ(div_huge_number("0", "-123").data(), "0");
  EXPECT_STREQ(div_huge_number("0", "123").data(), "0");
  EXPECT_STREQ(div_huge_number("123", "-1234").data(), "0");
  EXPECT_STREQ(div_huge_number("123", "-123").data(), "-1");
  EXPECT_STREQ(div_huge_number("123", "-12").data(), "-10");
  EXPECT_STREQ(div_huge_number("123", "123").data(), "1");
  EXPECT_STREQ(div_huge_number("123", "1234").data(), "0");
  EXPECT_STREQ(
      div_huge_number("24691357802469135780", "12345678901234567890").data(),
      "2");
}
