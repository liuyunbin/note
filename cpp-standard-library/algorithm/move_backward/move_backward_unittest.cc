
#include "move_backward.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_move_backward) {
  std::string str_from_1 = "1234";
  std::string str_from_2 = "1234";
  std::string str_to_1 = "abcd";
  std::string str_to_2 = "abcd";
  std::move_backward(str_from_1.begin(), str_from_1.end(), str_to_1.end());
  liuyunbin::move_backward(str_from_2.begin(), str_from_2.end(),
                           str_to_2.end());
  EXPECT_EQ(str_from_1, str_from_2);
  EXPECT_EQ(str_to_1, str_to_2);
}
