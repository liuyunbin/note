#ifndef CPP_STANDARD_LIBRARY_NUMERIC_H_
#define CPP_STANDARD_LIBRARY_NUMERIC_H_

#include <utility>

namespace liuyunbin {

/*
 * 函数原型：
 *    template <typename InputIt, typename T>
 *    T accumulate(InputIt first, InputIt last, T init);
 *
 *    template <typename InputIt, typename T, typename BinaryOperation>
 *    T accumulate(InputIt first, InputIt last, T init, BinaryOperation op);
 *
 * 函数说明：
 *    该函数用于求指定区间的值的和，可使用 std::move 提高效率
 *
 * 模板参数要求：
 *    至少是输入迭代器
 */
template <typename InputIt, typename T>
T accumulate(InputIt first, InputIt last, T init) {
  while (first != last)
    init = std::move(init) + *first++;
  return init;
}

template <typename InputIt, typename T, typename BinaryOperation>
T accumulate(InputIt first, InputIt last, T init, BinaryOperation op) {
  while (first != last)
    init = op(std::move(init), *first++);
  return init;
}

/*
 * 函数原型：
 *    template <typename InputIt, typename OutputIt>
 *    OutputIt adjacent_difference(InputIt first, InputIt last, OutputIt d_first);
 *
 *    template <typename InputIt, typename OutputIt, typename BinaryOperation>
 *    OutputIt adjacent_difference(InputIt first, InputIt last, OutputIt d_first, BinaryOperation op);
 *
 * 函数说明：
 *    该函数用于求指定区间的值的差值，可使用 std::move 提高效率
 *
 * 模板参数要求：
 *    至少是输入迭代器 和 输出迭代器
 */
template <typename InputIt, typename OutputIt>
OutputIt adjacent_difference(InputIt first, InputIt last, OutputIt d_first) {
  if (first == last)
    return d_first;
  auto previous_value = *first;
  *d_first++ = previous_value;
  while (++first != last) {
    *d_first++ = *first - std::move(previous_value);
    previous_value = *first;
  }
  return d_first;
}

template <typename InputIt, typename OutputIt, typename BinaryOperation>
OutputIt adjacent_difference(InputIt first, InputIt last, OutputIt d_first,
                             BinaryOperation op) {
  if (first == last)
    return d_first;
  auto previous_value = *first;
  *d_first++ = previous_value;
  while (++first != last) {
    *d_first++ = op(*first, std::move(previous_value));
    previous_value = *first;
  }
  return d_first;
}

/*
 * 函数原型：
 *    template <typename InputIt1, typename InputIt2, typename T>
 *    T inner_product(InputIt1 first1, InputIt1 last1, InputIt2 first2, T init);
 *
 *    template <typename InputIt1, typename InputIt2, typename T, typename BinaryOperation1, typename BinaryOperation2>
 *    T inner_product(InputIt1 first1, InputIt1 last1, InputIt2 first2, T init, BinaryOperation1 op1, BinaryOperation2 op2);
 *
 * 函数说明：
 *    该函数用于求指定区间的值的内积，可使用 std::move 提高效率
 *
 * 模板参数要求：
 *    至少是输入迭代器
 */
template <typename InputIt1, typename InputIt2, typename T>
T inner_product(InputIt1 first1, InputIt1 last1, InputIt2 first2, T init) {
  while (first1 != last1)
    init = std::move(init) + *first1++ * *first2++;
  return init;
}

template <typename InputIt1, typename InputIt2, typename T,
          typename BinaryOperation1, typename BinaryOperation2>
T inner_product(InputIt1 first1, InputIt1 last1, InputIt2 first2, T init,
                BinaryOperation1 op1, BinaryOperation2 op2) {
  while (first1 != last1)
    init = op1(std::move(init), op2(*first1++, *first2++));
  return init;
}

/*
 * 函数原型：
 *    template <typename ForwardIt, typename T>
 *    void iota(ForwardIt first, ForwardIt last, T value);
 *
 * 函数说明：
 *    以 value 为初始值，而后元素依次 ++
 *
 * 模板参数要求：
 *    至少是前向迭代器
 */
template <typename ForwardIt, typename T>
void iota(ForwardIt first, ForwardIt last, T value) {
  while (first != last)
    *first++ = value++;
}

/*
 * 函数原型：
 *    template<typename InputIt, typename OutputIt>
 *    OutputIt partial_sum(InputIt first, InputIt last, OutputIt d_first);
 *
 *    template<typename InputIt, typename OutputIt, typename BinaryOperation>
 *    OutputIt partial_sum(InputIt first, InputIt last, OutputIt d_first, BinaryOperation op);
 *
 * 函数说明：
 *    该函数用于求指定区间的部分和，可使用 std::move 提高效率
 *
 * 模板参数要求：
 *    至少是输入迭代器 和 输出迭代器
 */
template <typename InputIt, typename OutputIt>
OutputIt partial_sum(InputIt first, InputIt last, OutputIt d_first) {
  if (first == last)
    return d_first;
  auto value = *first;
  *d_first++ = value;
  while (++first != last) {
    value = std::move(value) + *first;
    *d_first++ = value;
  }
  return d_first;
}

template <typename InputIt, typename OutputIt, typename BinaryOperation>
OutputIt partial_sum(InputIt first, InputIt last, OutputIt d_first,
                     BinaryOperation op) {
  if (first == last)
    return d_first;
  auto value = *first;
  *d_first++ = value;
  while (++first != last) {
    value = op(std::move(value), *first);
    *d_first++ = value;
  }
  return d_first;
}

} // namespace liuyunbin

#endif
