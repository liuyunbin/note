
#include "partial_sum.h"

#include <list>
#include <numeric>

#include <gtest/gtest.h>

TEST(test_numeric, test_partial_sum) {
  std::list<int> li_1 = {1, 3, 5, 7, 9};
  std::list<int> li_2 = {1, 3, 5, 7, 9};
  std::partial_sum(li_1.cbegin(), li_1.cend(), li_1.begin());
  liuyunbin::partial_sum(li_2.cbegin(), li_2.cend(), li_2.begin());
  EXPECT_EQ(li_1, li_2);
}
