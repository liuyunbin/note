#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_COPY_IF_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_COPY_IF_H_

namespace liuyunbin {

/*
 * copy_if
 */
template <typename InputIt, typename OutputIt, typename UnaryPredicate>
OutputIt copy_if(InputIt first, InputIt last, OutputIt d_first,
                 UnaryPredicate op) {
  while (first != last) {
    if (op(*first))
      *d_first++ = *first;
    ++first;
  }
  return d_first;
}

} // namespace liuyunbin

#endif
