
#include "strrchr.h"

#include <string.h>

#include <gtest/gtest.h>

TEST(test_cstring, test_strrchr) {
  {
    const char *str = "1234567890123";
    const char ch = '1';
    EXPECT_EQ(::strrchr(str, ch), liuyunbin::strrchr(str, ch));
  }
  {
    const char *str = "1234567890123";
    const char ch = 'a';
    EXPECT_EQ(::strrchr(str, ch), liuyunbin::strrchr(str, ch));
  }
  {
    const char *str = "1234567890123";
    const char ch = '\0';
    EXPECT_EQ(::strrchr(str, ch), liuyunbin::strrchr(str, ch));
  }
}
