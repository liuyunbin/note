
#include "iterator.h"

#include <gtest/gtest.h>

#include <iterator>
#include <list>
#include <string>

TEST(test_iterator, test_advance) {
    {
        std::string str = "123456789";

        auto it_1 = str.begin();
        auto it_2 = str.begin();

        EXPECT_EQ(it_1, it_2);

        liuyunbin::advance(it_1, 5);
        std::advance(it_2, 5);

        EXPECT_EQ(it_1, it_2);
    }
    {
        std::list<int> li = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        auto it_1 = li.begin();
        auto it_2 = li.begin();

        EXPECT_EQ(it_1, it_2);

        liuyunbin::advance(it_1, 5);
        std::advance(it_2, 5);

        EXPECT_EQ(it_1, it_2);
    }
}

// 显示实例化
template class liuyunbin::back_insert_iterator<std::string>;

TEST(test_iterator, test_back_insert_iterator) {}

TEST(test_iterator, test_distance) {
    {
        std::string str = "123456789";

        auto it_1 = str.begin();
        auto it_2 = str.end();

        EXPECT_EQ(liuyunbin::distance(it_1, it_2), std::distance(it_1, it_2));
    }
    {
        std::list<int> li = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        auto it_1 = li.begin();
        auto it_2 = li.end();

        EXPECT_EQ(liuyunbin::distance(it_1, it_2), std::distance(it_1, it_2));
    }
}

// 显示实例化
template class liuyunbin::front_insert_iterator<std::list<int>>;

TEST(test_iterator, test_front_insert_iterator) {}

// 显示实例化
template class liuyunbin::insert_iterator<std::list<int>>;

TEST(test_iterator, test_insert_iterator) {}

// 显示实例化
template class liuyunbin::istream_iterator<int>;

TEST(test_iterator, test_istream_iterator) {}

// 显示实例化
template class liuyunbin::move_iterator<std::vector<int>::iterator>;

TEST(test_iterator, test_move_iterator) {}

TEST(test_iterator, test_next) {
    {
        std::string str = "123456789";

        auto it_1 = str.begin();
        auto it_2 = str.begin();

        EXPECT_EQ(liuyunbin::next(it_1, 5), std::next(it_2, 5));
    }
    {
        std::list<int> li = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        auto it_1 = li.begin();
        auto it_2 = li.begin();

        EXPECT_EQ(liuyunbin::next(it_1, 5), std::next(it_2, 5));
    }
}

// 显示实例化
template class liuyunbin::ostream_iterator<int>;

TEST(test_iterator, test_ostream_iterator) {}

TEST(test_iterator, test_prev) {
    {
        std::string str = "123456789";

        auto it_1 = str.end();
        auto it_2 = str.end();

        EXPECT_EQ(liuyunbin::prev(it_1, 5), std::prev(it_2, 5));
    }
    {
        std::list<int> li = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        auto it_1 = li.end();
        auto it_2 = li.end();

        EXPECT_EQ(liuyunbin::prev(it_1, 5), std::prev(it_2, 5));
    }
}

// 显示实例化
template class liuyunbin::reverse_iterator<std::vector<int>::iterator>;

TEST(test_iterator, test_reverse_iterator) {}
