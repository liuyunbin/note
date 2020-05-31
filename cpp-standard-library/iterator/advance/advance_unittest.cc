
#include "advance.h"

#include <iterator>
#include <list>
#include <string>

#include <gtest/gtest.h>

TEST(test_iterator, test_advance) {
  {
    std::string str = "123456789";

    auto it_1 = str.begin();
    auto it_2 = str.begin();

    EXPECT_EQ(it_1, it_2);

    liuyunbin::advance(it_1, 5);
    std::advance(it_2, 5);

    EXPECT_EQ(it_1, it_2);
  }
  {
    std::list<int> li = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto it_1 = li.begin();
    auto it_2 = li.begin();

    EXPECT_EQ(it_1, it_2);

    liuyunbin::advance(it_1, 5);
    std::advance(it_2, 5);

    EXPECT_EQ(it_1, it_2);
  }
}
