#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_GENERATE_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_GENERATE_H_

namespace liuyunbin {

/*
 * generate
 */
template <typename ForwardIt, typename Predicate>
void generate(ForwardIt first, ForwardIt last, Predicate p) {
  while (first != last)
    *first++ = p();
}

} // namespace liuyunbin

#endif
