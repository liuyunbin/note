#ifndef CPP_STANDARD_LIBRARY_ALGORITHM_SEARCH_H_
#define CPP_STANDARD_LIBRARY_ALGORITHM_SEARCH_H_

namespace liuyunbin {

/*
 * search
 */
template <typename ForwardIt1, typename ForwardIt2>
ForwardIt1 search(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2,
                  ForwardIt2 last2) {
  while (true) {
    auto temp = first1;
    for (auto it = first2;; ++it, ++temp) {
      if (it == last2)
        return first1;
      if (temp == last1)
        return last1;
      if (*temp == *it)
        continue;
      break;
    }
    ++first1;
  }
}

template <typename ForwardIt1, typename ForwardIt2, typename BinaryPredicate>
ForwardIt1 search(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2,
                  ForwardIt2 last2, BinaryPredicate p) {
  while (true) {
    auto temp = first1;
    for (auto it = first2;; ++it, ++temp) {
      if (it == last2)
        return first1;
      if (temp == last1)
        return last1;
      if (p(*temp, *it))
        continue;
      break;
    }
    ++first1;
  }
}

} // namespace liuyunbin

#endif
