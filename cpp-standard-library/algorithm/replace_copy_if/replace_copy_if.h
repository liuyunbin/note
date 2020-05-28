#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_REPLACE_COPY_IF_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_REPLACE_COPY_IF_H_

namespace liuyunbin {

/*
 * relace_copy_if
 */
template <typename InputIt, typename OutputIt, typename UnaryPredicate,
          typename T>
OutputIt replace_copy_if(InputIt first, InputIt last, OutputIt d_first,
                         UnaryPredicate p, const T &new_value) {
  while (first != last) {
    *d_first++ = p(*first) ? new_value : *first;
    ++first;
  }
  return d_first;
}

} // namespace liuyunbin

#endif
