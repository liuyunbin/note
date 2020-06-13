
#include "partial_sort_copy.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_partial_sort_copy) {
  // 随机迭代器
  std::string str_1 = "98653";
  std::string str_2 = "98653";
  std::string str_3 = "11111";
  std::string str_4 = "11111";
  std::partial_sort_copy(str_1.begin(), str_1.end(), str_3.begin(),
                         str_3.end());
  liuyunbin::partial_sort_copy(str_2.begin(), str_2.end(), str_4.begin(),
                               str_4.end());
  EXPECT_EQ(str_3, str_4);
}
