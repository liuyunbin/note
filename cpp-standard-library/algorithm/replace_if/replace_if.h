#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_REPLACE_IF_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_REPLACE_IF_H_

namespace liuyunbin {

/*
 * replace_if
 */
template <typename ForwardIt, typename UnaryPredicate, typename T>
void replace_if(ForwardIt first, ForwardIt last, UnaryPredicate p,
                const T &new_value) {
  while (first != last) {
    if (p(*first))
      *first = new_value;
    ++first;
  }
}

} // namespace liuyunbin

#endif
