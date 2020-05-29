
#include "array.h"

#include <array>

#include <gtest/gtest.h>

// 显示实例化
template class liuyunbin::array<int, 5>;

TEST(test_array, test_array) {
  liuyunbin::array<int, 5> arr_1 = {0, 1, 2, 3, 4};
  liuyunbin::array<int, 5> arr_2 = {5, 6, 7, 8, 9};

  arr_1.swap(arr_2);

  EXPECT_NE(arr_1, arr_2);
}
