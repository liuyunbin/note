#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_FIND_END_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_FIND_END_H_

#include <algorithm>
#include <iterator>

namespace liuyunbin {

/*
 * find_end
 */
template <typename ForwardIt1, typename ForwardIt2>
ForwardIt1 __find_end(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2,
                      ForwardIt2 last2, std::forward_iterator_tag,
                      std::forward_iterator_tag) {
  if (first2 == last2)
    return last1;
  auto result = last1;
  while (true) {
    auto new_result = std::search(first1, last1, first2, last2);
    if (new_result == last1)
      break;
    first1 = result = new_result;
    ++first1;
  }
  return result;
}

template <typename ForwardIt1, typename ForwardIt2>
ForwardIt1 __find_end(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2,
                      ForwardIt2 last2, std::bidirectional_iterator_tag,
                      std::bidirectional_iterator_tag) {
  if (first2 == last2)
    return last1;
  std::reverse_iterator<ForwardIt1> reverse_first1(first1);
  std::reverse_iterator<ForwardIt1> reverse_last1(last1);
  std::reverse_iterator<ForwardIt2> reverse_first2(first2);
  std::reverse_iterator<ForwardIt2> reverse_last2(last2);

  auto result =
      std::search(reverse_last1, reverse_first1, reverse_last2, reverse_first2);
  if (result == reverse_first1)
    return last1;
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
  if (first2 == last2)
    return last1;
  auto result = last1;
  while (true) {
    auto new_result = std::search(first1, last1, first2, last2, p);
    if (new_result == last1)
      break;
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
  if (first2 == last2)
    return last1;
  std::reverse_iterator<ForwardIt1> reverse_first1(first1);
  std::reverse_iterator<ForwardIt1> reverse_last1(last1);
  std::reverse_iterator<ForwardIt2> reverse_first2(first2);
  std::reverse_iterator<ForwardIt2> reverse_last2(last2);

  auto result = std::search(reverse_last1, reverse_first1, reverse_last2,
                            reverse_first2, p);
  if (result == reverse_first1)
    return last1;
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

} // namespace liuyunbin

#endif
