
#include "is_heap_until.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_is_heap_until) {
  {
    std::string str = "0123456789";
    EXPECT_EQ(std::is_heap_until(str.begin(), str.end()),
              liuyunbin::is_heap_until(str.begin(), str.end()));
  }
  {
    std::string str = "012abc3456789";
    EXPECT_EQ(std::is_heap_until(str.begin(), str.end()),
              liuyunbin::is_heap_until(str.begin(), str.end()));
  }
}
