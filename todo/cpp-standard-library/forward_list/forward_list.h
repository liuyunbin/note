#ifndef CPP_STANDARD_LIBRARY_FORWARD_LIST_H_
#define CPP_STANDARD_LIBRARY_FORWARD_LIST_H_

#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>

namespace liuyunbin {

namespace detail {

template <typename T>
struct forward_list_node {
  forward_list_node* next_;
  T data_;
};

/*****************************************
 *                                       *
 *           forward_list_iterator       *
 *                                       *
 *****************************************/

template <typename T, typename Reference, typename Pointer>
struct forward_list_iterator {
  using difference_type   = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;
  using pointer           = Pointer;
  using reference         = Reference;
  using value_type        = T;

  using iterator          = forward_list_iterator<T, T&, T*>;
  using const_iterator    = forward_list_iterator<T, const T&, const T*>;
  using self_iterator     = forward_list_iterator<T, Reference, Pointer>;

  forward_list_node<T>* node_;

  forward_list_iterator() : node_(nullptr) {}
  explicit forward_list_iterator(forward_list_node<T>* node) : node_(node) {}
  forward_list_iterator(const iterator& other) : node_(other.node_) {}
  // if self_iterator ==       iterator, iterator --> iterator
  // if self_iterator == const_iterator, iterator --> const_iterator or
  // const_iterator --> const_iterator

  reference operator*() const { return   node_->data_; }
  pointer  operator->() const { return &(operator*()); }

  self_iterator& operator++() {
    node_ = node_->next_;
    return *this;
  }
  self_iterator operator++(int) {
    auto temp = *this;
    node_ = node_->next_;
    return temp;
  }

  self_iterator& operator=(const iterator& other) {
    node_ = other.node_;
    return *this;
  }
  // if self_iterator ==       iterator,       iterator = iterator
  // if self_iterator == const_iterator, const_iterator = iterator or
  // const_iterator = const_iterator

  bool operator==(const       iterator& other) { return node_ == other.node_; }
  bool operator==(const const_iterator& other) { return node_ == other.node_; }
  bool operator!=(const       iterator& other) { return node_ != other.node_; }
  bool operator!=(const const_iterator& other) { return node_ != other.node_; }
};

}  // namespace detail

/***********************************************
 *                                             *
 *               forward_list                  *
 *                                             *
 ***********************************************/

template <typename T, typename Allocator = std::allocator<T>>
class forward_list {
 public:
  using      value_type = T;
  using allocator_type  = Allocator;
  using       size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using       reference = T&;
  using const_reference = const T&;
  using       pointer   = T*;
  using const_pointer   = const T*;
  using       iterator  = detail::forward_list_iterator<T, T&, T*>;
  using const_iterator  = detail::forward_list_iterator<T, const T&, const T*>;

  /*********************************
   *                               *
   *          constructor          *
   *                               *
   *********************************/

  forward_list() {
    node_ = allocate_node();
    node_->next_ = nullptr;
  }

  forward_list(size_type count, const T& value) : forward_list() {
    insert_after(cbefore_begin(), count, value);
  }

  explicit forward_list(size_type count) : forward_list(count, T()) {}

  template <typename InputIt>
  forward_list(InputIt first, InputIt last) : forward_list() {
    insert_after(cbefore_begin(), first, last);
  }

  forward_list(const forward_list& other)
      : forward_list(other.cbegin(), other.cend()) {}

  forward_list(forward_list&& other) noexcept { move_from(other); }

  forward_list(std::initializer_list<T> ilist)
      : forward_list(ilist.begin(), ilist.end()) {}

  /*********************************
   *                               *
   *          destructor           *
   *                               *
   *********************************/

  ~forward_list() { delete_forward_list(); }

  /***********************************
   *                                 *
   *         begin     end           *
   *                                 *
   *        cbegin    cend           *
   *                                 *
   ***********************************/

        iterator  begin()       { return static_cast<      iterator>(node_->next_); }
  const_iterator  begin() const { return static_cast<const_iterator>(node_->next_); }
  const_iterator cbegin() const { return static_cast<const_iterator>(node_->next_); }

        iterator  end()       { return static_cast<      iterator>(nullptr); }
  const_iterator  end() const { return static_cast<const_iterator>(nullptr); }
  const_iterator cend() const { return static_cast<const_iterator>(nullptr); }

  /***********************************
   *                                 *
   *          before_begin           *
   *                                 *
   *         cbefore_begin           *
   *                                 *
   ***********************************/

        iterator  before_begin()       { return static_cast<      iterator>(node_); }
  const_iterator  before_begin() const { return static_cast<const_iterator>(node_); }
  const_iterator cbefore_begin() const { return static_cast<const_iterator>(node_); }

  /************************************
   *                                  *
   *             empty                *
   *                                  *
   *             max_size             *
   *                                  *
   *             front                *
   *                                  *
   ************************************/

  bool empty() const { return cbegin() == cend(); }

  size_type max_size() const { return std::numeric_limits<size_type>::max(); }

        reference front()       { return *begin(); }
  const_reference front() const { return *begin(); }

  /*************************************
   *                                   *
   *             assign                *
   *                                   *
   *             =                     *
   *                                   *
   *************************************/

  forward_list& operator=(forward_list&& other) noexcept {
    if (this == &other) return *this;
    move_from(other);
    return *this;
  }

  forward_list& operator=(const forward_list& other) {
    if (this == &other) return *this;
    return *this = forward_list(other);
  }

  forward_list& operator=(std::initializer_list<T> ilist) {
    return *this = forward_list(ilist);
  }

  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    *this = forward_list(first, last);
  }
  void assign(size_type count, const T& value) {
    *this = forward_list(count, value);
  }
  void assign(std::initializer_list<T> ilist) { *this = forward_list(ilist); }

  /**************************************
   *                                    *
   *         insert_after               *
   *                                    *
   *        emplace_after               *
   *                                    *
   **************************************/

  iterator insert_after(const_iterator pos, const T& value) {
    auto current_node = pos.node_;
    auto new_node = create_node(value);
    new_node->next_ = current_node->next_;
    current_node->next_ = new_node;
    return static_cast<iterator>(new_node);
  }

  iterator insert_after(const_iterator pos, T&& value) {
    auto current_node = pos.node_;
    auto new_node = create_node(std::move(value));
    new_node->next_ = current_node->next_;
    current_node->next_ = new_node;
    return static_cast<iterator>(new_node);
  }

  iterator insert_after(const_iterator pos, size_type count, const T& value) {
    while (count-- != 0) pos = insert_after(pos, value);
    return static_cast<iterator>(pos.node_);
  }

  template <typename InputIt>
  iterator insert_after(const_iterator pos, InputIt first, InputIt last) {
    return insert_after_aux(pos, first, last, std::is_integral<InputIt>());
  }

  iterator insert_after(const_iterator pos, std::initializer_list<T> ilist) {
    return insert_after(pos, ilist.begin(), ilist.end());
  }

  template <typename... Args>
  iterator emplace_after(const_iterator pos, Args&&... args) {
    return insert_after(pos, T(std::forward<Args>(args)...));
  }

  /********************************************
   *                                          *
   *            push_front                    *
   *                                          *
   *            emplace_front                 *
   *                                          *
   ********************************************/

  void push_front(const T& value) { insert_after(cbefore_begin(), value); }
  void push_front(T&& value) {
    insert_after(cbefore_begin(), std::move(value));
  }

  template <typename... Args>
  void emplace_front(Args&&... args) {
    push_front(T(std::forward<Args>(args)...));
  }

  /*******************************************
   *                                         *
   *            erase_after                  *
   *                                         *
   *            clear                        *
   *                                         *
   *******************************************/

  iterator erase_after(const_iterator pos) {
    auto current_node = pos.node_;
    auto temp = current_node->next_;
    current_node->next_ = temp->next_;
    destroy_node(temp);
    return static_cast<iterator>(current_node->next_);
  }

  iterator erase_after(const_iterator first, const_iterator last) {
    while (first != last && std::next(first) != last) erase_after(first);
    return static_cast<iterator>(last.node_);
  }

  void clear() { erase_after(cbefore_begin(), cend()); }

  /***************************************
   *                                     *
   *             pop_front               *
   *                                     *
   ***************************************/

  void pop_front() { erase_after(cbefore_begin()); }

  /***************************************
   *                                     *
   *          resize                     *
   *                                     *
   ***************************************/

  void resize(size_type count, const T& value) {
    size_type size = std::distance(cbegin(), cend());

    if (count == size) return;
    if (count < size)
      erase_after(std::next(cbefore_begin(), count), cend());
    else
      insert_after(std::next(cbefore_begin(), count), count - size, value);
  }

  void resize(size_type count) { resize(count, T()); }

  /****************************************
   *                                      *
   *               swap                   *
   *                                      *
   ****************************************/

  void swap(forward_list& other) { std::swap(node_, other.node_); }

  /****************************************
   *                                      *
   *              remove                  *
   *                                      *
   *              remove_if               *
   *                                      *
   ****************************************/

  template <typename UnaryPredicate>
  size_type remove_if(UnaryPredicate p) {
    size_type count = 0;
    auto it = cbefore_begin();
    while (std::next(it) != cend()) {
      if (p(*std::next(it))) {
        erase_after(it);
        ++count;
      } else
        ++it;
    }
    return count;
  }

  size_type remove(const T& value) {
    return remove_if([value](const T& other) { return value == other; });
  }

  /**************************************
   *                                    *
   *             unique                 *
   *                                    *
   **************************************/

  template <typename BinaryPredicate>
  size_type unique(BinaryPredicate p) {
    auto it = cbegin();
    size_type count = 0;
    while (it != cend() && std::next(it) != cend()) {
      if (p(*it, *std::next(it))) {
        erase_after(it);
        ++count;
      } else
        ++it;
    }
    return count;
  }

  size_type unique() { return unique(std::equal_to<T>()); }

  /**************************************
   *                                    *
   *            splice_after            *
   *                                    *
   **************************************/

  void splice_after(const_iterator pos, forward_list& other,
                    const_iterator first, const_iterator last) {
    if (first == last || std::next(first) == last || pos == first) return;

    auto pos_node = pos.node_;
    auto first_node = first.node_;
    auto last_node = last.node_;
    auto prev_last_node = first_node;

    while (prev_last_node->next_ != last_node)
      prev_last_node = prev_last_node->next_;
    prev_last_node->next_ = pos_node->next_;
    pos_node->next_ = first_node->next_;
    first_node->next_ = last_node;
  }

  void splice_after(const_iterator pos, forward_list&& other,
                    const_iterator first, const_iterator last) {
    splice_after(pos, other, first, last);
  }

  void splice_after(const_iterator pos, forward_list& other) {
    splice_after(pos, other, other.before_begin(), other.end());
  }

  void splice_after(const_iterator pos, forward_list&& other) {
    splice_after(pos, other, other.before_begin(), other.end());
  }

  void splice_after(const_iterator pos, forward_list& other,
                    const_iterator it) {
    splice_after(pos, other, it, std::next(it, 2));
  }

  void splice_after(const_iterator pos, forward_list&& other,
                    const_iterator it) {
    splice_after(pos, other, it, std::next(it, 2));
  }

  /**************************************
   *                                    *
   *               merge                *
   *                                    *
   **************************************/

  template <typename Compare>
  void merge(forward_list& other, Compare comp) {
    if (this == &other) return;

    auto first1 = begin();
    auto last1 = end();
    auto first2 = other.begin();
    auto last2 = other.end();
    auto node = node_;

    while (first1 != last1 && first2 != last2) {
      if (comp(*first2, *first1)) {
        node = node->next_ = first2.node_;
        ++first2;
      } else {
        node = node->next_ = first1.node_;
        ++first1;
      }
    }
    if (first2 != last2)
      node->next_ = first2.node_;
    else
      node->next_ = first1.node_;
    other.node_->next_ = nullptr;
  }

  template <typename Compare>
  void merge(forward_list&& other, Compare comp) {
    merge(other, comp);
  }
  void merge(forward_list& other) { merge(other, std::less<T>()); }
  void merge(forward_list&& other) { merge(other); }

  /******************************************
   *                                        *
   *              reverse                   *
   *                                        *
   ******************************************/

  void reverse() {
    auto it = node_->next_;
    node_->next_ = nullptr;
    while (it != nullptr) {
      auto temp = it->next_;
      it->next_ = node_->next_;
      node_->next_ = it;
      it = temp;
    }
  }

  /*******************************************
   *                                         *
   *               sort                      *
   *                                         *
   *******************************************/
  // merge_sort
  template <typename Compare>
  void sort(Compare comp) {
    if (empty()) return;
    forward_list temp[64];  // 2^64 - 1
    forward_list carry;
    size_type n = 0;
    while (!empty()) {
      carry.splice_after(carry.before_begin(), *this, before_begin());
      size_type i = 0;
      while (!temp[i].empty()) {
        temp[i].merge(carry, comp);
        carry.swap(temp[i++]);
      }
      carry.swap(temp[i]);
      if (i == n) ++n;
    }
    for (size_type i = 1; i < n; ++i) temp[i].merge(temp[i - 1], comp);
    swap(temp[n - 1]);
  }

  void sort() { sort(std::less<T>()); }

 private:
  using forward_list_node_allocator =
      typename Allocator::template rebind<detail::forward_list_node<T>>::other;

  forward_list_node_allocator alloc;

  detail::forward_list_node<T>* node_ = nullptr;

  /****************************************************
   *                                                  *
   *             allocate_node                        *
   *                                                  *
   *             deallocate_node                      *
   *                                                  *
   *             create_node                          *
   *                                                  *
   *             destroy_node                         *
   *                                                  *
   ****************************************************/

  detail::forward_list_node<T>* allocate_node() { return alloc.allocate(1); }

  void deallocate_node(detail::forward_list_node<T>* p) {
    alloc.deallocate(p, 1);
  }

  detail::forward_list_node<T>* create_node(const T& value) {
    auto new_node = allocate_node();
    alloc.construct(&new_node->data_, value);
    return new_node;
  }

  detail::forward_list_node<T>* create_node(T&& value) {
    auto new_node = allocate_node();
    alloc.construct(&new_node->data_, std::move(value));
    return new_node;
  }

  void destroy_node(detail::forward_list_node<T>* p) {
    alloc.destroy(&p->data_);
    deallocate_node(p);
  }

  /**************************************
   *                                    *
   *            insert_after_aux        *
   *                                    *
   **************************************/

  template <typename InputIt>
  iterator insert_after_aux(const_iterator pos, InputIt first, InputIt last,
                            std::true_type) {
    return insert_after(pos, static_cast<size_type>(first),
                        static_cast<T>(last));
  }

  template <typename InputIt>
  iterator insert_after_aux(const_iterator pos, InputIt first, InputIt last,
                            std::false_type) {
    if (first == last) return static_cast<iterator>(pos.node_);
    auto temp = insert_after(pos, *first);
    pos = temp;
    while (++first != last) pos = insert_after(pos, *first);
    return static_cast<iterator>(temp.node_);
  }

  /******************************************
   *                                        *
   *             delete_forward_list        *
   *                                        *
   ******************************************/

  void delete_forward_list() {
    if (node_ == nullptr) return;
    clear();
    deallocate_node(node_);
    node_ = nullptr;
  }

  /*******************************************
   *                                         *
   *            move_from                    *
   *                                         *
   *******************************************/

  void move_from(forward_list& other) {
    delete_forward_list();
    node_ = other.node_;
    other.node_ = nullptr;
  }

};  // class forward_list

/*****************************
 *                           *
 *          swap             *
 *                           *
 *****************************/

template <typename T, typename Allocator>
void swap(forward_list<T, Allocator>& left, forward_list<T, Allocator>& right) {
  left.swap(right);
}

/************************************
 *                                  *
 *     ==   !=   <   <=   >   >=    *
 *                                  *
 ************************************/

template <typename T, typename Allocator>
bool operator<(const forward_list<T, Allocator>& left, const forward_list<T, Allocator>& right) {
  return std::lexicographical_compare(left.cbegin(), left.cend(), right.cbegin(), right.cend());
}

template <typename T, typename Allocator>
bool operator<=(const forward_list<T, Allocator>& left, const forward_list<T, Allocator>& right) {
  return !(right < left);
}

template <typename T, typename Allocator>
bool operator>(const forward_list<T, Allocator>& left, const forward_list<T, Allocator>& right) {
  return right < left;
}

template <typename T, typename Allocator>
bool operator>=(const forward_list<T, Allocator>& left, const forward_list<T, Allocator>& right) {
  return !(left < right);
}

template <typename T, typename Allocator>
bool operator==(const forward_list<T, Allocator>& left, const forward_list<T, Allocator>& right) {
  return left < right == false && right < left == false;
}

template <typename T, typename Allocator>
bool operator!=(const forward_list<T, Allocator>& left, const forward_list<T, Allocator>& right) {
  return left < right || right < left;
}

}  // namespace liuyunbin

#endif
