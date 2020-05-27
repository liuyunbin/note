
#include "equal.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_equal) {
  {
    std::string lhs = "12341234abcd";
    std::string rhs = "1234abcd1234";
    EXPECT_EQ(std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin()),
              liuyunbin::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin()));
  }
  {
    std::string lhs = "12341234abcd";
    std::string rhs = "12341234abcd";
    EXPECT_EQ(std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin()),
              liuyunbin::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin()));
  }
  {
    std::string lhs = "1234abcd1234";
    std::string rhs = "12341234abcd";
    EXPECT_EQ(std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin()),
              liuyunbin::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin()));
  }
}
