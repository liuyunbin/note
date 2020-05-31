#ifndef CPP_STANDARD_LIBRARY_ITERATOR_OSTREAM_ITERATOR_H_
#define CPP_STANDARD_LIBRARY_ITERATOR_OSTREAM_ITERATOR_H_

#include <iostream>
#include <iterator>

namespace liuyunbin {

/****************************************************
 *                                                  *
 *              ostream_iterator                    * just for char
 *                                                  *
 ****************************************************/

template <typename T, typename CharT = char, typename Traits = std::char_traits<CharT>>
class ostream_iterator {
 public:
  using iterator_category = std::output_iterator_tag;
  using        value_type = void;
  using   difference_type = void;
  using           pointer = void;
  using         reference = void;

  using    char_type = CharT;
  using  traits_type = Traits;
  using ostream_type = std::basic_ostream<CharT, Traits>;

  ostream_iterator(ostream_type &stream) : stream_(&stream), delim_(nullptr) {}
  ostream_iterator(ostream_type &stream, const char *delim)
      : stream_(&stream), delim_(delim) {}
  ostream_iterator(const ostream_iterator& other) = default;

  ostream_iterator& operator=(const T& value) {
    *stream_ << value;
    if (delim_ != nullptr) *stream_ << delim_;
    return *this;
  }

  ostream_iterator &operator*() { return *this; }
  ostream_iterator &operator++() { return *this; }
  ostream_iterator &operator++(int) { return *this; }

private:
  ostream_type* stream_;
  const CharT* delim_;
};

}  // namespace liuyunbin

#endif
