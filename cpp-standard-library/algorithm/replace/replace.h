#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_REPLACE_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_REPLACE_H_

namespace liuyunbin {

/*
 * replace
 */
template <typename ForwardIt, typename T>
void replace(ForwardIt first, ForwardIt last, const T &old_value,
             const T &new_value) {
  while (first != last) {
    if (*first == old_value)
      *first = new_value;
    ++first;
  }
}

} // namespace liuyunbin

#endif
