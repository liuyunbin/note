
#include "deque.h"

#include <gtest/gtest.h>

#include <deque>

// 显示实例化
template class liuyunbin::deque<int>;

TEST(test_deque, test_deque) {
    liuyunbin::deque<int> de_1 = {0, 1, 2, 3, 4};
    liuyunbin::deque<int> de_2 = {5, 6, 7, 8, 9};

    de_1.swap(de_2);

    EXPECT_NE(de_1, de_2);
}
