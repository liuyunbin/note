
#include "vector.h"

#include <gtest/gtest.h>

// 显示实例化
template class liuyunbin::vector<int>;

TEST(test_vector, test_vector) {
    liuyunbin::vector<int> ve_1 = {1, 2, 3, 4, 5};
    liuyunbin::vector<int> ve_2 = {2, 1, 4, 6, 8};

    ve_1.swap(ve_2);

    EXPECT_NE(ve_1, ve_2);
}
