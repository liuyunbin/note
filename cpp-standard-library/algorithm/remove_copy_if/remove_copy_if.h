#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_REMOVE_COPY_IF_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_REMOVE_COPY_IF_H_

namespace liuyunbin {

/*
 * remove_copy_if
 */
template <typename InputIt, typename OutputIt, typename UnaryPredicate>
OutputIt remove_copy_if(InputIt first, InputIt last, OutputIt d_first,
                        UnaryPredicate p) {
  while (first != last) {
    if (p(*first))
      ++first;
    else
      *d_first++ = *first++;
  }
  return d_first;
}

} // namespace liuyunbin

#endif
