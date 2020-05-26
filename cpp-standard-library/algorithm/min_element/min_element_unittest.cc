
#include "min_element.h"

#include <algorithm>
#include <initializer_list>

#include <gtest/gtest.h>

TEST(test_algorithm, test_min_element) {
  std::initializer_list<int> li = {1, 2, 3, 4, 5};
  EXPECT_EQ(std::min_element(li.begin(), li.end()),
            liuyunbin::min_element(li.begin(), li.end()));
}
