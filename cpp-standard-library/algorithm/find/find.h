#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_FIND_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_FIND_H_

namespace liuyunbin {

/*
 * find
 */
template <typename InputIt, typename T>
InputIt find(InputIt first, InputIt last, const T &val) {
  while (first != last && *first != val)
    ++first;
  return first;
}

} // namespace liuyunbin

#endif
