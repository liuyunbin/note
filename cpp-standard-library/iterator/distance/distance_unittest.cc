
#include "distance.h"

#include <iterator>
#include <list>
#include <string>

#include <gtest/gtest.h>

TEST(test_iterator, test_distance) {
  {
    std::string str = "123456789";

    auto it_1 = str.begin();
    auto it_2 = str.end();

    EXPECT_EQ(liuyunbin::distance(it_1, it_2), std::distance(it_1, it_2));
  }
  {
    std::list<int> li = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto it_1 = li.begin();
    auto it_2 = li.end();

    EXPECT_EQ(liuyunbin::distance(it_1, it_2), std::distance(it_1, it_2));
  }
}
