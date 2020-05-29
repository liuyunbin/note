
#include "sort_heap.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_sort_heap) {
  {
    std::string str_1 = "98653";
    std::string str_2 = "98653";
    std::sort_heap(str_1.begin(), str_1.end());
    liuyunbin::sort_heap(str_2.begin(), str_2.end());
    EXPECT_EQ(str_1, str_2);
  }
  {
    std::string str_1 = "98765";
    std::string str_2 = "98765";
    std::sort_heap(str_1.begin(), str_1.end());
    liuyunbin::sort_heap(str_2.begin(), str_2.end());
    EXPECT_EQ(str_1, str_2);
  }
}
