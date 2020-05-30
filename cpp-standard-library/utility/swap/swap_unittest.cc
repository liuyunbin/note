
#include "swap.h"

#include <string>

#include <gtest/gtest.h>

TEST(test_utility, test_swap) {
  std::string ve_1 = "234";
  std::string ve_2 = "456";

  liuyunbin::swap(ve_1, ve_2);
}
