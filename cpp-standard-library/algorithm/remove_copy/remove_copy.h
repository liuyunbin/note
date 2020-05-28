#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_REMOVE_COPY_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_REMOVE_COPY_H_

namespace liuyunbin {

/*
 * remove_copy
 */
template <typename InputIt, typename OutputIt, typename T>
OutputIt remove_copy(InputIt first, InputIt last, OutputIt d_first,
                     const T &value) {
  while (first != last) {
    if (*first == value)
      ++first;
    else
      *d_first++ = *first++;
  }
  return d_first;
}

} // namespace liuyunbin

#endif
