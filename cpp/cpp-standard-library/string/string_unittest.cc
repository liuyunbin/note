
#include "string.h"

#include <gtest/gtest.h>

TEST(test_string, test_string) {
    liuyunbin::string str_1 = "12345";
    liuyunbin::string str_2 = "123";

    str_1.swap(str_2);

    EXPECT_NE(str_1, str_2);
}
