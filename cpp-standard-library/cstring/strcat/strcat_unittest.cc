
#include "strcat.h"

#include <string.h>

#include <gtest/gtest.h>

TEST(test_cstring, test_strcat) {
  {
    const char *src = "";
    char to_1[100] = "";
    char to_2[100] = "";
    EXPECT_STREQ(::strcat(to_1, src), liuyunbin::strcat(to_2, src));
  }
  {
    const char *src = "1234567890";
    char to_1[100] = "123";
    char to_2[100] = "123";
    EXPECT_STREQ(::strcat(to_1, src), liuyunbin::strcat(to_2, src));
  }
}
