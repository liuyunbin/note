
#include "accumulate.h"

#include <list>
#include <numeric>
#include <string>

#include <gtest/gtest.h>

TEST(test_numeric, test_accumulate) {
  {
    std::list<int> li = {1, 2, 3, 4, 5};
    int a = 1;
    int x = std::accumulate(li.cbegin(), li.cend(), a);
    int y = liuyunbin::accumulate(li.cbegin(), li.cend(), a);
    EXPECT_EQ(x, y);
  }
  {
    std::list<std::string> li = {"1", "2", "3", "4", "5"};
    std::string str = "1";
    std::string x = std::accumulate(li.cbegin(), li.cend(), str);
    std::string y = liuyunbin::accumulate(li.cbegin(), li.cend(), str);
    EXPECT_EQ(x, y);
  }
}
