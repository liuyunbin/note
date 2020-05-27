#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_COPY_N_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_COPY_N_H_

namespace liuyunbin {

/*
 * copy_n
 */
template <typename InputIt, typename Size, typename OutputIt>
OutputIt copy_n(InputIt first, Size count, OutputIt result) {
  if (count > 0)
    for (Size i = 0; i < count; ++i)
      *result++ = *first++;
  return result;
}

} // namespace liuyunbin

#endif
