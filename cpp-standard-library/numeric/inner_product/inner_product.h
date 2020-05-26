#ifndef CPP_STANDARD_LIBRARY_NUMERIC_INNER_PRODUCT_H_
#define CPP_STANDARD_LIBRARY_NUMERIC_INNER_PRODUCT_H_

#include <utility>

namespace liuyunbin {

/*
 * inner_product()
 */
template <typename InputIt1, typename InputIt2, typename T>
T inner_product(InputIt1 first1, InputIt1 last1, InputIt2 first2, T init) {
  while (first1 != last1)
    init = std::move(init) + *first1++ * *first2++;
  return init;
}

template <typename InputIt1, typename InputIt2, typename T,
          typename BinaryOperation1, typename BinaryOperation2>
T inner_product(InputIt1 first1, InputIt1 last1, InputIt2 first2, T init,
                BinaryOperation1 op1, BinaryOperation2 op2) {
  while (first1 != last1)
    init = op1(std::move(init), op2(*first1++, *first2++));
  return init;
}

} // namespace liuyunbin

#endif
