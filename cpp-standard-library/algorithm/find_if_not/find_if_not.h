#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_FIND_IF_NOT_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_FIND_IF_NOT_H_

namespace liuyunbin {

/*
 * find_if_not
 */
template <typename InputIt, typename UnaryPredicate>
InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate p) {
  while (first != last && p(*first) == true)
    ++first;
  return first;
}

} // namespace liuyunbin

#endif
