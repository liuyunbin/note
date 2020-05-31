
#include "prev.h"

#include <iterator>
#include <list>
#include <string>

#include <gtest/gtest.h>

TEST(test_iterator, test_prev) {
  {
    std::string str = "123456789";

    auto it_1 = str.end();
    auto it_2 = str.end();

    EXPECT_EQ(liuyunbin::prev(it_1, 5), std::prev(it_2, 5));
  }
  {
    std::list<int> li = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto it_1 = li.end();
    auto it_2 = li.end();

    EXPECT_EQ(liuyunbin::prev(it_1, 5), std::prev(it_2, 5));
  }
}
