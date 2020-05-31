
#include "move_iterator.h"

#include <vector>

#include <gtest/gtest.h>

// 显示实例化
template class liuyunbin::move_iterator<std::vector<int>::iterator>;

TEST(test_iterator, test_move_iterator) {}
