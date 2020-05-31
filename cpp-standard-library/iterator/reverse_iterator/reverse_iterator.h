#ifndef CPP_STANDARD_LIBRARY_ITERATOR_REVERSE_ITERATOR_H_
#define CPP_STANDARD_LIBRARY_ITERATOR_REVERSE_ITERATOR_H_

#include <iterator>

namespace liuyunbin {

/***********************************************
 *                                             *
 *            reverse_iterstor                 *
 *                                             *
 ***********************************************/

template <typename Iterator>
class reverse_iterator {
 public:
  using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
  using        value_type = typename std::iterator_traits<Iterator>::value_type;
  using   difference_type = typename std::iterator_traits<Iterator>::difference_type;
  using           pointer = typename std::iterator_traits<Iterator>::pointer;
  using         reference = typename std::iterator_traits<Iterator>::reference;
  using     iterator_type = Iterator;

  reverse_iterator() : current_() {}
  explicit reverse_iterator(Iterator current) : current_(current) {}
  template <typename U>
  reverse_iterator(const reverse_iterator<U> &other) : current_(other.base()) {}
  // 1. reverse_iterator<iterator> --> reverse_iterator<const_iterator>
  // 2. reverse_iterator<iterator> --> reverse_iterator<      iterator>

  Iterator base() const { return current_; }

  reference operator*() const {
    Iterator temp = current_;
    return *--temp;
  }

  pointer operator->() const { return &(operator*()); }

  reverse_iterator &operator++() {
    --current_;
    return *this;
  }

  reverse_iterator operator++(int) {
    auto temp = *this;
    --current_;
    return temp;
  }

  reverse_iterator &operator--() {
    ++current_;
    return *this;
  }

  reverse_iterator operator--(int) {
    auto temp = *this;
    ++current_;
    return temp;
  }

  reverse_iterator operator+(difference_type n) const {
    return reverse_iterator(current_ - n);
  }

  reverse_iterator &operator+=(difference_type n) {
    current_ -= n;
    return *this;
  }

  reverse_iterator operator-(difference_type n) const {
    return reverse_iterator(current_ + n);
  }

  reverse_iterator &operator-=(difference_type n) {
    current_ += n;
    return *this;
  }

  reference operator[](difference_type n) const { return *(*this + n); }

  template <typename U>
  reverse_iterator &operator=(const reverse_iterator<U> &other) {
    current_ = other.base();
    return *this;
  }
  // 1. reverse_iterator<      iterator> = reverse_iterator<iterator>
  // 2. reverse_iterator<const_iterator> = reverse_iterator<iterator>

 private:
  Iterator current_;
};

/****************************************
 *                                      *
 *     ==   !=   <    <=   >   >=       *
 *                                      *
 ****************************************/

template <typename Iterator_left, typename Iterator_right>
bool operator==(const reverse_iterator<Iterator_left>& left, const reverse_iterator<Iterator_right>& right) {
  return left.base() == right.base();
}

template <typename Iterator_left, typename Iterator_right>
bool operator!=(const reverse_iterator<Iterator_left>& left, const reverse_iterator<Iterator_right>& right) {
  return left.base() != right.base();
}

template <typename Iterator_left, typename Iterator_right>
bool operator<(const reverse_iterator<Iterator_left>& left, const reverse_iterator<Iterator_right>& right) {
  return left.base() < right.base();
}

template <typename Iterator_left, typename Iterator_right>
bool operator<=(const reverse_iterator<Iterator_left>& left, const reverse_iterator<Iterator_right>& right) {
  return left.base() <= right.base();
}

template <typename Iterator_left, typename Iterator_right>
bool operator>(const reverse_iterator<Iterator_left>& left, const reverse_iterator<Iterator_right>& right) {
  return left.base() > right.base();
}

template <typename Iterator_left, typename Iterator_right>
bool operator>=(const reverse_iterator<Iterator_left>& left, const reverse_iterator<Iterator_right>& right) {
  return left.base() >= right.base();
}

/************************************************
 *                                              *
 *           +                   -              *
 *                                              *
 ************************************************/

template <typename Iterator>
reverse_iterator<Iterator> operator+(
    typename reverse_iterator<Iterator>::difference_type n,
    const reverse_iterator<Iterator>& it) {
  return it + n;
}

template <typename Iterator_left, typename Iterator_right>
auto operator-(const reverse_iterator<Iterator_left>& left,
               const reverse_iterator<Iterator_right>& right)
    -> decltype(left.base() - right.base()) {
  return left.base() - right.base();
}

/****************************************************
 *                                                  *
 *             make_reverse_iterator                *
 *                                                  *
 ****************************************************/

template <typename Iterator>
reverse_iterator<Iterator> make_reverse_iterator(Iterator it) {
  return reverse_iterator<Iterator>(it);
}

}  // namespace liuyunbin

#endif
