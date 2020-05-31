#ifndef CPP_STANDARD_LIBRARY_ITERATOR_MOVE_ITERATOR_H_
#define CPP_STANDARD_LIBRARY_ITERATOR_MOVE_ITERATOR_H_

#include <iterator>

namespace liuyunbin {

/******************************************************
 *                                                    *
 *                move_iterator                       *
 *                                                    *
 ******************************************************/

template <typename Iterator>
class move_iterator {
 public:
  using     iterator_type = Iterator;
  using difference_type = ptrdiff_t;
  using        value_type = typename std::iterator_traits<Iterator>::value_type;
  using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
  using         reference = value_type&&;
  using           pointer = Iterator;

  move_iterator() : current_() {}
  explicit move_iterator(Iterator current) : current_(current) {}
  template <typename U>
  move_iterator(const move_iterator<U> &other) : current_(other.current_) {}
  // 1. move_iterator<iterator> --> move_iterator<const_iterator>
  // 2. move_iterator<iterator> --> move_iterator<      iterator>

  template <typename U>
  move_iterator &operator=(const move_iterator<U> &other) {
    current_ = other.current_;
    return *this;
  }
  // 1. move_iterator<      iterator> = move_iterator<iterator>
  // 2. move_iterator<const_iterator> = move_iterator<iterator>

  Iterator base() const { return current_; }

  reference operator*() const { return static_cast<reference>(*current_); }

  pointer operator->() const { return current_; }

  move_iterator &operator++() {
    ++current_;
    return *this;
  }

  move_iterator operator++(int) {
    auto temp = *this;
    ++current_;
    return temp;
  }

  move_iterator &operator--() {
    --current_;
    return *this;
  }

  move_iterator operator--(int) {
    auto temp = *this;
    --current_;
    return temp;
  }

  move_iterator operator+(difference_type n) const {
    return move_iterator(current_ + n);
  }

  move_iterator &operator+=(difference_type n) {
    current_ += n;
    return *this;
  }

  move_iterator operator-(difference_type n) const {
    return move_iterator(current_ - n);
  }
  move_iterator &operator-=(difference_type n) {
    current_ -= n;
    return *this;
  }

  reference operator[](difference_type n) const {
    return std::move(current_[n]);
  }

 private:
  Iterator current_;
};

/****************************************
 *                                      *
 *     ==   !=   <    <=   >   >=       *
 *                                      *
 ****************************************/

template <typename Iterator_left, typename Iterator_right>
bool operator==(const move_iterator<Iterator_left>& left, const move_iterator<Iterator_right>& right) {
  return left.base() == right.base();
}

template <typename Iterator_left, typename Iterator_right>
bool operator!=(const move_iterator<Iterator_left>& left, const move_iterator<Iterator_right>& right) {
  return left.base() != right.base();
}

template <typename Iterator_left, typename Iterator_right>
bool operator<(const move_iterator<Iterator_left>& left, const move_iterator<Iterator_right>& right) {
  return left.base() < right.base();
}

template <typename Iterator_left, typename Iterator_right>
bool operator<=(const move_iterator<Iterator_left>& left, const move_iterator<Iterator_right>& right) {
  return left.base() <= right.base();
}

template <typename Iterator_left, typename Iterator_right>
bool operator>(const move_iterator<Iterator_left>& left, const move_iterator<Iterator_right>& right) {
  return left.base() > right.base();
}

template <typename Iterator_left, typename Iterator_right>
bool operator>=(const move_iterator<Iterator_left>& left, const move_iterator<Iterator_right>& right) {
  return left.base() >= right.base();
}

/************************************************
 *                                              *
 *           +                   -              *
 *                                              *
 ************************************************/

template <typename Iterator>
move_iterator<Iterator>
operator+(typename move_iterator<Iterator>::difference_type n,
          const move_iterator<Iterator> &it) {
  return it + n;
}

template <typename Iterator_left, typename Iterator_right>
auto operator-(const move_iterator<Iterator_left> &left,
               const move_iterator<Iterator_right> &right)
    -> decltype(left.base() - right.base()) {
  return left.base() - right.base();
}

/****************************************************
 *                                                  *
 *               make_move_iterator                 *
 *                                                  *
 ****************************************************/

template <typename Iterator>
move_iterator<Iterator> make_move_iterator(Iterator it) {
  return move_iterator<Iterator>(it);
}

}  // namespace liuyunbin

#endif
