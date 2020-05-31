
#include "reverse_iterator.h"

#include <vector>

#include <gtest/gtest.h>

// 显示实例化
template class liuyunbin::reverse_iterator<std::vector<int>::iterator>;

TEST(test_iterator, test_reverse_iterator) {}
