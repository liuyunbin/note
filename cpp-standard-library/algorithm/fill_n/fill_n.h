#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_FILL_N_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_FILL_N_H_

namespace liuyunbin {

/*
 * fill_n
 */
template <typename OutputIt, typename Size, typename T>
OutputIt fill_n(OutputIt first, Size n, const T &value) {
  while (n-- != 0)
    *first++ = value;
  return first;
}

} // namespace liuyunbin

#endif
