
#include "strtok.h"

#include <string.h>

#include <gtest/gtest.h>

TEST(test_cstring, test_strtok) {
  char str_1[] = "1234567890123";
  char str_2[] = "1234567890123";
  const char *delim = "13";
  EXPECT_STREQ(::strtok(str_1, delim), liuyunbin::strtok(str_2, delim));
  for (;;) {
    const char *p1 = ::strtok(NULL, delim);
    const char *p2 = liuyunbin::strtok(NULL, delim);
    EXPECT_STREQ(p1, p2);
    if (p1 == NULL)
      break;
  }
}
