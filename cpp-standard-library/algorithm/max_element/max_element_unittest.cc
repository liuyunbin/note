
#include "max_element.h"

#include <algorithm>
#include <initializer_list>

#include <gtest/gtest.h>

TEST(test_algorithm, test_max_element) {
  std::initializer_list<int> li = {1, 2, 3, 4, 5};
  EXPECT_EQ(std::max_element(li.begin(), li.end()),
            liuyunbin::max_element(li.begin(), li.end()));
}
