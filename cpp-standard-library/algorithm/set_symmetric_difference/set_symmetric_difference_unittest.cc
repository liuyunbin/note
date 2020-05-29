
#include "set_symmetric_difference.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_set_symmetric_difference) {
  std::string str_1 = "13579";
  std::string str_2 = "12345";
  std::string str_3 = "11111111111111111";
  std::string str_4 = "11111111111111111";
  std::set_symmetric_difference(str_1.begin(), str_1.end(), str_2.begin(),
                                str_2.end(), str_3.begin());
  liuyunbin::set_symmetric_difference(str_1.begin(), str_1.end(), str_2.begin(),
                                      str_2.end(), str_4.begin());
  EXPECT_EQ(str_3, str_4);
}
