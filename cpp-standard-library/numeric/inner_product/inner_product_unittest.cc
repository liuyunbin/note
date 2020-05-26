
#include "inner_product.h"

#include <list>
#include <numeric>

#include <gtest/gtest.h>

TEST(test_numeric, test_inner_product) {
  std::list<int> li_1 = {1, 3, 5, 7, 9};
  std::list<int> li_2 = {0, 2, 4, 6, 8};
  int a = 1;
  int x = std::inner_product(li_1.cbegin(), li_1.cend(), li_2.cbegin(), a);
  int y =
      liuyunbin::inner_product(li_1.cbegin(), li_1.cend(), li_2.cbegin(), a);
  EXPECT_EQ(x, y);
}
