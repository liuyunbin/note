#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_IS_PERMUTATION_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_IS_PERMUTATION_H_

#include <algorithm>
#include <iterator>
#include <utility>

namespace liuyunbin {

/*
 * is_permutation
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
    if (std::find(first1, i, *i) != i)
      continue;
    if (std::count(i, last1, *i) != std::count(first2, last2, *i))
      return false;
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

} // namespace liuyunbin

#endif
