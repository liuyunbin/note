#ifndef CPP_STANDARD_LIBRARY_ITERATOR_ISTREAM_ITERATOR_H_
#define CPP_STANDARD_LIBRARY_ITERATOR_ISTREAM_ITERATOR_H_

#include <iostream>
#include <iterator>

namespace liuyunbin {

/****************************************************
 *                                                  *
 *              istream_iterator                    * just for char
 *                                                  *
 ****************************************************/

template <typename T, typename CharT = char,
          typename Traits = std::char_traits<CharT>,
          typename Distance = std::ptrdiff_t>
class istream_iterator {
 public:
  using iterator_category = std::input_iterator_tag;
  using        value_type = T;
  using   difference_type = Distance;
  using           pointer = const T*;
  using         reference = const T&;

  using    char_type = CharT;
  using  traits_type = Traits;
  using istream_type = std::basic_istream<CharT, Traits>;

  constexpr istream_iterator() : stream_(&std::cin), end_marker_(false) {}
  istream_iterator(istream_type& stream) : stream_(&stream), end_marker_(true) {
    read();
  }
  istream_iterator(const istream_iterator& other) = default;

  const T& operator* () const { return         value_; }
  const T* operator->() const { return &(operator*()); }

  istream_iterator& operator++() {
    read();
    return *this;
  }
  istream_iterator operator++(int) {
    auto temp = *this;
    read();
    return temp;
  }

  bool operator==(const istream_iterator& right) {
    if (end_marker_ != right.end_marker_) return false;
    if (end_marker_ == false) return true;
    return stream_ == right.stream_;
  }

  bool operator!=(const istream_iterator& right) { return !(*this == right); }

 private:
  istream_type* stream_;
  T value_;
  bool end_marker_;

  void read() {
    end_marker_ = *stream_ ? true : false;
    if (end_marker_) *stream_ >> value_;
    end_marker_ = *stream_ ? true : false;
  }
};

}  // namespace liuyunbin

#endif
