#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_FOR_EACH_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_FOR_EACH_H_

namespace liuyunbin {

/*
 * for_each
 */
template <typename InputIt, typename UnaryPredicate>
UnaryPredicate for_each(InputIt first, InputIt last, UnaryPredicate f) {
  while (first != last)
    f(*first++);
  return f;
}

} // namespace liuyunbin

#endif
