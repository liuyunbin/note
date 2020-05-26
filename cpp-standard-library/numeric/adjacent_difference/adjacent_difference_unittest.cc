
#include "adjacent_difference.h"

#include <list>
#include <numeric>

#include <gtest/gtest.h>

TEST(test_numeric, test_adjacent_difference) {
  std::list<int> li = {1, 2, 3, 4, 5};
  std::list<int> li_to_1 = {0, 0, 0, 0, 0};
  std::list<int> li_to_2 = {0, 0, 0, 0, 0};
  std::adjacent_difference(li.cbegin(), li.cend(), li_to_1.begin());
  liuyunbin::adjacent_difference(li.cbegin(), li.cend(), li_to_2.begin());
  EXPECT_EQ(li_to_1, li_to_2);
}
