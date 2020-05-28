#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_SEARCH_N_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_SEARCH_N_H_

namespace liuyunbin {

/*
 * search_n
 */
template <typename ForwardIt, typename Size, typename T>
ForwardIt search_n(ForwardIt first, ForwardIt last, Size count,
                   const T &value) {

  for (; first != last; ++first) {
    if (!(*first == value))
      continue;
    auto temp = first;
    Size current_count = 0;
    while (true) {
      ++current_count;
      if (current_count == count)
        return temp;
      ++first;
      if (first == last)
        return last;
      if (*first == value)
        continue;
      break;
    }
  }
  return last;
}

template <typename ForwardIt, typename Size, typename T,
          typename BinaryPredicate>
ForwardIt search_n(ForwardIt first, ForwardIt last, Size count, const T &value,
                   BinaryPredicate p) {
  for (; first != last; ++first) {
    if (!p(*first, value))
      continue;
    auto temp = first;
    Size current_count = 0;
    while (true) {
      ++current_count;
      if (current_count == count)
        return temp;
      ++first;
      if (first == last)
        return last;
      if (p(*first, value))
        continue;
      break;
    }
  }
  return last;
}

} // namespace liuyunbin

#endif
