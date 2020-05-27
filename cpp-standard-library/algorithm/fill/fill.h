#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_FILL_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_FILL_H_

namespace liuyunbin {

/*
 * fill
 */
template <typename ForwardIt, typename T>
void fill(ForwardIt first, ForwardIt last, const T &value) {
  while (first != last)
    *first++ = value;
}

} // namespace liuyunbin

#endif
