
#include "strspn.h"

#include <string.h>

#include <gtest/gtest.h>

TEST(test_cstring, test_strspn) {
  {
    const char *dest = "1234567890123";
    const char *src = "13";
    EXPECT_EQ(::strspn(dest, src), liuyunbin::strspn(dest, src));
  }
  {
    const char *dest = "1234567890123";
    const char *src = "abc";
    EXPECT_EQ(::strspn(dest, src), liuyunbin::strspn(dest, src));
  }
  {
    const char *dest = "1234567890123";
    const char *src = "123abc";
    EXPECT_EQ(::strspn(dest, src), liuyunbin::strspn(dest, src));
  }
}
