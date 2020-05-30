
#include "move.h"

#include <string>

#include <gtest/gtest.h>

TEST(test_utility, test_move) {
  std::string ve_1 = "1234";
  std::string ve_2 = "1234";
  std::string ve_3 = liuyunbin::move(ve_2);
  std::string ve_4;

  EXPECT_EQ(ve_1, ve_3);
  EXPECT_EQ(ve_2, ve_4);
}
