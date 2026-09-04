
#include "utility.h"

#include <gtest/gtest.h>

#include <string>

bool fun(std::string &&) { return true; }

bool fun(const std::string &) { return false; }

template <typename T>
bool f(T &&t) {
    return fun(liuyunbin::forward<T>(t));
}

TEST(test_utility, test_forward) {
    std::string str = "1234";
    EXPECT_EQ(false, f(str));
    EXPECT_EQ(true, f(std::string("123")));
}

TEST(test_utility, test_move) {
    std::string ve_1 = "1234";
    std::string ve_2 = "1234";
    std::string ve_3 = liuyunbin::move(ve_2);
    std::string ve_4;

    EXPECT_EQ(ve_1, ve_3);
    EXPECT_EQ(ve_2, ve_4);
}

// 显示实例化
template class liuyunbin::pair<int, std::string>;

TEST(test_utility, test_pair) {
    liuyunbin::pair<int, std::string> ve_1 = {1, "234"};
    liuyunbin::pair<int, std::string> ve_2 = {2, "456"};

    ve_1.swap(ve_2);

    EXPECT_NE(ve_1, ve_2);
}

TEST(test_utility, test_swap) {
    std::string ve_1 = "234";
    std::string ve_2 = "456";

    liuyunbin::swap(ve_1, ve_2);
}
