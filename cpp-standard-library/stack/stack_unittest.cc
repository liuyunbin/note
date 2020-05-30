
#include "stack.h"

#include <gtest/gtest.h>

// 显示实例化
template class liuyunbin::stack<int>;

TEST(test_stack, test_stack) {
  liuyunbin::stack<int> li_1;
  li_1.push(0);
  li_1.push(1);
  li_1.push(2);
  li_1.push(3);
  li_1.push(4);
  liuyunbin::stack<int> li_2;
  li_2.push(5);
  li_2.push(6);
  li_2.push(7);
  li_2.push(8);
  li_2.push(9);

  li_1.swap(li_2);

  EXPECT_NE(li_1, li_2);
}
