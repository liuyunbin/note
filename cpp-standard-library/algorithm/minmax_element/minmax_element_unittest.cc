
#include "minmax_element.h"

#include <algorithm>
#include <initializer_list>

#include <gtest/gtest.h>

TEST(test_algorithm, test_minmax_element) {
  std::initializer_list<int> li = {1, 2, 3, 4, 5};
  EXPECT_EQ(std::minmax_element(li.begin(), li.end()),
            liuyunbin::minmax_element(li.begin(), li.end()));
}
