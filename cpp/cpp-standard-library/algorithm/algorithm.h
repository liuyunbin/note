#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_H_

#include <algorithm>
#include <iterator>

namespace liuyunbin {

/*
 * 函数原型：
 *    template <typename ForwardIt>
 *    ForwardIt adjacent_find(ForwardIt first, ForwardIt last);
 *
 *    template <typename ForwardIt, typename BinaryPredicate>
 *    ForwardIt adjacent_find(ForwardIt first,
 *                            ForwardIt last,
 *                            BinaryPredicate p);
 *
 * 函数说明：
 *    该函数用于查找在指定区间内是否存在连续的两个相等元素
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt>
ForwardIt adjacent_find(ForwardIt first, ForwardIt last) {
  if (first == last) return last;
  for (auto next = std::next(first); next != last; ++first, ++next)
    if (*next == *first) return first;
  return last;
}

template <typename ForwardIt, typename BinaryPredicate>
ForwardIt adjacent_find(ForwardIt first, ForwardIt last, BinaryPredicate p) {
  if (first == last) return last;
  for (auto next = std::next(first); next != last; ++first, ++next)
    if (p(*next, *first)) return first;
  return last;
}

/*
 * 函数原型：
 *    template <typename InputIt, typename UnaryPredicate>
 *    bool all_of(InputIt first, InputIt last, UnaryPredicate p);
 *
 * 函数说明：
 *    该函数用于查找在指定区间内是否都满足谓词 p
 *
 * 模板参数要求：
 *    至少是输入迭代器
 */
template <typename InputIt, typename UnaryPredicate>
bool all_of(InputIt first, InputIt last, UnaryPredicate p) {
  return std::find_if_not(first, last, p) == last;
}

/*
 * 函数原型：
 *    template <typename InputIt, typename UnaryPredicate>
 *    bool any_of(InputIt first, InputIt last, UnaryPredicate p);
 *
 * 函数说明：
 *    该函数用于查找在指定区间内是否存在至少一个元素满足谓词 p
 *
 * 模板参数要求：
 *    至少是输入迭代器
 */
template <typename InputIt, typename UnaryPredicate>
bool any_of(InputIt first, InputIt last, UnaryPredicate p) {
  return std::find_if(first, last, p) != last;
}

/*
 * 函数原型：
 *    template <typename ForwardIt, typename T, typename Compare>
 *    bool binary_search(ForwardIt first,
 *                       ForwardIt last,
 *                       const T &value,
 *                       Compare comp);
 *
 *    template <typename ForwardIt, typename T>
 *    bool binary_search(ForwardIt first, ForwardIt last, const T &value);
 *
 * 函数说明：
 *    该函数用于判断指有序区间内是否存在元素 value
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt, typename T, typename Compare>
bool binary_search(ForwardIt first, ForwardIt last, const T &value,
                   Compare comp) {
  first = std::lower_bound(first, last, value, comp);
  if (first == last) return false;
  return !comp(value, *first);
}

template <typename ForwardIt, typename T>
bool binary_search(ForwardIt first, ForwardIt last, const T &value) {
  first = std::lower_bound(first, last, value);
  if (first == last) return false;
  return !(value < *first);
}

/*
 * 函数原型：
 *    template <typename InputIt, typename OutputIt>
 *    OutputIt copy(InputIt first, InputIt last, OutputIt d_first);
 *
 * 函数说明：
 *    该函数用于复制指定的区间
 *
 * 模板参数要求：
 *    至少是输入迭代器 和 输出迭代器
 */
template <class InputIt, class OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt d_first) {
  while (first != last) *d_first++ = *first++;
  return d_first;
}

/*
 * 函数原型：
 *    template <typename BidirectionalIt1, typename BidirectionalIt2>
 *    BidirectionalIt2 copy_backward(BidirectionalIt1 first,
 *                                   BidirectionalIt1 last,
 *                                   BidirectionalIt2 d_last);
 *
 * 函数说明：
 *    该函数用于复制指定的区间（从后往前）
 *
 * 模板参数要求：
 *    至少是双向迭代器 和 双向迭代器
 */
template <typename BidirectionalIt1, typename BidirectionalIt2>
BidirectionalIt2 copy_backward(BidirectionalIt1 first, BidirectionalIt1 last,
                               BidirectionalIt2 d_last) {
  while (first != last) *--d_last = *--last;
  return d_last;
}

/*
 * 函数原型：
 *    template <typename InputIt, typename OutputIt, typename UnaryPredicate>
 *    OutputIt copy_if(InputIt first,
 *                     InputIt last,
 *                     OutputIt d_first,
 *                     UnaryPredicate op);
 *
 * 函数说明：
 *    该函数用于复制满足条件的数据
 *
 * 模板参数要求：
 *    至少是输入迭代器 和 输出迭代器
 */
template <typename InputIt, typename OutputIt, typename UnaryPredicate>
OutputIt copy_if(InputIt first, InputIt last, OutputIt d_first,
                 UnaryPredicate op) {
  while (first != last) {
    if (op(*first)) *d_first++ = *first;
    ++first;
  }
  return d_first;
}

/*
 * 函数原型：
 *    template <typename InputIt, typename Size, typename OutputIt>
 *    OutputIt copy_n(InputIt first, Size count, OutputIt result);
 *
 * 函数说明：
 *    该函数用于复制指定的数目的元素
 *
 * 模板参数要求：
 *    至少是输入迭代器 和 输出迭代器
 */
template <typename InputIt, typename Size, typename OutputIt>
OutputIt copy_n(InputIt first, Size count, OutputIt result) {
  if (count > 0)
    for (Size i = 0; i < count; ++i) *result++ = *first++;
  return result;
}

/*
 * 函数原型：
 *    template <typename InputIt, typename T>
 *    typename std::iterator_traits<InputIt>::difference_type
 *    count(InputIt first, InputIt last, const T &value);
 *
 * 函数说明：
 *    该函数用于统计制定元素的个数
 *
 * 模板参数要求：
 *    至少是输入迭代器
 */
template <typename InputIt, typename T>
typename std::iterator_traits<InputIt>::difference_type count(InputIt first,
                                                              InputIt last,
                                                              const T &value) {
  typename std::iterator_traits<InputIt>::difference_type n = 0;
  while (first != last)
    if (*first++ == value) ++n;
  return n;
}

/*
 * 函数原型：
 *    template <typename InputIt, typename UnaryPredicate>
 *    typename std::iterator_traits<InputIt>::difference_type count_if(InputIt
 * first, InputIt last, UnaryPredicate p);
 *
 * 函数说明：
 *    该函数用于统计满足指定条件的元素的个数
 *
 * 模板参数要求：
 *    至少是输入迭代器
 */
template <typename InputIt, typename UnaryPredicate>
typename std::iterator_traits<InputIt>::difference_type count_if(
    InputIt first, InputIt last, UnaryPredicate p) {
  typename std::iterator_traits<InputIt>::difference_type n = 0;
  while (first != last)
    if (p(*first++)) ++n;
  return n;
}

/*
 * 函数原型：
 *    template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
 *    bool equal(InputIt1 first1,
 *               InputIt1 last1,
 *               InputIt2 first2,
 *               BinaryPredicate op);
 *
 *    template <typename InputIt1, typename InputIt2>
 *    bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2);
 *
 *    // C++14
 *    template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
 *    bool equal(InputIt1 first1,
 *               InputIt1 last1,
 *               InputIt2 first2,
 *               InputIt2 last2,
 *               BinaryPredicate op);
 *
 *    template <typename InputIt1, typename InputIt2>
 *    bool equal(InputIt1 first1,
 *               InputIt1 last1,
 *               InputIt2 first2,
 *               InputIt2 last2);
 *
 * 函数说明：
 *    该函数用于比较指定的区间是否相等
 *
 * 模板参数要求：
 *    至少是输入迭代器
 */
template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2,
           BinaryPredicate op) {
  while (first1 != last1 && op(*first1, *first2)) {
    ++first1;
    ++first2;
  }
  return first1 == last1;
}

template <typename InputIt1, typename InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
  while (first1 != last1 && *first1 == *first2) {
    ++first1;
    ++first2;
  }
  return first1 == last1;
}

// C++14
template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2,
           BinaryPredicate op) {
  while (first1 != last1 && first2 != last2 && op(*first1, *first2)) {
    ++first1;
    ++first2;
  }
  return first1 == last1 && first2 == last2;
}

template <typename InputIt1, typename InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
  while (first1 != last1 && first2 != last2 && *first1 == *first2) {
    ++first1;
    ++first2;
  }
  return first1 == last1 && first2 == last2;
}

/*
 * 函数原型：
 *    template <typename ForwardIt, typename T, typename Compare>
 *    std::pair<ForwardIt, ForwardIt>
 *    equal_range(ForwardIt first,
 *                ForwardIt last,
 *                const T &value,
 *                Compare comp);
 *
 *    template <typename ForwardIt, typename T>
 *    std::pair<ForwardIt, ForwardIt>
 *    equal_range(ForwardIt first, ForwardIt last, const T &value);
 *
 * 函数说明：
 *    该函数返回在指定的有序区间内，第一个大于等于 value 的位置 和 第一个大于
 * value 的位置
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt, typename T, typename Compare>
std::pair<ForwardIt, ForwardIt> equal_range(ForwardIt first, ForwardIt last,
                                            const T &value, Compare comp) {
  return {std::lower_bound(first, last, value, comp),
          std::upper_bound(first, last, value, comp)};
}

template <typename ForwardIt, typename T>
std::pair<ForwardIt, ForwardIt> equal_range(ForwardIt first, ForwardIt last,
                                            const T &value) {
  return {std::lower_bound(first, last, value),
          std::upper_bound(first, last, value)};
}

/*
 * 函数原型：
 *    template <typename ForwardIt, typename T>
 *    void fill(ForwardIt first, ForwardIt last, const T &value);
 *
 * 函数说明：
 *    该函数用于在指定区间内填充元素 value
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt, typename T>
void fill(ForwardIt first, ForwardIt last, const T &value) {
  while (first != last) *first++ = value;
}

/*
 * 函数原型：
 *    template <typename OutputIt, typename Size, typename T>
 *    OutputIt fill_n(OutputIt first, Size n, const T &value);
 *
 * 函数说明：
 *    该函数用于在指定区间内填充 n 个元素 value
 *
 * 模板参数要求：
 *    至少是输出迭代器
 */
template <typename OutputIt, typename Size, typename T>
OutputIt fill_n(OutputIt first, Size n, const T &value) {
  while (n-- != 0) *first++ = value;
  return first;
}

/*
 * 函数原型：
 *    template <typename ForwardIt1, typename ForwardIt2>
 *    ForwardIt1 find_end(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, ForwardIt2 last2);
 *
 *    template <typename ForwardIt1, typename ForwardIt2, typename BinaryPredicate>
 *    ForwardIt1 find_end(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, ForwardIt2 last2, BinaryPredicate p);
 *
 * 函数说明：
 *    该函数用于查找是否前一个区间的某个子区间和后一个区间的元素相同，如果存在，返回，最后一个子区间的第一个元素的迭代器
 *    可以通过区分是否是双向迭代器来优化
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt1, typename ForwardIt2>
ForwardIt1 __find_end(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2,
                      ForwardIt2 last2, std::forward_iterator_tag,
                      std::forward_iterator_tag) {
  if (first2 == last2) return last1;
  auto result = last1;
  while (true) {
    auto new_result = std::search(first1, last1, first2, last2);
    if (new_result == last1) break;
    first1 = result = new_result;
    ++first1;
  }
  return result;
}

template <typename ForwardIt1, typename ForwardIt2>
ForwardIt1 __find_end(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2,
                      ForwardIt2 last2, std::bidirectional_iterator_tag,
                      std::bidirectional_iterator_tag) {
  if (first2 == last2) return last1;
  std::reverse_iterator<ForwardIt1> reverse_first1(first1);
  std::reverse_iterator<ForwardIt1> reverse_last1(last1);
  std::reverse_iterator<ForwardIt2> reverse_first2(first2);
  std::reverse_iterator<ForwardIt2> reverse_last2(last2);

  auto result =
      std::search(reverse_last1, reverse_first1, reverse_last2, reverse_first2);
  if (result == reverse_first1) return last1;
  return std::prev(result.base(), std::distance(first2, last2));
}

template <typename ForwardIt1, typename ForwardIt2>
ForwardIt1 find_end(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2,
                    ForwardIt2 last2) {
  return __find_end(
      first1, last1, first2, last2,
      typename std::iterator_traits<ForwardIt1>::iterator_category(),
      typename std::iterator_traits<ForwardIt2>::iterator_category());
}

template <typename ForwardIt1, typename ForwardIt2, typename BinaryPredicate>
ForwardIt1 __find_end(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2,
                      ForwardIt2 last2, BinaryPredicate p,
                      std::forward_iterator_tag, std::forward_iterator_tag) {
  if (first2 == last2) return last1;
  auto result = last1;
  while (true) {
    auto new_result = std::search(first1, last1, first2, last2, p);
    if (new_result == last1) break;
    first1 = result = new_result;
    ++first1;
  }
  return result;
}

template <typename ForwardIt1, typename ForwardIt2, typename BinaryPredicate>
ForwardIt1 __find_end(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2,
                      ForwardIt2 last2, BinaryPredicate p,
                      std::bidirectional_iterator_tag,
                      std::bidirectional_iterator_tag) {
  if (first2 == last2) return last1;
  std::reverse_iterator<ForwardIt1> reverse_first1(first1);
  std::reverse_iterator<ForwardIt1> reverse_last1(last1);
  std::reverse_iterator<ForwardIt2> reverse_first2(first2);
  std::reverse_iterator<ForwardIt2> reverse_last2(last2);

  auto result = std::search(reverse_last1, reverse_first1, reverse_last2,
                            reverse_first2, p);
  if (result == reverse_first1) return last1;
  return std::prev(result.base(), std::distance(first2, last2));
}

template <typename ForwardIt1, typename ForwardIt2, typename BinaryPredicate>
ForwardIt1 find_end(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2,
                    ForwardIt2 last2, BinaryPredicate p) {
  return __find_end(
      first1, last1, first2, last2, p,
      typename std::iterator_traits<ForwardIt1>::iterator_category(),
      typename std::iterator_traits<ForwardIt2>::iterator_category());
}

/*
 * 函数原型：
 *    template <typename InputIt, typename T>
 *    InputIt find(InputIt first, InputIt last, const T &val);
 *
 * 函数说明：
 *    该函数用于查找在指定区间内是否存在元素 val
 *
 * 模板参数要求：
 *    至少是输入迭代器
 */
template <typename InputIt, typename T>
InputIt find(InputIt first, InputIt last, const T &val) {
  while (first != last && *first != val) ++first;
  return first;
}

/*
 * 函数原型：
 *    template <typename InputIt, typename ForwardIt>
 *    InputIt find_first_of(InputIt first1, InputIt last1, ForwardIt first2, ForwardIt last2);
 *
 *    template <typename InputIt, typename ForwardIt, typename BinaryPredicate>
 *    InputIt find_first_of(InputIt first1, InputIt last1, ForwardIt first2, ForwardIt last2, BinaryPredicate p);
 *
 * 函数说明：
 *    该函数用于查找对于第一个区间内的元素，如果在第二个区间内的出现过，则返回第一个迭代器的位置
 *
 * 模板参数要求：
 *    至少是输入迭代器 和 前向迭代器
 */
template <typename InputIt, typename ForwardIt>
InputIt find_first_of(InputIt first1, InputIt last1, ForwardIt first2,
                      ForwardIt last2) {
  while (first1 != last1) {
    if (std::find(first2, last2, *first1) != last2) return first1;
    ++first1;
  }
  return last1;
}

template <typename InputIt, typename ForwardIt, typename BinaryPredicate>
InputIt find_first_of(InputIt first1, InputIt last1, ForwardIt first2,
                      ForwardIt last2, BinaryPredicate p) {
  while (first1 != last1) {
    for (auto it = first2; it != last2; ++it)
      if (p(*first1, *it)) return first1;
    ++first1;
  }
  return last1;
}

/*
 * 函数原型：
 *    template <typename InputIt, typename UnaryPredicate>
 *    InputIt find_if(InputIt first, InputIt last, UnaryPredicate p);
 *
 * 函数说明：
 *    该函数用于查找在指定区间内是否存在满足条件的元素
 *
 * 模板参数要求：
 *    至少是输入迭代器
 */
template <typename InputIt, typename UnaryPredicate>
InputIt find_if(InputIt first, InputIt last, UnaryPredicate p) {
  while (first != last && p(*first) == false) ++first;
  return first;
}

/*
 * 函数原型：
 *    template <typename InputIt, typename UnaryPredicate>
 *    InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate p);
 *
 * 函数说明：
 *    该函数用于查找在指定区间内是否存在不满足条件的元素
 *
 * 模板参数要求：
 *    至少是输入迭代器
 */
template <typename InputIt, typename UnaryPredicate>
InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate p) {
  while (first != last && p(*first) == true) ++first;
  return first;
}

/*
 * 函数原型：
 *    template <typename InputIt, typename UnaryPredicate>
 *    UnaryPredicate for_each(InputIt first, InputIt last, UnaryPredicate f);
 *
 * 函数说明：
 *    该函数用于对指定的区间依次执行指定的谓词
 *
 * 模板参数要求：
 *    至少是输入迭代器
 */
template <typename InputIt, typename UnaryPredicate>
UnaryPredicate for_each(InputIt first, InputIt last, UnaryPredicate f) {
  while (first != last) f(*first++);
  return f;
}

/*
 * 函数原型：
 *    template <typename ForwardIt, typename Predicate>
 *    void generate(ForwardIt first, ForwardIt last, Predicate p);
 *
 * 函数说明：
 *    该函数用于将 指定谓词 的返回结果 赋值给 指定的区间
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt, typename Predicate>
void generate(ForwardIt first, ForwardIt last, Predicate p) {
  while (first != last) *first++ = p();
}

/*
 *
 * 函数原型：
 *    template <typename OutputIt, typename Size, typename Predicate>
 *    OutputIt generate_n(OutputIt first, Size count, Predicate p);
 *
 * 函数说明：
 *    该函数用于将 指定谓词 的返回结果 赋值给 指定个数的区间
 *
 * 模板参数要求：
 *    至少是输出迭代器
 */
template <typename OutputIt, typename Size, typename Predicate>
OutputIt generate_n(OutputIt first, Size count, Predicate p) {
  while (count-- != 0) *first++ = p();
  return first;
}

/*
 * 函数原型：
 *    template <typename InputIt1, typename InputIt2, typename Compare>
 *    bool includes(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp);
 *
 *    template <typename InputIt1, typename InputIt2>
 *    bool includes(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2);
 *
 * 函数说明：
 *    对于两个有序区间，判断第二个区间是否是第一个区间的子序列
 *
 * 模板参数要求：
 *    至少是输入迭代器 和 输入迭代器
 */
template <typename InputIt1, typename InputIt2, typename Compare>
bool includes(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2,
              Compare comp) {
  while (first1 != last1 && first2 != last2) {
    if (comp(*first2, *first1))
      return false;
    else if (comp(*first1, *first2))
      ++first1;
    else {
      ++first1;
      ++first2;
    }
  }
  return first2 == last2;
}

template <typename InputIt1, typename InputIt2>
bool includes(InputIt1 first1, InputIt1 last1, InputIt2 first2,
              InputIt2 last2) {
  while (first1 != last1 && first2 != last2) {
    if (*first2 < *first1)
      return false;
    else if (*first1 < *first2)
      ++first1;
    else {
      ++first1;
      ++first2;
    }
  }
  return first2 == last2;
}

/*
 * 函数原型：
 *    template <typename ForwardIt, typename Compare>
 *    void inplace_merge(ForwardIt first, ForwardIt middle, ForwardIt last, Compare comp);
 *
 *    template <typename ForwardIt>
 *    void inplace_merge(ForwardIt first, ForwardIt middle, ForwardIt last);
 *
 * 函数说明：
 *    该函数用于原地合并两个有序区间
 *
 * 模板参数要求：
 *    C++11 要求 至少是双向迭代器，但我觉得 只要满足条件，前向迭代器就可以
 */
template <typename ForwardIt, typename Compare>
void inplace_merge(ForwardIt first, ForwardIt middle, ForwardIt last,
                   Compare comp) {
  auto n = std::distance(first, middle);
  auto *p = new typename std::iterator_traits<ForwardIt>::value_type[n];
  std::copy(first, middle, p);
  std::merge(p, p + n, middle, last, first, comp);
  delete[] p;
}

template <typename ForwardIt>
void inplace_merge(ForwardIt first, ForwardIt middle, ForwardIt last) {
  auto n = std::distance(first, middle);
  auto *p = new typename std::iterator_traits<ForwardIt>::value_type[n];
  std::copy(first, middle, p);
  std::merge(p, p + n, middle, last, first);
  delete[] p;
}

/*
 * 函数原型：
 *    template <typename RandomAccessIt, typename Compare>
 *    bool is_heap(RandomAccessIt first, RandomAccessIt last, Compare comp);
 *
 *    template <typename RandomAccessIt>
 *    bool is_heap(RandomAccessIt first, RandomAccessIt last);
 *
 * 函数说明：
 *    该函数用于判断指定区间是否满足堆
 *
 * 模板参数要求：
 *    要求是是随机迭代器
 */
template <typename RandomAccessIt, typename Compare>
bool is_heap(RandomAccessIt first, RandomAccessIt last, Compare comp) {
  auto n = last - first;
  decltype(n) i = 0;
  for (;;) {
    if (2 * i + 1 >= n) return true;
    if (comp(first[i], first[2 * i + 1])) return false;
    if (2 * i + 2 >= n) return true;
    if (comp(first[i], first[2 * i + 2])) return false;
    ++i;
  }
}

template <typename RandomAccessIt>
bool is_heap(RandomAccessIt first, RandomAccessIt last) {
  auto n = last - first;
  decltype(n) i = 0;
  for (;;) {
    if (2 * i + 1 >= n) return true;
    if (first[i] < first[2 * i + 1]) return false;
    if (2 * i + 2 >= n) return true;
    if (first[i] < first[2 * i + 2]) return false;
    ++i;
  }
}

/*
 * 函数原型：
 *    template <typename RandomAccessIt, typename Compare>
 *    RandomAccessIt is_heap_until(RandomAccessIt first, RandomAccessIt last, Compare comp);
 *
 *    template <typename RandomAccessIt>
 *    RandomAccessIt is_heap_until(RandomAccessIt first, RandomAccessIt last);
 *
 * 函数说明：
 *    该函数用于查找从头开始满足堆的子区间
 *
 * 模板参数要求：
 *    要求是是随机迭代器
 */
template <typename RandomAccessIt, typename Compare>
RandomAccessIt is_heap_until(RandomAccessIt first, RandomAccessIt last,
                             Compare comp) {
  auto n = last - first;
  decltype(n) i = 1;
  for (;;) {
    if (i >= n) return last;
    if (comp(first[(i - 1) / 2], first[i])) return first + i;
    ++i;
  }
}

template <typename RandomAccessIt>
RandomAccessIt is_heap_until(RandomAccessIt first, RandomAccessIt last) {
  auto n = last - first;
  decltype(n) i = 1;
  for (;;) {
    if (i >= n) return last;
    if (first[(i - 1) / 2] < first[i]) return first + i;
    ++i;
  }
}

/*
 * 函数原型：
 *    template <typename InputIt, typename UnaryPredicate>
 *    bool is_partitioned(InputIt first, InputIt last, UnaryPredicate p);
 *
 * 函数说明：
 *    该函数用于判断指定区间是否满足，符合谓词的在前，不符合的在后的条件
 *
 * 模板参数要求：
 *    至少是输入迭代器
 */
template <typename InputIt, typename UnaryPredicate>
bool is_partitioned(InputIt first, InputIt last, UnaryPredicate p) {
  while (first != last) {
    if (!p(*first)) break;
    ++first;
  }
  while (first != last) {
    if (p(*first)) return false;
    ++first;
  }
  return true;
}

/*
 * 函数原型：
 *    template <typename ForwardIt1, typename ForwardIt2, typename Compare>
 *    bool is_permutation(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, ForwardIt2 last2, Compare comp);
 *
 *    template <typename ForwardIt1, typename ForwardIt2>
 *    bool is_permutation(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, ForwardIt2 last2);
 *
 *    template <typename ForwardIt1, typename ForwardIt2, typename Compare>
 *    bool is_permutation(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, Compare comp);
 *
 *    template <typename ForwardIt1, typename ForwardIt2>
 *    bool is_permutation(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2);
 *
 *
 * 函数说明：
 *    该函数用于判断第一个区间能否通过交换转化为第二个区间
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt1, typename ForwardIt2, typename Compare>
bool is_permutation(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2,
                    ForwardIt2 last2, Compare comp) {
  if (std::distance(first1, last1) != std::distance(first2, last2))
    return false;
  using type = typename std::iterator_traits<ForwardIt1>::type;
  for (auto i = first1; i != last1; ++i) {
    if (std::find_if(first1, i,
                     [i, comp](const type &x) { return comp(*i, x); }) != i)
      continue;
    if (std::count_if(i, last1, [i, comp](const type &x) {
          return comp(*i, x);
        }) != std::count_if(first2, last2, [i, comp](const type &x) {
          return comp(*i, x);
        }))

      return false;
  }
  return true;
}

template <typename ForwardIt1, typename ForwardIt2>
bool is_permutation(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2,
                    ForwardIt2 last2) {
  if (std::distance(first1, last1) != std::distance(first2, last2))
    return false;
  for (auto i = first1; i != last1; ++i) {
    if (std::find(first1, i, *i) != i) continue;
    if (std::count(i, last1, *i) != std::count(first2, last2, *i)) return false;
  }
  return true;
}

template <typename ForwardIt1, typename ForwardIt2, typename Compare>
bool is_permutation(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2,
                    Compare comp) {
  return is_permutation(first1, last1, first2,
                        std::next(first2, std::distance(first1, last1)), comp);
}

template <typename ForwardIt1, typename ForwardIt2>
bool is_permutation(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2) {
  return is_permutation(first1, last1, first2,
                        std::next(first2, std::distance(first1, last1)));
}

/*
 * 函数原型：
 *    template <typename ForwardIt, typename Compare>
 *    bool is_sorted(ForwardIt first, ForwardIt last, Compare comp);
 *
 *    template <typename ForwardIt>
 *    bool is_sorted(ForwardIt first, ForwardIt last);
 *
 * 函数说明：
 *    该函数用于判断指定区间是否已排序
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt, typename Compare>
bool is_sorted(ForwardIt first, ForwardIt last, Compare comp) {
  return std::is_sorted_until(first, last, comp) == last;
}

template <typename ForwardIt>
bool is_sorted(ForwardIt first, ForwardIt last) {
  return std::is_sorted_until(first, last) == last;
}

/*
 * 函数原型：
 *    template <typename ForwardIt, typename Compare>
 *    ForwardIt is_sorted_until(ForwardIt first, ForwardIt last, Compare comp);
 *
 *    template <typename ForwardIt>
 *    ForwardIt is_sorted_until(ForwardIt first, ForwardIt last);
 *
 * 函数说明：
 *    该函数用于查找从头开始满足已排序的子区间
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt, typename Compare>
ForwardIt is_sorted_until(ForwardIt first, ForwardIt last, Compare comp) {
  if (first == last) return last;
  auto next = first;
  while (++next != last) {
    if (comp(*next, *first)) return next;
    first = next;
  }
  return last;
}

template <typename ForwardIt>
ForwardIt is_sorted_until(ForwardIt first, ForwardIt last) {
  if (first == last) return last;
  auto next = first;
  while (++next != last) {
    if (*next < *first) return next;
    first = next;
  }
  return last;
}

/*
 * 函数原型：
 *    template <typename ForwardIt1, typename ForwardIt2>
 *    void iter_swap(ForwardIt1 a, ForwardIt2 b);
 *
 * 函数说明：
 *    该函数用于交换两个迭代器所指向的值
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt1, typename ForwardIt2>
void iter_swap(ForwardIt1 a, ForwardIt2 b) {
  using std::swap;
  swap(*a, *b);
}

/*
 * 函数原型：
 *    template <typename InputIt1, typename InputIt2, typename Compare>
 *    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp);
 *
 *    template <typename InputIt1, typename InputIt2>
 *    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2);
 *
 * 函数说明：
 *    该函数用于判断两个区间的字典序的先后顺序
 *
 * 模板参数要求：
 *    至少是输入迭代器 和 输入迭代器
 */
template <typename InputIt1, typename InputIt2, typename Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                             InputIt2 last2, Compare comp) {
  while (first1 != last1 && first2 != last2) {
    if (comp(*first1, *first2)) return true;
    if (comp(*first2, *first1)) return false;
    ++first1;
    ++first2;
  }
  return first1 == last1 && first2 != last2;
}

template <typename InputIt1, typename InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                             InputIt2 last2) {
  while (first1 != last1 && first2 != last2) {
    if (*first1 < *first2) return true;
    if (*first2 < *first1) return false;
    ++first1;
    ++first2;
  }
  return first1 == last1 && first2 != last2;
}

/*
 * 函数原型：
 *    template <typename ForwardIt, typename T, typename Compare>
 *    ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T &value, Compare comp);
 *
 *    template <typename ForwardIt, typename T>
 *    ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T &value);
 *
 * 函数说明：
 *    该函数返回在指定的有序区间内，第一个大于等于 value 的位置
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt, typename T, typename Compare>
ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T &value,
                      Compare comp) {
  auto count = std::distance(first, last);
  while (count > 0) {
    auto half = count / 2;
    auto it = std::next(first, half);
    if (comp(*it, value)) {
      first = ++it;
      count -= half + 1;
    } else {
      count = half;
    }
  }
  return first;
}

template <typename ForwardIt, typename T>
ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T &value) {
  auto count = std::distance(first, last);
  while (count > 0) {
    auto half = count / 2;
    auto it = std::next(first, half);
    if (*it < value) {
      first = ++it;
      count -= half + 1;
    } else {
      count = half;
    }
  }
  return first;
}

/*
 * 函数原型：
 *    template <typename RandomAccessIt, typename Compare>
 *    void make_heap(RandomAccessIt first, RandomAccessIt last, Compare comp);
 *
 *    template <typename RandomAccessIt>
 *    void make_heap(RandomAccessIt first, RandomAccessIt last);
 *
 * 函数说明：
 *    该函数用于将指定区间转化为堆
 *
 * 模板参数要求：
 *    要求是随机迭代器
 */
namespace detail {

template <typename RandomAccessIt, typename Distance, typename T,
          typename Compare>
void __pop_heap(RandomAccessIt first, Distance current_index,
                Distance max_index, T &&value, Compare comp) {
  for (;;) {
    auto lhs_index = current_index * 2 + 1;
    auto rhs_index = lhs_index + 1;
    if (lhs_index >= max_index) break;
    if (rhs_index >= max_index) {
      if (comp(value, first[lhs_index])) {
        first[current_index] = std::move(first[lhs_index]);
        current_index = lhs_index;
      }
      break;
    }
    if (comp(first[lhs_index], value) && comp(first[rhs_index], value)) break;
    if (comp(first[lhs_index], first[rhs_index])) {
      first[current_index] = std::move(first[rhs_index]);
      current_index = rhs_index;
    } else {
      first[current_index] = std::move(first[lhs_index]);
      current_index = lhs_index;
    }
  }
  first[current_index] = std::move(value);
}

}  // namespace detail

template <typename RandomAccessIt, typename Compare>
void make_heap(RandomAccessIt first, RandomAccessIt last, Compare comp) {
  if (last - first <= 1) return;
  auto max_index = last - first;
  auto current_index = (max_index - 2) / 2;
  for (;;) {
    detail::__pop_heap(first, current_index, max_index,
                       std::move(first[current_index]), comp);
    if (current_index == 0) break;
    --current_index;
  }
}

template <typename RandomAccessIt>
void make_heap(RandomAccessIt first, RandomAccessIt last) {
  liuyunbin::make_heap(
      first, last,
      std::less<typename std::iterator_traits<RandomAccessIt>::value_type>());
}

/*
 * 函数原型：
 *    template <typename ForwardIt>
 *    ForwardIt max_element(ForwardIt first, ForwardIt last);
 *
 *    template <typename ForwardIt, typename Compare>
 *    ForwardIt max_element(ForwardIt first, ForwardIt last, Compare comp);
 *
 * 函数说明：
 *    该函数用于求指定区间的最大值
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt>
ForwardIt max_element(ForwardIt first, ForwardIt last) {
  if (first == last) return last;
  ForwardIt largest = first;
  while (++first != last)
    if (*largest < *first) largest = first;
  return largest;
}

template <typename ForwardIt, typename Compare>
ForwardIt max_element(ForwardIt first, ForwardIt last, Compare comp) {
  if (first == last) return last;
  ForwardIt largest = first;
  while (++first != last)
    if (comp(*largest, *first)) largest = first;
  return largest;
}

/*
 * 函数原型：
 *    template <typename T>
 *    const T &max(const T &lhs, const T &rhs);
 *
 *    template <typename T, typename Compare>
 *    const T &max(const T &lhs, const T &rhs, Compare comp);
 *
 *    template <typename T>
 *    T max(std::initializer_list<T> ilist);
 *
 *    template <typename T, typename Compare>
 *    T max(std::initializer_list<T> ilist, Compare comp);
 *
 * 函数说明：
 *    该函数用于求指定参数的最大值
 */
template <typename T>
const T &max(const T &lhs, const T &rhs) {
  return lhs < rhs ? rhs : lhs;
}

template <typename T, typename Compare>
const T &max(const T &lhs, const T &rhs, Compare comp) {
  return comp(lhs, rhs) ? rhs : lhs;
}

template <typename T>
T max(std::initializer_list<T> ilist) {
  return *std::max_element(ilist.begin(), ilist.end());
}

template <typename T, typename Compare>
T max(std::initializer_list<T> ilist, Compare comp) {
  return *std::max_element(ilist.begin(), ilist.end(), comp);
}

/*
 * 函数原型：
 *    template <typename InputIt1, typename InputIt2, typename OutputIt, typename Compare>
 *    OutputIt merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp);
 *
 *    template <typename InputIt1, typename InputIt2, typename OutputIt>
 *    OutputIt merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt d_first);
 *
 * 函数说明：
 *    该函数用于合并两个有序区间
 *
 * 模板参数要求：
 *    至少是 输入迭代器 输入迭代器 输出迭代器
 */
template <typename InputIt1, typename InputIt2, typename OutputIt,
          typename Compare>
OutputIt merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2,
               OutputIt d_first, Compare comp) {
  while (first1 != last1 && first2 != last2) {
    if (comp(*first2, *first1))
      *d_first++ = *first2++;
    else
      *d_first++ = *first1++;
  }
  if (first1 != last1) return std::copy(first1, last1, d_first);
  return std::copy(first2, last2, d_first);
}

template <typename InputIt1, typename InputIt2, typename OutputIt>
OutputIt merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2,
               OutputIt d_first) {
  while (first1 != last1 && first2 != last2) {
    if (*first2 < *first1)
      *d_first++ = *first2++;
    else
      *d_first++ = *first1++;
  }
  if (first1 != last1) return std::copy(first1, last1, d_first);
  return std::copy(first2, last2, d_first);
}

/*
 * 函数原型：
 *    template <typename ForwardIt>
 *    ForwardIt min_element(ForwardIt first, ForwardIt last);
 *
 *    template <typename ForwardIt, typename Compare>
 *    ForwardIt min_element(ForwardIt first, ForwardIt last, Compare comp);
 *
 * 函数说明：
 *    该函数用于求指定区间的最小值
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt>
ForwardIt min_element(ForwardIt first, ForwardIt last) {
  if (first == last) return last;
  ForwardIt smallest = first;
  while (++first != last)
    if (*first < *smallest) smallest = first;
  return smallest;
}

template <typename ForwardIt, typename Compare>
ForwardIt min_element(ForwardIt first, ForwardIt last, Compare comp) {
  if (first == last) return last;
  ForwardIt smallest = first;
  while (++first != last)
    if (comp(*first, *smallest)) smallest = first;
  return smallest;
}

/*
 * 函数原型：
 *    template <typename ForwardIt>
 *    std::pair<ForwardIt, ForwardIt>
 *    minmax_element(ForwardIt first, ForwardIt last);
 *
 *    template <typename ForwardIt, typename Compare>
 *    std::pair<ForwardIt, ForwardIt>
 *    minmax_element(ForwardIt first, ForwardIt last, Compare comp);
 *
 * 函数说明：
 *    该函数用于求指定区间的最小值和最大值
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt>
std::pair<ForwardIt, ForwardIt> minmax_element(ForwardIt first,
                                               ForwardIt last) {
  return {std::min_element(first, last), std::max_element(first, last)};
}

template <typename ForwardIt, typename Compare>
std::pair<ForwardIt, ForwardIt> minmax_element(ForwardIt first, ForwardIt last,
                                               Compare comp) {
  return {std::min_element(first, last, comp),
          std::max_element(first, last, comp)};
}

/*
 * 函数原型：
 *    template <typename T>
 *    std::pair<const T &, const T &>
 *    minmax(const T &lhs, const T &rhs);
 *
 *    template <typename T, typename Compare>
 *    std::pair<const T &, const T &>
 *    minmax(const T &lhs, const T &rhs, Compare comp);
 *
 *    template <typename T>
 *    std::pair<T, T>
 *    minmax(std::initializer_list<T> ilist);
 *
 *    template <typename T, typename Compare>
 *    std::pair<T, T>
 *    minmax(std::initializer_list<T> ilist, Compare comp);
 *
 * 函数说明：
 *    该函数用于求指定区间的最小值和最大值
 */
template <typename T>
std::pair<const T &, const T &> minmax(const T &lhs, const T &rhs) {
  if (lhs < rhs) return {lhs, rhs};
  return {rhs, lhs};
}

template <typename T, typename Compare>
std::pair<const T &, const T &> minmax(const T &lhs, const T &rhs,
                                       Compare comp) {
  if (comp(lhs, rhs)) return {lhs, rhs};
  return {rhs, lhs};
}

template <typename T>
std::pair<T, T> minmax(std::initializer_list<T> ilist) {
  auto p = std::minmax_element(ilist.begin(), ilist.end());
  return {*p.first, *p.second};
}

template <typename T, typename Compare>
std::pair<T, T> minmax(std::initializer_list<T> ilist, Compare comp) {
  auto p = std::minmax_element(ilist.begin(), ilist.end(), comp);
  return {*p.first, *p.second};
}

/*
 * 函数原型：
 *    template <typename T>
 *    const T &min(const T &lhs, const T &rhs);
 *
 *    template <typename T, typename Compare>
 *    const T &min(const T &lhs, const T &rhs, Compare comp);
 *
 *    template <typename T>
 *    T min(std::initializer_list<T> ilist);
 *
 *    template <typename T, typename Compare>
 *    T min(std::initializer_list<T> ilist, Compare comp);
 *
 * 函数说明：
 *    该函数用于求指定参数的最小值
 */
template <typename T>
const T &min(const T &lhs, const T &rhs) {
  return lhs < rhs ? lhs : rhs;
}

template <typename T, typename Compare>
const T &min(const T &lhs, const T &rhs, Compare comp) {
  return comp(lhs, rhs) ? lhs : rhs;
}

template <typename T>
T min(std::initializer_list<T> ilist) {
  return *std::min_element(ilist.begin(), ilist.end());
}

template <typename T, typename Compare>
T min(std::initializer_list<T> ilist, Compare comp) {
  return *std::min_element(ilist.begin(), ilist.end(), comp);
}

/*
 * 函数原型：
 *    template <typename InputIt1, typename InputIt2>
 *    std::pair<InputIt1, InputIt2>
 *    mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2);
 *
 *    template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
 *    std::pair<InputIt1, InputIt2>
 *    mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate op);
 *
 *    // C++14
 *    template <typename InputIt1, typename InputIt2>
 *    std::pair<InputIt1, InputIt2>
 *    mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2);
 *
 *    template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
 *    std::pair<InputIt1, InputIt2>
 *    mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, BinaryPredicate op);
 *
 * 函数说明：
 *    该函数用于返回两个区间内首个不相等的值对应的迭代器
 *
 * 模板参数要求：
 *    至少是 输入迭代器 和 输入迭代器
 */
template <typename InputIt1, typename InputIt2>
std::pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1,
                                       InputIt2 first2) {
  while (first1 != last1 && *first1 == *first2) {
    ++first1;
    ++first2;
  }
  return {first1, first2};
}

template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
std::pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1,
                                       InputIt2 first2, BinaryPredicate op) {
  while (first1 != last1 && op(*first1, *first2)) {
    ++first1;
    ++first2;
  }
  return {first1, first2};
}

// C++14
template <typename InputIt1, typename InputIt2>
std::pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1,
                                       InputIt2 first2, InputIt2 last2) {
  while (first1 != last1 && first2 != last2 && *first1 == *first2) {
    ++first1;
    ++first2;
  }
  return {first1, first2};
}

template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
std::pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1,
                                       InputIt2 first2, InputIt2 last2,
                                       BinaryPredicate op) {
  while (first1 != last1 && first2 != last2 && op(*first1, *first2)) {
    ++first1;
    ++first2;
  }
  return {first1, first2};
}

/*
 * 函数原型：
 *    template <typename BindirIt1, typename BindirIt2>
 *    BindirIt2 move_backward(BindirIt1 first, BindirIt1 last, BindirIt2 d_last);
 *
 * 函数说明：
 *    该函数用于将第二个序列的值移动到第一个序列（从后往前）
 *
 * 模板参数要求：
 *    至少是双向迭代器 和 双向迭代器
 */
template <typename BindirIt1, typename BindirIt2>
BindirIt2 move_backward(BindirIt1 first, BindirIt1 last, BindirIt2 d_last) {
  while (first != last) *--d_last = std::move(*--last);
  return d_last;
}

/*
 * 函数原型：
 *    template <typename InputIt, typename OutputIt>
 *    OutputIt move(InputIt first, InputIt last, OutputIt d_first);
 *
 * 函数说明：
 *    该函数用于将第二个序列的值移动到第一个序列
 *
 * 模板参数要求：
 *    至少是 输入迭代器 和 输出迭代器
 */
template <typename InputIt, typename OutputIt>
OutputIt move(InputIt first, InputIt last, OutputIt d_first) {
  while (first != last) *d_first++ = std::move(*first++);
  return d_first;
}

/*
 * 函数原型：
 *    template <typename BidirIt, typename Compare>
 *    bool next_permutation(BidirIt first, BidirIt last, Compare comp);
 *
 *    template <typename BidirIt>
 *    bool next_permutation(BidirIt first, BidirIt last);
 *
 * 函数说明：
 *    求该序列对应字典序的下一序列
 *
 * 模板参数要求：
 *    至少是双向迭代器
 */
template <typename BidirIt, typename Compare>
bool next_permutation(BidirIt first, BidirIt last, Compare comp) {
  if (first == last) return false;
  auto it = std::prev(last);
  if (first == it) return false;
  for (;;) {
    --it;
    if (comp(*it, *std::next(it))) {
      auto temp_it = last;
      while (!comp(*it, *--temp_it))
        ;
      std::iter_swap(it, temp_it);
      std::reverse(++it, last);
      return true;
    }
    if (it == first) {
      std::reverse(first, last);
      return true;
    }
  }
}

template <typename BidirIt>
bool next_permutation(BidirIt first, BidirIt last) {
  if (first == last) return false;
  auto it = std::prev(last);
  if (first == it) return false;
  for (;;) {
    --it;
    if (*it < *std::next(it)) {
      auto temp_it = last;
      while (!(*it < *--temp_it))
        ;
      std::iter_swap(it, temp_it);
      std::reverse(++it, last);
      return true;
    }
    if (it == first) {
      std::reverse(first, last);
      return true;
    }
  }
}

/*
 * 函数原型：
 *    template <typename InputIt, typename UnaryPredicate>
 *    bool none_of(InputIt first, InputIt last, UnaryPredicate p);
 *
 * 函数说明：
 *    该函数用于查找在指定区间内是否所有元素都不满足谓词 p
 *
 * 模板参数要求：
 *    至少是输入迭代器
 */
template <typename InputIt, typename UnaryPredicate>
bool none_of(InputIt first, InputIt last, UnaryPredicate p) {
  return std::find_if(first, last, p) == last;
}

/*
 * 函数原型：
 *    template <typename RandomAccessIt, typename Compare>
 *    void nth_element(RandomAccessIt first, RandomAccessIt nth, RandomAccessIt last, Compare comp);
 *
 *    template <typename RandomAccessIt>
 *    void nth_element(RandomAccessIt first, RandomAccessIt nth, RandomAccessIt last);
 *
 * 函数说明：
 *    该函数使得第 nth 个元素的元素和排好序的位置的元素相同，且，在它之前的元素都小于等于它，在它之后的元素都大于等于它
 *
 * 模板参数要求：
 *    要求是随机迭代器
 */
template <typename RandomAccessIt, typename Compare>
void nth_element(RandomAccessIt first, RandomAccessIt nth, RandomAccessIt last,
                 Compare comp) {
  if (last - first <= 1) return;
  auto value = std::move(*first);
  auto lhs = first;
  auto rhs = last - 1;
  while (lhs != rhs) {
    while (lhs != rhs && !comp(*rhs, value)) --rhs;
    if (lhs == rhs) break;
    *lhs++ = std::move(*rhs);
    while (lhs != rhs && !comp(value, *lhs)) ++lhs;
    if (lhs == rhs) break;
    *rhs-- = std::move(*lhs);
  }
  *lhs = std::move(value);
  if (lhs == nth) return;
  if (lhs < nth)
    liuyunbin::nth_element(lhs + 1, nth, last, comp);
  else
    liuyunbin::nth_element(first, nth, lhs, comp);
}

template <typename RandomAccessIt>
void nth_element(RandomAccessIt first, RandomAccessIt nth,
                 RandomAccessIt last) {
  liuyunbin::nth_element(
      first, nth, last,
      std::less<typename std::iterator_traits<RandomAccessIt>::value_type>());
}

/*
 * 函数原型：
 *    template <typename InputIt, typename RandomAccessIt, typename Compare>
 *    RandomAccessIt partial_sort_copy(InputIt first,
 *                                     InputIt last,
 *                                     RandomAccessIt d_first,
 *                                     RandomAccessIt d_last,
 *                                     Compare comp);
 *
 *    template <typename InputIt, typename RandomAccessIt>
 *    RandomAccessIt partial_sort_copy(InputIt first,
 *                                     InputIt last,
 *                                     RandomAccessIt d_first,
 *                                     RandomAccessIt d_last);
 *
 *
 * 函数说明：
 *    该函数用部分排序，并将结果存入指定区间
 *
 * 模板参数要求：
 *    至少是输入迭代器 随机迭代器
 */
template <typename InputIt, typename RandomAccessIt, typename Compare>
RandomAccessIt partial_sort_copy(InputIt first, InputIt last,
                                 RandomAccessIt d_first, RandomAccessIt d_last,
                                 Compare comp) {
  auto d_middle = d_first;
  while (first != last && d_middle != d_last) *d_middle++ = *first++;
  std::make_heap(d_first, d_middle);
  for (auto it = first; it != last; ++it)
    if (comp(*it, *d_first)) {
      std::pop_heap(d_first, d_middle, comp);
      std::swap(*it, *(d_middle - 1));
      std::push_heap(d_first, d_middle, comp);
    }
  std::sort_heap(d_first, d_middle);
  return d_middle;
}

template <typename InputIt, typename RandomAccessIt>
RandomAccessIt partial_sort_copy(InputIt first, InputIt last,
                                 RandomAccessIt d_first,
                                 RandomAccessIt d_last) {
  return liuyunbin::partial_sort_copy(
      first, last, d_first, d_last,
      std::less<typename std::iterator_traits<RandomAccessIt>::value_type>());
}

/*
 * 函数原型：
 *    template <typename RandomAccessIt, typename Compare>
 *    void partial_sort(RandomAccessIt first, RandomAccessIt middle, RandomAccessIt last, Compare comp);
 *
 *    template <typename RandomAccessIt>
 *    void partial_sort(RandomAccessIt first, RandomAccessIt middle, RandomAccessIt last);
 *
 * 函数说明：
 *    该函数用部分排序
 *
 * 模板参数要求：
 *    要求是随机迭代器
 */
template <typename RandomAccessIt, typename Compare>
void partial_sort(RandomAccessIt first, RandomAccessIt middle,
                  RandomAccessIt last, Compare comp) {
  std::make_heap(first, middle);
  for (auto it = middle; it != last; ++it)
    if (comp(*it, *first)) {
      std::pop_heap(first, middle, comp);
      std::swap(*it, *(middle - 1));
      std::push_heap(first, middle, comp);
    }
  std::sort_heap(first, middle);
}

template <typename RandomAccessIt>
void partial_sort(RandomAccessIt first, RandomAccessIt middle,
                  RandomAccessIt last) {
  liuyunbin::partial_sort(
      first, middle, last,
      std::less<typename std::iterator_traits<RandomAccessIt>::value_type>());
}

/*
 * 函数原型：
 *    template <typename InputIt, typename OutputIt1, typename OutputIt2, typename UnaryPredicate>
 *    std::pair<OutputIt1, OutputIt2> partition_copy(InputIt first,
 *                                                   InputIt last,
 *                                                   OutputIt1 d_first_true,
 *                                                   OutputIt2 d_first_false,
 *                                                   UnaryPredicate p);
 *
 * 函数说明：
 *    对于指定区间内的元素，符合谓词的拷贝在第二个区间，不符合的拷贝在第三个区间
 *
 * 模板参数要求：
 *    至少是输入迭代器 输出迭代器 输出迭代器
 */
template <typename InputIt, typename OutputIt1, typename OutputIt2,
          typename UnaryPredicate>
std::pair<OutputIt1, OutputIt2> partition_copy(InputIt first, InputIt last,
                                               OutputIt1 d_first_true,
                                               OutputIt2 d_first_false,
                                               UnaryPredicate p) {
  while (first != last) {
    if (p(*first))
      *d_first_true++ = *first++;
    else
      *d_first_false++ = *first++;
  }
  return {d_first_true, d_first_false};
}

/*
 * 函数原型：
 *    template <typename ForwardIt, typename UnaryPredicate>
 *    ForwardIt partition_point(ForwardIt first, ForwardIt last, UnaryPredicate p);
 *
 * 函数说明：
 *    找出第一个不满足谓词 p 的迭代器
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt, typename UnaryPredicate>
ForwardIt partition_point(ForwardIt first, ForwardIt last, UnaryPredicate p) {
  while (first != last && p(*first)) ++first;
  return first;
}

/*
 * 函数原型：
 *    template <typename ForwardIt, typename UnaryPredicate>
 *    ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPredicate p);
 *
 * 函数说明：
 *    调整指定区间内元素的顺序，使得，符合谓词的在前，不符合的在后
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt, typename UnaryPredicate>
ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPredicate p) {
  first = std::find_if_not(first, last, p);
  if (first == last) return first;
  for (auto next = std::next(first); next != last; ++next)
    if (p(*next)) std::iter_swap(first++, next);
  return first;
}

/*
 * 函数原型：
 *    template <typename RandomAccessIt, typename Compare>
 *    void pop_heap(RandomAccessIt first, RandomAccessIt last, Compare comp);
 *
 *    template <typename RandomAccessIt>
 *    void pop_heap(RandomAccessIt first, RandomAccessIt last);
 *
 * 函数说明：
 *    该函数用于删除堆顶元素，并将放在最后一个位置
 *
 * 模板参数要求：
 *    要求是随机迭代器
 */
template <typename RandomAccessIt, typename Compare>
void pop_heap(RandomAccessIt first, RandomAccessIt last, Compare comp) {
  if (last - first <= 1) return;
  auto value = std::move(*--last);
  *last = std::move(*first);

  auto max_index = last - first;
  decltype(max_index) current_index = 0;
  detail::__pop_heap(first, current_index, max_index, std::move(value), comp);
}

template <typename RandomAccessIt>
void pop_heap(RandomAccessIt first, RandomAccessIt last) {
  liuyunbin::pop_heap(
      first, last,
      std::less<typename std::iterator_traits<RandomAccessIt>::value_type>());
}

/*
 * 函数原型：
 *    template <typename BidirIt, typename Compare>
 *    bool prev_permutation(BidirIt first, BidirIt last, Compare comp);
 *
 *    template <typename BidirIt>
 *    bool prev_permutation(BidirIt first, BidirIt last);
 *
 * 函数说明：
 *    求该序列对应字典序的上一序列
 *
 * 模板参数要求：
 *    至少是双向迭代器
 */
template <typename BidirIt, typename Compare>
bool prev_permutation(BidirIt first, BidirIt last, Compare comp) {
  if (first == last) return false;
  auto it = std::prev(last);
  if (first == it) return false;
  for (;;) {
    --it;
    if (comp(*std::next(it), *it)) {
      auto temp_it = last;
      while (!comp(*--temp_it, *it))
        ;
      std::iter_swap(it, temp_it);
      std::reverse(++it, last);
      return true;
    }
    if (it == first) {
      std::reverse(first, last);
      return true;
    }
  }
}

template <typename BidirIt>
bool prev_permutation(BidirIt first, BidirIt last) {
  if (first == last) return false;
  auto it = std::prev(last);
  if (first == it) return false;
  for (;;) {
    --it;
    if (*std::next(it) < *it) {
      auto temp_it = last;
      while (!(*--temp_it < *it))
        ;
      std::iter_swap(it, temp_it);
      std::reverse(++it, last);
      return true;
    }
    if (it == first) {
      std::reverse(first, last);
      return true;
    }
  }
}

/*
 * 函数原型：
 *    template <typename RandomAccessIt, typename Compare>
 *    void push_heap(RandomAccessIt first, RandomAccessIt last, Compare comp);
 *
 *    template <typename RandomAccessIt>
 *    void push_heap(RandomAccessIt first, RandomAccessIt last);
 *
 * 函数说明：
 *    该函数用于将最后一个元素打入堆
 *
 * 模板参数要求：
 *    要求是随机迭代器
 */
template <typename RandomAccessIt, typename Compare>
void push_heap(RandomAccessIt first, RandomAccessIt last, Compare comp) {
  if (last - first <= 1) return;
  auto value = std::move(*--last);
  auto current_index = last - first;
  auto parent_index = (current_index - 1) / 2;
  while (current_index > 0 && comp(first[parent_index], value)) {
    first[current_index] = std::move(first[parent_index]);
    current_index = parent_index;
    parent_index = (current_index - 1) / 2;
  }
  first[current_index] = std::move(value);
}

template <typename RandomAccessIt>
void push_heap(RandomAccessIt first, RandomAccessIt last) {
  if (last - first <= 1) return;
  auto value = std::move(*--last);
  auto current_index = last - first;
  auto parent_index = (current_index - 1) / 2;
  while (current_index > 0 && first[parent_index] < value) {
    first[current_index] = std::move(first[parent_index]);
    current_index = parent_index;
    parent_index = (current_index - 1) / 2;
  }
  first[current_index] = std::move(value);
}

/*
 * 函数原型：
 *    template <typename InputIt, typename OutputIt, typename UnaryPredicate>
 *    OutputIt remove_copy_if(InputIt first, InputIt last, OutputIt d_first, UnaryPredicate p);
 *
 * 函数说明：
 *    该函数用于移除区间内的满足指定谓词的元素，并将结果存入指定区间
 *
 * 模板参数要求：
 *    至少是输入迭代器 输出迭代器
 */
template <typename InputIt, typename OutputIt, typename UnaryPredicate>
OutputIt remove_copy_if(InputIt first, InputIt last, OutputIt d_first,
                        UnaryPredicate p) {
  while (first != last) {
    if (p(*first))
      ++first;
    else
      *d_first++ = *first++;
  }
  return d_first;
}

/*
 * 函数原型：
 *    template <typename InputIt, typename OutputIt, typename T>
 *    OutputIt remove_copy(InputIt first, InputIt last, OutputIt d_first, const T &value);
 *
 * 函数说明：
 *    该函数用于移除区间内的指定元素，并将结果存入指定区间
 *
 * 模板参数要求：
 *    至少是输入迭代器 输出迭代器
 */
template <typename InputIt, typename OutputIt, typename T>
OutputIt remove_copy(InputIt first, InputIt last, OutputIt d_first,
                     const T &value) {
  while (first != last) {
    if (*first == value)
      ++first;
    else
      *d_first++ = *first++;
  }
  return d_first;
}

/*
 * 函数原型：
 *    template <typename ForwardIt, typename UnaryPredicate>
 *    ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate p);
 *
 * 函数说明：
 *    该函数用于移除区间内的满足指定谓词的元素
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt, typename UnaryPredicate>
ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate p) {
  for (auto it = first; it != last; ++it) {
    if (p(*it)) continue;
    *first++ = *it;
  }
  return first;
}

/*
 * 函数原型：
 *    template <typename ForwardIt, typename T>
 *    ForwardIt remove(ForwardIt first, ForwardIt last, const T &value);
 *
 * 函数说明：
 *    该函数用于移除区间内的指定元素
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt, typename T>
ForwardIt remove(ForwardIt first, ForwardIt last, const T &value) {
  for (auto it = first; it != last; ++it) {
    if (*it == value) continue;
    *first++ = *it;
  }
  return first;
}

/*
 * 函数原型：
 *    template <typename InputIt,
 *              typename OutputIt,
 *              typename UnaryPredicate,
 *              typename T>
 *    OutputIt replace_copy_if(InputIt first,
 *                             InputIt last,
 *                             OutputIt d_first,
 *                             UnaryPredicate p,
 *                             const T &new_value);
 *
 * 函数说明：
 *    该函数用于替换区间内的满足指定谓词的元素，并将结果存入指定区间
 *
 * 模板参数要求：
 *  至少是输入迭代器 输出迭代器
 */
template <typename InputIt, typename OutputIt, typename UnaryPredicate,
          typename T>
OutputIt replace_copy_if(InputIt first, InputIt last, OutputIt d_first,
                         UnaryPredicate p, const T &new_value) {
  while (first != last) {
    *d_first++ = p(*first) ? new_value : *first;
    ++first;
  }
  return d_first;
}

/*
 * 函数原型：
 *    template <typename InputIt, typename OutputIt, typename T>
 *    OutputIt replace_copy(InputIt first,
 *                          InputIt last,
 *                          OutputIt d_first,
 *                          const T &old_value,
 *                          const T &new_value);
 *
 * 函数说明：
 *    该函数用于替换区间内的指定元素，并将结果存入指定区间
 *
 * 模板参数要求：
 *    至少是输入迭代器 输出迭代器
 */
template <typename InputIt, typename OutputIt, typename T>
OutputIt replace_copy(InputIt first, InputIt last, OutputIt d_first,
                      const T &old_value, const T &new_value) {
  while (first != last) {
    *d_first++ = *first == old_value ? new_value : *first;
    ++first;
  }
  return d_first;
}

/*
 * 函数原型：
 *    template <typename ForwardIt, typename UnaryPredicate, typename T>
 *    void replace_if(ForwardIt first, ForwardIt last, UnaryPredicate p, const T &new_value);
 *
 * 函数说明：
 *    该函数用于替换区间内的满足指定谓词的元素
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt, typename UnaryPredicate, typename T>
void replace_if(ForwardIt first, ForwardIt last, UnaryPredicate p,
                const T &new_value) {
  while (first != last) {
    if (p(*first)) *first = new_value;
    ++first;
  }
}

/*
 * 函数原型：
 *    template <typename ForwardIt, typename T>
 *    void replace(ForwardIt first, ForwardIt last, const T &old_value, const T &new_value);
 *
 * 函数说明：
 *    该函数用于替换区间内的指定元素
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt, typename T>
void replace(ForwardIt first, ForwardIt last, const T &old_value,
             const T &new_value) {
  while (first != last) {
    if (*first == old_value) *first = new_value;
    ++first;
  }
}

/*
 * 函数原型：
 *    template <typename BidirIt, typename OutputIt>
 *    OutputIt reverse_copy(BidirIt first, BidirIt last, OutputIt d_first);
 *
 * 函数说明：
 *    该函数将指定区间逆序，并将结果存入指定区间
 *
 * 模板参数要求：
 *    至少是双向迭代器 和 输出迭代器
 */
template <typename BidirIt, typename OutputIt>
OutputIt reverse_copy(BidirIt first, BidirIt last, OutputIt d_first) {
  while (first != last) *d_first++ = *--last;
  return d_first;
}

/*
 * 函数原型：
 *    template <typename BidirIt>
 *    void reverse(BidirIt first, BidirIt last);
 *
 * 函数说明：
 *    该函数用于将指定区间逆序
 *
 * 模板参数要求：
 *    至少是双向迭代器
 */
template <typename BidirIt>
void reverse(BidirIt first, BidirIt last) {
  while (first != last && --last != first) std::iter_swap(first++, last);
}

/*
 * 函数原型：
 *    template <typename ForwardIt, typename OutputIt>
 *    OutputIt rotate_copy(ForwardIt first, ForwardIt n_first, ForwardIt last, OutputIt d_first);
 *
 * 函数说明：
 *    该函数用于交换区间内的元素，并将结果拷入指定区间
 *
 * 模板参数要求：
 *    至少是前向迭代器 和 输出迭代器
 */
template <typename ForwardIt, typename OutputIt>
OutputIt rotate_copy(ForwardIt first, ForwardIt n_first, ForwardIt last,
                     OutputIt d_first) {
  d_first = std::copy(n_first, last, d_first);
  return std::copy(first, n_first, d_first);
}

/*
 * 函数原型：
 *    template <typename ForwardIt>
 *    ForwardIt rotate(ForwardIt first, ForwardIt n_first, ForwardIt last);
 *
 * 函数说明：
 *    该函数用于交换区间内的元素
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt>
ForwardIt rotate(ForwardIt first, ForwardIt n_first, ForwardIt last) {
  if (first == n_first) return last;
  if (n_first == last) return first;
  auto next = n_first;
  while (next != last) {
    std::iter_swap(next++, first++);
    if (first == n_first) n_first = next;
  }
  auto return_value = first;
  std::rotate(first, n_first, last);
  return return_value;
}

/*
 * 函数原型：
 *    template <typename ForwardIt, typename Size, typename T>
 *    ForwardIt search_n(ForwardIt first, ForwardIt last, Size count, const T &value);
 *
 *    template <typename ForwardIt, typename Size, typename T, typename BinaryPredicate>
 *    ForwardIt search_n(ForwardIt first,
 *                       ForwardIt last,
 *                       Size count,
 *                       const T &value,
 *                       BinaryPredicate p);
 *
 * 函数说明：
 *    该函数用于查找是否前一个区间的某个子区间是否存在连续的 count 个元素 value，
 *    如果存在，返回，第一个子区间的第一个元素的迭代器
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt, typename Size, typename T>
ForwardIt search_n(ForwardIt first, ForwardIt last, Size count,
                   const T &value) {
  for (; first != last; ++first) {
    if (!(*first == value)) continue;
    auto temp = first;
    Size current_count = 0;
    while (true) {
      ++current_count;
      if (current_count == count) return temp;
      ++first;
      if (first == last) return last;
      if (*first == value) continue;
      break;
    }
  }
  return last;
}

template <typename ForwardIt, typename Size, typename T,
          typename BinaryPredicate>
ForwardIt search_n(ForwardIt first, ForwardIt last, Size count, const T &value,
                   BinaryPredicate p) {
  for (; first != last; ++first) {
    if (!p(*first, value)) continue;
    auto temp = first;
    Size current_count = 0;
    while (true) {
      ++current_count;
      if (current_count == count) return temp;
      ++first;
      if (first == last) return last;
      if (p(*first, value)) continue;
      break;
    }
  }
  return last;
}

/*
 * 函数原型：
 *    template <typename ForwardIt1, typename ForwardIt2>
 *    ForwardIt1 search(ForwardIt1 first1,
 *                      ForwardIt1 last1,
 *                      ForwardIt2 first2,
 *                      ForwardIt2 last2);
 *
 *    template <typename ForwardIt1, typename ForwardIt2, typename BinaryPredicate>
 *    ForwardIt1 search(ForwardIt1 first1,
 *                      ForwardIt1 last1,
 *                      ForwardIt2 first2,
 *                      ForwardIt2 last2,
 *                      BinaryPredicate p);
 *
 * 函数说明：
 *    该函数用于查找是否前一个区间的某个子区间和后一个区间的元素相同，如果存在，返回，第一个子区间的第一个元素的迭代器
 *
 * 模板参数要求：
 *    至少是前向迭代器 和 前向迭代器
 */
template <typename ForwardIt1, typename ForwardIt2>
ForwardIt1 search(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2,
                  ForwardIt2 last2) {
  while (true) {
    auto temp = first1;
    for (auto it = first2;; ++it, ++temp) {
      if (it == last2) return first1;
      if (temp == last1) return last1;
      if (*temp == *it) continue;
      break;
    }
    ++first1;
  }
}

template <typename ForwardIt1, typename ForwardIt2, typename BinaryPredicate>
ForwardIt1 search(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2,
                  ForwardIt2 last2, BinaryPredicate p) {
  while (true) {
    auto temp = first1;
    for (auto it = first2;; ++it, ++temp) {
      if (it == last2) return first1;
      if (temp == last1) return last1;
      if (p(*temp, *it)) continue;
      break;
    }
    ++first1;
  }
}

/*
 * 函数原型：
 *    template <typename InputIt1, typename InputIt2, typename OutputIt, typename Compare>
 *    OutputIt set_difference(InputIt1 first1,
 *                            InputIt1 last1,
 *                            InputIt2 first2,
 *                            InputIt2 last2,
 *                            OutputIt d_first,
 *                            Compare comp);
 *
 *    template <typename InputIt1, typename InputIt2, typename OutputIt>
 *    OutputIt set_difference(InputIt1 first1,
 *                            InputIt1 last1,
 *                            InputIt2 first2,
 *                            InputIt2 last2,
 *                            OutputIt d_first);
 *
 * 函数说明：
 *    求两个有序集合的差集
 *
 * 模板参数要求：
 *    至少是输入迭代器 输入迭代器 输出迭代器
 */
template <typename InputIt1, typename InputIt2, typename OutputIt,
          typename Compare>
OutputIt set_difference(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                        InputIt2 last2, OutputIt d_first, Compare comp) {
  while (first1 != last1 && first2 != last2) {
    if (comp(*first2, *first1))
      ++first2;
    else if (comp(*first1, *first2))
      *d_first++ = *first1++;
    else {
      ++first1;
      ++first2;
    }
  }
  return std::copy(first1, last1, d_first);
}

template <typename InputIt1, typename InputIt2, typename OutputIt>
OutputIt set_difference(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                        InputIt2 last2, OutputIt d_first) {
  while (first1 != last1 && first2 != last2) {
    if (*first2 < *first1)
      ++first2;
    else if (*first1 < *first2)
      *d_first++ = *first1++;
    else {
      ++first1;
      ++first2;
    }
  }
  return std::copy(first1, last1, d_first);
}

/*
 * 函数原型：
 *    template <typename InputIt1, typename InputIt2, typename OutputIt, typename Compare>
 *    OutputIt set_intersection(InputIt1 first1,
 *                              InputIt1 last1,
 *                              InputIt2 first2,
 *                              InputIt2 last2,
 *                              OutputIt d_first,
 *                              Compare comp);
 *
 *    template <typename InputIt1, typename InputIt2, typename OutputIt>
 *    OutputIt set_intersection(InputIt1 first1,
 *                              InputIt1 last1,
 *                              InputIt2 first2,
 *                              InputIt2 last2,
 *                              OutputIt d_first);
 *
 * 函数说明：
 *    求两个有序集合的交集
 *
 * 模板参数要求：
 *    至少是输入迭代器 输入迭代器 输出迭代器
 */
template <typename InputIt1, typename InputIt2, typename OutputIt,
          typename Compare>
OutputIt set_intersection(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                          InputIt2 last2, OutputIt d_first, Compare comp) {
  while (first1 != last1 && first2 != last2) {
    if (comp(*first2, *first1))
      ++first2;
    else if (comp(*first1, *first2))
      ++first1;
    else {
      *d_first++ = *first1++;
      ++first2;
    }
  }
  return d_first;
}

template <typename InputIt1, typename InputIt2, typename OutputIt>
OutputIt set_intersection(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                          InputIt2 last2, OutputIt d_first) {
  while (first1 != last1 && first2 != last2) {
    if (*first2 < *first1)
      ++first2;
    else if (*first1 < *first2)
      ++first1;
    else {
      *d_first++ = *first1++;
      ++first2;
    }
  }
  return d_first;
}

/*
 * 函数原型：
 *    template <typename InputIt1, typename InputIt2, typename OutputIt, typename Compare>
 *    OutputIt set_symmetric_difference(InputIt1 first1,
 *                                      InputIt1 last1,
 *                                      InputIt2 first2,
 *                                      InputIt2 last2,
 *                                      OutputIt d_first,
 *                                      Compare comp);
 *
 *    template <typename InputIt1, typename InputIt2, typename OutputIt>
 *    OutputIt set_symmetric_difference(InputIt1 first1,
 *                                      InputIt1 last1,
 *                                      InputIt2 first2,
 *                                      InputIt2 last2,
 *                                      OutputIt d_first);
 *
 * 函数说明：
 *    求两个有序集合的补集
 *
 * 模板参数要求：
 *    至少是输入迭代器 输入迭代器 输出迭代器
 */
template <typename InputIt1, typename InputIt2, typename OutputIt,
          typename Compare>
OutputIt set_symmetric_difference(InputIt1 first1, InputIt1 last1,
                                  InputIt2 first2, InputIt2 last2,
                                  OutputIt d_first, Compare comp) {
  while (first1 != last1 && first2 != last2) {
    if (comp(*first2, *first1))
      *d_first++ = *first2++;
    else if (comp(*first1, *first2))
      *d_first++ = *first1++;
    else {
      ++first1;
      ++first2;
    }
  }
  if (first1 != last1) return std::copy(first1, last1, d_first);
  return std::copy(first2, last2, d_first);
}

template <typename InputIt1, typename InputIt2, typename OutputIt>
OutputIt set_symmetric_difference(InputIt1 first1, InputIt1 last1,
                                  InputIt2 first2, InputIt2 last2,
                                  OutputIt d_first) {
  while (first1 != last1 && first2 != last2) {
    if (*first2 < *first1)
      *d_first++ = *first2++;
    else if (*first1 < *first2)
      *d_first++ = *first1++;
    else {
      ++first1;
      ++first2;
    }
  }
  if (first1 != last1) return std::copy(first1, last1, d_first);
  return std::copy(first2, last2, d_first);
}

/*
 * 函数原型：
 *    template <typename InputIt1, typename InputIt2, typename OutputIt, typename Compare>
 *    OutputIt set_union(InputIt1 first1,
 *                       InputIt1 last1,
 *                       InputIt2 first2,
 *                       InputIt2 last2,
 *                       OutputIt d_first,
 *                       Compare comp);
 *
 *    template <typename InputIt1, typename InputIt2, typename OutputIt>
 *    OutputIt set_union(InputIt1 first1,
 *                       InputIt1 last1,
 *                       InputIt2 first2,
 *                       InputIt2 last2,
 *                       OutputIt d_first);
 *
 * 函数说明：
 *    求两个有序集合的并集
 *
 * 模板参数要求：
 *    至少是输入迭代器 输入迭代器 输出迭代器
 */
template <typename InputIt1, typename InputIt2, typename OutputIt,
          typename Compare>
OutputIt set_union(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                   InputIt2 last2, OutputIt d_first, Compare comp) {
  while (first1 != last1 && first2 != last2) {
    if (comp(*first2, *first1))
      *d_first++ = *first2++;
    else if (comp(*first1, *first2))
      *d_first++ = *first1++;
    else {
      *d_first++ = *first1++;
      ++first2;
    }
  }
  if (first1 != last1) return std::copy(first1, last1, d_first);
  return std::copy(first2, last2, d_first);
}

template <typename InputIt1, typename InputIt2, typename OutputIt>
OutputIt set_union(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                   InputIt2 last2, OutputIt d_first) {
  while (first1 != last1 && first2 != last2) {
    if (*first2 < *first1)
      *d_first++ = *first2++;
    else if (*first1 < *first2)
      *d_first++ = *first1++;
    else {
      *d_first++ = *first1++;
      ++first2;
    }
  }
  if (first1 != last1) return std::copy(first1, last1, d_first);
  return std::copy(first2, last2, d_first);
}

/*
 * 函数原型：
 *    template <typename RandomAccessIt, typename Compare>
 *    void sort_heap(RandomAccessIt first, RandomAccessIt last, Compare comp);
 *
 *    template <typename RandomAccessIt>
 *    void sort_heap(RandomAccessIt first, RandomAccessIt last);
 *
 * 函数说明：
 *    该函数用于对堆进行排序
 *
 * 模板参数要求：
 *    要求是随机迭代器
 */
template <typename RandomAccessIt, typename Compare>
void sort_heap(RandomAccessIt first, RandomAccessIt last, Compare comp) {
  if (last - first <= 1) return;
  while (last - first > 1) std::pop_heap(first, last--, comp);
}

template <typename RandomAccessIt>
void sort_heap(RandomAccessIt first, RandomAccessIt last) {
  liuyunbin::sort_heap(
      first, last,
      std::less<typename std::iterator_traits<RandomAccessIt>::value_type>());
}

/*
 * 函数原型：
 *    template <typename RandomAccessIt, typename Compare>
 *    void sort(RandomAccessIt first, RandomAccessIt last, Compare comp);
 *
 *    template <typename RandomAccessIt>
 *    void sort(RandomAccessIt first, RandomAccessIt last);
 *
 * 函数说明：
 *    该函数用于对指定区间进行排序
 *
 * 模板参数要求：
 *    要求是随机迭代器
 */
template <typename RandomAccessIt, typename Compare>
void sort(RandomAccessIt first, RandomAccessIt last, Compare comp) {
  if (last - first <= 1) return;
  auto value = std::move(*first);
  auto lhs = first;
  auto rhs = last - 1;
  while (lhs != rhs) {
    while (lhs != rhs && !comp(*rhs, value)) --rhs;
    if (lhs == rhs) break;
    *lhs++ = std::move(*rhs);
    while (lhs != rhs && !comp(value, *lhs)) ++lhs;
    if (lhs == rhs) break;
    *rhs-- = std::move(*lhs);
  }
  *lhs = std::move(value);
  std::sort(first, lhs, comp);
  std::sort(lhs + 1, last, comp);
}

template <typename RandomAccessIt>
void sort(RandomAccessIt first, RandomAccessIt last) {
  liuyunbin::sort(
      first, last,
      std::less<typename std::iterator_traits<RandomAccessIt>::value_type>());
}

/*
 * 函数原型：
 *    template <typename ForwardIt, typename UnaryPredicate>
 *    ForwardIt stable_partition(ForwardIt first, ForwardIt last, UnaryPredicate p);
 *
 * 函数说明：
 *    调整指定区间内元素的顺序，使得，符合谓词的在前，不符合的在后，保持元素的相对位置
 *
 * 模板参数要求：
 *     C++11 要求至少是双向迭代器，但我觉得用 前向迭代器 就可以
 */
template <typename ForwardIt, typename UnaryPredicate>
ForwardIt stable_partition(ForwardIt first, ForwardIt last, UnaryPredicate p) {
  while (first != last && p(*first)) ++first;
  if (first == last) return last;

  auto n = std::distance(first, last);
  auto *temp_memory =
      new typename std::iterator_traits<ForwardIt>::value_type[n];
  decltype(n) index = 0;
  auto current = first;

  while (first != last) {
    if (p(*first))
      *current++ = *first++;
    else
      temp_memory[index++] = *first++;
  }
  std::copy_n(temp_memory, index, current);
  delete[] temp_memory;
  return current;
}

/*
 * 函数原型：
 *    template <typename RandomAccessIt, typename Compare>
 *    void stable_sort(RandomAccessIt first, RandomAccessIt last, Compare comp);
 *
 *    template <typename RandomAccessIt>
 *    void stable_sort(RandomAccessIt first, RandomAccessIt last);
 *
 * 函数说明：
 *    该函数用于对指定区间进行排序，保持元素的相对位置
 *
 * 模板参数要求：
 *    要求是随机迭代器
 */
template <typename RandomAccessIt, typename Compare>
void stable_sort(RandomAccessIt first, RandomAccessIt last, Compare comp) {
  if (last - first <= 1) return;
  auto mid = first + (last - first) / 2;
  std::sort(first, mid, comp);
  std::sort(mid, last, comp);
  std::inplace_merge(first, mid, last);
}

template <typename RandomAccessIt>
void stable_sort(RandomAccessIt first, RandomAccessIt last) {
  liuyunbin::stable_sort(
      first, last,
      std::less<typename std::iterator_traits<RandomAccessIt>::value_type>());
}

/*
 * 函数原型：
 *    template <typename ForwardIt1, typename ForwardIt2>
 *    ForwardIt2 swap_ranges(ForwardIt1 first1,
 *                           ForwardIt1 last1,
 *                           ForwardIt2 first2);
 *
 * 函数说明：
 *    该函数用于交换两个迭代器区间
 *
 * 模板参数要求：
 *    至少是前向迭代器 前向迭代器
 */
template <typename ForwardIt1, typename ForwardIt2>
ForwardIt2 swap_ranges(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2) {
  while (first1 != last1) std::iter_swap(first1++, first2++);
  return first2;
}

/*
 * 函数原型：
 *    template <typename InputIt, typename OutputIt, typename UnaryPredicate>
 *    OutputIt transform(InputIt first,
 *                       InputIt last,
 *                       OutputIt d_first,
 *                       UnaryPredicate p);
 *
 *    template <typename InputIt1, typename InputIt2, typename OutputIt, typename BinaryPredicate>
 *    OutputIt transform(InputIt1 first1,
 *                       InputIt1 last1,
 *                       InputIt2 first2,
 *                       OutputIt d_first,
 *                       BinaryPredicate p);
 *
 * 函数说明：
 *    该函数用于对指定区间内的元素进行转化
 *
 * 模板参数要求：
 *    至少是输入迭代器 输出迭代器
 */
template <typename InputIt, typename OutputIt, typename UnaryPredicate>
OutputIt transform(InputIt first, InputIt last, OutputIt d_first,
                   UnaryPredicate p) {
  while (first != last) *d_first++ = p(*first++);
  return d_first;
}

template <typename InputIt1, typename InputIt2, typename OutputIt,
          typename BinaryPredicate>
OutputIt transform(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                   OutputIt d_first, BinaryPredicate p) {
  while (first1 != last1) *d_first++ = p(*first1++, *first2++);
  return d_first;
}

/*
 * 函数原型：
 *    template <typename InputIt, typename OutputIt>
 *    OutputIt unique_copy(InputIt first,
 *                         InputIt last,
 *                         OutputIt d_first);
 *
 *    template <typename InputIt, typename OutputIt, typename BinaryPredicate>
 *    OutputIt unique_copy(InputIt first,
 *                         InputIt last,
 *                         OutputIt d_first,
 *                         BinaryPredicate p);
 *
 * 函数说明：
 *    该函数用于去除指定区间内相同的相邻元素，并将结果拷入对应区间
 *
 * 模板参数要求：
 *    至少是输入迭代器 输出迭代器
 */
template <typename InputIt, typename OutputIt>
OutputIt unique_copy(InputIt first, InputIt last, OutputIt d_first) {
  if (first == last) return d_first;
  *d_first = *first;
  while (++first != last)
    if (!(*first == *d_first)) *++d_first = *first;
  return ++d_first;
}

template <typename InputIt, typename OutputIt, typename BinaryPredicate>
OutputIt unique_copy(InputIt first, InputIt last, OutputIt d_first,
                     BinaryPredicate p) {
  if (first == last) return d_first;
  *d_first = *first;
  while (++first != last)
    if (!p(*first, *d_first)) *++d_first = *first;
  return ++d_first;
}

/*
 * 函数原型：
 *    template <typename ForwardIt>
 *    ForwardIt unique(ForwardIt first, ForwardIt last);
 *
 *    template <typename ForwardIt, typename BinaryPredicate>
 *    ForwardIt unique(ForwardIt first,
 *                     ForwardIt last,
 *                     BinaryPredicate p);
 *
 * 函数说明：
 *    该函数用于去除指定区间内相同的相邻元素
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt>
ForwardIt unique(ForwardIt first, ForwardIt last) {
  if (first == last) return last;
  auto next = first;
  while (++next != last)
    if (!(*first == *next)) *++first = std::move(*next);
  return ++first;
}

template <typename ForwardIt, typename BinaryPredicate>
ForwardIt unique(ForwardIt first, ForwardIt last, BinaryPredicate p) {
  if (first == last) return last;
  auto next = first;
  while (++next != last)
    if (!p(*first, *next)) *++first = std::move(*next);
  return ++first;
}

/*
 * 函数原型：
 *    template <typename ForwardIt, typename T, typename Compare>
 *    ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T &value, Compare comp);
 *
 *    template <typename ForwardIt, typename T>
 *    ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T &value);
 *
 * 函数说明：
 *    该函数返回在指定的有序区间内，第一个大于 value 的位置
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt, typename T, typename Compare>
ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T &value,
                      Compare comp) {
  auto count = std::distance(first, last);
  while (count > 0) {
    auto half = count / 2;
    auto it = std::next(first, half);
    if (!comp(value, *it)) {
      first = ++it;
      count -= half + 1;
    } else {
      count = half;
    }
  }
  return first;
}

template <typename ForwardIt, typename T>
ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T &value) {
  auto count = std::distance(first, last);
  while (count > 0) {
    auto half = count / 2;
    auto it = std::next(first, half);
    if (!(value < *it)) {
      first = ++it;
      count -= half + 1;
    } else {
      count = half;
    }
  }
  return first;
}

}  // namespace liuyunbin

#endif
