
#include "forward.h"

#include <string>

#include <gtest/gtest.h>

bool fun(std::string &&) { return true; }

bool fun(const std::string &) { return false; }

template <typename T> bool f(T &&t) { return fun(liuyunbin::forward<T>(t)); }

TEST(test_utility, test_forward) {
  std::string str = "1234";
  EXPECT_EQ(false, f(str));
  EXPECT_EQ(true, f(std::string("123")));
}
