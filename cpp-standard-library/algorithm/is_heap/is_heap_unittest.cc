
#include "is_heap.h"

#include <algorithm>
#include <cctype>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_is_heap) {
  {
    std::string str = "0123456789";
    EXPECT_EQ(std::is_heap(str.begin(), str.end()),
              liuyunbin::is_heap(str.begin(), str.end()));
  }
  {
    std::string str = "012abc3456789";
    EXPECT_EQ(std::is_heap(str.begin(), str.end()),
              liuyunbin::is_heap(str.begin(), str.end()));
  }
}
