#ifndef CPP_STANDARD_LIBRARY_ITERATOR_H_
#define CPP_STANDARD_LIBRARY_ITERATOR_H_

#include <iterator>
#include <iostream>

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

/***********************************
 *                                 *
 *           advance               *
 *                                 *
 ***********************************/

namespace detail {

template <typename InputIt, typename Distance>
void __advance(InputIt& it, Distance n, std::input_iterator_tag) {
  while (n-- != 0) ++it;
}

template <typename BidirectionalIt, typename Distance>
void __advance(BidirectionalIt& it, Distance n, std::bidirectional_iterator_tag) {
  if (n == 0) return;
  if (n > 0)
    while (n-- > 0) ++it;
  else
    while (n++ < 0) --it;
}

template <typename RandomAccessIt, typename Distance>
void __advance(RandomAccessIt& it, Distance n, std::random_access_iterator_tag) {
  it += n;
}

}  // namespace detail

template <typename InputIt, typename Distance>
void advance(InputIt& it, Distance n) {
  detail::__advance(
      it, n, typename std::iterator_traits<InputIt>::iterator_category());
}

/**************************************
 *                                    *
 *         back_insert_iterator       *
 *                                    *
 *         back_inserter              *
 *                                    *
 **************************************/

template <typename Container>
class back_insert_iterator {
 public:
  using        value_type = void;
  using   difference_type = void;
  using           pointer = void;
  using         reference = void;
  using iterator_category = std::output_iterator_tag;

  using container_type = Container;

  explicit back_insert_iterator(Container& container)
      : container_(&container) {}

  back_insert_iterator& operator=(const typename Container::value_type& value) {
    container_->push_back(value);
    return *this;
  }

  back_insert_iterator& operator=(typename Container::value_type&& value) {
    container_->push_back(std::move(value));
    return *this;
  }

  back_insert_iterator& operator* ()    { return *this; }
  back_insert_iterator& operator++()    { return *this; }
  back_insert_iterator& operator++(int) { return *this; }

 private:
  Container* container_;
};

template <typename Container>
back_insert_iterator<Container> back_inserter(Container& x) {
  return back_insert_iterator<Container>(x);
}

/***********************************
 *                                 *
 *           distance              *
 *                                 *
 ***********************************/

namespace detail {

template <typename InputIt>
typename std::iterator_traits<InputIt>::difference_type
__distance(InputIt first, InputIt last, std::input_iterator_tag) {
  typename std::iterator_traits<InputIt>::difference_type n = 0;
  while (first != last) {
    ++n;
    ++first;
  }
  return n;
}

template <typename RandomAccessIt, typename Distance>
typename std::iterator_traits<RandomAccessIt>::difference_type
__distance(RandomAccessIt first, RandomAccessIt last,
           std::random_access_iterator_tag) {
  return last - first;
}

}  // namespace detail

template <typename InputIt>
typename std::iterator_traits<InputIt>::difference_type
distance(InputIt first, InputIt last) {
  return detail::__distance(
      first, last, typename std::iterator_traits<InputIt>::iterator_category());
}

/**************************************
 *                                    *
 *        front_insert_iterator       *
 *                                    *
 *        front_inserter              *
 *                                    *
 **************************************/

template <typename Container>
class front_insert_iterator {
 public:
  using        value_type = void;
  using   difference_type = void;
  using           pointer = void;
  using         reference = void;
  using iterator_category = std::output_iterator_tag;

  using container_type = Container;

  explicit front_insert_iterator(Container& container)
      : container_(&container) {}

  front_insert_iterator& operator=(
      const typename Container::value_type& value) {
    container_->push_front(value);
    return *this;
  }

  front_insert_iterator& operator=(typename Container::value_type&& value) {
    container_->push_front(std::move(value));
    return *this;
  }

  front_insert_iterator& operator* ()    { return *this; }
  front_insert_iterator& operator++()    { return *this; }
  front_insert_iterator& operator++(int) { return *this; }

 private:
  Container* container_;
};

template <typename Container>
front_insert_iterator<Container> front_inserter(Container& x) {
  return front_insert_iterator<Container>(x);
}

/**************************************
 *                                    *
 *           insert_iterator          *
 *                                    *
 *           inserter                 *
 *                                    *
 **************************************/

template <typename Container>
class insert_iterator {
 private:
  using iterator = typename Container::iterator;

 public:
  using        value_type = void;
  using   difference_type = void;
  using           pointer = void;
  using         reference = void;
  using iterator_category = std::output_iterator_tag;

  using    container_type = Container;

  explicit insert_iterator(Container& container, iterator iter)
      : container_(&container), iter_(iter) {}

  insert_iterator& operator=(const typename Container::value_type& value) {
    iter_ = container_->insert(iter_, value);
    ++iter_;
    return *this;
  }

  insert_iterator& operator=(typename Container::value_type&& value) {
    iter_ = container_->insert(iter_, std::move(value));
    ++iter_;
    return *this;
  }

  insert_iterator& operator* ()    { return *this; }
  insert_iterator& operator++()    { return *this; }
  insert_iterator& operator++(int) { return *this; }

 private:
  Container* container_;
  iterator iter_;
};

template <typename Container, typename Iterator>
insert_iterator<Container> inserter(Container& x, Iterator it) {
  using iterator = typename Container::iterator;
  return insert_iterator<Container>(x, iterator(it));
}

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

/******************************************************
 *                                                    *
 *                move_iterator                       *
 *                                                    *
 ******************************************************/

template <typename Iterator>
class move_iterator {
 public:
  using     iterator_type = Iterator;
  using difference_type =
      typename std::iterator_traits<Iterator>::difference_type;
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

/*******************************************
 *                                         *
 *                next                     *
 *                                         *
 *******************************************/

template <typename InputIt>
InputIt next(
    InputIt it,
    typename std::iterator_traits<InputIt>::difference_type n = 1) {
  std::advance(it, n);
  return it;
}

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

/*******************************************
 *                                         *
 *                prev                     *
 *                                         *
 *******************************************/

template <typename BidirectionalIt>
BidirectionalIt prev(
    BidirectionalIt it,
    typename std::iterator_traits<BidirectionalIt>::difference_type n =
        1) {
  std::advance(it, -n);
  return it;
}

}  // namespace liuyunbin

#endif
