
#include "push_heap.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_push_heap) {
  {
    std::string str_1 = "98653";
    std::string str_2 = "98653";
    std::push_heap(str_1.begin(), str_1.end());
    liuyunbin::push_heap(str_2.begin(), str_2.end());
    EXPECT_EQ(str_1, str_2);
  }
  {
    std::string str_1 = "98657";
    std::string str_2 = "98657";
    std::push_heap(str_1.begin(), str_1.end());
    liuyunbin::push_heap(str_2.begin(), str_2.end());
    EXPECT_EQ(str_1, str_2);
  }
}
