
#include "memory.h"

#include <gtest/gtest.h>

// 显示实例化
template class liuyunbin::allocator<int>;

TEST(test_memory, test_allocator) {}

// 显示实例化
template class liuyunbin::shared_ptr<int>;

TEST(test_memory, test_shared_ptr) {}

// 显示实例化
template class liuyunbin::unique_ptr<int>;

TEST(test_memory, test_unique_ptr) {}
