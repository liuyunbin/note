
#include "iota.h"

#include <list>
#include <numeric>

#include <gtest/gtest.h>

TEST(test_numeric, test_iota) {
  std::list<int> li_1 = {1, 3, 5, 7, 9};
  std::list<int> li_2 = {0, 2, 4, 6, 8};
  int a = 1;
  std::iota(li_1.begin(), li_1.end(), a);
  liuyunbin::iota(li_2.begin(), li_2.end(), a);
  EXPECT_EQ(li_1, li_2);
}
