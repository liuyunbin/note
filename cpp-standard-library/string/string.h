#ifndef CPP_STANDARD_LIBRARY_STRING_H_
#define CPP_STANDARD_LIBRARY_STRING_H_

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <iterator>
#include <cstring>
#include <memory>

namespace liuyunbin {

template <typename, typename, typename>
class basic_string;

using string = basic_string<char, std::char_traits<char>, std::allocator<char>>;

/******************************************
 *                                        *
 *          basic_string                  *  just for char
 *                                        *
 ******************************************/

template <typename CharT, typename Traits = std::char_traits<CharT>,
          typename Allocator = std::allocator<CharT>>
class basic_string {
 public:
  using             trait_type = Traits;
  using         allocator_type = Allocator;
  using              size_type = typename Allocator::size_type;
  using        difference_type = typename Allocator::difference_type;
  using             value_type = CharT;
  using              reference = value_type&;
  using        const_reference = const value_type&;
  using               iterator = value_type*;
  using         const_iterator = const value_type*;
  using                pointer = value_type*;
  using          const_pointer = const value_type*;
  using       reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  static constexpr size_type npos = std::numeric_limits<size_type>::max();  // definition

 public:
  /*****************************************
   *                                       *
   *             construct                 *
   *                                       *
   *****************************************/

  basic_string() = default;

  basic_string(basic_string&& str) noexcept { swap(str); }

  template <typename InputIt>
  basic_string(InputIt first, InputIt last) {
    initialize_aux(first, last, std::is_integral<InputIt>());
  }

  basic_string(const basic_string& str)
      : basic_string(str.cbegin(), str.cend()) {}
  basic_string(const CharT* s, size_type count) : basic_string(s, s + count) {}
  basic_string(const CharT* s) : basic_string(s, s + std::strlen(s)) {}
  basic_string(std::initializer_list<CharT> ilist)
      : basic_string(ilist.begin(), ilist.end()) {}

  basic_string(const basic_string& str, size_type pos, size_type count = npos)
      : basic_string(
            str.begin() + pos,
            str.begin() + pos + std::min(count, str.size() - pos)) {}

  basic_string(size_type count, CharT ch) { fill_initialize(count, ch); }

  /*****************************************
   *                                       *
   *             destruct                  *
   *                                       *
   *****************************************/

  ~basic_string() {
    clear();
    if (start_ != nullptr) alloc.deallocate(start_, capacity());
  }

  /************************************************************
   *                                                          *
   *                      begin                               *
   *                     cbegin                               *
   *                                                          *
   *                        end                               *
   *                       cend                               *
   *                                                          *
   ************************************************************/

        iterator  begin()       { return start_; }
  const_iterator  begin() const { return start_; }
  const_iterator cbegin() const { return start_; }

        iterator  end()       { return finish_; }
  const_iterator  end() const { return finish_; }
  const_iterator cend() const { return finish_; }

  /************************************************************
   *                                                          *
   *                      rbegin                              *
   *                     crbegin                              *
   *                                                          *
   *                       rend                               *
   *                      crend                               *
   *                                                          *
   ************************************************************/

        reverse_iterator  rbegin()       { return static_cast<      reverse_iterator>(end()); }
  const_reverse_iterator  rbegin() const { return static_cast<const_reverse_iterator>(end()); }
  const_reverse_iterator crbegin() const { return static_cast<const_reverse_iterator>(cend()); }

        reverse_iterator  rend()       { return static_cast<      reverse_iterator>(begin()); }
  const_reverse_iterator  rend() const { return static_cast<const_reverse_iterator>(begin()); }
  const_reverse_iterator crend() const { return static_cast<const_reverse_iterator>(cbegin()); }

  /************************************************************
   *                                                          *
   *                       data                               *
   *                                                          *
   *                       c_str                              *
   *                                                          *
   ************************************************************/

  /* This data() and c_str() not end with '\0'                */
        pointer data()       { return start_; }
  const_pointer data() const { return start_; }
  const_pointer c_str() const { return data(); }

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
   *                   capacity                    *
   *                                               *
   *************************************************/

  bool empty() const { return cend() == cbegin(); }

  size_type size() const { return cend() - cbegin(); }

  size_type max_size() const { return npos; }

  size_type capacity() const { return end_of_storage_ - start_; }

  /************************************************************
   *                                                          *
   *                       swap                               *
   *                                                          *
   ************************************************************/

  void swap(basic_string& other) noexcept {
    std::swap(start_, other.start_);
    std::swap(finish_, other.finish_);
    std::swap(end_of_storage_, other.end_of_storage_);
  }

  /************************************************************
   *                                                          *
   *                  reserve                                 *
   *                                                          *
   *                  shrink_to_fit                           *
   *                                                          *
   *                  resize                                  *
   *                                                          *
   ************************************************************/
  // c++ 20
  void reserve(size_type new_cap) {
    if (new_cap > capacity()) reallocate(new_cap);
  }

  void shrink_to_fit() { reallocate(size()); }

  void resize(size_type new_size, CharT value) {
    if (size() < new_size)
      insert(end(), new_size - size(), value);
    else
      erase(cbegin() + new_size, cend());
  }

  void resize(size_type new_size) { resize(new_size, CharT()); }

  /******************************************************
   *                                                    *
   *                   insert                           *
   *                                                    *
   ******************************************************/

  iterator insert(const_iterator pos, const basic_string& other) {
    if (other.size() <= capacity() - size()) {
      auto new_pos = const_cast<iterator>(pos);
      const size_type count_after = cend() - pos;
      if (count_after >= other.size()) {
        std::uninitialized_copy(cend() - other.size(), cend(), end());
        std::copy_backward(pos, cend() - other.size(), end());
        std::copy(other.cbegin(), other.cend(), new_pos);
        finish_ += other.size();
      } else {
        auto it = std::uninitialized_copy(other.cbegin() + count_after,
                                                other.cend(), end());
        finish_ = std::uninitialized_copy(pos, cend(), it);
        std::copy_n(other.cbegin(), count_after, new_pos);
      }
      return new_pos;
    }
    const size_type new_size = size() + std::max(size(), other.size());
    basic_string temp;
    temp.start_ = alloc.allocate(new_size);
    auto new_pos = temp.start_ + (pos - cbegin());
    temp.finish_ = std::uninitialized_copy(cbegin(), pos, temp.start_);
    temp.finish_ = std::uninitialized_copy(other.cbegin(), other.cend(),
                                                 temp.finish_);
    temp.finish_ = std::uninitialized_copy(pos, cend(), temp.finish_);
    temp.end_of_storage_ = temp.start_ + new_size;
    swap(temp);
    return new_pos;
  }

  template <typename InputIt>
  iterator insert(const_iterator pos, InputIt first, InputIt last) {
    return insert(pos, basic_string(first, last));
  }

  iterator insert(const_iterator pos, std::initializer_list<CharT> ilist) {
    return insert(pos, basic_string(ilist));
  }

  iterator insert(const_iterator pos, size_type count, CharT value) {
    return insert(pos, basic_string(count, value));
  }

  iterator insert(const_iterator pos, CharT value) {
    return insert(pos, basic_string(1, value));
  }

  basic_string& insert(size_type index, const basic_string& str) {
    insert(cbegin() + index, str);
    return *this;
  }

  basic_string& insert(size_type index, const CharT* s, size_type count) {
    return insert(index, basic_string(s, count));
  }

  basic_string& insert(size_type index, const CharT* s) {
    return insert(index, basic_string(s));
  }

  basic_string& insert(size_type index, size_type count, CharT ch) {
    return insert(index, basic_string(count, ch));
  }

  basic_string& insert(size_type index, const basic_string& str,
                       size_type index_str, size_type count = npos) {
    return insert(index, basic_string(str, index_str, count));
  }

  /******************************************************
   *                                                    *
   *                   push_back                        *
   *                                                    *
   ******************************************************/

  void push_back(CharT value) { insert(cend(), value); }

  /**********************************************
   *                                            *
   *                    erase                   *
   *                                            *
   *                    pop_back                *
   *                                            *
   *                    clear                   *
   *                                            *
   **********************************************/

  iterator erase(const_iterator first, const_iterator last) {
    auto new_first = const_cast<iterator>(first);
    finish_ = std::copy(last, cend(), new_first);
    return new_first;
  }

  iterator erase(const_iterator p) { return erase(p, p + 1); }

  basic_string& erase(size_type index = 0, size_type count = npos) {
    erase(cbegin() + index, cbegin() + index + std::min(count, size() - index));
    return *this;
  }

  void pop_back() { erase(end() - 1); }

  void clear() { erase(cbegin(), cend()); }

  /****************************************
   *                                      *
   *               assign  =              *
   *                                      *
   ****************************************/

  basic_string& operator=(basic_string&& str) noexcept {
    if (this == &str) return *this;
    swap(str);
    return *this;
  }

  basic_string& operator=(const basic_string& str) {
    if (this == &str) return *this;
    return *this = basic_string(str);
  }

  template <typename InputIt>
  basic_string& assign(InputIt first, InputIt last) {
    return *this = basic_string(first, last);
  }

  basic_string& assign(const basic_string& str) { return *this = str; }
  
  basic_string& assign(const basic_string& str, size_type pos, size_type count = npos) {
    return *this = basic_string(str, pos, count);
  }

  basic_string& assign(size_type count, CharT ch) {
    return *this = basic_string(count, ch);
  }

  basic_string& assign(const CharT* s) { return *this = basic_string(s); }
  
  basic_string& assign(const CharT* s, size_type count) {
    return *this = basic_string(s, count);
  }

  basic_string& assign(std::initializer_list<CharT> ilist) {
    return *this = basic_string(ilist);
  }

  basic_string& assign(basic_string&& str) noexcept {
    return *this = std::move(str);
  }

  basic_string& operator=(const CharT* s) { return *this = basic_string(s); }
  basic_string& operator=(CharT ch) { return *this = basic_string(1, ch); }
  basic_string& operator=(std::initializer_list<CharT> ilist) {
    return *this = basic_string(ilist);
  }

  /****************************************
   *                                      *
   *             append    +=             *
   *                                      *
   ****************************************/

  basic_string& operator+=(const basic_string& str) {
    return insert(size(), str);
  }

  template <typename InputIt>
  basic_string& append(InputIt first, InputIt last) {
    return *this += basic_string(first, last);
  }

  basic_string& append(const basic_string& str) { return *this += str; }
  basic_string& append(size_type count, CharT ch) {
    return *this += base_string(count, ch);
  }

  basic_string& append(const CharT* s) { return *this += basic_string(s); }
  basic_string& append(const CharT* s, size_type count) {
    return *this += basic_string(s, count);
  }

  basic_string& append(std::initializer_list<CharT> ilist) {
    return *this += basic_string(ilist);
  }

  basic_string& append(const basic_string& st, size_type pos, size_type count = npos) {
    return *this += basic_string(st, pos, count);
  }
  basic_string& operator+=(const CharT* s) { return *this += basic_string(s); }
  basic_string& operator+=(CharT ch) { return *this += basic_string(1, ch); }
  basic_string& operator+=(std::initializer_list<CharT> ilist) {
    return *this += basic_string(ilist);
  }

  /**********************************
   *                                *
   *        replace                 *
   *                                *
   *********************************/

  basic_string& replace(const_iterator first, const_iterator last, const basic_string& str) {
    erase(first, last);
    return insert(first - cbegin(), str);
  }

  template <typename InputIt>
  basic_string& replace(const_iterator first, const_iterator last, InputIt first2, InputIt last2) {
    return replace(first, last, basic_string(first2, last2));
  }

  basic_string& replace(const_iterator first, const_iterator last, const CharT* s, size_type count) {
    return replace(first, last, basic_string(s, count));
  }

  basic_string& replace(const_iterator first, const_iterator last, const CharT* s) {
    return replace(first, last, basic_string(s));
  }

  basic_string& replace(const_iterator first, const_iterator last, size_type count, CharT ch) {
    return replace(first, last, basic_string(count, ch));
  }

  basic_string& replace(const_iterator first, const_iterator last, std::initializer_list<CharT> ilist) {
    return replace(first, last, basic_string(ilist));
  }

  basic_string& replace(size_type pos, size_type count, const basic_string& str) {
    erase(pos, count);
    return insert(pos, str);
  }

  basic_string& replace(size_type pos, size_type count, const basic_string& str,
                        size_type pos2, size_type count2 = npos) {
    return replace(pos, count, basic_string(str, pos2, count2));
  }

  basic_string& replace(size_type pos, size_type count, const CharT* s, size_type count2) {
    return replace(pos, count, basic_string(s, count2));
  }

  basic_string& replace(size_type pos, size_type count, const CharT* s) {
    return replace(pos, count, basic_string(s));
  }

  basic_string& replace(size_type pos, size_type count, size_type count2, CharT ch) {
    return replace(pos, count, basic_string(count2, ch));
  }

  /***************************************
   *                                     *
   *            compare                  *
   *                                     *
   ***************************************/

  int compare(const basic_string& str) const {
    size_type i = 0;
    while (i != size() && i != str.size() && at(i) == str[i]) ++i;
    if (i == size() && i == str.size()) return 0;
    if (i == size()) return -1;
    if (i == str.size()) return 1;
    return at(i) < str[i] ? -1 : 1;
  }

  int compare(size_type pos1, size_type count1, const basic_string& str) const {
    return basic_string(*this, pos1, count1).compare(str);
  }

  int compare(size_type pos1, size_type count1, const basic_string& str,
              size_type pos2, size_type count2 = npos) const {
    return basic_string(*this, pos1, count1).cpmpare(basic_string(str, pos2, count2));
  }

  int compare(const CharT* s) const { return compare(basic_string(s)); }

  int compare(size_type pos1, size_type count1, const CharT* s) const {
    return basic_string(*this, pos1, count1).compare(basic_string(s));
  }

  int compare(size_type pos1, size_type count1, const CharT* s, size_type count2) const {
    return basic_string(*this, pos1, count1).compare(basic_string(s, count2));
  }

  /**************************************************
   *                                                *
   *                    find                        *
   *                                                *
   **************************************************/

  size_type find(const basic_string& str, size_type pos = 0) const {
    auto it = std::search(cbegin() + pos, cend(), str.cbegin(), str.cend());
    return it == cend() ? npos : it - cbegin();
  }

  size_type find(const CharT* s, size_type pos, size_type count) const {
    return find(basic_string(s, count), pos);
  }

  size_type find(const CharT* s, size_type pos = 0) const {
    return find(basic_string(s), pos);
  }

  size_type find(CharT ch, size_type pos = 0) const {
    return find(basic_string(1, ch), pos);
  }

  /**************************************************
   *                                                *
   *                   rfind                        *
   *                                                *
   *************************************************/

  size_type rfind(const basic_string& str, size_type pos = npos) const {
    if (str.size() == 0) return std::min(pos, size());
    auto i = size() > pos ? pos + 1 : size();
    while (i-- != 0) {
      if (size() - i < str.size()) continue;
      if (std::equal(str.cbegin(), str.cend(), cbegin() + i)) return i;
    }
    return npos;
  }

  size_type rfind(const CharT* s, size_type pos, size_type count) const {
    return rfind(basic_string(s, count), pos);
  }

  size_type rfind(const CharT* s, size_type pos = npos) const {
    return rfind(basic_string(s), pos);
  }

  size_type rfind(CharT ch, size_type pos = npos) const {
    return rfind(basic_string(1, ch), pos);
  }

  /**************************************************
   *                                                *
   *               find_first_of                    *
   *                                                *
   **************************************************/

  size_type find_first_of(const basic_string& str, size_type pos = 0) const {
    auto it = std::find_first_of(cbegin() + pos, cend(), str.cbegin(),
                                       str.cend());
    return it != cend() ? it - cbegin() : npos;
  }

  size_type find_first_of(const CharT* s, size_type pos,
                          size_type count) const {
    return find_first_of(basic_string(s, count), pos);
  }

  size_type find_first_of(const CharT* s, size_type pos = 0) const {
    return find_first_of(basic_string(s), pos);
  }

  size_type find_first_of(CharT ch, size_type pos = 0) const {
    return find_first_of(basic_string(1, ch), pos);
  }

  /**************************************************
   *                                                *
   *               find_first_not_of                *
   *                                                *
   **************************************************/

  size_type find_first_not_of(const basic_string& str,
                              size_type pos = 0) const {
    while (pos != size()) {
      if (std::find(str.cbegin(), str.cend(), at(pos)) == str.cend())
        return pos;
      ++pos;
    }
    return npos;
  }

  size_type find_first_not_of(const CharT* s, size_type pos,
                              size_type count) const {
    return find_first_not_of(basic_string(s, count), pos);
  }

  size_type find_first_not_of(const CharT* s, size_type pos = 0) const {
    return find_first_not_of(basic_string(s), pos);
  }

  size_type find_first_not_of(CharT ch, size_type pos = 0) const {
    return find_first_not_of(basic_string(1, ch), pos);
  }

  /**************************************************
   *                                                *
   *               find_last_of                     *
   *                                                *
   **************************************************/

  size_type find_last_of(const basic_string& str, size_type pos = npos) const {
    for (pos = pos >= size() ? size() : pos + 1; pos-- != 0;) {
      if (std::find(str.cbegin(), str.cend(), at(pos)) != str.cend())
        return pos;
    }
    return npos;
  }

  size_type find_last_of(const CharT* s, size_type pos, size_type count) const {
    return find_last_of(basic_string(s, count), pos);
  }

  size_type find_last_of(const CharT* s, size_type pos = npos) const {
    return find_last_of(basic_string(s), pos);
  }

  size_type find_last_of(CharT ch, size_type pos = npos) const {
    return find_last_of(basic_string(1, ch), pos);
  }

  /**************************************************
   *                                                *
   *               find_last_not_of                 *
   *                                                *
   **************************************************/

  size_type find_last_not_of(const basic_string& str,
                             size_type pos = npos) const {
    for (pos = pos >= size() ? size() : pos + 1; pos-- != 0;) {
      if (std::find(str.cbegin(), str.cend(), at(pos)) == str.cend())
        return pos;
    }
    return npos;
  }

  size_type find_last_not_of(const CharT* s, size_type pos,
                             size_type count) const {
    return find_last_not_of(basic_string(s, count), pos);
  }

  size_type find_last_not_of(const CharT* s, size_type pos = npos) const {
    return find_last_not_of(basic_string(s), pos);
  }

  size_type find_last_not_of(CharT ch, size_type pos = npos) const {
    return find_last_not_of(basic_string(1, ch), pos);
  }

  /************************************************************
   *                                                          *
   *                    substr                                *
   *                    copy                                  *
   *                                                          *
   ************************************************************/

  basic_string substr(size_type pos = 0, size_type count = npos) const {
    return basic_string(*this, pos, count);
  }

  size_type copy(CharT* dest, size_type count, size_type pos = 0) const {
    auto num = std::min(count, size() - pos);
    std::copy_n(cbegin() + pos, num, dest);
    return num;
  }

 private:
  iterator          start_ = nullptr;
  iterator         finish_ = nullptr;
  iterator end_of_storage_ = nullptr;

  Allocator alloc;

  /**********************************************************************
   *                                                                    *
   *                      fill_initialize                               *
   *                                                                    *
   **********************************************************************/

  void fill_initialize(size_type n, CharT value) {
    start_ = alloc.allocate(n);
    finish_ = std::uninitialized_fill_n(start_, n, value);
    end_of_storage_ = finish_;
  }

  /**********************************************************************
   *                                                                    *
   *                      copy_initialize                               *
   *                                                                    *
   **********************************************************************/

  template <typename ForwardIt>
  void copy_initialize(ForwardIt first, ForwardIt last, std::forward_iterator_tag) {
             start_ = alloc.allocate(std::distance(first, last));
            finish_ = std::uninitialized_copy(first, last, start_);
    end_of_storage_ = finish_;
  }

  template <typename InputIt>
  void copy_initialize(InputIt first, InputIt last, std::input_iterator_tag) {
    while (first != last) {
      if (capacity() == size()) reallocate(size() == 0 ? 1 : 2 * size());
      Allocator::construct(finish_++, *first++);
    }
  }

  /**********************************************************************
   *                                                                    *
   *                      initialize_aux                                *
   *                                                                    *
   **********************************************************************/

  template <typename InputIt>
  void initialize_aux(InputIt first, InputIt last, std::true_type) {  // is int
    fill_initialize(first, last);
  }

  template <typename InputIt>
  void initialize_aux(InputIt first, InputIt last, std::false_type) {
    using category = typename std::iterator_traits<InputIt>::iterator_category;
    copy_initialize(first, last, category());
  }

  /***************************************************************************
   *                                                                         *
   *                      reallocate                                         *
   *                                                                         *
   ***************************************************************************/

  void reallocate(size_type new_cap) {
    basic_string temp;
    temp.start_ = alloc.allocate(new_cap);
    temp.finish_ = std::uninitialized_copy(cbegin(), cend(), temp.start_);
    temp.end_of_storage_ = temp.start_ + new_cap;
    swap(temp);
  }

};  // class basic_string

/***********************************************************
 *                                                         *
 *           Non-member functions                          *
 *                                                         *
 ***********************************************************/

/************************************************************
 *                                                          *
 *                         swap                             *
 *                                                          *
 ************************************************************/

template <typename CharT, typename Traits, typename Allocator>
void swap(basic_string<CharT, Traits, Allocator>& left,
          basic_string<CharT, Traits, Allocator>& right) {
  left.swap(right);
}

/************************************************************
 *                                                          *
 *                       getline >> <<                      *
 *                                                          *
 ************************************************************/

template <typename CharT, typename Traits, typename Allocator>
std::istream& getline(std::istream& in, basic_string<CharT, Traits, Allocator>& str, CharT delim = '\n') {
  CharT ch;
  str.clear();
  while ((ch = in.get()) != delim) str.push_back(ch);
  return in;
}

template <typename CharT, typename Traits, typename Allocator>
std::ostream& operator<<(std::ostream& os, const basic_string<CharT, Traits, Allocator>& str) {
  std::for_each(str.cbegin(), str.cend(), [&os](CharT ch) { os << ch; });
  return os;
}

template <typename CharT, typename Traits, typename Allocator>
std::istream& operator>>(std::istream& in, basic_string<CharT, Traits, Allocator>& str) {
  CharT ch;
  str.clear();
  if (!(in >> ch)) return in;
  str.push_back(ch);
  while (!std::isspace(ch = in.get())) str.push_back(ch);
  return in;
}

/************************************************************
 *                                                          *
 *                           ==                             *
 *                           !=                             *
 *                           <                              *
 *                           <=                             *
 *                           >                              *
 *                           >=                             *
 *                                                          *
 ************************************************************/

template <typename CharT, typename Traits, typename Allocator>
bool operator==(const basic_string<CharT, Traits, Allocator>& left,
                const basic_string<CharT, Traits, Allocator>& right) {
  return left.size() == right.size() && left.compare(right) == 0;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator!=(const basic_string<CharT, Traits, Allocator>& left,
                const basic_string<CharT, Traits, Allocator>& right) {
  return left.size() != right.size() || left.compare(right) != 0;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator<(const basic_string<CharT, Traits, Allocator>& left,
               const basic_string<CharT, Traits, Allocator>& right) {
  return left.compare(right) < 0;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator<=(const basic_string<CharT, Traits, Allocator>& left,
                const basic_string<CharT, Traits, Allocator>& right) {
  return left.compare(right) <= 0;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator>(const basic_string<CharT, Traits, Allocator>& left,
               const basic_string<CharT, Traits, Allocator>& right) {
  return left.compare(right) > 0;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator>=(const basic_string<CharT, Traits, Allocator>& left,
                const basic_string<CharT, Traits, Allocator>& right) {
  return left.compare(right) >= 0;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator==(const CharT* left,
                const basic_string<CharT, Traits, Allocator>& right) {
  return basic_string<CharT, Traits, Allocator>(left) == right;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator!=(const CharT* left,
                const basic_string<CharT, Traits, Allocator>& right) {
  return basic_string<CharT, Traits, Allocator>(left) != right;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator<(const CharT* left,
               const basic_string<CharT, Traits, Allocator>& right) {
  return basic_string<CharT, Traits, Allocator>(left) < right;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator<=(const CharT* left,
                const basic_string<CharT, Traits, Allocator>& right) {
  return basic_string<CharT, Traits, Allocator>(left) <= right;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator>(const CharT* left,
               const basic_string<CharT, Traits, Allocator>& right) {
  return basic_string<CharT, Traits, Allocator>(left) > right;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator>=(const CharT* left,
                const basic_string<CharT, Traits, Allocator>& right) {
  return basic_string<CharT, Traits, Allocator>(left) >= right;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator==(const basic_string<CharT, Traits, Allocator>& left,
                const CharT* right) {
  return left == basic_string<CharT, Traits, Allocator>(right);
}

template <typename CharT, typename Traits, typename Allocator>
bool operator!=(const basic_string<CharT, Traits, Allocator>& left,
                const CharT* right) {
  return left != basic_string<CharT, Traits, Allocator>(right);
}

template <typename CharT, typename Traits, typename Allocator>
bool operator<(const basic_string<CharT, Traits, Allocator>& left,
               const CharT* right) {
  return left < basic_string<CharT, Traits, Allocator>(right);
}

template <typename CharT, typename Traits, typename Allocator>
bool operator<=(const basic_string<CharT, Traits, Allocator>& left,
                const CharT* right) {
  return left <= basic_string<CharT, Traits, Allocator>(right);
}

template <typename CharT, typename Traits, typename Allocator>
bool operator>(const basic_string<CharT, Traits, Allocator>& left,
               const CharT* right) {
  return left > basic_string<CharT, Traits, Allocator>(right);
}

template <typename CharT, typename Traits, typename Allocator>
bool operator>=(const basic_string<CharT, Traits, Allocator>& left,
                const CharT* right) {
  return left >= basic_string<CharT, Traits, Allocator>(right);
}

/************************************************************
 *                                                          *
 *                            +                             *
 *                                                          *
 ************************************************************/

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator> operator+(
    const basic_string<CharT, Traits, Allocator>& left,
    const basic_string<CharT, Traits, Allocator>& right) {
  return basic_string<CharT, Traits, Allocator>(left) += right;
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator> operator+(
    CharT ch, const basic_string<CharT, Traits, Allocator>& right) {
  return basic_string<CharT, Traits, Allocator>(1, ch) += right;
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator> operator+(
    const CharT* left, const basic_string<CharT, Traits, Allocator>& right) {
  return basic_string<CharT, Traits, Allocator>(left) += right;
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator> operator+(
    const basic_string<CharT, Traits, Allocator>& left, CharT ch) {
  return basic_string<CharT, Traits, Allocator>(left) += ch;
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator> operator+(
    const basic_string<CharT, Traits, Allocator>& left, const CharT* right) {
  return basic_string<CharT, Traits, Allocator>(left) += right;
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator> operator+(
    basic_string<CharT, Traits, Allocator>&& left,
    basic_string<CharT, Traits, Allocator>&& right) {
  return std::move(left += right);
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator> operator+(
    const basic_string<CharT, Traits, Allocator>& left,
    basic_string<CharT, Traits, Allocator>&& right) {
  return std::move(right.insert(0, left));
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator> operator+(
    basic_string<CharT, Traits, Allocator>&& left,
    const basic_string<CharT, Traits, Allocator>& right) {
  return std::move(left += right);
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator> operator+(
    CharT ch, const basic_string<CharT, Traits, Allocator>&& right) {
  return std::move(right.insert(0, 1, ch));
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator> operator+(
    const CharT* left, const basic_string<CharT, Traits, Allocator>&& right) {
  return std::move(right.insert(0, left));
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator> operator+(
    const basic_string<CharT, Traits, Allocator>&& left, CharT ch) {
  return std::move(left += ch);
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator> operator+(
    const basic_string<CharT, Traits, Allocator>&& left, const CharT* right) {
  return std::move(left += right);
}

/**********************************************************
 *                                                        *
 *                   to_string                            *
 *                                                        *
 **********************************************************/

string to_string(int value) {
  char st[100];
  snprintf(st, sizeof(st), "%d", value);
  return st;
}

string to_string(long value) {
  char st[100];
  snprintf(st, sizeof(st), "%ld", value);
  return st;
}

string to_string(long long value) {
  char st[100];
  snprintf(st, sizeof(st), "%lld", value);
  return st;
}

string to_string(unsigned int value) {
  char st[100];
  snprintf(st, sizeof(st), "%u", value);
  return st;
}

string to_string(unsigned long value) {
  char st[100];
  snprintf(st, sizeof(st), "%lu", value);
  return st;
}

string to_string(unsigned long long value) {
  char st[100];
  snprintf(st, sizeof(st), "%llu", value);
  return st;
}

string to_string(float value) {
  char st[100];
  snprintf(st, sizeof(st), "%f", value);
  return st;
}

string to_string(double value) {
  char st[100];
  snprintf(st, sizeof(st), "%f", value);
  return st;
}

string to_string(long double value) {
  char st[100];
  snprintf(st, sizeof(st), "%Lf", value);
  return st;
}

/**********************************************************
 *                                                        *
 *                     stoi                               *
 *                     stol                               *
 *                     stoul                              *
 *                     stoll                              *
 *                     stoull                             *
 *                     stof                               *
 *                     stod                               *
 *                     stold                              *
 *                                                        *
 **********************************************************/

int stoi(const string& str, std::size_t* pos = nullptr, int base = 10) {
  char* ptr;
  int return_value = std::strtol(str.c_str(), &ptr, base);
  if (pos != nullptr) *pos = ptr - str.data();
  return return_value;
}

long stol(const string& str, std::size_t* pos = nullptr, int base = 10) {
  char* ptr;
  long return_value = std::strtol(str.c_str(), &ptr, base);
  if (pos != nullptr) *pos = ptr - str.data();
  return return_value;
}

long long stoll(const string& str, std::size_t* pos = nullptr, int base = 10) {
  char* ptr;
  long long return_value = std::strtoll(str.c_str(), &ptr, base);
  if (pos != nullptr) *pos = ptr - str.data();
  return return_value;
}

unsigned long stoul(const string& str, std::size_t* pos = nullptr,
                    int base = 10) {
  char* ptr;
  unsigned long return_value = std::strtoul(str.c_str(), &ptr, base);
  if (pos != nullptr) *pos = ptr - str.data();
  return return_value;
}

unsigned long long stoull(const string& str, std::size_t* pos = nullptr,
                          int base = 10) {
  char* ptr;
  unsigned long long return_value = std::strtoull(str.c_str(), &ptr, base);
  if (pos != nullptr) *pos = ptr - str.data();
  return return_value;
}

float stof(const string& str, std::size_t* pos = nullptr) {
  char* ptr;
  float return_value = std::strtof(str.c_str(), &ptr);
  if (pos != nullptr) *pos = ptr - str.data();
  return return_value;
}

double stod(const string& str, std::size_t* pos = nullptr) {
  char* ptr;
  double return_value = std::strtod(str.c_str(), &ptr);
  if (pos != nullptr) *pos = ptr - str.data();
  return return_value;
}

long double stold(const string& str, std::size_t* pos = nullptr) {
  char* ptr;
  long double return_value = std::strtold(str.c_str(), &ptr);
  if (pos != nullptr) *pos = ptr - str.data();
  return return_value;
}

}  // namespace liuyunbin

#endif
