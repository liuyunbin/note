
#include "next.h"

#include <iterator>
#include <list>
#include <string>

#include <gtest/gtest.h>

TEST(test_iterator, test_next) {
  {
    std::string str = "123456789";

    auto it_1 = str.begin();
    auto it_2 = str.begin();

    EXPECT_EQ(liuyunbin::next(it_1, 5), std::next(it_2, 5));
  }
  {
    std::list<int> li = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto it_1 = li.begin();
    auto it_2 = li.begin();

    EXPECT_EQ(liuyunbin::next(it_1, 5), std::next(it_2, 5));
  }
}
