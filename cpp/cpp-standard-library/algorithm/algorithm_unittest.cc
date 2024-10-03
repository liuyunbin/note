
#include "algorithm.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <cctype>
#include <forward_list>
#include <iterator>
#include <list>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

TEST(test_algorithm, test_adjacent_find) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        auto x =
            std::adjacent_find(forward_list_1.cbegin(), forward_list_1.cend());
        auto y = liuyunbin::adjacent_find(forward_list_1.cbegin(),
                                          forward_list_1.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 2, 3, 3, 4, 5};
        auto x =
            std::adjacent_find(forward_list_1.cbegin(), forward_list_1.cend());
        auto y = liuyunbin::adjacent_find(forward_list_1.cbegin(),
                                          forward_list_1.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<std::string> forward_list_1 = {"0",  "12", "3",
                                                         "45", "6",  "789"};
        auto x =
            std::adjacent_find(forward_list_1.cbegin(), forward_list_1.cend());
        auto y = liuyunbin::adjacent_find(forward_list_1.cbegin(),
                                          forward_list_1.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<std::string> forward_list_1 = {
            "0", "12", "3", "3", "45", "45", "6", "789"};
        auto x =
            std::adjacent_find(forward_list_1.cbegin(), forward_list_1.cend());
        auto y = liuyunbin::adjacent_find(forward_list_1.cbegin(),
                                          forward_list_1.cend());
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        auto x = std::adjacent_find(list_1.cbegin(), list_1.cend());
        auto y = liuyunbin::adjacent_find(list_1.cbegin(), list_1.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {1, 2, 2, 3, 3, 4, 5};
        auto x = std::adjacent_find(list_1.cbegin(), list_1.cend());
        auto y = liuyunbin::adjacent_find(list_1.cbegin(), list_1.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::list<std::string> list_1 = {"0", "12", "3", "45", "6", "789"};
        auto x = std::adjacent_find(list_1.cbegin(), list_1.cend());
        auto y = liuyunbin::adjacent_find(list_1.cbegin(), list_1.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::list<std::string> list_1 = {"0",  "12", "3", "3",
                                         "45", "45", "6", "789"};
        auto x = std::adjacent_find(list_1.cbegin(), list_1.cend());
        auto y = liuyunbin::adjacent_find(list_1.cbegin(), list_1.cend());
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        auto x = std::adjacent_find(vector_1.cbegin(), vector_1.cend());
        auto y = liuyunbin::adjacent_find(vector_1.cbegin(), vector_1.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {1, 2, 2, 3, 3, 4, 5};
        auto x = std::adjacent_find(vector_1.cbegin(), vector_1.cend());
        auto y = liuyunbin::adjacent_find(vector_1.cbegin(), vector_1.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::vector<std::string> vector_1 = {"0", "12", "3", "45", "6", "789"};
        auto x = std::adjacent_find(vector_1.cbegin(), vector_1.cend());
        auto y = liuyunbin::adjacent_find(vector_1.cbegin(), vector_1.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::vector<std::string> vector_1 = {"0",  "12", "3", "3",
                                             "45", "45", "6", "789"};
        auto x = std::adjacent_find(vector_1.cbegin(), vector_1.cend());
        auto y = liuyunbin::adjacent_find(vector_1.cbegin(), vector_1.cend());
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_all_of) {
    // 输入迭代器
    {
        std::istringstream stream_1("1 2 3 4 5 1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5 1 2 3 4 5");
        auto f = [](int v) { return v < 5 ? true : false; };
        auto x = std::all_of(std::istream_iterator<int>(stream_1),
                             std::istream_iterator<int>(), f);
        auto y = liuyunbin::all_of(std::istream_iterator<int>(stream_2),
                                   std::istream_iterator<int>(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::istringstream stream_1("1 2 3 4 1 2 3 4");
        std::istringstream stream_2("1 2 3 4 1 2 3 4");
        auto f = [](int v) { return v < 5 ? true : false; };
        auto x = std::all_of(std::istream_iterator<int>(stream_1),
                             std::istream_iterator<int>(), f);
        auto y = liuyunbin::all_of(std::istream_iterator<int>(stream_2),
                                   std::istream_iterator<int>(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::istringstream stream_1("1 2 3 4 5 1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5 1 2 3 4 5");
        auto f = [](char ch) { return std::isdigit(ch) ? true : false; };
        auto x = std::all_of(std::istream_iterator<char>(stream_1),
                             std::istream_iterator<char>(), f);
        auto y = liuyunbin::all_of(std::istream_iterator<char>(stream_2),
                                   std::istream_iterator<char>(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::istringstream stream_1("1 2 3 4 5 a 1 2 3 4 5 a");
        std::istringstream stream_2("1 2 3 4 5 a 1 2 3 4 5 a");
        auto f = [](char ch) { return std::isdigit(ch) ? true : false; };
        auto x = std::all_of(std::istream_iterator<char>(stream_1),
                             std::istream_iterator<char>(), f);
        auto y = liuyunbin::all_of(std::istream_iterator<char>(stream_2),
                                   std::istream_iterator<char>(), f);
        EXPECT_EQ(x, y);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        auto f = [](int v) { return v < 5 ? true : false; };
        auto x = std::all_of(forward_list_1.cbegin(), forward_list_1.cend(), f);
        auto y = liuyunbin::all_of(forward_list_1.cbegin(),
                                   forward_list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 1, 2, 3, 4};
        auto f = [](int v) { return v < 5 ? true : false; };
        auto x = std::all_of(forward_list_1.cbegin(), forward_list_1.cend(), f);
        auto y = liuyunbin::all_of(forward_list_1.cbegin(),
                                   forward_list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<char> forward_list_1 = {'1', '2', '3', '4', '5',
                                                  '1', '2', '3', '4', '5'};
        auto f = [](char ch) { return std::isdigit(ch) ? true : false; };
        auto x = std::all_of(forward_list_1.cbegin(), forward_list_1.cend(), f);
        auto y = liuyunbin::all_of(forward_list_1.cbegin(),
                                   forward_list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<char> forward_list_1 = {'1', '2', '3', '4', '5', 'a',
                                                  '1', '2', '3', '4', '5', 'a'};
        auto f = [](char ch) { return std::isdigit(ch) ? true : false; };
        auto x = std::all_of(forward_list_1.cbegin(), forward_list_1.cend(), f);
        auto y = liuyunbin::all_of(forward_list_1.cbegin(),
                                   forward_list_1.cend(), f);
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        auto f = [](int v) { return v < 5 ? true : false; };
        auto x = std::all_of(list_1.cbegin(), list_1.cend(), f);
        auto y = liuyunbin::all_of(list_1.cbegin(), list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 1, 2, 3, 4};
        auto f = [](int v) { return v < 5 ? true : false; };
        auto x = std::all_of(list_1.cbegin(), list_1.cend(), f);
        auto y = liuyunbin::all_of(list_1.cbegin(), list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::list<char> list_1 = {'1', '2', '3', '4', '5',
                                  '1', '2', '3', '4', '5'};
        auto f = [](char ch) { return std::isdigit(ch) ? true : false; };
        auto x = std::all_of(list_1.cbegin(), list_1.cend(), f);
        auto y = liuyunbin::all_of(list_1.cbegin(), list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::list<char> list_1 = {'1', '2', '3', '4', '5', 'a',
                                  '1', '2', '3', '4', '5', 'a'};
        auto f = [](char ch) { return std::isdigit(ch) ? true : false; };
        auto x = std::all_of(list_1.cbegin(), list_1.cend(), f);
        auto y = liuyunbin::all_of(list_1.cbegin(), list_1.cend(), f);
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        auto f = [](int v) { return v < 5 ? true : false; };
        auto x = std::all_of(vector_1.cbegin(), vector_1.cend(), f);
        auto y = liuyunbin::all_of(vector_1.cbegin(), vector_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 1, 2, 3, 4};
        auto f = [](int v) { return v < 5 ? true : false; };
        auto x = std::all_of(vector_1.cbegin(), vector_1.cend(), f);
        auto y = liuyunbin::all_of(vector_1.cbegin(), vector_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<char> vector_1 = {'1', '2', '3', '4', '5',
                                      '1', '2', '3', '4', '5'};
        auto f = [](char ch) { return std::isdigit(ch) ? true : false; };
        auto x = std::all_of(vector_1.cbegin(), vector_1.cend(), f);
        auto y = liuyunbin::all_of(vector_1.cbegin(), vector_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<char> vector_1 = {'1', '2', '3', '4', '5', 'a',
                                      '1', '2', '3', '4', '5', 'a'};
        auto f = [](char ch) { return std::isdigit(ch) ? true : false; };
        auto x = std::all_of(vector_1.cbegin(), vector_1.cend(), f);
        auto y = liuyunbin::all_of(vector_1.cbegin(), vector_1.cend(), f);
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_any_of) {
    // 输入迭代器
    {
        std::istringstream stream_1("1 2 3 4 5 1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5 1 2 3 4 5");
        auto f = [](int v) { return v >= 5 ? true : false; };
        auto x = std::any_of(std::istream_iterator<int>(stream_1),
                             std::istream_iterator<int>(), f);
        auto y = liuyunbin::any_of(std::istream_iterator<int>(stream_2),
                                   std::istream_iterator<int>(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::istringstream stream_1("1 2 3 4 1 2 3 4");
        std::istringstream stream_2("1 2 3 4 1 2 3 4");
        auto f = [](int v) { return v >= 5 ? true : false; };
        auto x = std::any_of(std::istream_iterator<int>(stream_1),
                             std::istream_iterator<int>(), f);
        auto y = liuyunbin::any_of(std::istream_iterator<int>(stream_2),
                                   std::istream_iterator<int>(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::istringstream stream_1("1 2 3 4 5 1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5 1 2 3 4 5");
        auto f = [](char ch) { return std::isalpha(ch) ? true : false; };
        auto x = std::any_of(std::istream_iterator<char>(stream_1),
                             std::istream_iterator<char>(), f);
        auto y = liuyunbin::any_of(std::istream_iterator<char>(stream_2),
                                   std::istream_iterator<char>(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::istringstream stream_1("1 2 3 4 5 a 1 2 3 4 5 a");
        std::istringstream stream_2("1 2 3 4 5 a 1 2 3 4 5 a");
        auto f = [](char ch) { return std::isalpha(ch) ? true : false; };
        auto x = std::any_of(std::istream_iterator<char>(stream_1),
                             std::istream_iterator<char>(), f);
        auto y = liuyunbin::any_of(std::istream_iterator<char>(stream_2),
                                   std::istream_iterator<char>(), f);
        EXPECT_EQ(x, y);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        auto f = [](int v) { return v >= 5 ? true : false; };
        auto x = std::any_of(forward_list_1.cbegin(), forward_list_1.cend(), f);
        auto y = liuyunbin::any_of(forward_list_1.cbegin(),
                                   forward_list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 1, 2, 3, 4};
        auto f = [](int v) { return v >= 5 ? true : false; };
        auto x = std::any_of(forward_list_1.cbegin(), forward_list_1.cend(), f);
        auto y = liuyunbin::any_of(forward_list_1.cbegin(),
                                   forward_list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<char> forward_list_1 = {'1', '2', '3', '4', '5',
                                                  '1', '2', '3', '4', '5'};
        auto f = [](char ch) { return std::isalpha(ch) ? true : false; };
        auto x = std::any_of(forward_list_1.cbegin(), forward_list_1.cend(), f);
        auto y = liuyunbin::any_of(forward_list_1.cbegin(),
                                   forward_list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<char> forward_list_1 = {'1', '2', '3', '4', '5', 'a',
                                                  '1', '2', '3', '4', '5', 'a'};
        auto f = [](char ch) { return std::isalpha(ch) ? true : false; };
        auto x = std::any_of(forward_list_1.cbegin(), forward_list_1.cend(), f);
        auto y = liuyunbin::any_of(forward_list_1.cbegin(),
                                   forward_list_1.cend(), f);
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        auto f = [](int v) { return v >= 5 ? true : false; };
        auto x = std::any_of(list_1.cbegin(), list_1.cend(), f);
        auto y = liuyunbin::any_of(list_1.cbegin(), list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 1, 2, 3, 4};
        auto f = [](int v) { return v >= 5 ? true : false; };
        auto x = std::any_of(list_1.cbegin(), list_1.cend(), f);
        auto y = liuyunbin::any_of(list_1.cbegin(), list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::list<char> list_1 = {'1', '2', '3', '4', '5',
                                  '1', '2', '3', '4', '5'};
        auto f = [](char ch) { return std::isalpha(ch) ? true : false; };
        auto x = std::any_of(list_1.cbegin(), list_1.cend(), f);
        auto y = liuyunbin::any_of(list_1.cbegin(), list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::list<char> list_1 = {'1', '2', '3', '4', '5', 'a',
                                  '1', '2', '3', '4', '5', 'a'};
        auto f = [](char ch) { return std::isalpha(ch) ? true : false; };
        auto x = std::any_of(list_1.cbegin(), list_1.cend(), f);
        auto y = liuyunbin::any_of(list_1.cbegin(), list_1.cend(), f);
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        auto f = [](int v) { return v >= 5 ? true : false; };
        auto x = std::any_of(vector_1.cbegin(), vector_1.cend(), f);
        auto y = liuyunbin::any_of(vector_1.cbegin(), vector_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 1, 2, 3, 4};
        auto f = [](int v) { return v >= 5 ? true : false; };
        auto x = std::any_of(vector_1.cbegin(), vector_1.cend(), f);
        auto y = liuyunbin::any_of(vector_1.cbegin(), vector_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<char> vector_1 = {'1', '2', '3', '4', '5',
                                      '1', '2', '3', '4', '5'};
        auto f = [](char ch) { return std::isalpha(ch) ? true : false; };
        auto x = std::any_of(vector_1.cbegin(), vector_1.cend(), f);
        auto y = liuyunbin::any_of(vector_1.cbegin(), vector_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<char> vector_1 = {'1', '2', '3', '4', '5', 'a',
                                      '1', '2', '3', '4', '5', 'a'};
        auto f = [](char ch) { return std::isalpha(ch) ? true : false; };
        auto x = std::any_of(vector_1.cbegin(), vector_1.cend(), f);
        auto y = liuyunbin::any_of(vector_1.cbegin(), vector_1.cend(), f);
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_binary_search) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        int v = 5;
        auto x = std::binary_search(forward_list_1.cbegin(),
                                    forward_list_1.cend(), v);
        auto y = liuyunbin::binary_search(forward_list_1.cbegin(),
                                          forward_list_1.cend(), v);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 6, 7, 8, 9};
        int v = 5;
        auto x = std::binary_search(forward_list_1.cbegin(),
                                    forward_list_1.cend(), v);
        auto y = liuyunbin::binary_search(forward_list_1.cbegin(),
                                          forward_list_1.cend(), v);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<char> forward_list_1 = {'1', '2', '3', '4', '5',
                                                  '6', '7', '8', '9'};
        char ch = '5';
        auto x = std::binary_search(forward_list_1.cbegin(),
                                    forward_list_1.cend(), ch);
        auto y = liuyunbin::binary_search(forward_list_1.cbegin(),
                                          forward_list_1.cend(), ch);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<char> forward_list_1 = {'1', '2', '3', '4',
                                                  '6', '7', '8', '9'};
        char ch = '5';
        auto x = std::binary_search(forward_list_1.cbegin(),
                                    forward_list_1.cend(), ch);
        auto y = liuyunbin::binary_search(forward_list_1.cbegin(),
                                          forward_list_1.cend(), ch);
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        int v = 5;
        auto x = std::binary_search(list_1.cbegin(), list_1.cend(), v);
        auto y = liuyunbin::binary_search(list_1.cbegin(), list_1.cend(), v);
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 6, 7, 8, 9};
        int v = 5;
        auto x = std::binary_search(list_1.cbegin(), list_1.cend(), v);
        auto y = liuyunbin::binary_search(list_1.cbegin(), list_1.cend(), v);
        EXPECT_EQ(x, y);
    }
    {
        std::list<char> list_1 = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
        char ch = '5';
        auto x = std::binary_search(list_1.cbegin(), list_1.cend(), ch);
        auto y = liuyunbin::binary_search(list_1.cbegin(), list_1.cend(), ch);
        EXPECT_EQ(x, y);
    }
    {
        std::list<char> list_1 = {'1', '2', '3', '4', '6', '7', '8', '9'};
        char ch = '5';
        auto x = std::binary_search(list_1.cbegin(), list_1.cend(), ch);
        auto y = liuyunbin::binary_search(list_1.cbegin(), list_1.cend(), ch);
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        int v = 5;
        auto x = std::binary_search(vector_1.cbegin(), vector_1.cend(), v);
        auto y =
            liuyunbin::binary_search(vector_1.cbegin(), vector_1.cend(), v);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 6, 7, 8, 9};
        int v = 5;
        auto x = std::binary_search(vector_1.cbegin(), vector_1.cend(), v);
        auto y =
            liuyunbin::binary_search(vector_1.cbegin(), vector_1.cend(), v);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<char> vector_1 = {'1', '2', '3', '4', '5',
                                      '6', '7', '8', '9'};
        char ch = '5';
        auto x = std::binary_search(vector_1.cbegin(), vector_1.cend(), ch);
        auto y =
            liuyunbin::binary_search(vector_1.cbegin(), vector_1.cend(), ch);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<char> vector_1 = {'1', '2', '3', '4', '6', '7', '8', '9'};
        char ch = '5';
        auto x = std::binary_search(vector_1.cbegin(), vector_1.cend(), ch);
        auto y =
            liuyunbin::binary_search(vector_1.cbegin(), vector_1.cend(), ch);
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_copy_backward) {
    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        std::list<int> list_2 = {0, 1, 2, 3, 4};
        std::list<int> list_3 = {5, 6, 7, 8, 9};
        std::copy_backward(list_1.cbegin(), list_1.cend(), list_2.end());
        liuyunbin::copy_backward(list_1.cbegin(), list_1.cend(), list_3.end());
        EXPECT_EQ(list_2, list_3);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        std::list<int> list_2 = {0, 1, 2, 3, 4};
        std::list<int> list_3 = {5, 6, 7, 8, 9};
        std::copy_backward(vector_1.cbegin(), vector_1.cend(), list_2.end());
        liuyunbin::copy_backward(vector_1.cbegin(), vector_1.cend(),
                                 list_3.end());
        EXPECT_EQ(list_2, list_3);
    }
}

TEST(test_algorithm, test_copy) {
    // 输入迭代器
    {
        std::istringstream stream_1("1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5");
        std::forward_list<int> forward_list_3 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_4 = {5, 6, 7, 8, 9};
        std::copy(std::istream_iterator<int>(stream_1),
                  std::istream_iterator<int>(), forward_list_3.begin());
        liuyunbin::copy(std::istream_iterator<int>(stream_2),
                        std::istream_iterator<int>(), forward_list_4.begin());
        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_3 = {5, 6, 7, 8, 9};
        std::copy(forward_list_1.cbegin(), forward_list_1.cend(),
                  forward_list_2.begin());
        liuyunbin::copy(forward_list_1.cbegin(), forward_list_1.cend(),
                        forward_list_3.begin());
        EXPECT_EQ(forward_list_2, forward_list_3);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_3 = {5, 6, 7, 8, 9};
        std::copy(list_1.cbegin(), list_1.cend(), forward_list_2.begin());
        liuyunbin::copy(list_1.cbegin(), list_1.cend(), forward_list_3.begin());
        EXPECT_EQ(forward_list_2, forward_list_3);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_3 = {5, 6, 7, 8, 9};
        std::copy(vector_1.cbegin(), vector_1.cend(), forward_list_2.begin());
        liuyunbin::copy(vector_1.cbegin(), vector_1.cend(),
                        forward_list_3.begin());
        EXPECT_EQ(forward_list_2, forward_list_3);
    }
}

TEST(test_algorithm, test_copy_if) {
    // 输入迭代器
    {
        std::istringstream stream_1("1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5");
        std::forward_list<int> forward_list_3 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_4 = {5, 6, 2, 3, 4};
        auto f = [](int v) { return v < 3 ? true : false; };
        std::copy_if(std::istream_iterator<int>(stream_1),
                     std::istream_iterator<int>(), forward_list_3.begin(), f);
        liuyunbin::copy_if(std::istream_iterator<int>(stream_2),
                           std::istream_iterator<int>(), forward_list_4.begin(),
                           f);
        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_3 = {5, 6, 2, 3, 4};
        auto f = [](int v) { return v < 3 ? true : false; };
        std::copy_if(forward_list_1.cbegin(), forward_list_1.cend(),
                     forward_list_2.begin(), f);
        liuyunbin::copy_if(forward_list_1.cbegin(), forward_list_1.cend(),
                           forward_list_3.begin(), f);
        EXPECT_EQ(forward_list_2, forward_list_3);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_3 = {5, 6, 2, 3, 4};
        auto f = [](int v) { return v < 3 ? true : false; };
        std::copy_if(list_1.cbegin(), list_1.cend(), forward_list_2.begin(), f);
        liuyunbin::copy_if(list_1.cbegin(), list_1.cend(),
                           forward_list_3.begin(), f);
        EXPECT_EQ(forward_list_2, forward_list_3);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_3 = {5, 6, 2, 3, 4};
        auto f = [](int v) { return v < 3 ? true : false; };
        std::copy_if(vector_1.cbegin(), vector_1.cend(), forward_list_2.begin(),
                     f);
        liuyunbin::copy_if(vector_1.cbegin(), vector_1.cend(),
                           forward_list_3.begin(), f);
        EXPECT_EQ(forward_list_2, forward_list_3);
    }
}

TEST(test_algorithm, test_copy_n) {
    // 输入迭代器
    {
        std::istringstream stream_1("1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5");
        int n = 5;
        std::forward_list<int> forward_list_3 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_4 = {5, 6, 7, 8, 9};
        std::copy_n(std::istream_iterator<int>(stream_1), n,
                    forward_list_3.begin());
        liuyunbin::copy_n(std::istream_iterator<int>(stream_2), n,
                          forward_list_4.begin());
        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_3 = {5, 6, 7, 8, 9};
        int n = 5;
        std::copy_n(forward_list_1.cbegin(), n, forward_list_2.begin());
        liuyunbin::copy_n(forward_list_1.cbegin(), n, forward_list_3.begin());
        EXPECT_EQ(forward_list_2, forward_list_3);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_3 = {5, 6, 7, 8, 9};
        int n = 5;
        std::copy_n(list_1.cbegin(), n, forward_list_2.begin());
        liuyunbin::copy_n(list_1.cbegin(), n, forward_list_3.begin());
        EXPECT_EQ(forward_list_2, forward_list_3);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_3 = {5, 6, 7, 8, 9};
        int n = 5;
        std::copy_n(vector_1.cbegin(), n, forward_list_2.begin());
        liuyunbin::copy_n(vector_1.cbegin(), n, forward_list_3.begin());
        EXPECT_EQ(forward_list_2, forward_list_3);
    }
}

TEST(test_algorithm, test_count) {
    // 输入迭代器
    {
        std::istringstream stream_1("1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5");
        int v = 3;
        auto x = std::count(std::istream_iterator<int>(stream_1),
                            std::istream_iterator<int>(), v);
        auto y = liuyunbin::count(std::istream_iterator<int>(stream_2),
                                  std::istream_iterator<int>(), v);
        EXPECT_EQ(x, y);
    }
    {
        std::istringstream stream_1("1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5");
        int v = 10;
        auto x = std::count(std::istream_iterator<int>(stream_1),
                            std::istream_iterator<int>(), v);
        auto y = liuyunbin::count(std::istream_iterator<int>(stream_2),
                                  std::istream_iterator<int>(), v);
        EXPECT_EQ(x, y);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        int v = 3;
        auto x = std::count(forward_list_1.cbegin(), forward_list_1.cend(), v);
        auto y =
            liuyunbin::count(forward_list_1.cbegin(), forward_list_1.cend(), v);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        int v = 10;
        auto x = std::count(forward_list_1.cbegin(), forward_list_1.cend(), v);
        auto y =
            liuyunbin::count(forward_list_1.cbegin(), forward_list_1.cend(), v);
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        int v = 3;
        auto x = std::count(list_1.cbegin(), list_1.cend(), v);
        auto y = liuyunbin::count(list_1.cbegin(), list_1.cend(), v);
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        int v = 10;
        auto x = std::count(list_1.cbegin(), list_1.cend(), v);
        auto y = liuyunbin::count(list_1.cbegin(), list_1.cend(), v);
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        int v = 3;
        auto x = std::count(vector_1.cbegin(), vector_1.cend(), v);
        auto y = liuyunbin::count(vector_1.cbegin(), vector_1.cend(), v);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        int v = 10;
        auto x = std::count(vector_1.cbegin(), vector_1.cend(), v);
        auto y = liuyunbin::count(vector_1.cbegin(), vector_1.cend(), v);
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_count_if) {
    // 输入迭代器
    {
        std::istringstream stream_1("1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5");
        auto f = [](int v) { return v < 3 ? true : false; };
        auto x = std::count_if(std::istream_iterator<int>(stream_1),
                               std::istream_iterator<int>(), f);
        auto y = liuyunbin::count_if(std::istream_iterator<int>(stream_2),
                                     std::istream_iterator<int>(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::istringstream stream_1("1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5");
        auto f = [](int v) { return v < 0 ? true : false; };
        auto x = std::count_if(std::istream_iterator<int>(stream_1),
                               std::istream_iterator<int>(), f);
        auto y = liuyunbin::count_if(std::istream_iterator<int>(stream_2),
                                     std::istream_iterator<int>(), f);
        EXPECT_EQ(x, y);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v < 3 ? true : false; };
        auto x =
            std::count_if(forward_list_1.cbegin(), forward_list_1.cend(), f);
        auto y = liuyunbin::count_if(forward_list_1.cbegin(),
                                     forward_list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v < 0 ? true : false; };
        auto x =
            std::count_if(forward_list_1.cbegin(), forward_list_1.cend(), f);
        auto y = liuyunbin::count_if(forward_list_1.cbegin(),
                                     forward_list_1.cend(), f);
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v < 3 ? true : false; };
        auto x = std::count_if(list_1.cbegin(), list_1.cend(), f);
        auto y = liuyunbin::count_if(list_1.cbegin(), list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v < 0 ? true : false; };
        auto x = std::count_if(list_1.cbegin(), list_1.cend(), f);
        auto y = liuyunbin::count_if(list_1.cbegin(), list_1.cend(), f);
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v < 3 ? true : false; };
        auto x = std::count_if(vector_1.cbegin(), vector_1.cend(), f);
        auto y = liuyunbin::count_if(vector_1.cbegin(), vector_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v < 0 ? true : false; };
        auto x = std::count_if(vector_1.cbegin(), vector_1.cend(), f);
        auto y = liuyunbin::count_if(vector_1.cbegin(), vector_1.cend(), f);
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_equal) {
    // 输入迭代器
    {
        std::istringstream stream_1("0 1 2 3 4");
        std::istringstream stream_2("5 6 7 8 9");
        std::istringstream stream_3("0 1 2 3 4");
        std::istringstream stream_4("5 6 7 8 9");

        auto x = std::equal(std::istream_iterator<int>(stream_1),
                            std::istream_iterator<int>(),
                            std::istream_iterator<int>(stream_2));
        auto y = liuyunbin::equal(std::istream_iterator<int>(stream_3),
                                  std::istream_iterator<int>(),
                                  std::istream_iterator<int>(stream_4));
        EXPECT_EQ(x, y);
    }
    {
        std::istringstream stream_1("0 1 2 3 4");
        std::istringstream stream_2("0 1 2 3 4");
        std::istringstream stream_3("0 1 2 3 4");
        std::istringstream stream_4("0 1 2 3 4");

        auto x = std::equal(std::istream_iterator<int>(stream_1),
                            std::istream_iterator<int>(),
                            std::istream_iterator<int>(stream_2));
        auto y = liuyunbin::equal(std::istream_iterator<int>(stream_3),
                                  std::istream_iterator<int>(),
                                  std::istream_iterator<int>(stream_4));
        EXPECT_EQ(x, y);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};

        auto x = std::equal(forward_list_1.cbegin(), forward_list_1.cend(),
                            forward_list_2.cbegin());
        auto y =
            liuyunbin::equal(forward_list_1.cbegin(), forward_list_1.cend(),
                             forward_list_2.cbegin());
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};

        auto x = std::equal(forward_list_1.cbegin(), forward_list_1.cend(),
                            forward_list_1.cbegin());
        auto y =
            liuyunbin::equal(forward_list_1.cbegin(), forward_list_1.cend(),
                             forward_list_1.cbegin());
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};
        std::list<int> list_2 = {5, 6, 7, 8, 9};

        auto x = std::equal(list_1.cbegin(), list_1.cend(), list_2.cbegin());
        auto y =
            liuyunbin::equal(list_1.cbegin(), list_1.cend(), list_2.cbegin());
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};

        auto x = std::equal(list_1.cbegin(), list_1.cend(), list_1.cbegin());
        auto y =
            liuyunbin::equal(list_1.cbegin(), list_1.cend(), list_1.cbegin());
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {5, 6, 7, 8, 9};

        auto x =
            std::equal(vector_1.cbegin(), vector_1.cend(), vector_2.cbegin());
        auto y = liuyunbin::equal(vector_1.cbegin(), vector_1.cend(),
                                  vector_2.cbegin());
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};

        auto x =
            std::equal(vector_1.cbegin(), vector_1.cend(), vector_1.cbegin());
        auto y = liuyunbin::equal(vector_1.cbegin(), vector_1.cend(),
                                  vector_1.cbegin());
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_equal_range) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};

        int v = 3;
        auto x =
            std::equal_range(forward_list_1.cbegin(), forward_list_1.cend(), v);
        auto y = liuyunbin::equal_range(forward_list_1.cbegin(),
                                        forward_list_1.cend(), v);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};

        int v = 10;
        auto x =
            std::equal_range(forward_list_1.cbegin(), forward_list_1.cend(), v);
        auto y = liuyunbin::equal_range(forward_list_1.cbegin(),
                                        forward_list_1.cend(), v);
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};

        int v = 3;
        auto x = std::equal_range(list_1.cbegin(), list_1.cend(), v);
        auto y = liuyunbin::equal_range(list_1.cbegin(), list_1.cend(), v);
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};

        int v = 10;
        auto x = std::equal_range(list_1.cbegin(), list_1.cend(), v);
        auto y = liuyunbin::equal_range(list_1.cbegin(), list_1.cend(), v);
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};

        int v = 3;
        auto x = std::equal_range(vector_1.cbegin(), vector_1.cend(), v);
        auto y = liuyunbin::equal_range(vector_1.cbegin(), vector_1.cend(), v);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};

        int v = 10;
        auto x = std::equal_range(vector_1.cbegin(), vector_1.cend(), v);
        auto y = liuyunbin::equal_range(vector_1.cbegin(), vector_1.cend(), v);
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_fill) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};

        int v = 3;
        std::fill(forward_list_1.begin(), forward_list_1.end(), v);
        liuyunbin::fill(forward_list_2.begin(), forward_list_2.end(), v);
        EXPECT_EQ(forward_list_1, forward_list_2);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};
        std::list<int> list_2 = {5, 6, 7, 8, 9};

        int v = 3;
        std::fill(list_1.begin(), list_1.end(), v);
        liuyunbin::fill(list_2.begin(), list_2.end(), v);
        EXPECT_EQ(list_1, list_2);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {5, 6, 7, 8, 9};

        int v = 3;
        std::fill(vector_1.begin(), vector_1.end(), v);
        liuyunbin::fill(vector_2.begin(), vector_2.end(), v);
        EXPECT_EQ(vector_1, vector_2);
    }
}

TEST(test_algorithm, test_fill_n) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};

        int v = 3;
        int n = 5;
        std::fill_n(forward_list_1.begin(), n, v);
        liuyunbin::fill_n(forward_list_2.begin(), n, v);
        EXPECT_EQ(forward_list_1, forward_list_2);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};
        std::list<int> list_2 = {5, 6, 7, 8, 9};

        int v = 3;
        int n = 5;
        std::fill_n(list_1.begin(), n, v);
        liuyunbin::fill_n(list_2.begin(), n, v);
        EXPECT_EQ(list_1, list_2);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {5, 6, 7, 8, 9};

        int v = 3;
        int n = 5;
        std::fill_n(vector_1.begin(), n, v);
        liuyunbin::fill_n(vector_2.begin(), n, v);
        EXPECT_EQ(vector_1, vector_2);
    }
}

TEST(test_algorithm, test_find_end) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {1, 2, 3};

        auto x = std::find_end(forward_list_1.cbegin(), forward_list_1.cend(),
                               forward_list_2.cbegin(), forward_list_2.cend());
        auto y =
            liuyunbin::find_end(forward_list_1.cbegin(), forward_list_1.cend(),
                                forward_list_2.cbegin(), forward_list_2.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4, 0, 2, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {1, 2, 4};

        auto x = std::find_end(forward_list_1.cbegin(), forward_list_1.cend(),
                               forward_list_2.cbegin(), forward_list_2.cend());
        auto y =
            liuyunbin::find_end(forward_list_1.cbegin(), forward_list_1.cend(),
                                forward_list_2.cbegin(), forward_list_2.cend());
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4};
        std::list<int> list_2 = {1, 2, 3};

        auto x = std::find_end(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                               list_2.cend());
        auto y = liuyunbin::find_end(list_1.cbegin(), list_1.cend(),
                                     list_2.cbegin(), list_2.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4};
        std::list<int> list_2 = {1, 2, 4};

        auto x = std::find_end(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                               list_2.cend());
        auto y = liuyunbin::find_end(list_1.cbegin(), list_1.cend(),
                                     list_2.cbegin(), list_2.cend());
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {1, 2, 3};

        auto x = std::find_end(vector_1.cbegin(), vector_1.cend(),
                               vector_2.cbegin(), vector_2.cend());
        auto y = liuyunbin::find_end(vector_1.cbegin(), vector_1.cend(),
                                     vector_2.cbegin(), vector_2.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {1, 2, 3};

        auto x = std::find_end(vector_1.cbegin(), vector_1.cend(),
                               vector_2.cbegin(), vector_2.cend());
        auto y = liuyunbin::find_end(vector_1.cbegin(), vector_1.cend(),
                                     vector_2.cbegin(), vector_2.cend());
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_find) {
    // 输入迭代器 不好测试
    /*
    {
      std::istringstream stream_1("1 2 3 4 5");
      std::istringstream stream_2("1 2 3 4 5");
      int v = 3;
      auto x = std::find(std::istream_iterator<int>(stream_1),
                         std::istream_iterator<int>(), v);
      auto y = liuyunbin::find(std::istream_iterator<int>(stream_2),
                               std::istream_iterator<int>(), v);
      EXPECT_EQ(x, y);
    }
    {
      std::istringstream stream_1("1 2 3 4 5");
      std::istringstream stream_2("1 2 3 4 5");
      int v = 10;
      auto x = std::find(std::istream_iterator<int>(stream_1),
                         std::istream_iterator<int>(), v);
      auto y = liuyunbin::find(std::istream_iterator<int>(stream_2),
                               std::istream_iterator<int>(), v);
      EXPECT_EQ(x, y);
    }
    */

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        int v = 3;
        auto x = std::find(forward_list_1.cbegin(), forward_list_1.cend(), v);
        auto y =
            liuyunbin::find(forward_list_1.cbegin(), forward_list_1.cend(), v);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        int v = 10;
        auto x = std::find(forward_list_1.cbegin(), forward_list_1.cend(), v);
        auto y =
            liuyunbin::find(forward_list_1.cbegin(), forward_list_1.cend(), v);
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        int v = 3;
        auto x = std::find(list_1.cbegin(), list_1.cend(), v);
        auto y = liuyunbin::find(list_1.cbegin(), list_1.cend(), v);
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        int v = 10;
        auto x = std::find(list_1.cbegin(), list_1.cend(), v);
        auto y = liuyunbin::find(list_1.cbegin(), list_1.cend(), v);
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        int v = 3;
        auto x = std::find(vector_1.cbegin(), vector_1.cend(), v);
        auto y = liuyunbin::find(vector_1.cbegin(), vector_1.cend(), v);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        int v = 10;
        auto x = std::find(vector_1.cbegin(), vector_1.cend(), v);
        auto y = liuyunbin::find(vector_1.cbegin(), vector_1.cend(), v);
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_find_first_of) {
    // 输入迭代器 不好测试

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};

        auto x =
            std::find_first_of(forward_list_1.cbegin(), forward_list_1.cend(),
                               forward_list_2.cbegin(), forward_list_2.cend());
        auto y = liuyunbin::find_first_of(
            forward_list_1.cbegin(), forward_list_1.cend(),
            forward_list_2.cbegin(), forward_list_2.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9, 2};

        auto x =
            std::find_first_of(forward_list_1.cbegin(), forward_list_1.cend(),
                               forward_list_2.cbegin(), forward_list_2.cend());
        auto y = liuyunbin::find_first_of(
            forward_list_1.cbegin(), forward_list_1.cend(),
            forward_list_2.cbegin(), forward_list_2.cend());
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};
        std::list<int> list_2 = {5, 6, 7, 8, 9};

        auto x = std::find_first_of(list_1.cbegin(), list_1.cend(),
                                    list_2.cbegin(), list_2.cend());
        auto y = liuyunbin::find_first_of(list_1.cbegin(), list_1.cend(),
                                          list_2.cbegin(), list_2.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};
        std::list<int> list_2 = {5, 6, 7, 8, 9, 2};

        auto x = std::find_first_of(list_1.cbegin(), list_1.cend(),
                                    list_2.cbegin(), list_2.cend());
        auto y = liuyunbin::find_first_of(list_1.cbegin(), list_1.cend(),
                                          list_2.cbegin(), list_2.cend());
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {5, 6, 7, 8, 9};

        auto x = std::find_first_of(vector_1.cbegin(), vector_1.cend(),
                                    vector_2.cbegin(), vector_2.cend());
        auto y = liuyunbin::find_first_of(vector_1.cbegin(), vector_1.cend(),
                                          vector_2.cbegin(), vector_2.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {5, 6, 7, 8, 9, 2};

        auto x = std::find_first_of(vector_1.cbegin(), vector_1.cend(),
                                    vector_2.cbegin(), vector_2.cend());
        auto y = liuyunbin::find_first_of(vector_1.cbegin(), vector_1.cend(),
                                          vector_2.cbegin(), vector_2.cend());
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_find_if) {
    // 输入迭代器 不好测试

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v == 3; };
        auto x =
            std::find_if(forward_list_1.cbegin(), forward_list_1.cend(), f);
        auto y = liuyunbin::find_if(forward_list_1.cbegin(),
                                    forward_list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v == 10; };
        auto x =
            std::find_if(forward_list_1.cbegin(), forward_list_1.cend(), f);
        auto y = liuyunbin::find_if(forward_list_1.cbegin(),
                                    forward_list_1.cend(), f);
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v == 3; };
        auto x = std::find_if(list_1.cbegin(), list_1.cend(), f);
        auto y = liuyunbin::find_if(list_1.cbegin(), list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v == 10; };
        auto x = std::find_if(list_1.cbegin(), list_1.cend(), f);
        auto y = liuyunbin::find_if(list_1.cbegin(), list_1.cend(), f);
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v == 3; };
        auto x = std::find_if(vector_1.cbegin(), vector_1.cend(), f);
        auto y = liuyunbin::find_if(vector_1.cbegin(), vector_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v == 10; };
        auto x = std::find_if(vector_1.cbegin(), vector_1.cend(), f);
        auto y = liuyunbin::find_if(vector_1.cbegin(), vector_1.cend(), f);
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_find_if_not) {
    // 输入迭代器 不好测试

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v == 3; };
        auto x =
            std::find_if_not(forward_list_1.cbegin(), forward_list_1.cend(), f);
        auto y = liuyunbin::find_if_not(forward_list_1.cbegin(),
                                        forward_list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v == 10; };
        auto x =
            std::find_if_not(forward_list_1.cbegin(), forward_list_1.cend(), f);
        auto y = liuyunbin::find_if_not(forward_list_1.cbegin(),
                                        forward_list_1.cend(), f);
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v == 3; };
        auto x = std::find_if_not(list_1.cbegin(), list_1.cend(), f);
        auto y = liuyunbin::find_if_not(list_1.cbegin(), list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v == 10; };
        auto x = std::find_if_not(list_1.cbegin(), list_1.cend(), f);
        auto y = liuyunbin::find_if_not(list_1.cbegin(), list_1.cend(), f);
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v == 3; };
        auto x = std::find_if_not(vector_1.cbegin(), vector_1.cend(), f);
        auto y = liuyunbin::find_if_not(vector_1.cbegin(), vector_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v == 10; };
        auto x = std::find_if_not(vector_1.cbegin(), vector_1.cend(), f);
        auto y = liuyunbin::find_if_not(vector_1.cbegin(), vector_1.cend(), f);
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_for_each) {
    // 输入迭代器
    {
        std::istringstream stream_1("1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5");

        std::vector<int> ve_1;
        std::vector<int> ve_2;

        auto f_1 = [&ve_1](const int &v) { return ve_1.push_back(v); };
        auto f_2 = [&ve_2](const int &v) { return ve_2.push_back(v); };

        std::for_each(std::istream_iterator<int>(stream_1),
                      std::istream_iterator<int>(), f_1);
        liuyunbin::for_each(std::istream_iterator<int>(stream_2),
                            std::istream_iterator<int>(), f_2);
        EXPECT_EQ(ve_1, ve_2);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};

        std::vector<int> ve_1;
        std::vector<int> ve_2;

        auto f_1 = [&ve_1](const int &v) { return ve_1.push_back(v); };
        auto f_2 = [&ve_2](const int &v) { return ve_2.push_back(v); };

        std::for_each(forward_list_1.cbegin(), forward_list_1.cend(), f_1);
        liuyunbin::for_each(forward_list_1.cbegin(), forward_list_1.cend(),
                            f_2);
        EXPECT_EQ(ve_1, ve_2);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};

        std::vector<int> ve_1;
        std::vector<int> ve_2;

        auto f_1 = [&ve_1](const int &v) { return ve_1.push_back(v); };
        auto f_2 = [&ve_2](const int &v) { return ve_2.push_back(v); };

        std::for_each(list_1.cbegin(), list_1.cend(), f_1);
        liuyunbin::for_each(list_1.cbegin(), list_1.cend(), f_2);
        EXPECT_EQ(ve_1, ve_2);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};

        std::vector<int> ve_1;
        std::vector<int> ve_2;

        auto f_1 = [&ve_1](const int &v) { return ve_1.push_back(v); };
        auto f_2 = [&ve_2](const int &v) { return ve_2.push_back(v); };

        std::for_each(vector_1.cbegin(), vector_1.cend(), f_1);
        liuyunbin::for_each(vector_1.cbegin(), vector_1.cend(), f_2);
        EXPECT_EQ(ve_1, ve_2);
    }
}

TEST(test_algorithm, test_generate) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};

        auto f = []() { return 1; };

        std::generate(forward_list_1.begin(), forward_list_1.end(), f);
        liuyunbin::generate(forward_list_2.begin(), forward_list_2.end(), f);
        EXPECT_EQ(forward_list_1, forward_list_2);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};
        std::list<int> list_2 = {5, 6, 7, 8, 9};

        auto f = []() { return 1; };

        std::generate(list_1.begin(), list_1.end(), f);
        liuyunbin::generate(list_2.begin(), list_2.end(), f);
        EXPECT_EQ(list_1, list_2);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {5, 6, 7, 8, 9};

        auto f = []() { return 1; };

        std::generate(vector_1.begin(), vector_1.end(), f);
        liuyunbin::generate(vector_2.begin(), vector_2.end(), f);
        EXPECT_EQ(vector_1, vector_2);
    }
}

TEST(test_algorithm, test_generate_n) {
    // 输出迭代器 不好测试

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};

        auto f = []() { return 1; };
        int n = 5;

        std::generate_n(forward_list_1.begin(), n, f);
        liuyunbin::generate_n(forward_list_2.begin(), n, f);
        EXPECT_EQ(forward_list_1, forward_list_2);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};
        std::list<int> list_2 = {5, 6, 7, 8, 9};

        auto f = []() { return 1; };
        int n = 5;

        std::generate_n(list_1.begin(), n, f);
        liuyunbin::generate_n(list_2.begin(), n, f);
        EXPECT_EQ(list_1, list_2);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {5, 6, 7, 8, 9};

        auto f = []() { return 1; };
        int n = 5;

        std::generate_n(vector_1.begin(), n, f);
        liuyunbin::generate_n(vector_2.begin(), n, f);
        EXPECT_EQ(vector_1, vector_2);
    }
}

TEST(test_algorithm, test_includes) {
    // 输入迭代器
    {
        std::istringstream stream_1("0 1 2 3 4");
        std::istringstream stream_2("5 6 7 8 9");
        std::istringstream stream_3("0 1 2 3 4");
        std::istringstream stream_4("5 6 7 8 9");

        auto x = std::includes(
            std::istream_iterator<int>(stream_1), std::istream_iterator<int>(),
            std::istream_iterator<int>(stream_2), std::istream_iterator<int>());
        auto y = liuyunbin::includes(
            std::istream_iterator<int>(stream_3), std::istream_iterator<int>(),
            std::istream_iterator<int>(stream_4), std::istream_iterator<int>());
        EXPECT_EQ(x, y);
    }
    {
        std::istringstream stream_1("0 1 2 3 4");
        std::istringstream stream_2("2 3 4");
        std::istringstream stream_3("0 1 2 3 4");
        std::istringstream stream_4("2 3 4");

        auto x = std::includes(
            std::istream_iterator<int>(stream_1), std::istream_iterator<int>(),
            std::istream_iterator<int>(stream_2), std::istream_iterator<int>());
        auto y = liuyunbin::includes(
            std::istream_iterator<int>(stream_3), std::istream_iterator<int>(),
            std::istream_iterator<int>(stream_4), std::istream_iterator<int>());
        EXPECT_EQ(x, y);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};

        auto x = std::includes(forward_list_1.cbegin(), forward_list_1.cend(),
                               forward_list_2.cbegin(), forward_list_2.cend());
        auto y =
            liuyunbin::includes(forward_list_1.cbegin(), forward_list_1.cend(),
                                forward_list_2.cbegin(), forward_list_2.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {2, 3, 4};

        auto x = std::includes(forward_list_1.cbegin(), forward_list_1.cend(),
                               forward_list_2.cbegin(), forward_list_2.cend());
        auto y =
            liuyunbin::includes(forward_list_1.cbegin(), forward_list_1.cend(),
                                forward_list_2.cbegin(), forward_list_2.cend());
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};
        std::list<int> list_2 = {5, 6, 7, 8, 9};

        auto x = std::includes(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                               list_2.cend());
        auto y = liuyunbin::includes(list_1.cbegin(), list_1.cend(),
                                     list_2.cbegin(), list_2.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};
        std::list<int> list_2 = {2, 3, 4};

        auto x = std::includes(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                               list_2.cend());
        auto y = liuyunbin::includes(list_1.cbegin(), list_1.cend(),
                                     list_2.cbegin(), list_2.cend());
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {5, 6, 7, 8, 9};

        auto x = std::includes(vector_1.cbegin(), vector_1.cend(),
                               vector_2.cbegin(), vector_2.cend());
        auto y = liuyunbin::includes(vector_1.cbegin(), vector_1.cend(),
                                     vector_2.cbegin(), vector_2.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {2, 3, 4};

        auto x = std::includes(vector_1.cbegin(), vector_1.cend(),
                               vector_2.cbegin(), vector_2.cend());
        auto y = liuyunbin::includes(vector_1.cbegin(), vector_1.cend(),
                                     vector_2.cbegin(), vector_2.cend());
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_inplace_merge) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {7, 8, 0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {7, 8, 0, 1, 2, 3, 4};

        liuyunbin::inplace_merge(forward_list_1.begin(),
                                 std::next(forward_list_1.begin(), 2),
                                 forward_list_1.end());
        liuyunbin::inplace_merge(forward_list_2.begin(),
                                 std::next(forward_list_2.begin(), 2),
                                 forward_list_2.end());
        EXPECT_EQ(forward_list_1, forward_list_2);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {7, 8, 0, 1, 2, 3, 4};
        std::list<int> list_2 = {7, 8, 0, 1, 2, 3, 4};

        std::inplace_merge(list_1.begin(), std::next(list_1.begin(), 2),
                           list_1.end());
        liuyunbin::inplace_merge(list_2.begin(), std::next(list_2.begin(), 2),
                                 list_2.end());
        EXPECT_EQ(list_1, list_2);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {7, 8, 0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {7, 8, 0, 1, 2, 3, 4};

        std::inplace_merge(vector_1.begin(), std::next(vector_1.begin(), 2),
                           vector_1.end());
        liuyunbin::inplace_merge(
            vector_2.begin(), std::next(vector_2.begin(), 2), vector_2.end());
        EXPECT_EQ(vector_1, vector_2);
    }
}

TEST(test_algorithm, test_is_heap) {
    // 随机迭代器
    {
        std::string str = "0123456789";
        EXPECT_EQ(std::is_heap(str.begin(), str.end()),
                  liuyunbin::is_heap(str.begin(), str.end()));
    }
    {
        std::string str = "012abc3456789";
        EXPECT_EQ(std::is_heap(str.begin(), str.end()),
                  liuyunbin::is_heap(str.begin(), str.end()));
    }
}

TEST(test_algorithm, test_is_heap_until) {
    // 随机迭代器
    {
        std::string str = "0123456789";
        EXPECT_EQ(std::is_heap_until(str.begin(), str.end()),
                  liuyunbin::is_heap_until(str.begin(), str.end()));
    }
    {
        std::string str = "012abc3456789";
        EXPECT_EQ(std::is_heap_until(str.begin(), str.end()),
                  liuyunbin::is_heap_until(str.begin(), str.end()));
    }
}

TEST(test_algorithm, test_is_partitioned) {
    // 输入迭代器
    {
        std::istringstream stream_1("1 2 3 4 5 1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5 1 2 3 4 5");
        auto f = [](int v) { return v < 5 ? true : false; };
        auto x = std::is_partitioned(std::istream_iterator<int>(stream_1),
                                     std::istream_iterator<int>(), f);
        auto y = liuyunbin::is_partitioned(std::istream_iterator<int>(stream_2),
                                           std::istream_iterator<int>(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::istringstream stream_1("1 2 3 4 5 7 9 8 6");
        std::istringstream stream_2("1 2 3 4 5 7 9 8 6");
        auto f = [](int v) { return v < 5 ? true : false; };
        auto x = std::is_partitioned(std::istream_iterator<int>(stream_1),
                                     std::istream_iterator<int>(), f);
        auto y = liuyunbin::is_partitioned(std::istream_iterator<int>(stream_2),
                                           std::istream_iterator<int>(), f);
        EXPECT_EQ(x, y);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        auto f = [](int v) { return v < 5 ? true : false; };
        auto x = std::is_partitioned(forward_list_1.cbegin(),
                                     forward_list_1.cend(), f);
        auto y = liuyunbin::is_partitioned(forward_list_1.cbegin(),
                                           forward_list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 7, 9, 8, 6};
        auto f = [](int v) { return v < 5 ? true : false; };
        auto x = std::is_partitioned(forward_list_1.cbegin(),
                                     forward_list_1.cend(), f);
        auto y = liuyunbin::is_partitioned(forward_list_1.cbegin(),
                                           forward_list_1.cend(), f);
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        auto f = [](int v) { return v < 5 ? true : false; };
        auto x = std::is_partitioned(list_1.cbegin(), list_1.cend(), f);
        auto y = liuyunbin::is_partitioned(list_1.cbegin(), list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 7, 9, 8, 6};
        auto f = [](int v) { return v < 5 ? true : false; };
        auto x = std::is_partitioned(list_1.cbegin(), list_1.cend(), f);
        auto y = liuyunbin::is_partitioned(list_1.cbegin(), list_1.cend(), f);
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        auto f = [](int v) { return v < 5 ? true : false; };
        auto x = std::is_partitioned(vector_1.cbegin(), vector_1.cend(), f);
        auto y =
            liuyunbin::is_partitioned(vector_1.cbegin(), vector_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 7, 9, 8, 6};
        auto f = [](int v) { return v < 5 ? true : false; };
        auto x = std::is_partitioned(vector_1.cbegin(), vector_1.cend(), f);
        auto y =
            liuyunbin::is_partitioned(vector_1.cbegin(), vector_1.cend(), f);
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_is_permutation) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {1, 1, 2, 2, 3, 4, 3, 4, 5, 5};
        auto x =
            std::is_permutation(forward_list_1.cbegin(), forward_list_1.cend(),
                                forward_list_2.cbegin());
        auto y = liuyunbin::is_permutation(forward_list_1.cbegin(),
                                           forward_list_1.cend(),
                                           forward_list_2.cbegin());
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {1, 1, 2, 2, 3, 4, 3, 4, 5, 6};
        auto x =
            std::is_permutation(forward_list_1.cbegin(), forward_list_1.cend(),
                                forward_list_2.cbegin());
        auto y = liuyunbin::is_permutation(forward_list_1.cbegin(),
                                           forward_list_1.cend(),
                                           forward_list_2.cbegin());
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 1, 2, 2, 3, 4, 3, 4, 5, 5};
        auto x = std::is_permutation(list_1.cbegin(), list_1.cend(),
                                     list_2.cbegin());
        auto y = liuyunbin::is_permutation(list_1.cbegin(), list_1.cend(),
                                           list_2.cbegin());
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 1, 2, 2, 3, 4, 3, 4, 5, 6};
        auto x = std::is_permutation(list_1.cbegin(), list_1.cend(),
                                     list_2.cbegin());
        auto y = liuyunbin::is_permutation(list_1.cbegin(), list_1.cend(),
                                           list_2.cbegin());
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 1, 2, 2, 3, 4, 3, 4, 5, 5};
        auto x = std::is_permutation(vector_1.cbegin(), vector_1.cend(),
                                     vector_2.cbegin());
        auto y = liuyunbin::is_permutation(vector_1.cbegin(), vector_1.cend(),
                                           vector_2.cbegin());
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 1, 2, 2, 3, 4, 3, 4, 5, 6};
        auto x = std::is_permutation(vector_1.cbegin(), vector_1.cend(),
                                     vector_2.cbegin());
        auto y = liuyunbin::is_permutation(vector_1.cbegin(), vector_1.cend(),
                                           vector_2.cbegin());
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_is_sorted) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        auto x = std::is_sorted(forward_list_1.cbegin(), forward_list_1.cend());
        auto y = liuyunbin::is_sorted(forward_list_1.cbegin(),
                                      forward_list_1.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        auto x = std::is_sorted(forward_list_1.cbegin(), forward_list_1.cend());
        auto y = liuyunbin::is_sorted(forward_list_1.cbegin(),
                                      forward_list_1.cend());
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        auto x = std::is_sorted(list_1.cbegin(), list_1.cend());
        auto y = liuyunbin::is_sorted(list_1.cbegin(), list_1.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        auto x = std::is_sorted(list_1.cbegin(), list_1.cend());
        auto y = liuyunbin::is_sorted(list_1.cbegin(), list_1.cend());
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        auto x = std::is_sorted(vector_1.cbegin(), vector_1.cend());
        auto y = liuyunbin::is_sorted(vector_1.cbegin(), vector_1.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        auto x = std::is_sorted(vector_1.cbegin(), vector_1.cend());
        auto y = liuyunbin::is_sorted(vector_1.cbegin(), vector_1.cend());
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_is_sorted_until) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        auto x = std::is_sorted_until(forward_list_1.cbegin(),
                                      forward_list_1.cend());
        auto y = liuyunbin::is_sorted_until(forward_list_1.cbegin(),
                                            forward_list_1.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        auto x = std::is_sorted_until(forward_list_1.cbegin(),
                                      forward_list_1.cend());
        auto y = liuyunbin::is_sorted_until(forward_list_1.cbegin(),
                                            forward_list_1.cend());
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        auto x = std::is_sorted_until(list_1.cbegin(), list_1.cend());
        auto y = liuyunbin::is_sorted_until(list_1.cbegin(), list_1.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        auto x = std::is_sorted_until(list_1.cbegin(), list_1.cend());
        auto y = liuyunbin::is_sorted_until(list_1.cbegin(), list_1.cend());
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        auto x = std::is_sorted_until(vector_1.cbegin(), vector_1.cend());
        auto y = liuyunbin::is_sorted_until(vector_1.cbegin(), vector_1.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        auto x = std::is_sorted_until(vector_1.cbegin(), vector_1.cend());
        auto y = liuyunbin::is_sorted_until(vector_1.cbegin(), vector_1.cend());
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_iter_swap) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5};
        std::iter_swap(forward_list_1.begin(),
                       std::next(forward_list_1.begin(), 2));
        liuyunbin::iter_swap(forward_list_2.begin(),
                             std::next(forward_list_2.begin(), 2));
        EXPECT_EQ(forward_list_1, forward_list_2);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5};
        std::iter_swap(list_1.begin(), std::next(list_1.begin(), 2));
        liuyunbin::iter_swap(list_2.begin(), std::next(list_2.begin(), 2));
        EXPECT_EQ(list_1, list_2);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5};
        std::iter_swap(vector_1.begin(), std::next(vector_1.begin(), 2));
        liuyunbin::iter_swap(vector_2.begin(), std::next(vector_2.begin(), 2));
        EXPECT_EQ(vector_1, vector_2);
    }
}

TEST(test_algorithm, test_lexicographical_compare) {
    // 输入迭代器
    {
        std::istringstream stream_1("0 1 2 3 4");
        std::istringstream stream_2("5 6 7 8 9");
        std::istringstream stream_3("0 1 2 3 4");
        std::istringstream stream_4("5 6 7 8 9");

        auto x = std::lexicographical_compare(
            std::istream_iterator<int>(stream_1), std::istream_iterator<int>(),
            std::istream_iterator<int>(stream_2), std::istream_iterator<int>());
        auto y = liuyunbin::lexicographical_compare(
            std::istream_iterator<int>(stream_3), std::istream_iterator<int>(),
            std::istream_iterator<int>(stream_4), std::istream_iterator<int>());
        EXPECT_EQ(x, y);
    }
    {
        std::istringstream stream_1("0 1 2 3 4");
        std::istringstream stream_2("0 1 2 3 4");
        std::istringstream stream_3("0 1 2 3 4");
        std::istringstream stream_4("0 1 2 3 4");

        auto x = std::lexicographical_compare(
            std::istream_iterator<int>(stream_1), std::istream_iterator<int>(),
            std::istream_iterator<int>(stream_2), std::istream_iterator<int>());
        auto y = liuyunbin::lexicographical_compare(
            std::istream_iterator<int>(stream_3), std::istream_iterator<int>(),
            std::istream_iterator<int>(stream_4), std::istream_iterator<int>());
        EXPECT_EQ(x, y);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};

        auto x = std::lexicographical_compare(
            forward_list_1.cbegin(), forward_list_1.cend(),
            forward_list_2.cbegin(), forward_list_2.cend());
        auto y = liuyunbin::lexicographical_compare(
            forward_list_1.cbegin(), forward_list_1.cend(),
            forward_list_2.cbegin(), forward_list_2.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};

        auto x = std::lexicographical_compare(
            forward_list_1.cbegin(), forward_list_1.cend(),
            forward_list_1.cbegin(), forward_list_1.cend());
        auto y = liuyunbin::lexicographical_compare(
            forward_list_1.cbegin(), forward_list_1.cend(),
            forward_list_1.cbegin(), forward_list_1.cend());
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};
        std::list<int> list_2 = {5, 6, 7, 8, 9};

        auto x = std::lexicographical_compare(list_1.cbegin(), list_1.cend(),
                                              list_2.cbegin(), list_2.cend());
        auto y = liuyunbin::lexicographical_compare(
            list_1.cbegin(), list_1.cend(), list_2.cbegin(), list_2.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};

        auto x = std::lexicographical_compare(list_1.cbegin(), list_1.cend(),
                                              list_1.cbegin(), list_1.cend());
        auto y = liuyunbin::lexicographical_compare(
            list_1.cbegin(), list_1.cend(), list_1.cbegin(), list_1.cend());
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {5, 6, 7, 8, 9};

        auto x =
            std::lexicographical_compare(vector_1.cbegin(), vector_1.cend(),
                                         vector_2.cbegin(), vector_2.cend());
        auto y = liuyunbin::lexicographical_compare(
            vector_1.cbegin(), vector_1.cend(), vector_2.cbegin(),
            vector_2.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};

        auto x =
            std::lexicographical_compare(vector_1.cbegin(), vector_1.cend(),
                                         vector_1.cbegin(), vector_1.cend());
        auto y = liuyunbin::lexicographical_compare(
            vector_1.cbegin(), vector_1.cend(), vector_1.cbegin(),
            vector_1.cend());
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_lower_bound) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};

        int v = 3;
        auto x =
            std::lower_bound(forward_list_1.cbegin(), forward_list_1.cend(), v);
        auto y = liuyunbin::lower_bound(forward_list_1.cbegin(),
                                        forward_list_1.cend(), v);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};

        int v = 10;
        auto x =
            std::lower_bound(forward_list_1.cbegin(), forward_list_1.cend(), v);
        auto y = liuyunbin::lower_bound(forward_list_1.cbegin(),
                                        forward_list_1.cend(), v);
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};

        int v = 3;
        auto x = std::lower_bound(list_1.cbegin(), list_1.cend(), v);
        auto y = liuyunbin::lower_bound(list_1.cbegin(), list_1.cend(), v);
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};

        int v = 10;
        auto x = std::lower_bound(list_1.cbegin(), list_1.cend(), v);
        auto y = liuyunbin::lower_bound(list_1.cbegin(), list_1.cend(), v);
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};

        int v = 3;
        auto x = std::lower_bound(vector_1.cbegin(), vector_1.cend(), v);
        auto y = liuyunbin::lower_bound(vector_1.cbegin(), vector_1.cend(), v);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};

        int v = 10;
        auto x = std::lower_bound(vector_1.cbegin(), vector_1.cend(), v);
        auto y = liuyunbin::lower_bound(vector_1.cbegin(), vector_1.cend(), v);
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_make_heap) {
    // 随机迭代器
    {
        std::string str_1 = "98653";
        std::string str_2 = "98653";
        std::make_heap(str_1.begin(), str_1.end());
        liuyunbin::make_heap(str_2.begin(), str_2.end());
        EXPECT_EQ(str_1, str_2);
    }
    {
        std::string str_1 = "98657";
        std::string str_2 = "98657";
        std::make_heap(str_1.begin(), str_1.end());
        liuyunbin::make_heap(str_2.begin(), str_2.end());
        EXPECT_EQ(str_1, str_2);
    }
}

TEST(test_algorithm, test_max_element) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 8, 4, 5};
        auto x =
            std::max_element(forward_list_1.cbegin(), forward_list_1.cend());
        auto y = liuyunbin::max_element(forward_list_1.cbegin(),
                                        forward_list_1.cend());
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 8, 4, 5};
        auto x = std::max_element(list_1.cbegin(), list_1.cend());
        auto y = liuyunbin::max_element(list_1.cbegin(), list_1.cend());
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 8, 4, 5};
        auto x = std::max_element(vector_1.cbegin(), vector_1.cend());
        auto y = liuyunbin::max_element(vector_1.cbegin(), vector_1.cend());
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_max) {
    {
        int x = 10;
        int y = 5;
        EXPECT_EQ(std::max(x, y), liuyunbin::max(x, y));
    }
    {
        std::initializer_list<int> li = {1, 2, 3, 4, 5};
        EXPECT_EQ(std::max(li), liuyunbin::max(li));
    }
}

TEST(test_algorithm, test_merge) {
    // 输入迭代器
    {
        std::istringstream stream_1("0 1 2 3 4");
        std::istringstream stream_2("5 6 7 8 9");
        std::istringstream stream_3("0 1 2 3 4");
        std::istringstream stream_4("5 6 7 8 9");

        std::forward_list<int> forward_list_5 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_6 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

        std::merge(std::istream_iterator<int>(stream_1),
                   std::istream_iterator<int>(),
                   std::istream_iterator<int>(stream_2),
                   std::istream_iterator<int>(), forward_list_5.begin());
        liuyunbin::merge(std::istream_iterator<int>(stream_3),
                         std::istream_iterator<int>(),
                         std::istream_iterator<int>(stream_4),
                         std::istream_iterator<int>(), forward_list_6.begin());
        EXPECT_EQ(forward_list_5, forward_list_6);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};

        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

        std::merge(forward_list_1.cbegin(), forward_list_1.cend(),
                   forward_list_2.cbegin(), forward_list_2.cend(),
                   forward_list_3.begin());
        liuyunbin::merge(forward_list_1.cbegin(), forward_list_1.cend(),
                         forward_list_2.cbegin(), forward_list_2.cend(),
                         forward_list_4.begin());
        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};
        std::list<int> list_2 = {5, 6, 7, 8, 9};

        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

        std::merge(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                   list_2.cend(), forward_list_3.begin());
        liuyunbin::merge(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                         list_2.cend(), forward_list_4.begin());

        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {5, 6, 7, 8, 9};

        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

        std::merge(vector_1.cbegin(), vector_1.cend(), vector_2.cbegin(),
                   vector_2.cend(), forward_list_3.begin());

        liuyunbin::merge(vector_1.cbegin(), vector_1.cend(), vector_2.cbegin(),
                         vector_2.cend(), forward_list_4.begin());

        EXPECT_EQ(forward_list_3, forward_list_4);
    }
}

TEST(test_algorithm, test_min_element) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 8, 4, 5};
        auto x =
            std::min_element(forward_list_1.cbegin(), forward_list_1.cend());
        auto y = liuyunbin::min_element(forward_list_1.cbegin(),
                                        forward_list_1.cend());
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 8, 4, 5};
        auto x = std::min_element(list_1.cbegin(), list_1.cend());
        auto y = liuyunbin::min_element(list_1.cbegin(), list_1.cend());
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 8, 4, 5};
        auto x = std::min_element(vector_1.cbegin(), vector_1.cend());
        auto y = liuyunbin::min_element(vector_1.cbegin(), vector_1.cend());
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_minmax_element) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 8, 4, 5};
        auto x =
            std::minmax_element(forward_list_1.cbegin(), forward_list_1.cend());
        auto y = liuyunbin::minmax_element(forward_list_1.cbegin(),
                                           forward_list_1.cend());
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 8, 4, 5};
        auto x = std::minmax_element(list_1.cbegin(), list_1.cend());
        auto y = liuyunbin::minmax_element(list_1.cbegin(), list_1.cend());
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 8, 4, 5};
        auto x = std::minmax_element(vector_1.cbegin(), vector_1.cend());
        auto y = liuyunbin::minmax_element(vector_1.cbegin(), vector_1.cend());
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_minmax) {
    {
        int x = 10;
        int y = 5;
        EXPECT_EQ(std::minmax(x, y), liuyunbin::minmax(x, y));
    }
    {
        std::initializer_list<int> li = {1, 2, 3, 4, 5};
        EXPECT_EQ(std::minmax(li), liuyunbin::minmax(li));
    }
}

TEST(test_algorithm, test_min) {
    {
        int x = 10;
        int y = 5;
        EXPECT_EQ(std::min(x, y), liuyunbin::min(x, y));
    }
    {
        std::initializer_list<int> li = {1, 2, 3, 4, 5};
        EXPECT_EQ(std::min(li), liuyunbin::min(li));
    }
}

TEST(test_algorithm, test_mismatch) {
    // 输入迭代器 不好测试

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};

        auto x = std::mismatch(forward_list_1.cbegin(), forward_list_1.cend(),
                               forward_list_2.cbegin());
        auto y =
            liuyunbin::mismatch(forward_list_1.cbegin(), forward_list_1.cend(),
                                forward_list_2.cbegin());
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};

        auto x = std::mismatch(forward_list_1.cbegin(), forward_list_1.cend(),
                               forward_list_1.cbegin());
        auto y =
            liuyunbin::mismatch(forward_list_1.cbegin(), forward_list_1.cend(),
                                forward_list_1.cbegin());
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};
        std::list<int> list_2 = {5, 6, 7, 8, 9};

        auto x = std::mismatch(list_1.cbegin(), list_1.cend(), list_2.cbegin());
        auto y = liuyunbin::mismatch(list_1.cbegin(), list_1.cend(),
                                     list_2.cbegin());
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};

        auto x = std::mismatch(list_1.cbegin(), list_1.cend(), list_1.cbegin());
        auto y = liuyunbin::mismatch(list_1.cbegin(), list_1.cend(),
                                     list_1.cbegin());
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {5, 6, 7, 8, 9};

        auto x = std::mismatch(vector_1.cbegin(), vector_1.cend(),
                               vector_2.cbegin());
        auto y = liuyunbin::mismatch(vector_1.cbegin(), vector_1.cend(),
                                     vector_2.cbegin());
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};

        auto x = std::mismatch(vector_1.cbegin(), vector_1.cend(),
                               vector_1.cbegin());
        auto y = liuyunbin::mismatch(vector_1.cbegin(), vector_1.cend(),
                                     vector_1.cbegin());
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_move_backward) {
    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        std::list<int> list_2 = {0, 1, 2, 3, 4};
        std::list<int> list_3 = {5, 6, 7, 8, 9};
        std::move_backward(list_1.cbegin(), list_1.cend(), list_2.end());
        liuyunbin::move_backward(list_1.cbegin(), list_1.cend(), list_3.end());
        EXPECT_EQ(list_2, list_3);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        std::list<int> list_2 = {0, 1, 2, 3, 4};
        std::list<int> list_3 = {5, 6, 7, 8, 9};
        std::move_backward(vector_1.cbegin(), vector_1.cend(), list_2.end());
        liuyunbin::move_backward(vector_1.cbegin(), vector_1.cend(),
                                 list_3.end());
        EXPECT_EQ(list_2, list_3);
    }
}

TEST(test_algorithm, test_move) {
    // 输入迭代器
    {
        std::istringstream stream_1("1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5");
        std::forward_list<int> forward_list_3 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_4 = {5, 6, 7, 8, 9};
        std::move(std::istream_iterator<int>(stream_1),
                  std::istream_iterator<int>(), forward_list_3.begin());
        liuyunbin::move(std::istream_iterator<int>(stream_2),
                        std::istream_iterator<int>(), forward_list_4.begin());
        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_3 = {5, 6, 7, 8, 9};
        std::move(forward_list_1.cbegin(), forward_list_1.cend(),
                  forward_list_2.begin());
        liuyunbin::move(forward_list_1.cbegin(), forward_list_1.cend(),
                        forward_list_3.begin());
        EXPECT_EQ(forward_list_2, forward_list_3);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_3 = {5, 6, 7, 8, 9};
        std::move(list_1.cbegin(), list_1.cend(), forward_list_2.begin());
        liuyunbin::move(list_1.cbegin(), list_1.cend(), forward_list_3.begin());
        EXPECT_EQ(forward_list_2, forward_list_3);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_3 = {5, 6, 7, 8, 9};
        std::move(vector_1.cbegin(), vector_1.cend(), forward_list_2.begin());
        liuyunbin::move(vector_1.cbegin(), vector_1.cend(),
                        forward_list_3.begin());
        EXPECT_EQ(forward_list_2, forward_list_3);
    }
}

TEST(test_algorithm, test_next_permutation) {
    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5};
        std::next_permutation(list_1.begin(), list_1.end());
        liuyunbin::next_permutation(list_2.begin(), list_2.end());
        EXPECT_EQ(list_1, list_2);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 3};
        std::list<int> list_2 = {1, 2, 3, 4, 5, 3};
        std::next_permutation(list_1.begin(), list_1.end());
        liuyunbin::next_permutation(list_2.begin(), list_2.end());
        EXPECT_EQ(list_1, list_2);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5};
        std::next_permutation(vector_1.begin(), vector_1.end());
        liuyunbin::next_permutation(vector_2.begin(), vector_2.end());
        EXPECT_EQ(vector_1, vector_2);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 3};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5, 3};
        std::next_permutation(vector_1.begin(), vector_1.end());
        liuyunbin::next_permutation(vector_2.begin(), vector_2.end());
        EXPECT_EQ(vector_1, vector_2);
    }
}

TEST(test_algorithm, test_none_of) {
    // 输入迭代器
    {
        std::istringstream stream_1("1 2 3 4 5 1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5 1 2 3 4 5");
        auto f = [](int v) { return v >= 5 ? true : false; };
        auto x = std::none_of(std::istream_iterator<int>(stream_1),
                              std::istream_iterator<int>(), f);
        auto y = liuyunbin::none_of(std::istream_iterator<int>(stream_2),
                                    std::istream_iterator<int>(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::istringstream stream_1("1 2 3 4 1 2 3 4");
        std::istringstream stream_2("1 2 3 4 1 2 3 4");
        auto f = [](int v) { return v >= 5 ? true : false; };
        auto x = std::none_of(std::istream_iterator<int>(stream_1),
                              std::istream_iterator<int>(), f);
        auto y = liuyunbin::none_of(std::istream_iterator<int>(stream_2),
                                    std::istream_iterator<int>(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::istringstream stream_1("1 2 3 4 5 1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5 1 2 3 4 5");
        auto f = [](char ch) { return std::isalpha(ch) ? true : false; };
        auto x = std::none_of(std::istream_iterator<char>(stream_1),
                              std::istream_iterator<char>(), f);
        auto y = liuyunbin::none_of(std::istream_iterator<char>(stream_2),
                                    std::istream_iterator<char>(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::istringstream stream_1("1 2 3 4 5 a 1 2 3 4 5 a");
        std::istringstream stream_2("1 2 3 4 5 a 1 2 3 4 5 a");
        auto f = [](char ch) { return std::isalpha(ch) ? true : false; };
        auto x = std::none_of(std::istream_iterator<char>(stream_1),
                              std::istream_iterator<char>(), f);
        auto y = liuyunbin::none_of(std::istream_iterator<char>(stream_2),
                                    std::istream_iterator<char>(), f);
        EXPECT_EQ(x, y);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        auto f = [](int v) { return v >= 5 ? true : false; };
        auto x =
            std::none_of(forward_list_1.cbegin(), forward_list_1.cend(), f);
        auto y = liuyunbin::none_of(forward_list_1.cbegin(),
                                    forward_list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 1, 2, 3, 4};
        auto f = [](int v) { return v >= 5 ? true : false; };
        auto x =
            std::none_of(forward_list_1.cbegin(), forward_list_1.cend(), f);
        auto y = liuyunbin::none_of(forward_list_1.cbegin(),
                                    forward_list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<char> forward_list_1 = {'1', '2', '3', '4', '5',
                                                  '1', '2', '3', '4', '5'};
        auto f = [](char ch) { return std::isalpha(ch) ? true : false; };
        auto x =
            std::none_of(forward_list_1.cbegin(), forward_list_1.cend(), f);
        auto y = liuyunbin::none_of(forward_list_1.cbegin(),
                                    forward_list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<char> forward_list_1 = {'1', '2', '3', '4', '5', 'a',
                                                  '1', '2', '3', '4', '5', 'a'};
        auto f = [](char ch) { return std::isalpha(ch) ? true : false; };
        auto x =
            std::none_of(forward_list_1.cbegin(), forward_list_1.cend(), f);
        auto y = liuyunbin::none_of(forward_list_1.cbegin(),
                                    forward_list_1.cend(), f);
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        auto f = [](int v) { return v >= 5 ? true : false; };
        auto x = std::none_of(list_1.cbegin(), list_1.cend(), f);
        auto y = liuyunbin::none_of(list_1.cbegin(), list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 1, 2, 3, 4};
        auto f = [](int v) { return v >= 5 ? true : false; };
        auto x = std::none_of(list_1.cbegin(), list_1.cend(), f);
        auto y = liuyunbin::none_of(list_1.cbegin(), list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::list<char> list_1 = {'1', '2', '3', '4', '5',
                                  '1', '2', '3', '4', '5'};
        auto f = [](char ch) { return std::isalpha(ch) ? true : false; };
        auto x = std::none_of(list_1.cbegin(), list_1.cend(), f);
        auto y = liuyunbin::none_of(list_1.cbegin(), list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::list<char> list_1 = {'1', '2', '3', '4', '5', 'a',
                                  '1', '2', '3', '4', '5', 'a'};
        auto f = [](char ch) { return std::isalpha(ch) ? true : false; };
        auto x = std::none_of(list_1.cbegin(), list_1.cend(), f);
        auto y = liuyunbin::none_of(list_1.cbegin(), list_1.cend(), f);
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        auto f = [](int v) { return v >= 5 ? true : false; };
        auto x = std::none_of(vector_1.cbegin(), vector_1.cend(), f);
        auto y = liuyunbin::none_of(vector_1.cbegin(), vector_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 1, 2, 3, 4};
        auto f = [](int v) { return v >= 5 ? true : false; };
        auto x = std::none_of(vector_1.cbegin(), vector_1.cend(), f);
        auto y = liuyunbin::none_of(vector_1.cbegin(), vector_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<char> vector_1 = {'1', '2', '3', '4', '5',
                                      '1', '2', '3', '4', '5'};
        auto f = [](char ch) { return std::isalpha(ch) ? true : false; };
        auto x = std::none_of(vector_1.cbegin(), vector_1.cend(), f);
        auto y = liuyunbin::none_of(vector_1.cbegin(), vector_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<char> vector_1 = {'1', '2', '3', '4', '5', 'a',
                                      '1', '2', '3', '4', '5', 'a'};
        auto f = [](char ch) { return std::isalpha(ch) ? true : false; };
        auto x = std::none_of(vector_1.cbegin(), vector_1.cend(), f);
        auto y = liuyunbin::none_of(vector_1.cbegin(), vector_1.cend(), f);
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_nth_element) {
    // 随机迭代器
    std::string str_1 = "246810";
    std::string str_2 = "864210";
    std::nth_element(str_1.begin(), str_1.begin() + 3, str_1.end());
    liuyunbin::nth_element(str_2.begin(), str_2.begin() + 3, str_2.end());
    EXPECT_EQ(str_1[2], str_2[2]);
}

TEST(test_algorithm, test_partial_sort_copy) {
    // 随机迭代器
    std::string str_1 = "98653";
    std::string str_2 = "98653";
    std::string str_3 = "11111";
    std::string str_4 = "11111";
    std::partial_sort_copy(str_1.begin(), str_1.end(), str_3.begin(),
                           str_3.end());
    liuyunbin::partial_sort_copy(str_2.begin(), str_2.end(), str_4.begin(),
                                 str_4.end());
    EXPECT_EQ(str_3, str_4);
}

TEST(test_algorithm, test_partial_sort) {
    // 随机迭代器
    std::string str_1 = "98653";
    std::string str_2 = "98653";
    std::partial_sort(str_1.begin(), str_1.begin() + 3, str_1.end());
    liuyunbin::partial_sort(str_2.begin(), str_2.begin() + 3, str_2.end());
    EXPECT_EQ(std::equal(str_1.begin(), str_1.begin() + 3, str_2.begin()),
              true);
}

TEST(test_algorithm, test_partition_copy) {
    // 输入迭代器
    {
        std::istringstream stream_1("1 2 3 4 5 1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5 1 2 3 4 5");
        auto f = [](int v) { return v < 5 ? true : false; };
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_5 = {0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_6 = {0, 0, 0, 0, 0, 0, 0, 0};
        std::partition_copy(std::istream_iterator<int>(stream_1),
                            std::istream_iterator<int>(),
                            forward_list_3.begin(), forward_list_4.begin(), f);
        std::partition_copy(std::istream_iterator<int>(stream_2),
                            std::istream_iterator<int>(),
                            forward_list_5.begin(), forward_list_6.begin(), f);
        EXPECT_EQ(forward_list_3, forward_list_5);
        EXPECT_EQ(forward_list_4, forward_list_6);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_5 = {0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_6 = {0, 0, 0, 0, 0, 0, 0, 0};
        auto f = [](int v) { return v < 5 ? true : false; };

        std::partition_copy(forward_list_1.begin(), forward_list_1.end(),
                            forward_list_3.begin(), forward_list_4.begin(), f);
        std::partition_copy(forward_list_2.begin(), forward_list_2.end(),
                            forward_list_5.begin(), forward_list_6.begin(), f);

        EXPECT_EQ(forward_list_3, forward_list_5);
        EXPECT_EQ(forward_list_4, forward_list_6);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_5 = {0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_6 = {0, 0, 0, 0, 0, 0, 0, 0};
        auto f = [](int v) { return v < 5 ? true : false; };

        std::partition_copy(list_1.begin(), list_1.end(),
                            forward_list_3.begin(), forward_list_4.begin(), f);
        std::partition_copy(list_2.begin(), list_2.end(),
                            forward_list_5.begin(), forward_list_6.begin(), f);

        EXPECT_EQ(forward_list_3, forward_list_5);
        EXPECT_EQ(forward_list_4, forward_list_6);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_5 = {0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_6 = {0, 0, 0, 0, 0, 0, 0, 0};
        auto f = [](int v) { return v < 5 ? true : false; };

        std::partition_copy(vector_1.begin(), vector_1.end(),
                            forward_list_3.begin(), forward_list_4.begin(), f);
        std::partition_copy(vector_2.begin(), vector_2.end(),
                            forward_list_5.begin(), forward_list_6.begin(), f);

        EXPECT_EQ(forward_list_3, forward_list_5);
        EXPECT_EQ(forward_list_4, forward_list_6);
    }
}

TEST(test_algorithm, test_partition) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        auto f = [](int v) { return v < 5 ? true : false; };
        auto x =
            std::partition(forward_list_1.begin(), forward_list_1.end(), f);
        auto y = liuyunbin::partition(forward_list_1.begin(),
                                      forward_list_1.end(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 7, 9, 8, 6};
        auto f = [](int v) { return v < 5 ? true : false; };
        auto x =
            std::partition(forward_list_1.begin(), forward_list_1.end(), f);
        auto y = liuyunbin::partition(forward_list_1.begin(),
                                      forward_list_1.end(), f);
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        auto f = [](int v) { return v < 5 ? true : false; };
        auto x = std::partition(list_1.begin(), list_1.end(), f);
        auto y = liuyunbin::partition(list_1.begin(), list_1.end(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 7, 9, 8, 6};
        auto f = [](int v) { return v < 5 ? true : false; };
        auto x = std::partition(list_1.begin(), list_1.end(), f);
        auto y = liuyunbin::partition(list_1.begin(), list_1.end(), f);
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        auto f = [](int v) { return v < 5 ? true : false; };
        auto x = std::partition(vector_1.begin(), vector_1.end(), f);
        auto y = liuyunbin::partition(vector_1.begin(), vector_1.end(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 7, 9, 8, 6};
        auto f = [](int v) { return v < 5 ? true : false; };
        auto x = std::partition(vector_1.begin(), vector_1.end(), f);
        auto y = liuyunbin::partition(vector_1.begin(), vector_1.end(), f);
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_partition_point) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v < 3; };
        auto x = std::partition_point(forward_list_1.cbegin(),
                                      forward_list_1.cend(), f);
        auto y = liuyunbin::partition_point(forward_list_1.cbegin(),
                                            forward_list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v == 10; };
        auto x = std::partition_point(forward_list_1.cbegin(),
                                      forward_list_1.cend(), f);
        auto y = liuyunbin::partition_point(forward_list_1.cbegin(),
                                            forward_list_1.cend(), f);
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v < 3; };
        auto x = std::partition_point(list_1.cbegin(), list_1.cend(), f);
        auto y = liuyunbin::partition_point(list_1.cbegin(), list_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v == 10; };
        auto x = std::partition_point(list_1.cbegin(), list_1.cend(), f);
        auto y = liuyunbin::partition_point(list_1.cbegin(), list_1.cend(), f);
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v < 3; };
        auto x = std::partition_point(vector_1.cbegin(), vector_1.cend(), f);
        auto y =
            liuyunbin::partition_point(vector_1.cbegin(), vector_1.cend(), f);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        auto f = [](int v) { return v == 10; };
        auto x = std::partition_point(vector_1.cbegin(), vector_1.cend(), f);
        auto y =
            liuyunbin::partition_point(vector_1.cbegin(), vector_1.cend(), f);
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_pop_heap) {
    // 随机迭代器
    {
        std::string str_1 = "98653";
        std::string str_2 = "98653";
        std::pop_heap(str_1.begin(), str_1.end());
        liuyunbin::pop_heap(str_2.begin(), str_2.end());
        EXPECT_EQ(str_1, str_2);
    }
    {
        std::string str_1 = "98765";
        std::string str_2 = "98765";
        std::pop_heap(str_1.begin(), str_1.end());
        liuyunbin::pop_heap(str_2.begin(), str_2.end());
        EXPECT_EQ(str_1, str_2);
    }
}

TEST(test_algorithm, test_prev_permutation) {
    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5};
        std::prev_permutation(list_1.begin(), list_1.end());
        liuyunbin::prev_permutation(list_2.begin(), list_2.end());
        EXPECT_EQ(list_1, list_2);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 3};
        std::list<int> list_2 = {1, 2, 3, 4, 5, 3};
        std::prev_permutation(list_1.begin(), list_1.end());
        liuyunbin::prev_permutation(list_2.begin(), list_2.end());
        EXPECT_EQ(list_1, list_2);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5};
        std::prev_permutation(vector_1.begin(), vector_1.end());
        liuyunbin::prev_permutation(vector_2.begin(), vector_2.end());
        EXPECT_EQ(vector_1, vector_2);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 3};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5, 3};
        std::prev_permutation(vector_1.begin(), vector_1.end());
        liuyunbin::prev_permutation(vector_2.begin(), vector_2.end());
        EXPECT_EQ(vector_1, vector_2);
    }
}

TEST(test_algorithm, test_push_heap) {
    // 随机迭代器
    {
        std::string str_1 = "98653";
        std::string str_2 = "98653";
        std::push_heap(str_1.begin(), str_1.end());
        liuyunbin::push_heap(str_2.begin(), str_2.end());
        EXPECT_EQ(str_1, str_2);
    }
    {
        std::string str_1 = "98657";
        std::string str_2 = "98657";
        std::push_heap(str_1.begin(), str_1.end());
        liuyunbin::push_heap(str_2.begin(), str_2.end());
        EXPECT_EQ(str_1, str_2);
    }
}

TEST(test_algorithm, test_remove_copy_if) {
    // 输入迭代器
    {
        std::istringstream stream_1("1 2 3 4 5 1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5 1 2 3 4 5");

        auto f = [](char ch) { return std::isdigit(ch) ? true : false; };
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::remove_copy_if(std::istream_iterator<int>(stream_1),
                            std::istream_iterator<int>(),
                            forward_list_3.begin(), f);
        std::remove_copy_if(std::istream_iterator<int>(stream_2),
                            std::istream_iterator<int>(),
                            forward_list_4.begin(), f);
        EXPECT_EQ(forward_list_3, forward_list_4);
    }
    {
        std::istringstream stream_1("1 2 3 4 5 1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5 1 2 3 4 5");

        auto f = [](char ch) { return std::isalpha(ch) ? true : false; };
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::remove_copy_if(std::istream_iterator<int>(stream_1),
                            std::istream_iterator<int>(),
                            forward_list_3.begin(), f);
        std::remove_copy_if(std::istream_iterator<int>(stream_2),
                            std::istream_iterator<int>(),
                            forward_list_4.begin(), f);
        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        auto f = [](const int &v) { return v < 3 ? true : false; };
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::remove_copy_if(forward_list_1.cbegin(), forward_list_1.cend(),
                            forward_list_3.begin(), f);
        std::remove_copy_if(forward_list_2.begin(), forward_list_2.end(),
                            forward_list_4.begin(), f);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        auto f = [](const int &v) { return v > 10 ? true : false; };
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::remove_copy_if(forward_list_1.cbegin(), forward_list_1.cend(),
                            forward_list_3.begin(), f);
        std::remove_copy_if(forward_list_2.begin(), forward_list_2.end(),
                            forward_list_4.begin(), f);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        auto f = [](const int &v) { return v < 3 ? true : false; };
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::remove_copy_if(list_1.cbegin(), list_1.cend(),
                            forward_list_3.begin(), f);
        std::remove_copy_if(list_2.cbegin(), list_2.cend(),
                            forward_list_4.begin(), f);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        auto f = [](const int &v) { return v > 10 ? true : false; };
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::remove_copy_if(list_1.cbegin(), list_1.cend(),
                            forward_list_3.begin(), f);
        std::remove_copy_if(list_2.cbegin(), list_2.cend(),
                            forward_list_4.begin(), f);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        auto f = [](const int &v) { return v < 3 ? true : false; };
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::remove_copy_if(vector_1.cbegin(), vector_1.cend(),
                            forward_list_3.begin(), f);
        std::remove_copy_if(vector_2.cbegin(), vector_2.cend(),
                            forward_list_4.begin(), f);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        auto f = [](const int &v) { return v > 10 ? true : false; };
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::remove_copy_if(vector_1.cbegin(), vector_1.cend(),
                            forward_list_3.begin(), f);
        std::remove_copy_if(vector_2.cbegin(), vector_2.cend(),
                            forward_list_4.begin(), f);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }
}

TEST(test_algorithm, test_remove_copy) {
    // 输入迭代器
    {
        std::istringstream stream_1("1 2 3 4 5 1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5 1 2 3 4 5");

        int v = 3;
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::remove_copy(std::istream_iterator<int>(stream_1),
                         std::istream_iterator<int>(), forward_list_3.begin(),
                         v);
        std::remove_copy(std::istream_iterator<int>(stream_2),
                         std::istream_iterator<int>(), forward_list_4.begin(),
                         v);
        EXPECT_EQ(forward_list_3, forward_list_4);
    }
    {
        std::istringstream stream_1("1 2 3 4 5 1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5 1 2 3 4 5");

        int v = 10;
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::remove_copy(std::istream_iterator<int>(stream_1),
                         std::istream_iterator<int>(), forward_list_3.begin(),
                         v);
        std::remove_copy(std::istream_iterator<int>(stream_2),
                         std::istream_iterator<int>(), forward_list_4.begin(),
                         v);
        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        int v = 3;
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::remove_copy(forward_list_1.cbegin(), forward_list_1.cend(),
                         forward_list_3.begin(), v);
        std::remove_copy(forward_list_2.begin(), forward_list_2.end(),
                         forward_list_4.begin(), v);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        int v = 10;
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::remove_copy(forward_list_1.cbegin(), forward_list_1.cend(),
                         forward_list_3.begin(), v);
        std::remove_copy(forward_list_2.begin(), forward_list_2.end(),
                         forward_list_4.begin(), v);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        int v = 3;
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::remove_copy(list_1.cbegin(), list_1.cend(), forward_list_3.begin(),
                         v);
        std::remove_copy(list_2.cbegin(), list_2.cend(), forward_list_4.begin(),
                         v);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        int v = 10;
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::remove_copy(list_1.cbegin(), list_1.cend(), forward_list_3.begin(),
                         v);
        std::remove_copy(list_2.cbegin(), list_2.cend(), forward_list_4.begin(),
                         v);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        int v = 3;
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::remove_copy(vector_1.cbegin(), vector_1.cend(),
                         forward_list_3.begin(), v);
        std::remove_copy(vector_2.cbegin(), vector_2.cend(),
                         forward_list_4.begin(), v);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        int v = 10;
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::remove_copy(vector_1.cbegin(), vector_1.cend(),
                         forward_list_3.begin(), v);
        std::remove_copy(vector_2.cbegin(), vector_2.cend(),
                         forward_list_4.begin(), v);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }
}

TEST(test_algorithm, test_remove_if) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5};

        auto f = [](const int &v) { return v < 3 ? true : false; };
        std::remove_if(forward_list_1.begin(), forward_list_1.end(), f);
        liuyunbin::remove_if(forward_list_2.begin(), forward_list_2.end(), f);
        EXPECT_EQ(forward_list_1, forward_list_2);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5};

        auto f = [](const int &v) { return v > 10 ? true : false; };
        std::remove_if(forward_list_1.begin(), forward_list_1.end(), f);
        liuyunbin::remove_if(forward_list_2.begin(), forward_list_2.end(), f);
        EXPECT_EQ(forward_list_1, forward_list_2);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5};

        auto f = [](const int &v) { return v < 3 ? true : false; };
        std::remove_if(list_1.begin(), list_1.end(), f);
        liuyunbin::remove_if(list_2.begin(), list_2.end(), f);
        EXPECT_EQ(list_1, list_2);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5};

        auto f = [](const int &v) { return v > 10 ? true : false; };
        std::remove_if(list_1.begin(), list_1.end(), f);
        liuyunbin::remove_if(list_2.begin(), list_2.end(), f);
        EXPECT_EQ(list_1, list_2);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5};

        auto f = [](const int &v) { return v < 3 ? true : false; };
        std::remove_if(vector_1.begin(), vector_1.end(), f);
        liuyunbin::remove_if(vector_2.begin(), vector_2.end(), f);
        EXPECT_EQ(vector_1, vector_2);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5};

        auto f = [](const int &v) { return v > 10 ? true : false; };
        std::remove_if(vector_1.begin(), vector_1.end(), f);
        liuyunbin::remove_if(vector_2.begin(), vector_2.end(), f);
        EXPECT_EQ(vector_1, vector_2);
    }
}

TEST(test_algorithm, test_remove) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5};

        int v = 3;
        std::remove(forward_list_1.begin(), forward_list_1.end(), v);
        liuyunbin::remove(forward_list_2.begin(), forward_list_2.end(), v);
        EXPECT_EQ(forward_list_1, forward_list_2);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5};

        int v = 10;
        std::remove(forward_list_1.begin(), forward_list_1.end(), v);
        liuyunbin::remove(forward_list_2.begin(), forward_list_2.end(), v);
        EXPECT_EQ(forward_list_1, forward_list_2);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5};

        int v = 3;
        std::remove(list_1.begin(), list_1.end(), v);
        liuyunbin::remove(list_2.begin(), list_2.end(), v);
        EXPECT_EQ(list_1, list_2);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5};

        int v = 10;
        std::remove(list_1.begin(), list_1.end(), v);
        liuyunbin::remove(list_2.begin(), list_2.end(), v);
        EXPECT_EQ(list_1, list_2);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5};

        int v = 3;
        std::remove(vector_1.begin(), vector_1.end(), v);
        liuyunbin::remove(vector_2.begin(), vector_2.end(), v);
        EXPECT_EQ(vector_1, vector_2);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5};

        int v = 10;
        std::remove(vector_1.begin(), vector_1.end(), v);
        liuyunbin::remove(vector_2.begin(), vector_2.end(), v);
        EXPECT_EQ(vector_1, vector_2);
    }
}

TEST(test_algorithm, test_replace_copy_if) {
    // 输入迭代器
    {
        std::istringstream stream_1("1 2 3 4 5 1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5 1 2 3 4 5");

        int new_v = 5;
        auto f = [](const int &v) { return v == 3 ? true : false; };
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::replace_copy_if(std::istream_iterator<int>(stream_1),
                             std::istream_iterator<int>(),
                             forward_list_3.begin(), f, new_v);
        std::replace_copy_if(std::istream_iterator<int>(stream_2),
                             std::istream_iterator<int>(),
                             forward_list_4.begin(), f, new_v);
        EXPECT_EQ(forward_list_3, forward_list_4);
    }
    {
        std::istringstream stream_1("1 2 3 4 5 1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5 1 2 3 4 5");

        int new_v = 5;
        auto f = [](const int &v) { return v == 10 ? true : false; };
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::replace_copy_if(std::istream_iterator<int>(stream_1),
                             std::istream_iterator<int>(),
                             forward_list_3.begin(), f, new_v);
        std::replace_copy_if(std::istream_iterator<int>(stream_2),
                             std::istream_iterator<int>(),
                             forward_list_4.begin(), f, new_v);
        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        int new_v = 5;
        auto f = [](const int &v) { return v < 3 ? true : false; };
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::replace_copy_if(forward_list_1.cbegin(), forward_list_1.cend(),
                             forward_list_3.begin(), f, new_v);
        std::replace_copy_if(forward_list_2.begin(), forward_list_2.end(),
                             forward_list_4.begin(), f, new_v);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        int new_v = 5;
        auto f = [](const int &v) { return v > 10 ? true : false; };
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::replace_copy_if(forward_list_1.cbegin(), forward_list_1.cend(),
                             forward_list_3.begin(), f, new_v);
        std::replace_copy_if(forward_list_2.begin(), forward_list_2.end(),
                             forward_list_4.begin(), f, new_v);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        int new_v = 5;
        auto f = [](const int &v) { return v < 3 ? true : false; };
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::replace_copy_if(list_1.cbegin(), list_1.cend(),
                             forward_list_3.begin(), f, new_v);
        std::replace_copy_if(list_2.cbegin(), list_2.cend(),
                             forward_list_4.begin(), f, new_v);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        int new_v = 5;
        auto f = [](const int &v) { return v > 10 ? true : false; };
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::replace_copy_if(list_1.cbegin(), list_1.cend(),
                             forward_list_3.begin(), f, new_v);
        std::replace_copy_if(list_2.cbegin(), list_2.cend(),
                             forward_list_4.begin(), f, new_v);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        int new_v = 5;
        auto f = [](const int &v) { return v < 3 ? true : false; };
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::replace_copy_if(vector_1.cbegin(), vector_1.cend(),
                             forward_list_3.begin(), f, new_v);
        std::replace_copy_if(vector_2.cbegin(), vector_2.cend(),
                             forward_list_4.begin(), f, new_v);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        int new_v = 5;
        auto f = [](const int &v) { return v > 10 ? true : false; };
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::replace_copy_if(vector_1.cbegin(), vector_1.cend(),
                             forward_list_3.begin(), f, new_v);
        std::replace_copy_if(vector_2.cbegin(), vector_2.cend(),
                             forward_list_4.begin(), f, new_v);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }
}

TEST(test_algorithm, test_replace_copy) {
    // 输入迭代器
    {
        std::istringstream stream_1("1 2 3 4 5 1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5 1 2 3 4 5");

        int old_v = 3;
        int new_v = 5;
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::replace_copy(std::istream_iterator<int>(stream_1),
                          std::istream_iterator<int>(), forward_list_3.begin(),
                          old_v, new_v);
        std::replace_copy(std::istream_iterator<int>(stream_2),
                          std::istream_iterator<int>(), forward_list_4.begin(),
                          old_v, new_v);
        EXPECT_EQ(forward_list_3, forward_list_4);
    }
    {
        std::istringstream stream_1("1 2 3 4 5 1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5 1 2 3 4 5");

        int old_v = 10;
        int new_v = 5;
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::replace_copy(std::istream_iterator<int>(stream_1),
                          std::istream_iterator<int>(), forward_list_3.begin(),
                          old_v, new_v);
        std::replace_copy(std::istream_iterator<int>(stream_2),
                          std::istream_iterator<int>(), forward_list_4.begin(),
                          old_v, new_v);
        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        int old_v = 3;
        int new_v = 5;
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::replace_copy(forward_list_1.cbegin(), forward_list_1.cend(),
                          forward_list_3.begin(), old_v, new_v);
        std::replace_copy(forward_list_2.begin(), forward_list_2.end(),
                          forward_list_4.begin(), old_v, new_v);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        int old_v = 10;
        int new_v = 5;
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::replace_copy(forward_list_1.cbegin(), forward_list_1.cend(),
                          forward_list_3.begin(), old_v, new_v);
        std::replace_copy(forward_list_2.begin(), forward_list_2.end(),
                          forward_list_4.begin(), old_v, new_v);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        int old_v = 3;
        int new_v = 5;
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::replace_copy(list_1.cbegin(), list_1.cend(),
                          forward_list_3.begin(), old_v, new_v);
        std::replace_copy(list_2.cbegin(), list_2.cend(),
                          forward_list_4.begin(), old_v, new_v);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        int old_v = 10;
        int new_v = 5;
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::replace_copy(list_1.cbegin(), list_1.cend(),
                          forward_list_3.begin(), old_v, new_v);
        std::replace_copy(list_2.cbegin(), list_2.cend(),
                          forward_list_4.begin(), old_v, new_v);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        int old_v = 3;
        int new_v = 5;
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::replace_copy(vector_1.cbegin(), vector_1.cend(),
                          forward_list_3.begin(), old_v, new_v);
        std::replace_copy(vector_2.cbegin(), vector_2.cend(),
                          forward_list_4.begin(), old_v, new_v);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        int old_v = 10;
        int new_v = 5;
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::replace_copy(vector_1.cbegin(), vector_1.cend(),
                          forward_list_3.begin(), old_v, new_v);
        std::replace_copy(vector_2.cbegin(), vector_2.cend(),
                          forward_list_4.begin(), old_v, new_v);

        EXPECT_EQ(forward_list_3, forward_list_4);
    }
}

TEST(test_algorithm, test_replace_if) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5};

        int new_v = 5;
        auto f = [](const int &v) { return v < 3 ? true : false; };
        std::replace_if(forward_list_1.begin(), forward_list_1.end(), f, new_v);
        liuyunbin::replace_if(forward_list_2.begin(), forward_list_2.end(), f,
                              new_v);
        EXPECT_EQ(forward_list_1, forward_list_2);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5};

        int new_v = 5;
        auto f = [](const int &v) { return v > 10 ? true : false; };
        std::replace_if(forward_list_1.begin(), forward_list_1.end(), f, new_v);
        liuyunbin::replace_if(forward_list_2.begin(), forward_list_2.end(), f,
                              new_v);
        EXPECT_EQ(forward_list_1, forward_list_2);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5};

        int new_v = 5;
        auto f = [](const int &v) { return v < 3 ? true : false; };
        std::replace_if(list_1.begin(), list_1.end(), f, new_v);
        liuyunbin::replace_if(list_2.begin(), list_2.end(), f, new_v);
        EXPECT_EQ(list_1, list_2);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5};

        int new_v = 5;
        auto f = [](const int &v) { return v > 10 ? true : false; };
        std::replace_if(list_1.begin(), list_1.end(), f, new_v);
        liuyunbin::replace_if(list_2.begin(), list_2.end(), f, new_v);
        EXPECT_EQ(list_1, list_2);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5};

        int new_v = 5;
        auto f = [](const int &v) { return v < 3 ? true : false; };
        std::replace_if(vector_1.begin(), vector_1.end(), f, new_v);
        liuyunbin::replace_if(vector_2.begin(), vector_2.end(), f, new_v);
        EXPECT_EQ(vector_1, vector_2);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5};

        int new_v = 5;
        auto f = [](const int &v) { return v > 10 ? true : false; };
        std::replace_if(vector_1.begin(), vector_1.end(), f, new_v);
        liuyunbin::replace_if(vector_2.begin(), vector_2.end(), f, new_v);
        EXPECT_EQ(vector_1, vector_2);
    }
}

TEST(test_algorithm, test_replace) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5};

        int old_v = 3;
        int new_v = 5;
        std::replace(forward_list_1.begin(), forward_list_1.end(), old_v,
                     new_v);
        liuyunbin::replace(forward_list_2.begin(), forward_list_2.end(), old_v,
                           new_v);
        EXPECT_EQ(forward_list_1, forward_list_2);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5};

        int old_v = 10;
        int new_v = 5;
        std::replace(forward_list_1.begin(), forward_list_1.end(), old_v,
                     new_v);
        liuyunbin::replace(forward_list_2.begin(), forward_list_2.end(), old_v,
                           new_v);
        EXPECT_EQ(forward_list_1, forward_list_2);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5};

        int old_v = 3;
        int new_v = 5;
        std::replace(list_1.begin(), list_1.end(), old_v, new_v);
        liuyunbin::replace(list_2.begin(), list_2.end(), old_v, new_v);
        EXPECT_EQ(list_1, list_2);
    }
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5};

        int old_v = 10;
        int new_v = 5;
        std::replace(list_1.begin(), list_1.end(), old_v, new_v);
        liuyunbin::replace(list_2.begin(), list_2.end(), old_v, new_v);
        EXPECT_EQ(list_1, list_2);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5};

        int old_v = 3;
        int new_v = 5;
        std::replace(vector_1.begin(), vector_1.end(), old_v, new_v);
        liuyunbin::replace(vector_2.begin(), vector_2.end(), old_v, new_v);
        EXPECT_EQ(vector_1, vector_2);
    }
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5};

        int old_v = 10;
        int new_v = 5;
        std::replace(vector_1.begin(), vector_1.end(), old_v, new_v);
        liuyunbin::replace(vector_2.begin(), vector_2.end(), old_v, new_v);
        EXPECT_EQ(vector_1, vector_2);
    }
}

TEST(test_algorithm, test_reverse_copy) {
    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::reverse_copy(list_1.cbegin(), list_1.cend(),
                          forward_list_3.begin());
        liuyunbin::reverse_copy(list_2.cbegin(), list_2.cend(),
                                forward_list_4.begin());
        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::reverse_copy(vector_1.cbegin(), vector_1.cend(),
                          forward_list_3.begin());
        liuyunbin::reverse_copy(vector_2.cbegin(), vector_2.cend(),
                                forward_list_4.begin());
        EXPECT_EQ(forward_list_3, forward_list_4);
    }
}

TEST(test_algorithm, test_reverse) {
    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        std::reverse(list_1.begin(), list_1.end());
        liuyunbin::reverse(list_2.begin(), list_2.end());
        EXPECT_EQ(list_1, list_2);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        std::reverse(vector_1.begin(), vector_1.end());
        liuyunbin::reverse(vector_2.begin(), vector_2.end());
        EXPECT_EQ(vector_1, vector_2);
    }
}

TEST(test_algorithm, test_rotate_copy) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {7, 8, 0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {7, 8, 0, 1, 2, 3, 4};

        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0};

        liuyunbin::rotate_copy(forward_list_1.cbegin(),
                               std::next(forward_list_1.cbegin(), 2),
                               forward_list_1.cend(), forward_list_3.begin());
        liuyunbin::rotate_copy(forward_list_2.cbegin(),
                               std::next(forward_list_2.cbegin(), 2),
                               forward_list_2.cend(), forward_list_4.begin());
        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {7, 8, 0, 1, 2, 3, 4};
        std::list<int> list_2 = {7, 8, 0, 1, 2, 3, 4};

        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0};

        liuyunbin::rotate_copy(list_1.cbegin(), std::next(list_1.cbegin(), 2),
                               list_1.cend(), forward_list_3.begin());
        liuyunbin::rotate_copy(list_2.cbegin(), std::next(list_2.cbegin(), 2),
                               list_2.cend(), forward_list_4.begin());
        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {7, 8, 0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {7, 8, 0, 1, 2, 3, 4};

        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0};

        liuyunbin::rotate_copy(vector_1.cbegin(),
                               std::next(vector_1.cbegin(), 2), vector_1.cend(),
                               forward_list_3.begin());
        liuyunbin::rotate_copy(vector_2.cbegin(),
                               std::next(vector_2.cbegin(), 2), vector_2.cend(),
                               forward_list_4.begin());
        EXPECT_EQ(forward_list_3, forward_list_4);
    }
}

TEST(test_algorithm, test_rotate) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {7, 8, 0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {7, 8, 0, 1, 2, 3, 4};

        liuyunbin::rotate(forward_list_1.begin(),
                          std::next(forward_list_1.begin(), 2),
                          forward_list_1.end());
        liuyunbin::rotate(forward_list_2.begin(),
                          std::next(forward_list_2.begin(), 2),
                          forward_list_2.end());
        EXPECT_EQ(forward_list_1, forward_list_2);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {7, 8, 0, 1, 2, 3, 4};
        std::list<int> list_2 = {7, 8, 0, 1, 2, 3, 4};

        std::rotate(list_1.begin(), std::next(list_1.begin(), 2), list_1.end());
        liuyunbin::rotate(list_2.begin(), std::next(list_2.begin(), 2),
                          list_2.end());
        EXPECT_EQ(list_1, list_2);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {7, 8, 0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {7, 8, 0, 1, 2, 3, 4};

        std::rotate(vector_1.begin(), std::next(vector_1.begin(), 2),
                    vector_1.end());
        liuyunbin::rotate(vector_2.begin(), std::next(vector_2.begin(), 2),
                          vector_2.end());
        EXPECT_EQ(vector_1, vector_2);
    }
}

TEST(test_algorithm, test_search_n) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};

        int n = 2;
        int v = 3;
        auto x =
            std::search_n(forward_list_1.cbegin(), forward_list_1.cend(), n, v);
        auto y = liuyunbin::search_n(forward_list_1.cbegin(),
                                     forward_list_1.cend(), n, v);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {0, 1, 3, 3, 4};

        int n = 2;
        int v = 3;
        auto x =
            std::search_n(forward_list_1.cbegin(), forward_list_1.cend(), n, v);
        auto y = liuyunbin::search_n(forward_list_1.cbegin(),
                                     forward_list_1.cend(), n, v);
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};

        int n = 2;
        int v = 3;
        auto x = std::search_n(list_1.cbegin(), list_1.cend(), n, v);
        auto y = liuyunbin::search_n(list_1.cbegin(), list_1.cend(), n, v);
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {0, 1, 3, 3, 4};

        int n = 2;
        int v = 3;
        auto x = std::search_n(list_1.cbegin(), list_1.cend(), n, v);
        auto y = liuyunbin::search_n(list_1.cbegin(), list_1.cend(), n, v);
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};

        int n = 2;
        int v = 3;
        auto x = std::search_n(vector_1.cbegin(), vector_1.cend(), n, v);
        auto y = liuyunbin::search_n(vector_1.cbegin(), vector_1.cend(), n, v);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {0, 1, 3, 3, 4};

        int n = 2;
        int v = 3;
        auto x = std::search_n(vector_1.cbegin(), vector_1.cend(), n, v);
        auto y = liuyunbin::search_n(vector_1.cbegin(), vector_1.cend(), n, v);
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_search) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};

        auto x = std::search(forward_list_1.cbegin(), forward_list_1.cend(),
                             forward_list_2.cbegin(), forward_list_2.cend());
        auto y =
            liuyunbin::search(forward_list_1.cbegin(), forward_list_1.cend(),
                              forward_list_2.cbegin(), forward_list_2.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {2, 3, 4};

        auto x = std::search(forward_list_1.cbegin(), forward_list_1.cend(),
                             forward_list_2.cbegin(), forward_list_2.cend());
        auto y =
            liuyunbin::search(forward_list_1.cbegin(), forward_list_1.cend(),
                              forward_list_2.cbegin(), forward_list_2.cend());
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};
        std::list<int> list_2 = {5, 6, 7, 8, 9};

        auto x = std::search(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                             list_2.cend());
        auto y = liuyunbin::search(list_1.cbegin(), list_1.cend(),
                                   list_2.cbegin(), list_2.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};
        std::list<int> list_2 = {2, 3, 4};

        auto x = std::search(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                             list_2.cend());
        auto y = liuyunbin::search(list_1.cbegin(), list_1.cend(),
                                   list_2.cbegin(), list_2.cend());
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {5, 6, 7, 8, 9};

        auto x = std::search(vector_1.cbegin(), vector_1.cend(),
                             vector_2.cbegin(), vector_2.cend());
        auto y = liuyunbin::search(vector_1.cbegin(), vector_1.cend(),
                                   vector_2.cbegin(), vector_2.cend());
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {2, 3, 4};

        auto x = std::search(vector_1.cbegin(), vector_1.cend(),
                             vector_2.cbegin(), vector_2.cend());
        auto y = liuyunbin::search(vector_1.cbegin(), vector_1.cend(),
                                   vector_2.cbegin(), vector_2.cend());
        EXPECT_EQ(x, y);
    }
}

TEST(test_algorithm, test_set_difference) {
    // 输入迭代器
    {
        std::istringstream stream_1("0 1 2 3 4");
        std::istringstream stream_2("1 3 5 5 6");
        std::istringstream stream_3("0 1 2 3 4");
        std::istringstream stream_4("1 3 5 5 6");

        std::forward_list<int> forward_list_5 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_6 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::set_difference(
            std::istream_iterator<int>(stream_1), std::istream_iterator<int>(),
            std::istream_iterator<int>(stream_2), std::istream_iterator<int>(),
            forward_list_5.begin());
        liuyunbin::set_difference(
            std::istream_iterator<int>(stream_3), std::istream_iterator<int>(),
            std::istream_iterator<int>(stream_4), std::istream_iterator<int>(),
            forward_list_6.begin());
        EXPECT_EQ(forward_list_5, forward_list_6);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {1, 3, 5, 5, 6};

        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::set_difference(forward_list_1.cbegin(), forward_list_1.cend(),
                            forward_list_2.cbegin(), forward_list_2.cend(),
                            forward_list_3.begin());
        liuyunbin::set_difference(
            forward_list_1.cbegin(), forward_list_1.cend(),
            forward_list_2.cbegin(), forward_list_2.cend(),
            forward_list_4.begin());
        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};
        std::list<int> list_2 = {1, 3, 5, 5, 6};

        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::set_difference(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                            list_2.cend(), forward_list_3.begin());
        liuyunbin::set_difference(list_1.cbegin(), list_1.cend(),
                                  list_2.cbegin(), list_2.cend(),
                                  forward_list_4.begin());

        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {1, 3, 5, 5, 6};

        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::set_difference(vector_1.cbegin(), vector_1.cend(),
                            vector_2.cbegin(), vector_2.cend(),
                            forward_list_3.begin());

        liuyunbin::set_difference(vector_1.cbegin(), vector_1.cend(),
                                  vector_2.cbegin(), vector_2.cend(),
                                  forward_list_4.begin());

        EXPECT_EQ(forward_list_3, forward_list_4);
    }
}

TEST(test_algorithm, test_set_intersection) {
    // 输入迭代器
    {
        std::istringstream stream_1("0 1 2 3 4");
        std::istringstream stream_2("1 3 5 5 6");
        std::istringstream stream_3("0 1 2 3 4");
        std::istringstream stream_4("1 3 5 5 6");

        std::forward_list<int> forward_list_5 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_6 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::set_intersection(
            std::istream_iterator<int>(stream_1), std::istream_iterator<int>(),
            std::istream_iterator<int>(stream_2), std::istream_iterator<int>(),
            forward_list_5.begin());
        liuyunbin::set_intersection(
            std::istream_iterator<int>(stream_3), std::istream_iterator<int>(),
            std::istream_iterator<int>(stream_4), std::istream_iterator<int>(),
            forward_list_6.begin());
        EXPECT_EQ(forward_list_5, forward_list_6);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {1, 3, 5, 5, 6};

        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::set_intersection(forward_list_1.cbegin(), forward_list_1.cend(),
                              forward_list_2.cbegin(), forward_list_2.cend(),
                              forward_list_3.begin());
        liuyunbin::set_intersection(
            forward_list_1.cbegin(), forward_list_1.cend(),
            forward_list_2.cbegin(), forward_list_2.cend(),
            forward_list_4.begin());
        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};
        std::list<int> list_2 = {1, 3, 5, 5, 6};

        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::set_intersection(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                              list_2.cend(), forward_list_3.begin());
        liuyunbin::set_intersection(list_1.cbegin(), list_1.cend(),
                                    list_2.cbegin(), list_2.cend(),
                                    forward_list_4.begin());

        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {1, 3, 5, 5, 6};

        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::set_intersection(vector_1.cbegin(), vector_1.cend(),
                              vector_2.cbegin(), vector_2.cend(),
                              forward_list_3.begin());

        liuyunbin::set_intersection(vector_1.cbegin(), vector_1.cend(),
                                    vector_2.cbegin(), vector_2.cend(),
                                    forward_list_4.begin());

        EXPECT_EQ(forward_list_3, forward_list_4);
    }
}

TEST(test_algorithm, test_set_symmetric_difference) {
    // 输入迭代器
    {
        std::istringstream stream_1("0 1 2 3 4");
        std::istringstream stream_2("1 3 5 5 6");
        std::istringstream stream_3("0 1 2 3 4");
        std::istringstream stream_4("1 3 5 5 6");

        std::forward_list<int> forward_list_5 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_6 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::set_symmetric_difference(
            std::istream_iterator<int>(stream_1), std::istream_iterator<int>(),
            std::istream_iterator<int>(stream_2), std::istream_iterator<int>(),
            forward_list_5.begin());
        liuyunbin::set_symmetric_difference(
            std::istream_iterator<int>(stream_3), std::istream_iterator<int>(),
            std::istream_iterator<int>(stream_4), std::istream_iterator<int>(),
            forward_list_6.begin());
        EXPECT_EQ(forward_list_5, forward_list_6);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {1, 3, 5, 5, 6};

        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::set_symmetric_difference(
            forward_list_1.cbegin(), forward_list_1.cend(),
            forward_list_2.cbegin(), forward_list_2.cend(),
            forward_list_3.begin());
        liuyunbin::set_symmetric_difference(
            forward_list_1.cbegin(), forward_list_1.cend(),
            forward_list_2.cbegin(), forward_list_2.cend(),
            forward_list_4.begin());
        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};
        std::list<int> list_2 = {1, 3, 5, 5, 6};

        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::set_symmetric_difference(list_1.cbegin(), list_1.cend(),
                                      list_2.cbegin(), list_2.cend(),
                                      forward_list_3.begin());
        liuyunbin::set_symmetric_difference(list_1.cbegin(), list_1.cend(),
                                            list_2.cbegin(), list_2.cend(),
                                            forward_list_4.begin());

        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {1, 3, 5, 5, 6};

        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::set_symmetric_difference(vector_1.cbegin(), vector_1.cend(),
                                      vector_2.cbegin(), vector_2.cend(),
                                      forward_list_3.begin());

        liuyunbin::set_symmetric_difference(vector_1.cbegin(), vector_1.cend(),
                                            vector_2.cbegin(), vector_2.cend(),
                                            forward_list_4.begin());

        EXPECT_EQ(forward_list_3, forward_list_4);
    }
}

TEST(test_algorithm, test_set_union) {
    // 输入迭代器
    {
        std::istringstream stream_1("0 1 2 3 4");
        std::istringstream stream_2("1 3 5 5 6");
        std::istringstream stream_3("0 1 2 3 4");
        std::istringstream stream_4("1 3 5 5 6");

        std::forward_list<int> forward_list_5 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_6 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::set_union(std::istream_iterator<int>(stream_1),
                       std::istream_iterator<int>(),
                       std::istream_iterator<int>(stream_2),
                       std::istream_iterator<int>(), forward_list_5.begin());
        liuyunbin::set_union(
            std::istream_iterator<int>(stream_3), std::istream_iterator<int>(),
            std::istream_iterator<int>(stream_4), std::istream_iterator<int>(),
            forward_list_6.begin());
        EXPECT_EQ(forward_list_5, forward_list_6);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {1, 3, 5, 5, 6};

        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::set_union(forward_list_1.cbegin(), forward_list_1.cend(),
                       forward_list_2.cbegin(), forward_list_2.cend(),
                       forward_list_3.begin());
        liuyunbin::set_union(forward_list_1.cbegin(), forward_list_1.cend(),
                             forward_list_2.cbegin(), forward_list_2.cend(),
                             forward_list_4.begin());
        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};
        std::list<int> list_2 = {1, 3, 5, 5, 6};

        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::set_union(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                       list_2.cend(), forward_list_3.begin());
        liuyunbin::set_union(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                             list_2.cend(), forward_list_4.begin());

        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {1, 3, 5, 5, 6};

        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        std::set_union(vector_1.cbegin(), vector_1.cend(), vector_2.cbegin(),
                       vector_2.cend(), forward_list_3.begin());

        liuyunbin::set_union(vector_1.cbegin(), vector_1.cend(),
                             vector_2.cbegin(), vector_2.cend(),
                             forward_list_4.begin());

        EXPECT_EQ(forward_list_3, forward_list_4);
    }
}

TEST(test_algorithm, test_sort_heap) {
    // 随机迭代器
    {
        std::string str_1 = "98653";
        std::string str_2 = "98653";
        std::sort_heap(str_1.begin(), str_1.end());
        liuyunbin::sort_heap(str_2.begin(), str_2.end());
        EXPECT_EQ(str_1, str_2);
    }
    {
        std::string str_1 = "98765";
        std::string str_2 = "98765";
        std::sort_heap(str_1.begin(), str_1.end());
        liuyunbin::sort_heap(str_2.begin(), str_2.end());
        EXPECT_EQ(str_1, str_2);
    }
}

TEST(test_algorithm, test_sort) {
    // 随机迭代器
    std::string str_1 = "98653";
    std::string str_2 = "98653";
    std::sort(str_1.begin(), str_1.end());
    liuyunbin::sort(str_2.begin(), str_2.end());
    EXPECT_EQ(str_1, str_2);
}

TEST(test_algorithm, test_stable_partition) {
    // 前向迭代器
    {
        std::forward_list<std::pair<char, std::string>> forward_list_1 = {
            {'1', "100"}, {'2', "102"}, {'3', "103"}, {'4', "104"},
            {'a', "105"}, {'b', "106"}, {'c', "107"}, {'d', "108"},
            {'1', "109"}, {'2', "110"}, {'e', "111"}, {'f', "112"},
            {'g', "113"}, {'1', "114"}, {'2', "115"},
        };
        std::forward_list<std::pair<char, std::string>> forward_list_2(
            forward_list_1);

        auto f = [](const std::pair<char, std::string> &item) {
            return std::isdigit(item.first) ? true : false;
        };

        std::stable_partition(forward_list_1.begin(), forward_list_1.end(), f);
        liuyunbin::stable_partition(forward_list_2.begin(),
                                    forward_list_2.end(), f);
        EXPECT_EQ(forward_list_1, forward_list_2);
    }

    // 双向迭代器
    {
        std::list<std::pair<char, std::string>> list_1 = {
            {'1', "100"}, {'2', "102"}, {'3', "103"}, {'4', "104"},
            {'a', "105"}, {'b', "106"}, {'c', "107"}, {'d', "108"},
            {'1', "109"}, {'2', "110"}, {'e', "111"}, {'f', "112"},
            {'g', "113"}, {'1', "114"}, {'2', "115"},
        };
        std::list<std::pair<char, std::string>> list_2(list_1);

        auto f = [](const std::pair<char, std::string> &item) {
            return std::isdigit(item.first) ? true : false;
        };

        std::stable_partition(list_1.begin(), list_1.end(), f);
        liuyunbin::stable_partition(list_2.begin(), list_2.end(), f);

        EXPECT_EQ(list_1, list_2);
    }

    // 随机迭代器
    {
        std::vector<std::pair<char, std::string>> vector_1 = {
            {'1', "100"}, {'2', "102"}, {'3', "103"}, {'4', "104"},
            {'a', "105"}, {'b', "106"}, {'c', "107"}, {'d', "108"},
            {'1', "109"}, {'2', "110"}, {'e', "111"}, {'f', "112"},
            {'g', "113"}, {'1', "114"}, {'2', "115"},
        };
        std::vector<std::pair<char, std::string>> vector_2(vector_1);

        auto f = [](const std::pair<char, std::string> &item) {
            return std::isdigit(item.first) ? true : false;
        };

        std::stable_partition(vector_1.begin(), vector_1.end(), f);
        liuyunbin::stable_partition(vector_2.begin(), vector_2.end(), f);

        EXPECT_EQ(vector_1, vector_2);
    }
}

TEST(test_algorithm, test_stable_sort) {
    // 随机迭代器
    std::vector<std::pair<char, std::string>> vector_1 = {
        {'1', "100"}, {'2', "102"}, {'3', "103"}, {'4', "104"}, {'a', "105"},
        {'b', "106"}, {'c', "107"}, {'d', "108"}, {'1', "109"}, {'2', "110"},
        {'e', "111"}, {'f', "112"}, {'g', "113"}, {'1', "114"}, {'2', "115"},
    };
    std::vector<std::pair<char, std::string>> vector_2(vector_1);

    std::stable_sort(vector_1.begin(), vector_1.end());
    liuyunbin::stable_sort(vector_2.begin(), vector_2.end());
    EXPECT_EQ(vector_1, vector_2);
}

TEST(test_algorithm, test_swap_ranges) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};
        std::forward_list<int> forward_list_3 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_4 = {5, 6, 7, 8, 9};

        std::swap_ranges(forward_list_1.begin(), forward_list_1.end(),
                         forward_list_2.begin());
        liuyunbin::swap_ranges(forward_list_3.begin(), forward_list_3.end(),
                               forward_list_4.begin());
        EXPECT_EQ(forward_list_1, forward_list_3);
        EXPECT_EQ(forward_list_2, forward_list_4);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};
        std::list<int> list_2 = {5, 6, 7, 8, 9};
        std::list<int> list_3 = {0, 1, 2, 3, 4};
        std::list<int> list_4 = {5, 6, 7, 8, 9};

        std::swap_ranges(list_1.begin(), list_1.end(), list_2.begin());
        liuyunbin::swap_ranges(list_3.begin(), list_3.end(), list_4.begin());
        EXPECT_EQ(list_1, list_3);
        EXPECT_EQ(list_2, list_4);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};
        std::vector<int> vector_2 = {5, 6, 7, 8, 9};
        std::vector<int> vector_3 = {0, 1, 2, 3, 4};
        std::vector<int> vector_4 = {5, 6, 7, 8, 9};

        std::swap_ranges(vector_1.begin(), vector_1.end(), vector_2.begin());
        liuyunbin::swap_ranges(vector_3.begin(), vector_3.end(),
                               vector_4.begin());
        EXPECT_EQ(vector_1, vector_3);
        EXPECT_EQ(vector_2, vector_4);
    }
}

TEST(test_algorithm, test_transform) {
    // 输入迭代器
    {
        std::istringstream stream_1("1 2 3 4 5");
        std::istringstream stream_2("1 2 3 4 5");

        std::forward_list<int> forward_list_3 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_4 = {5, 6, 2, 3, 4};

        auto f = [](int v) { return v * 3; };

        std::transform(std::istream_iterator<int>(stream_1),
                       std::istream_iterator<int>(), forward_list_3.begin(), f);
        liuyunbin::transform(std::istream_iterator<int>(stream_2),
                             std::istream_iterator<int>(),
                             forward_list_4.begin(), f);
        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_3 = {5, 6, 2, 3, 4};

        auto f = [](int v) { return v * 3; };

        std::transform(forward_list_1.cbegin(), forward_list_1.cend(),
                       forward_list_2.begin(), f);
        liuyunbin::transform(forward_list_1.cbegin(), forward_list_1.cend(),
                             forward_list_3.begin(), f);
        EXPECT_EQ(forward_list_2, forward_list_3);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5};

        std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_3 = {5, 6, 2, 3, 4};

        auto f = [](int v) { return v * 3; };

        std::transform(list_1.cbegin(), list_1.cend(), forward_list_2.begin(),
                       f);
        liuyunbin::transform(list_1.cbegin(), list_1.cend(),
                             forward_list_3.begin(), f);
        EXPECT_EQ(forward_list_2, forward_list_3);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};

        std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
        std::forward_list<int> forward_list_3 = {5, 6, 2, 3, 4};

        auto f = [](int v) { return v * 3; };

        std::transform(vector_1.cbegin(), vector_1.cend(),
                       forward_list_2.begin(), f);
        liuyunbin::transform(vector_1.cbegin(), vector_1.cend(),
                             forward_list_3.begin(), f);
        EXPECT_EQ(forward_list_2, forward_list_3);
    }
}

TEST(test_algorithm, test_unique_copy) {
    // 输入迭代器
    {
        std::istringstream stream_1("1 1 2 2 3 4 5");
        std::istringstream stream_2("1 1 2 2 3 4 5");

        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0};

        std::unique_copy(std::istream_iterator<int>(stream_1),
                         std::istream_iterator<int>(), forward_list_3.begin());
        liuyunbin::unique_copy(std::istream_iterator<int>(stream_2),
                               std::istream_iterator<int>(),
                               forward_list_4.begin());

        EXPECT_EQ(forward_list_3, forward_list_4);
    }

    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 1, 2, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0};

        std::unique_copy(forward_list_1.cbegin(), forward_list_1.cend(),
                         forward_list_2.begin());
        liuyunbin::unique_copy(forward_list_1.cbegin(), forward_list_1.cend(),
                               forward_list_3.begin());

        EXPECT_EQ(forward_list_2, forward_list_3);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 1, 2, 2, 3, 4, 5};

        std::forward_list<int> forward_list_2 = {0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0};

        std::unique_copy(list_1.cbegin(), list_1.cend(),
                         forward_list_2.begin());
        liuyunbin::unique_copy(list_1.cbegin(), list_1.cend(),
                               forward_list_3.begin());

        EXPECT_EQ(forward_list_2, forward_list_3);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5};

        std::forward_list<int> forward_list_2 = {0, 0, 0, 0, 0, 0};
        std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0};

        std::unique_copy(vector_1.cbegin(), vector_1.cend(),
                         forward_list_2.begin());
        liuyunbin::unique_copy(vector_1.cbegin(), vector_1.cend(),
                               forward_list_3.begin());

        EXPECT_EQ(forward_list_2, forward_list_3);
    }
}

TEST(test_algorithm, test_unique) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        std::unique(forward_list_1.begin(), forward_list_1.end());
        liuyunbin::unique(forward_list_2.begin(), forward_list_2.end());

        EXPECT_EQ(forward_list_1, forward_list_2);
    }
    {
        std::forward_list<int> forward_list_1 = {1, 1, 2, 2, 3, 3, 4, 5};
        std::forward_list<int> forward_list_2 = {1, 1, 2, 2, 3, 3, 4, 5};

        std::unique(forward_list_1.begin(), forward_list_1.end());
        liuyunbin::unique(forward_list_2.begin(), forward_list_2.end());

        EXPECT_EQ(forward_list_1, forward_list_2);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        std::unique(list_1.begin(), list_1.end());
        liuyunbin::unique(list_2.begin(), list_2.end());

        EXPECT_EQ(list_1, list_2);
    }
    {
        std::list<int> list_1 = {1, 1, 2, 2, 3, 4, 5};
        std::list<int> list_2 = {1, 1, 2, 2, 3, 4, 5};

        std::unique(list_1.begin(), list_1.end());
        liuyunbin::unique(list_2.begin(), list_2.end());

        EXPECT_EQ(list_1, list_2);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

        std::unique(vector_1.begin(), vector_1.end());
        liuyunbin::unique(vector_2.begin(), vector_2.end());

        EXPECT_EQ(vector_1, vector_2);
    }
    {
        std::vector<int> vector_1 = {1, 1, 2, 2, 3, 4, 5};
        std::vector<int> vector_2 = {1, 1, 2, 2, 3, 4, 5};

        std::unique(vector_1.begin(), vector_1.end());
        liuyunbin::unique(vector_2.begin(), vector_2.end());

        EXPECT_EQ(vector_1, vector_2);
    }
}

TEST(test_algorithm, test_upper_bound) {
    // 前向迭代器
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};

        int v = 3;
        auto x =
            std::upper_bound(forward_list_1.cbegin(), forward_list_1.cend(), v);
        auto y = liuyunbin::upper_bound(forward_list_1.cbegin(),
                                        forward_list_1.cend(), v);
        EXPECT_EQ(x, y);
    }
    {
        std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};

        int v = 10;
        auto x =
            std::upper_bound(forward_list_1.cbegin(), forward_list_1.cend(), v);
        auto y = liuyunbin::upper_bound(forward_list_1.cbegin(),
                                        forward_list_1.cend(), v);
        EXPECT_EQ(x, y);
    }

    // 双向迭代器
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};

        int v = 3;
        auto x = std::upper_bound(list_1.cbegin(), list_1.cend(), v);
        auto y = liuyunbin::upper_bound(list_1.cbegin(), list_1.cend(), v);
        EXPECT_EQ(x, y);
    }
    {
        std::list<int> list_1 = {0, 1, 2, 3, 4};

        int v = 10;
        auto x = std::upper_bound(list_1.cbegin(), list_1.cend(), v);
        auto y = liuyunbin::upper_bound(list_1.cbegin(), list_1.cend(), v);
        EXPECT_EQ(x, y);
    }

    // 随机迭代器
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};

        int v = 3;
        auto x = std::upper_bound(vector_1.cbegin(), vector_1.cend(), v);
        auto y = liuyunbin::upper_bound(vector_1.cbegin(), vector_1.cend(), v);
        EXPECT_EQ(x, y);
    }
    {
        std::vector<int> vector_1 = {0, 1, 2, 3, 4};

        int v = 10;
        auto x = std::upper_bound(vector_1.cbegin(), vector_1.cend(), v);
        auto y = liuyunbin::upper_bound(vector_1.cbegin(), vector_1.cend(), v);
        EXPECT_EQ(x, y);
    }
}
