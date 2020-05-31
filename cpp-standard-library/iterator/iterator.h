#ifndef CPP_STANDARD_LIBRARY_ITERATOR_H_
#define CPP_STANDARD_LIBRARY_ITERATOR_H_

#include <iterator>

namespace liuyunbin {

/*
 *  表示迭代器类型的结构体
 */

struct         input_iterator_tag {};
struct        output_iterator_tag {};
struct       forward_iterator_tag : public         input_iterator_tag {};
struct bidirectional_iterator_tag : public       forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

/*******************************************
 *                                         *
 *           iterator_traits               *
 *                                         *
 *******************************************/

template <typename Iterator>
struct iterator_traits {
  using   difference_type = typename Iterator::difference_type;
  using        value_type = typename Iterator::value_type;
  using           pointer = typename Iterator::pointer;
  using         reference = typename Iterator::reference;
  using iterator_category = typename Iterator::iterator_category;
};

// partial specialization
template <typename T>
struct iterator_traits<T*> {
  using   difference_type = std::ptrdiff_t;
  using        value_type = T;
  using           pointer = T*;
  using         reference = T&;
  using iterator_category = random_access_iterator_tag;
};

template <typename T>
struct iterator_traits<const T*> {
  using   difference_type = std::ptrdiff_t;
  using        value_type = T;
  using           pointer = const T*;
  using         reference = const T&;
  using iterator_category = random_access_iterator_tag;
};

/********************************************
 *                                          *
 *           iterator_category              *
 *                                          *
 *            difference_type               *
 *                                          *
 *                 value_type               *
 *                                          *
 ********************************************/

template <typename Iterator>
typename std::iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&) {
  using category = typename std::iterator_traits<Iterator>::iterator_category;
  return category();
}

template <typename Iterator>
typename std::iterator_traits<Iterator>::difference_type* 
difference_type(const Iterator&) {
  using difference = typename std::iterator_traits<Iterator>::difference_type;
  return static_cast<difference*>(0);
}

template <typename Iterator>
typename std::iterator_traits<Iterator>::value_type* 
value_type(const Iterator&) {
  using value = typename std::iterator_traits<Iterator>::value_type;
  return static_cast<value*>(0);
}

/*******************************************
 *                                         *
 *               begin                     *
 *              cbegin                     *
 *                                         *
 *******************************************/

template <typename T, std::size_t N>
constexpr T* begin(T (&array)[N]) {
  return array;
}

template <typename C>
constexpr auto begin(C& c) -> decltype(c.begin()) {
  return c.begin();
}

template <typename C>
constexpr auto begin(const C& c) -> decltype(c.begin()) {
  return c.begin();
}

template <typename C>
constexpr auto cbegin(const C& c) -> decltype(begin(c)) {
  return begin(c);
}

/*******************************************
 *                                         *
 *               end                       *
 *              cend                       *
 *                                         *
 *******************************************/

template <typename T, std::size_t N>
constexpr T* end(T (&array)[N]) {
  return array + N;
}

template <typename C>
constexpr auto end(C& c) -> decltype(c.end()) {
  return c.end();
}

template <typename C>
constexpr auto end(const C& c) -> decltype(c.end()) {
  return c.end();
}

template <typename C>
constexpr auto cend(const C& c) -> decltype(end(c)) {
  return end(c);
}

/*******************************************
 *                                         *
 *               rbegin                    *
 *              crbegin                    *
 *                                         *
 *******************************************/

template <typename T, std::size_t N>
constexpr std::reverse_iterator<T*> rbegin(T (&array)[N]) {
  return liuyunbin::make_reverse_iterator(array + N);
}

template <typename C>
constexpr auto rbegin(C& c) -> decltype(c.rbegin()) {
  return c.rbegin();
}

template <typename C>
constexpr auto rbegin(const C& c) -> decltype(c.rbegin()) {
  return c.rbegin();
}

template <typename C>
constexpr auto crbegin(const C& c) -> decltype(rbegin(c)) {
  return rbegin(c);
}

/*******************************************
 *                                         *
 *               rend                      *
 *              crend                      *
 *                                         *
 *******************************************/

template <typename T, std::size_t N>
constexpr std::reverse_iterator<T*> rend(T (&array)[N]) {
  return liuyunbin::make_reverse_iterator(array);
}

template <typename C>
constexpr auto rend(C& c) -> decltype(c.rend()) {
  return c.rend();
}

template <typename C>
constexpr auto rend(const C& c) -> decltype(c.rend()) {
  return c.rend();
}

template <typename C>
constexpr auto crend(const C& c) -> decltype(rend(c)) {
  return rend(c);
}

/*********************************************
 *                                           *
 *                 size                      *
 *                                           *
 *********************************************/

template <typename T, std::size_t N>
constexpr std::size_t size(T (&array)[N]) {
  return N;
}

template <typename C>
constexpr auto size(const C& c) -> decltype(c.size()) {
  return c.size();
}

/*********************************************
 *                                           *
 *                 empty                     *
 *                                           *
 *********************************************/

template <typename T, std::size_t N>
constexpr bool empty(T (&array)[N]) {
  return false;
}

template <typename C>
constexpr auto empty(const C& c) -> decltype(c.empty()) {
  return c.empty();
}

/*********************************************
 *                                           *
 *                 data                      *
 *                                           *
 *********************************************/

template <typename T, std::size_t N>
constexpr T* data(T (&array)[N]) {
  return array;
}

template <typename C>
constexpr auto data(const C& c) -> decltype(c.data()) {
  return c.data();
}

template <typename C>
constexpr auto data(C& c) -> decltype(c.data()) {
  return c.data();
}

}  // namespace liuyunbin

#endif
