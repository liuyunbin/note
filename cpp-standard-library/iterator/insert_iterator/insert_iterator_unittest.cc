
#include "insert_iterator.h"

#include <list>

#include <gtest/gtest.h>

// 显示实例化
template class liuyunbin::insert_iterator<std::list<int>>;

TEST(test_iterator, test_insert_iterator) {}
