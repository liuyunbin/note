#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_GENERATE_N_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_GENERATE_N_H_

namespace liuyunbin {

/*
 * generate_n
 */
template <typename OutputIt, typename Size, typename Predicate>
OutputIt generate_n(OutputIt first, Size count, Predicate p) {
  while (count-- != 0)
    *first++ = p();
  return first;
}

} // namespace liuyunbin

#endif
