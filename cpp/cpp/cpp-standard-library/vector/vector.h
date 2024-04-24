#ifndef CPP_STANDARD_LIBRARY_VECTOR_H_
#define CPP_STANDARD_LIBRARY_VECTOR_H_

#include <algorithm>
#include <iostream>
#include <iterator>
#include <initializer_list>
#include <limits>
#include <memory>

namespace liuyunbin {

/***********************************************
 *                                             *
 *                    vector                   *
 *                                             *
 ***********************************************/

template <typename T, typename Allocator = std::allocator<T>>
class vector {
 public:
  using         allocator_type = Allocator;
  using              size_type = std::size_t;
  using        difference_type = std::ptrdiff_t;
  using             value_type = T;
  using              reference = T&;
  using        const_reference = const T&;
  using               iterator = T*;
  using         const_iterator = const T*;
  using                pointer = T*;
  using          const_pointer = const T*;
  using       reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

 public:
  /************************************************************
   *                                                          *
   *                       construct                          *
   *                                                          *
   ************************************************************/

  vector() : start_(nullptr), finish_(nullptr), end_of_storage_(nullptr) {}

  vector(vector&& other) noexcept : vector() { swap(other); }

  vector(size_type count, const T& value) { fill_initialize(count, value); }
  explicit vector(size_type count) : vector(count, T()) {}

  template <typename InputIt>
  vector(InputIt first, InputIt last) : vector() {
    initialize_aux(first, last, std::is_integral<InputIt>());
  }
  vector(const vector& other) : vector(other.cbegin(), other.cend()) {}
  vector(std::initializer_list<T> ilist) : vector(ilist.begin(), ilist.end()) {}

  /************************************************************
   *                                                          *
   *                       destruct                           *
   *                                                          *
   ************************************************************/

  ~vector() {
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
   ************************************************************/

  /* This data() not end with '\0'                */
        pointer data()       { return start_; }
  const_pointer data() const { return start_; }

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

  size_type max_size() const { return std::numeric_limits<size_type>::max(); }

  size_type capacity() const { return end_of_storage_ - start_; }

  /************************************************************
   *                                                          *
   *                       swap                               *
   *                                                          *
   ************************************************************/

  void swap(vector& other) noexcept {
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

  void resize(size_type new_size, const T& value) {
    if (size() < new_size)
      insert(end(), new_size - size(), value);
    else
      erase(cbegin() + new_size, cend());
  }

  void resize(size_type new_size) { resize(new_size, T()); }

  /******************************************************
   *                                                    *
   *                   insert                           *
   *                                                    *
   *                   emplace                          *
   *                                                    *
   ******************************************************/

  iterator insert(const_iterator pos, const vector& other) {
    if (other.size() <= capacity() - size()) {
      auto new_pos = const_cast<iterator>(pos);
      const size_type count_after = cend() - pos;
      if (count_after >= other.size()) {
        std::uninitialized_copy(cend() - other.size(), cend(), end());
        std::copy_backward(pos, cend() - other.size(), end());
        std::copy(other.begin(), other.end(), new_pos);
        finish_ += other.size();
      } else {
        auto it = std::uninitialized_copy(other.begin() + count_after,
                                                other.end(), end());
        finish_ = std::uninitialized_copy(pos, cend(), it);
        std::copy_n(other.cbegin(), count_after, new_pos);
      }
      return new_pos;
    }
    size_type new_size = size() + std::max(size(), other.size());
    vector temp;
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
    return insert(pos, vector(first, last));
  }

  iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
    return insert(pos, vector(ilist));
  }

  iterator insert(const_iterator pos, size_type count, const T& value) {
    return insert(pos, vector(count, value));
  }

  iterator insert(const_iterator pos, const T& value) {
    return insert(pos, vector(1, value));
  }

  iterator insert(const_iterator pos, T&& value) {
    if (capacity() > size()) {
      auto new_pos = const_cast<iterator>(pos);
      alloc.construct(finish_++, value);
      std::copy_backward(pos, cend() - 1, end());
      *new_pos = std::move(value);
      return new_pos;
    }
    const size_type new_size = size() == 0 ? 1 : 2 * size();
    vector temp;
    temp.start_ = alloc.allocate(new_size);
    auto new_pos = temp.start_ + (pos - cbegin());
    temp.finish_ = std::uninitialized_copy(cbegin(), pos, temp.start_);
    alloc.construct(temp.finish_++, std::move(value));
    temp.finish_ = std::uninitialized_copy(pos, cend(), temp.finish_);
    temp.end_of_storage_ = temp.start_ + new_size;
    swap(temp);
    return new_pos;
  }

  template <typename... Args>
  iterator emplace(const_iterator pos, Args&&... args) {
    return insert(pos, T(std::forward<Args>(args)...));
  }

  /******************************************************
   *                                                    *
   *                   push_back                        *
   *                                                    *
   *                emplace_back                        *
   *                                                    *
   ******************************************************/

  void push_back(const T& value) { insert(cend(), value); }
  void push_back(T&& value) { insert(cend(), std::move(value)); }

  template <typename... Args>
  void emplace_back(Args&&... args) {
    push_back(T(std::forward<Args>(args)...));
  }

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
    auto it = std::copy(last, cend(), new_first);
    for (auto i = it; i != finish_; ++i)
      alloc.destroy(i);
    finish_ = it;
    return new_first;
  }

  iterator erase(const_iterator p) { return erase(p, p + 1); }

  void pop_back() { erase(end() - 1); }

  void clear() { erase(cbegin(), cend()); }

  /****************************************
   *                                      *
   *               assign  =              *
   *                                      *
   ****************************************/

  vector& operator=(vector&& other) noexcept {
    if (this == &other) return *this;
    swap(other);
    return *this;
  }

  vector& operator=(const vector& other) {
    if (this == &other) return *this;
    vector temp(other);
    swap(temp);
    return *this;
  }

  template <typename InputIt>
  vector& assign(InputIt first, InputIt last) {
    return *this = vector(first, last);
  }

  vector& assign(size_type count, const T& value) {
    return *this = vector(count, value);
  }

  vector& assign(std::initializer_list<T> ilist) {
    return *this = vector(ilist);
  }

  vector& operator=(std::initializer_list<T> ilist) {
    return *this = vector(ilist);
  }

 private:
  iterator start_;
  iterator finish_;
  iterator end_of_storage_;

  Allocator alloc;

 private:
  /**********************************************************************
   *                                                                    *
   *                      fill_initialize                               *
   *                                                                    *
   **********************************************************************/

  void fill_initialize(size_type n, const T& value) {
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
      if (size() == capacity()) reallocate(size() == 0 ? 1 : 2 * size());
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
    using iterator_category = typename std::iterator_traits<InputIt>::iterator_category;
    copy_initialize(first, last, iterator_category());
  }

  /***************************************************************************
   *                                                                         *
   *                      reallocate                                         *
   *                                                                         *
   ***************************************************************************/

  void reallocate(size_type new_cap) {
    vector temp;
    temp.start_ = alloc.allocate(new_cap);
    temp.finish_ = std::uninitialized_copy(cbegin(), cend(), temp.start_);
    temp.end_of_storage_ = temp.finish_;
    swap(temp);
  }

};  // class vector

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

template <typename T, typename Allocator>
void swap(vector<T, Allocator>& left, vector<T, Allocator>& right) {
  left.swap(right);
}

/************************************************************
 *                                                          *
 *                 == != < <= > >=                          *
 *                                                          *
 ************************************************************/

template <typename T, typename Allocator>
bool operator==(const vector<T, Allocator>& left, const vector<T, Allocator>& right) {
  return left.size() == right.size() && std::equal(left.cbegin(), left.cend(), right.cbegin());
}

template <typename T, typename Allocator>
bool operator!=(const vector<T, Allocator>& left, const vector<T, Allocator>& right) {
  return left.size() != right.size() || !std::equal(left.cbegin(), left.cend(), right.cbegin());
}

template <typename T, typename Allocator>
bool operator<(const vector<T, Allocator>& left, const vector<T, Allocator>& right) {
  return std::lexicographical_compare(left.cbegin(), left.cend(), right.cbegin(), right.cend());
}

template <typename T, typename Allocator>
bool operator<=(const vector<T, Allocator>& left, const vector<T, Allocator>& right) {
  return !(right < left);
}

template <typename T, typename Allocator>
bool operator>(const vector<T, Allocator>& left, const vector<T, Allocator>& right) {
  return right < left;
}

template <typename T, typename Allocator>
bool operator>=(const vector<T, Allocator>& left, const vector<T, Allocator>& right) {
  return !(left < right);
}

}  // namespace liuyunbin

#endif
