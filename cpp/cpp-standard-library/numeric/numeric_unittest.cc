
#include "numeric.h"

#include <gtest/gtest.h>

#include <forward_list>
#include <iterator>
#include <list>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

TEST(test_numeric, test_accumulate) {
    // 输入迭代器
    {
        std::istringstream stream_1("1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5");
        int a = 1;
        int x = std::accumulate(std::istream_iterator<int>(stream_1),
                                std::istream_iterator<int>(), a);
        int y = liuyunbin::accumulate(std::istream_iterator<int>(stream_2),
                                      std::istream_iterator<int>(), a);
        EXPECT_EQ(x, y);
    }
    {
        std::istringstream stream_1("0 12 3 45 6 789");
        std::istringstream stream_2("0 12 3 45 6 789");
        std::string str;
        std::string x =
            std::accumulate(std::istream_iterator<std::string>(stream_1),
                            std::istream_iterator<std::string>(), str);
        std::string y =
            liuyunbin::accumulate(std::istream_iterator<std::string>(stream_2),
                                  std::istream_iterator<std::string>(), str);
        EXPECT_EQ(x, y);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        int a = 1;
        int x =
            std::accumulate(forward_list_1.cbegin(), forward_list_1.cend(), a);
        int y = liuyunbin::accumulate(forward_list_1.cbegin(),
                                      forward_list_1.cend(), a);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<std::string> forward_list_1 = {"0",  "12", "3",
                                                         "45", "6",  "789"};
        std::string str;
        std::string x = std::accumulate(forward_list_1.cbegin(),
                                        forward_list_1.cend(), str);
        std::string y = liuyunbin::accumulate(forward_list_1.cbegin(),
                                              forward_list_1.cend(), str);
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        int a = 1;
        int x = std::accumulate(list_1.cbegin(), list_1.cend(), a);
        int y = liuyunbin::accumulate(list_1.cbegin(), list_1.cend(), a);
        EXPECT_EQ(x, y);
    }
    {
        std::list<std::string> list_1 = {"0", "12", "3", "45", "6", "789"};
        std::string str;
        std::string x = std::accumulate(list_1.cbegin(), list_1.cend(), str);
        std::string y =
            liuyunbin::accumulate(list_1.cbegin(), list_1.cend(), str);
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        int a = 1;
        int x = std::accumulate(vector_1.cbegin(), vector_1.cend(), a);
        int y = liuyunbin::accumulate(vector_1.cbegin(), vector_1.cend(), a);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<std::string> vector_1 = {"0", "12", "3", "45", "6", "789"};
        std::string str;
        std::string x =
            std::accumulate(vector_1.cbegin(), vector_1.cend(), str);
        std::string y =
            liuyunbin::accumulate(vector_1.cbegin(), vector_1.cend(), str);
        EXPECT_EQ(x, y);
    }
}

TEST(test_numeric, test_adjacent_difference) {
    // 输入迭代器
    {
        std::istringstream stream_1("1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5");
        std::forward_list<int> forward_list_3 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_4 = {5, 6, 7, 8, 9};
        std::adjacent_difference(std::istream_iterator<int>(stream_1),
                                 std::istream_iterator<int>(),
                                 forward_list_3.begin());
        liuyunbin::adjacent_difference(std::istream_iterator<int>(stream_2),
                                       std::istream_iterator<int>(),
                                       forward_list_4.begin());
        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_3 = {5, 6, 7, 8, 9};
        std::adjacent_difference(forward_list_1.cbegin(), forward_list_1.cend(),
                                 forward_list_2.begin());
        liuyunbin::adjacent_difference(forward_list_1.cbegin(),
                                       forward_list_1.cend(),
                                       forward_list_3.begin());
        EXPECT_EQ(forward_list_2, forward_list_3);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_3 = {5, 6, 7, 8, 9};
        std::adjacent_difference(list_1.cbegin(), list_1.cend(),
                                 forward_list_2.begin());
        liuyunbin::adjacent_difference(list_1.cbegin(), list_1.cend(),
                                       forward_list_3.begin());
        EXPECT_EQ(forward_list_2, forward_list_3);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_3 = {5, 6, 7, 8, 9};
        std::adjacent_difference(vector_1.cbegin(), vector_1.cend(),
                                 forward_list_2.begin());
        liuyunbin::adjacent_difference(vector_1.cbegin(), vector_1.cend(),
                                       forward_list_3.begin());
        EXPECT_EQ(forward_list_2, forward_list_3);
    }
}

TEST(test_numeric, test_inner_product) {
    // 输入迭代器
    {
        std::istringstream stream_1("0 1 2 3 4");
        std::istringstream stream_2("5 6 7 8 9");
        std::istringstream stream_3("0 1 2 3 4");
        std::istringstream stream_4("5 6 7 8 9");

        int a = 1;
        int x = std::inner_product(std::istream_iterator<int>(stream_1),
                                   std::istream_iterator<int>(),
                                   std::istream_iterator<int>(stream_2), a);
        int y = liuyunbin::inner_product(
            std::istream_iterator<int>(stream_3), std::istream_iterator<int>(),
            std::istream_iterator<int>(stream_4), a);
        EXPECT_EQ(x, y);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};
        int a = 1;
        int x =
            std::inner_product(forward_list_1.cbegin(), forward_list_1.cend(),
                               forward_list_2.begin(), a);
        int y = liuyunbin::inner_product(forward_list_1.cbegin(),
                                         forward_list_1.cend(),
                                         forward_list_2.begin(), a);
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};
        std::list<int> list_2 = {5, 6, 7, 8, 9};
        int a = 1;
        int x = std::inner_product(list_1.cbegin(), list_1.cend(),
                                   list_2.begin(), a);
        int y = liuyunbin::inner_product(list_1.cbegin(), list_1.cend(),
                                         list_2.begin(), a);
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {5, 6, 7, 8, 9};
        int a = 1;
        int x = std::inner_product(vector_1.cbegin(), vector_1.cend(),
                                   vector_2.begin(), a);
        int y = liuyunbin::inner_product(vector_1.cbegin(), vector_1.cend(),
                                         vector_2.begin(), a);
        EXPECT_EQ(x, y);
    }
}

TEST(test_numeric, test_iota) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};
        int a = 1;
        std::iota(forward_list_1.begin(), forward_list_1.end(), a);
        liuyunbin::iota(forward_list_2.begin(), forward_list_2.end(), a);
        EXPECT_EQ(forward_list_1, forward_list_2);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};
        std::list<int> list_2 = {5, 6, 7, 8, 9};
        int a = 1;
        std::iota(list_1.begin(), list_1.end(), a);
        liuyunbin::iota(list_2.begin(), list_2.end(), a);
        EXPECT_EQ(list_1, list_2);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {5, 6, 7, 8, 9};
        int a = 1;
        std::iota(vector_1.begin(), vector_1.end(), a);
        liuyunbin::iota(vector_2.begin(), vector_2.end(), a);
        EXPECT_EQ(vector_1, vector_2);
    }
}

TEST(test_numeric, test_partial_sum) {
    // 输入迭代器
    {
        std::istringstream stream_1("1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5");
        std::forward_list<int> forward_list_3 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_4 = {5, 6, 7, 8, 9};
        std::partial_sum(std::istream_iterator<int>(stream_1),
                         std::istream_iterator<int>(), forward_list_3.begin());
        liuyunbin::partial_sum(std::istream_iterator<int>(stream_2),
                               std::istream_iterator<int>(),
                               forward_list_4.begin());
        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_3 = {5, 6, 7, 8, 9};
        std::partial_sum(forward_list_1.cbegin(), forward_list_1.cend(),
                         forward_list_2.begin());
        liuyunbin::partial_sum(forward_list_1.cbegin(), forward_list_1.cend(),
                               forward_list_3.begin());
        EXPECT_EQ(forward_list_2, forward_list_3);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_3 = {5, 6, 7, 8, 9};
        std::partial_sum(list_1.cbegin(), list_1.cend(),
                         forward_list_2.begin());
        liuyunbin::partial_sum(list_1.cbegin(), list_1.cend(),
                               forward_list_3.begin());
        EXPECT_EQ(forward_list_2, forward_list_3);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_3 = {5, 6, 7, 8, 9};
        std::partial_sum(vector_1.cbegin(), vector_1.cend(),
                         forward_list_2.begin());
        liuyunbin::partial_sum(vector_1.cbegin(), vector_1.cend(),
                               forward_list_3.begin());
        EXPECT_EQ(forward_list_2, forward_list_3);
    }
}
