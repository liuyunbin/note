#ifndef CPP_STANDARD_LIBRARY_ARRAY_H_
#define CPP_STANDARD_LIBRARY_ARRAY_H_

#include <iostream>
#include <iterator>

namespace liuyunbin {

/***********************************************
 *                                             *
 *                    array                    *
 *                                             *
 ***********************************************/

template <typename T, std::size_t N>
struct array {
  using size_type              = std::size_t;
  using difference_type        = std::ptrdiff_t;
  using value_type             = T;
  using       reference        =       T&;
  using const_reference        = const T&;
  using       iterator         =       T*;
  using const_iterator         = const T*;
  using       pointer          =       T*;
  using const_pointer          = const T*;
  using       reverse_iterator = std::reverse_iterator<      iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  /************************************************************
   *                                                          *
   *                      begin                               *
   *                     cbegin                               *
   *                                                          *
   *                        end                               *
   *                       cend                               *
   *                                                          *
   ************************************************************/

  T _start_[N];

        iterator  begin()       { return _start_; }
  const_iterator  begin() const { return _start_; }
  const_iterator cbegin() const { return _start_; }

        iterator end()        { return _start_ + N; }
  const_iterator end()  const { return _start_ + N; }
  const_iterator cend() const { return _start_ + N; }

  /************************************************************
   *                                                          *
   *                      rbegin                              *
   *                     crbegin                              *
   *                                                          *
   *                       rend                               *
   *                      crend                               *
   *                                                          *
   ************************************************************/

        reverse_iterator  rbegin()       { return static_cast<      reverse_iterator>( end()); }
  const_reverse_iterator   regin() const { return static_cast<const_reverse_iterator>( end()); }
  const_reverse_iterator crbegin() const { return static_cast<const_reverse_iterator>(cend()); }

        reverse_iterator  rend()       { return static_cast<      reverse_iterator>( begin()); }
  const_reverse_iterator  rend() const { return static_cast<const_reverse_iterator>( begin()); }
  const_reverse_iterator crend() const { return static_cast<const_reverse_iterator>(cbegin()); }

  /************************************************************
   *                                                          *
   *                       data                               *
   *                                                          *
   ************************************************************/

        pointer data()       { return _start_; }
  const_pointer data() const { return _start_; }

  /************************************************************
   *                                                          *
   *                   []     at                              *
   *                                                          *
   *                 front   back                             *
   *                                                          *
   ************************************************************/

        reference at(size_type pos)       { return *(begin() + pos); }
  const_reference at(size_type pos) const { return *(begin() + pos); }

        reference operator[](size_type pos)       { return at(pos); }
  const_reference operator[](size_type pos) const { return at(pos); }

        reference front()       { return *begin(); }
  const_reference front() const { return *begin(); }

        reference back()       { return *(end() - 1); }
  const_reference back() const { return *(end() - 1); }

  /*************************************************
   *                                               *
   *                   empty                       *
   *                   size                        *
   *                   max_size                    *
   *                                               *
   *************************************************/

  bool         empty() const { return cend() == cbegin(); }

  size_type     size() const { return N; }

  size_type max_size() const { return N; }

  /************************************************************
   *                                                          *
   *                       swap                               *
   *                                                          *
   ************************************************************/

  void swap(array& other) noexcept {
    using std::swap;
    for (size_type i = 0; i != N; ++i)
      swap(_start_[i], other._start_[i]);
  }

  /************************************************************
   *                                                          *
   *                       fill                               *
   *                                                          *
   ************************************************************/

  void fill(const T& value) {
    for (size_type i = 0; i != N; ++i)
      _start_[i] = value;
  }

};  // class array

/***********************************************************
 *                                                         *
 *           Non-member functions                          *
 *                                                         *
 ***********************************************************/

/************************************************************
 *                                                          *
 *                  swap                                    *
 *                                                          *
 ************************************************************/

template <typename T, std::size_t N>
void swap(array<T, N>& left, array<T, N>& right) {
  left.swap(right);
}

/************************************************************
 *                                                          *
 *                 == != < <= > >=                          *
 *                                                          *
 ************************************************************/

template <typename T, std::size_t N>
bool operator==(const array<T, N>& left, const array<T, N>& right) {
  return left.size() == right.size() && std::equal(left.cbegin(), left.cend(), right.cbegin());
}

template <typename T, std::size_t N>
bool operator!=(const array<T, N>& left, const array<T, N>& right) {
  return left.size() != right.size() || !std::equal(left.cbegin(), left.cend(), right.cbegin());
}

template <typename T, std::size_t N>
bool operator<(const array<T, N>& left, const array<T, N>& right) {
  return std::lexicographical_compare(left.cbegin(), left.cend(), right.cbegin(), right.cend());
}

template <typename T, std::size_t N>
bool operator<=(const array<T, N>& left, const array<T, N>& right) {
  return !(right < left);
}

template <typename T, std::size_t N>
bool operator>(const array<T, N>& left, const array<T, N>& right) {
  return right < left;
}

template <typename T, std::size_t N>
bool operator>=(const array<T, N>& left, const array<T, N>& right) {
  return !(left < right);
}

}  // namespace liuyunbin

#endif
