#ifndef CPP_STANDARD_LIBRARY_DEQUE_H_
#define CPP_STANDARD_LIBRARY_DEQUE_H_

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>

namespace liuyunbin {

namespace detail {

constexpr std::size_t deque_node_size = 8;

/***********************************************************
 *                                                         *
 *                 class __deque_iterator                  *
 *                                                         *
 ***********************************************************/

template <typename T, typename Ref, typename Ptr>
class deque_iterator {
 public:
  using        value_type = T;
  using           pointer = Ptr;
  using         reference = Ref;
  using   difference_type = std::ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;
  using         size_type = std::size_t;
  using          iterator = deque_iterator<T, T&, T*>;
  using    const_iterator = deque_iterator<T, const T&, const T*>;
  using     self_iterator = deque_iterator<T, Ref, Ptr>;

  T* first_;
  T* last_;
  T* cur_;

  T** node_;

  void set_node(T** new_node) {
    node_  = new_node;
    first_ = *node_;
    last_  = first_ + deque_node_size;
  }

  /*********************************************
   *                                           *
   *             constructor                   *
   *                                           *
   *********************************************/

  deque_iterator() : first_(nullptr), last_(nullptr), cur_(nullptr), node_(nullptr) {}
  deque_iterator(const iterator& other) {  // iterator -->  iterator or const_iterator
    set_node(other.node_);
    cur_ = other.cur_;
  }

  /*********************************************
   *                                           *
   *                  =                        *
   *                                           *
   *********************************************/

  self_iterator& operator=(const iterator& other) {  // iterator -->  iterator or const_iterator
    set_node(other.node_);
    cur_ = other.cur_;
    return *this;
  }

  /*********************************************
   *                                           *
   *             *   ->                        *
   *                                           *
   *********************************************/

  reference operator*() const { return          *cur_; }
  pointer  operator->() const { return &(operator*()); }

  /*********************************************
   *                                           *
   *         ++ -- + += - -= []                *
   *                                           *
   *********************************************/

  self_iterator& operator++() {
    ++cur_;
    if (cur_ == last_) {
      set_node(node_ + 1);
      cur_ = first_;
    }
    return *this;
  }

  self_iterator operator++(int) {
    auto temp = *this;
    ++*this;
    return temp;
  }

  self_iterator& operator--() {
    if (cur_ == first_) {
      set_node(node_ - 1);
      cur_ = last_;
    }
    --cur_;
    return *this;
  }

  self_iterator operator--(int) {
    auto temp = *this;
    --*this;
    return temp;
  }

  self_iterator& operator+=(difference_type n) {
    difference_type offset = n + (cur_ - first_);
    if (offset >= 0 && static_cast<std::size_t>(offset) < deque_node_size) {
      cur_ += n;
      return *this;
    }
    difference_type node_offset;
    if (offset > 0)
      node_offset = offset / deque_node_size;
    else
      node_offset = -((-offset - 1) / deque_node_size + 1);
    set_node(node_ + node_offset);
    cur_ = first_ + (offset - node_offset * deque_node_size);
    return *this;
  }

  self_iterator operator+(difference_type n) const {
    auto temp = *this;
    temp += n;
    return temp;
  }

  self_iterator& operator-=(difference_type n) { return *this += -n; }

  self_iterator operator-(difference_type n) const {
    auto temp = *this;
    temp -= n;
    return temp;
  }

  reference operator[](difference_type n) const { return *(*this + n); }
};

/*********************************************
 *                                           *
 *           -              +                *
 *                                           *
 *********************************************/

template <typename T, typename RefL, typename PtrL, typename RefR, typename PtrR>
typename deque_iterator<T, RefL, PtrL>::difference_type operator-(
    const deque_iterator<T, RefL, PtrL>& left,
    const deque_iterator<T, RefR, PtrR>& right) {
  if (left.node_ == right.node_) return left.cur_ - right.cur_;
  return (left.node_ - right.node_ - 1) * deque_node_size +
         (left.cur_ - left.first_) + (right.last_ - right.cur_);
}

template <typename T, typename Ref, typename Ptr>
deque_iterator<T, Ref, Ptr> operator+(
    typename deque_iterator<T, Ref, Ptr>::difference_type n,
    const deque_iterator<T, Ref, Ptr>& right) {
  return right + n;
}

/*********************************************
 *                                           *
 *     ==    !=    <     <=    >     >=      *
 *                                           *
 *********************************************/

template <typename T, typename RefL, typename PtrL, typename RefR, typename PtrR>
bool operator==(const deque_iterator<T, RefL, PtrL>& left, const deque_iterator<T, RefR, PtrR>& right) {
  return left.cur_ == right.cur_;
}

template <typename T, typename RefL, typename PtrL, typename RefR, typename PtrR>
bool operator!=(const deque_iterator<T, RefL, PtrL>& left, const deque_iterator<T, RefR, PtrR>& right) {
  return left.cur_ != right.cur_;
}

template <typename T, typename RefL, typename PtrL, typename RefR, typename PtrR>
bool operator<(const deque_iterator<T, RefL, PtrL>& left, const deque_iterator<T, RefR, PtrR>& right) {
  if (left.node_ == right.node_) return left.cur_ < right.cur_;
  return left.node_ < right.node_;
}

template <typename T, typename RefL, typename PtrL, typename RefR, typename PtrR>
bool operator<=(const deque_iterator<T, RefL, PtrL>& left, const deque_iterator<T, RefR, PtrR>& right) {
  if (left.node_ == right.node_) return left.cur_ <= right.cur_;
  return left.node_ < right.node_;
}

template <typename T, typename RefL, typename PtrL, typename RefR, typename PtrR>
bool operator>(const deque_iterator<T, RefL, PtrL>& left, const deque_iterator<T, RefR, PtrR>& right) {
  if (left.node_ == right.node_) return left.cur_ > right.cur_;
  return left.node_ > right.node_;
}

template <typename T, typename RefL, typename PtrL, typename RefR, typename PtrR>
bool operator>=(const deque_iterator<T, RefL, PtrL>& left, const deque_iterator<T, RefR, PtrR>& right) {
  if (left.node_ == right.node_) return left.cur_ >= right.cur_;
  return left.node_ > right.node_;
}

}  // namespace detail

/*********************************************
 *                                           *
 *                deque                      *
 *                                           *
 *********************************************/

template <typename T, typename Allocator = std::allocator<T>>
class deque {
 public:
  using             value_type = T;
  using         allocator_type = Allocator;
  using              size_type = std::size_t;
  using        difference_type = std::ptrdiff_t;
  using              reference = T&;
  using        const_reference = const T&;
  using                pointer = T*;
  using          const_pointer = const T*;
  using               iterator = detail::deque_iterator<T, T&, T*>;
  using         const_iterator = detail::deque_iterator<T, const T&, const T*>;
  using       reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

 private:
  using node_allocator = Allocator;
  using map_allocator = typename Allocator::template rebind<T*>::other;

 public:
  /***********************************
   *                                 *
   *          constructor            *
   *                                 *
   ***********************************/

  deque() { empty_initialize(); }

  deque(size_type count, const T& value) { fill_initialize(count, value); }

  explicit deque(size_type count) { fill_initialize(count, T()); }

  template <typename InputIt>
  deque(InputIt first, InputIt last) {
    initialize_aux(first, last, std::is_integral<InputIt>());
  }

  deque(const deque& other) : deque(other.cbegin(), other.cend()) {}

  deque(std::initializer_list<T> ilist) : deque(ilist.begin(), ilist.end()) {}

  deque(deque&& other) { move_from(other); }

  /***********************************
   *                                 *
   *           destructor            *
   *                                 *
   ***********************************/

  ~deque() { delete_deque(); }

  /***********************************
   *                                 *
   *        begin         end        *
   *       cbegin        cend        *
   *                                 *
   ***********************************/

        iterator  begin()       { return start_; }
  const_iterator  begin() const { return start_; }
  const_iterator cbegin() const { return start_; }

        iterator  end()       { return finish_; }
  const_iterator  end() const { return finish_; }
  const_iterator cend() const { return finish_; }

  /***********************************
   *                                 *
   *        rbegin         rend      *
   *       crbegin        crend      *
   *                                 *
   ***********************************/

        reverse_iterator  rbegin()       { return static_cast<      reverse_iterator>(end()); }
  const_reverse_iterator  rbegin() const { return static_cast<const_reverse_iterator>(end()); }
  const_reverse_iterator crbegin() const { return static_cast<const_reverse_iterator>(end()); }

        reverse_iterator  rend()       { return static_cast<      reverse_iterator>(begin()); }
  const_reverse_iterator  rend() const { return static_cast<const_reverse_iterator>(begin()); }
  const_reverse_iterator crend() const { return static_cast<const_reverse_iterator>(begin()); }

  /************************************
   *                                  *
   *         []         at            *
   *                                  *
   ************************************/

        reference at(size_type pos)       { return start_[pos]; }
  const_reference at(size_type pos) const { return start_[pos]; }
        reference operator[](size_type pos)       { return start_[pos]; }
  const_reference operator[](size_type pos) const { return start_[pos]; }

  /*************************************
   *                                   *
   *     front          back           *
   *                                   *
   *************************************/

        reference front()       { return *start_; }
  const_reference front() const { return *start_; }

        reference back()       { return *(finish_ - 1); }
  const_reference back() const { return *(finish_ - 1); }

  /*************************************
   *                                   *
   *             empty                 *
   *                                   *
   *             size                  *
   *                                   *
   *             max_size              *
   *                                   *
   *************************************/

  bool         empty() const { return finish_ == start_; }
  size_type     size() const { return finish_ -  start_; }

  size_type max_size() const { return std::numeric_limits<size_type>::max(); }

  /**************************************
   *                                    *
   *             swap                   *
   *                                    *
   **************************************/

  void swap(deque& other) {
    std::swap(start_, other.start_);
    std::swap(finish_, other.finish_);
    std::swap(map_, other.map_);
    std::swap(map_size_, other.map_size_);
  }

  /*************************************
   *                                   *
   *              insert               *
   *                                   *
   *              emplace              *
   *                                   *
   *************************************/

  iterator insert(const_iterator pos, const deque& other) {
    size_type elements_before = pos - start_;
    if (elements_before < size() / 2) {
      iterator new_start = reserve_elements_at_front(other.size());
      auto new_pos = start_ + elements_before;
      if (elements_before < other.size()) {
        auto it = std::uninitialized_copy_n(start_, elements_before, new_start);
        std::uninitialized_copy_n(other.cbegin(), other.size() - elements_before, it);
        std::copy(other.cend() - elements_before, other.cend(), start_);
      } else {
        std::uninitialized_copy_n(start_, other.size(), new_start);
        auto it = std::copy(start_ + other.size(), new_pos, start_);
        std::copy(other.cbegin(), other.cend(), it);
      }
      start_ = new_start;
      return new_pos - other.size();
    }
    iterator new_finish = reserve_elements_at_back(other.size());
    auto new_pos = start_ + elements_before;
    auto elements_after = size() - elements_before;
    if (elements_after < other.size()) {
      auto it = std::uninitialized_copy(other.cbegin() + elements_after, other.cend(), finish_);
      std::uninitialized_copy(new_pos, finish_, it);
      std::copy_n(other.cbegin(), elements_after, new_pos);
    } else {
      std::uninitialized_copy(end() - other.size(), end(), finish_);
      std::copy_backward(new_pos, end() - other.size(), end());
      std::copy(other.cbegin(), other.cend(), new_pos);
    }
    finish_ = new_finish;
    return new_pos;
  }

  iterator insert(const_iterator pos, T&& value) {
    size_type elements_before = pos - start_;
    if (elements_before < size() / 2) {
      reserve_elements_at_front(1);
      auto new_pos = start_ + elements_before;
      node_alloc.construct(&*--start_, value);
      std::copy(start_ + 1, new_pos, start_);
      *--new_pos = std::move(value);
      return new_pos;
    }
    reserve_elements_at_back(1);
    auto new_pos = start_ + elements_before;
    node_alloc.construct(&*finish_++, value);
    std::copy_backward(new_pos, finish_ - 1, finish_);
    *new_pos = std::move(value);
    return new_pos;
  }

  iterator insert(const_iterator pos, const T& value) {
    return insert(pos, deque(1, value));
  }
  iterator insert(const_iterator pos, size_type count, const T& value) {
    return insert(pos, deque(count, value));
  }

  template <typename InputIt>
  iterator insert(const_iterator pos, InputIt first, InputIt last) {
    return insert(pos, deque(first, last));
  }

  iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
    return insert(pos, deque(ilist));
  }

  template <typename... Args>
  iterator emplace(const_iterator pos, Args&&... args) {
    return insert(pos, T(std::forward<Args>(args)...));
  }

  /**************************************
   *                                    *
   *             push_back              *
   *                                    *
   *             push_front             *
   *                                    *
   *             emplace_back           *
   *                                    *
   *             emplace_front          *
   *                                    *
   **************************************/

  void push_back(const T&  value) { insert(cend(),           value) ; }
  void push_back(      T&& value) { insert(cend(), std::move(value)); }

  template <typename... Args>
  void emplace_back(Args&&... args) {
    push_back(T(std::forward<Args>(args)...));
  }

  void push_front(const T&  value) { insert(cbegin(),           value);  }
  void push_front(      T&& value) { insert(cbegin(), std::move(value)); }

  template <typename... Args>
  void emplace_front(Args&&... args) {
    push_front(T(std::forward<Args>(args)...));
  }

  /***************************************
   *                                     *
   *               erase                 *
   *                                     *
   *               clear                 *
   *                                     *
   ***************************************/

  iterator erase(const_iterator first, const_iterator last) {
    auto new_first = begin() + (first - cbegin());
    auto new_end = std::copy(last, cend(), new_first);

    for (auto it = new_end; it != finish_; ++it) node_alloc.destroy(&*it);
    for (auto i = new_end.node_ + 1; i <= finish_.node_; ++i)
      deallocate_node(*i);
    finish_ = new_end;
    return new_first;
  }

  iterator erase(const_iterator pos) { return erase(pos, pos + 1); }

  void clear() { erase(start_, finish_); }

  /***************************************
   *                                     *
   *                pop_back             *
   *                                     *
   *                pop_front            *
   *                                     *
   ***************************************/

  void pop_back() { erase(cend() - 1); }
  void pop_front() { erase(cbegin()); }

  /***************************************
   *                                     *
   *            shrink_to_fit            *
   *                                     *
   ***************************************/

  void shrink_to_fit() {}  // nothing

  /***************************************
   *                                     *
   *           assign      =             *
   *                                     *
   ***************************************/

  deque& operator=(deque&& other) noexcept {
    if (this == &other) return *this;
    move_from(other);
    return *this;
  }

  deque& operator=(const deque& other) {
    if (this == &other) return *this;
    return *this = deque(other);
  }

  deque& operator=(std::initializer_list<T> ilist) {
    return *this = deque(ilist);
  }

  void assign(size_type count, const T &value) { *this = deque(count, value); }

  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    *this = deque(first, last);
  }

  void assign(std::initializer_list<T> ilist) { *this = deque(ilist); }

  /***************************************
   *                                     *
   *             resize                  *
   *                                     *
   ***************************************/

  void resize(size_type count, const T& value) {
    if (count < size())
      erase(cbegin() + count, cend());
    else
      insert(cend(), count - size(), value);
  }

  void resize(size_type count) { resize(count, T()); }

 private:
  static constexpr size_type min_map_size_ = 8;

  node_allocator node_alloc;
  map_allocator map_alloc;

  iterator start_;
  iterator finish_;

  T** map_ = nullptr;
  size_type map_size_;

  /*******************************
   *                             *
   *       empty_initialize      *
   *                             *
   *******************************/

  void empty_initialize() { create_map_and_nodes(); }

  /*******************************
   *                             *
   *       fill_initialize       *
   *                             *
   *******************************/

  void fill_initialize(size_type n, const T& value) {
    create_map_and_nodes(n);
    for (auto it = start_.node_; it < finish_.node_; ++it)
      std::uninitialized_fill(*it, *it + detail::deque_node_size, value);
    std::uninitialized_fill(finish_.first_, finish_.cur_, value);
  }

  /*******************************
   *                             *
   *        copy_initialize      *
   *                             *
   *******************************/

  template <typename InputIt>
  void copy_initialize(InputIt first, InputIt last, std::input_iterator_tag) {
    create_map_and_nodes();
    while (first != last) {
      reserve_elements_at_back(1);
      Allocator::construct(&*finish_++, *first++);
    }
  }

  template <typename ForwardIt>
  void copy_initialize(ForwardIt first, ForwardIt last, std::forward_iterator_tag) {
    auto n = std::distance(first, last);
    create_map_and_nodes(n);
    for (auto it = start_.node_; it < finish_.node_; ++it) {
      auto next = std::next(first, detail::deque_node_size);
      std::uninitialized_copy(first, next, *it);
      first = next;
    }
    std::uninitialized_copy(first, last, finish_.first_);
  }

  /*******************************
   *                             *
   *       initialize_aux        *
   *                             *
   *******************************/

  template <typename InputIt>
  void initialize_aux(InputIt first, InputIt last, std::true_type) {
    fill_initialize(first, last);
  }

  template <typename InputIt>
  void initialize_aux(InputIt first, InputIt last, std::false_type) {
    using category = typename std::iterator_traits<InputIt>::iterator_category;
    copy_initialize(first, last, category());
  }

  /*******************************
   *                             *
   *      create_map_and_nodes   *
   *                             *
   *******************************/

  void create_map_and_nodes(size_type num_elements = 0) {
    size_type num_nodes = num_elements / detail::deque_node_size + 1;
    map_size_ = std::max(num_nodes + 2, min_map_size_);
    map_ = allocate_map();
    T** nstart = map_ + (map_size_ - num_nodes) / 2;
    T** nfinish = nstart + num_nodes - 1;
    for (auto it = nstart; it <= nfinish; ++it) *it = allocate_node();
    start_.set_node(nstart);
    finish_.set_node(nfinish);
    start_.cur_ = start_.first_;
    finish_.cur_ = finish_.first_ + num_elements % detail::deque_node_size;
  }

  /*************************************
   *                                   *
   *          delete_deque             *
   *                                   *
   *************************************/

  void delete_deque() {
    if (map_ == nullptr) return;
    clear();
    deallocate_node(*start_.node_);
    deallocate_map();
    map_ = nullptr;
  }

  /*************************************
   *                                   *
   *             set                   *
   *                                   *
   *************************************/

  void set(iterator start, iterator finish, T** map, size_type map_size) {
    start_ = start;
    finish_ = finish;
    map_ = map;
    map_size_ = map_size;
  }

  /*************************************
   *                                   *
   *             move_from             *
   *                                   *
   *************************************/

  void move_from(deque& other) {
    delete_deque();
    set(other.start_, other.finish_, other.map_, other.map_size_);
    other.map_ = nullptr;
  }

  /**************************************
   *                                    *
   *      reallocate_map                *
   *                                    *
   *      reserve_map_at_front          *
   *                                    *
   *      reserve_map_at_back           *
   *                                    *
   *      new_elements_at_front         *
   *                                    *
   *      new_elements_at_back          *
   *                                    *
   *      reserve_elements_at_front     *
   *                                    *
   *      reserve_elements_at_back      *
   *                                    *
   *************************************/

  void reallocate_map(size_type nodes_to_add, bool add_at_front) {
    size_type old_num_nodes = finish_.node_ - start_.node_ + 1;
    size_type new_num_nodes = old_num_nodes + nodes_to_add;
    T** new_start;
    if (map_size_ > 2 * new_num_nodes) {
      new_start = map_ + (map_size_ - new_num_nodes) / 2 +
                  (add_at_front ? nodes_to_add : 0);
      if (new_start < start_.node_)
        std::copy(start_.node_, finish_.node_ + 1, new_start);
      else
        std::copy_backward(start_.node_, finish_.node_ + 1,
                                 new_start + old_num_nodes);
    } else {
      map_size_ += std::max(map_size_, nodes_to_add) + 2;
      auto new_map = allocate_map();
      new_start = new_map + (map_size_ - new_num_nodes) / 2 +
                  (add_at_front ? nodes_to_add : 0);
      std::copy(start_.node_, finish_.node_ + 1, new_start);
      deallocate_map();
      map_ = new_map;
    }
    start_.set_node(new_start);
    finish_.set_node(new_start + old_num_nodes - 1);
  }

  void reserve_map_at_front(size_type nodes_to_add = 1) {
    if (nodes_to_add > static_cast<size_type>(start_.node_ - map_))
      reallocate_map(nodes_to_add, true);
  }

  void reserve_map_at_back(size_type nodes_to_add = 1) {
    if (nodes_to_add > map_size_ - (finish_.node_ - map_) - 1)
      reallocate_map(nodes_to_add, false);
  }

  void new_elements_at_front(size_type new_elements) {
    size_type new_nodes =
        (new_elements + detail::deque_node_size - 1) / detail::deque_node_size;
    reserve_map_at_front(new_nodes);
    for (size_type i = 1; i <= new_nodes; ++i)
      *(start_.node_ - i) = allocate_node();
  }

  void new_elements_at_back(size_type new_elements) {
    size_type new_nodes =
        (new_elements + detail::deque_node_size - 1) / detail::deque_node_size;
    reserve_map_at_back(new_nodes);
    for (size_type i = 1; i <= new_nodes; ++i)
      *(finish_.node_ + i) = allocate_node();
  }

  iterator reserve_elements_at_front(size_type n) {
    size_type n_before = start_.cur_ - start_.first_;
    if (n > n_before) new_elements_at_front(n - n_before);
    return start_ - n;
  }

  iterator reserve_elements_at_back(size_type n) {
    size_type n_before = finish_.last_ - finish_.cur_ - 1;
    if (n > n_before) new_elements_at_back(n - n_before);
    return finish_ + n;
  }

  /*******************************
   *                             *
   *        allocate_map         *
   *                             *
   *        deallocate_map       *
   *                             *
   *******************************/

  T** allocate_map() { return map_alloc.allocate(map_size_); }

  void deallocate_map() { map_alloc.deallocate(map_, map_size_); }

  /*******************************
   *                             *
   *        allocate_node        *
   *                             *
   *        deallocate_node      *
   *                             *
   *******************************/

  T* allocate_node() { return node_alloc.allocate(detail::deque_node_size); }

  void deallocate_node(T* p) {
    node_alloc.deallocate(p, detail::deque_node_size);
  }

};  // class deque

template <typename T, typename Allocator>
constexpr typename deque<T, Allocator>::size_type deque<T, Allocator>::min_map_size_;

/********************************
 *                              *
 *           swap               *
 *                              *
 ********************************/

template <typename T, typename Allocator>
void swap(deque<T, Allocator>& left, deque<T, Allocator>& right) {
  return left.swap(right);
}

/*************************************
 *                                   *
 *    ==   !=   <   <=   >    >=     *
 *                                   *
 *************************************/

template <typename T, typename Allocator>
bool operator==(const deque<T, Allocator>& left, const deque<T, Allocator>& right) {
  return left.size() == right.size() && std::equal(left.cbegin(), left.cend(), right.cbegin());
}

template <typename T, typename Allocator>
bool operator!=(const deque<T, Allocator>& left, const deque<T, Allocator>& right) {
  return left.size() != right.size() || !std::equal(left.cbegin(), left.cend(), right.cbegin());
}

template <typename T, typename Allocator>
bool operator<(const deque<T, Allocator>& left, const deque<T, Allocator>& right) {
  return std::lexicographical_compare(left.cbegin(), left.cend(), right.cbegin(), right.cend());
}

template <typename T, typename Allocator>
bool operator<=(const deque<T, Allocator>& left, const deque<T, Allocator>& right) {
  return !(right < left);
}

template <typename T, typename Allocator>
bool operator>(const deque<T, Allocator>& left, const deque<T, Allocator>& right) {
  return right < left;
}

template <typename T, typename Allocator>
bool operator>=(const deque<T, Allocator>& left, const deque<T, Allocator>& right) {
  return !(left < right);
}

}  // namespace liuyunbin

#endif
