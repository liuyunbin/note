#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_FIND_IF_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_FIND_IF_H_

namespace liuyunbin {

/*
 * find_if
 */
template <typename InputIt, typename UnaryPredicate>
InputIt find_if(InputIt first, InputIt last, UnaryPredicate p) {
  while (first != last && p(*first) == false)
    ++first;
  return first;
}

} // namespace liuyunbin

#endif
