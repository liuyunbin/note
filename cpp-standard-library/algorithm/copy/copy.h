#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_COPY_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_COPY_H_

namespace liuyunbin {

/*
 * copy
 */
template <class InputIt, class OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt d_first) {
  while (first != last)
    *d_first++ = *first++;
  return d_first;
}

} // namespace liuyunbin

#endif
