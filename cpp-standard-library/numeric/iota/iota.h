#ifndef CPP_STANDARD_LIBRARY_NUMERIC_IOTA_H_
#define CPP_STANDARD_LIBRARY_NUMERIC_IOTA_H_

namespace liuyunbin {

/*
 * iota()
 */
template <typename ForwardIt, typename T>
void iota(ForwardIt first, ForwardIt last, T value) {
  while (first != last)
    *first++ = value++;
}

} // namespace liuyunbin

#endif
