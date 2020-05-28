#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_REPLACE_COPY_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_REPLACE_COPY_H_

namespace liuyunbin {

/*
 * relace_copy
 */
template <typename InputIt, typename OutputIt, typename T>
OutputIt replace_copy(InputIt first, InputIt last, OutputIt d_first,
                      const T &old_value, const T &new_value) {
  while (first != last) {
    *d_first++ = *first == old_value ? new_value : *first;
    ++first;
  }
  return d_first;
}

} // namespace liuyunbin

#endif
