#ifndef CPP_STANDARD_LIBRARY_LIST_H_
#define CPP_STANDARD_LIBRARY_LIST_H_

#include <iostream>
#include <iterator>
#include <initializer_list>
#include <limits>

namespace liuyunbin {

namespace detail {

template <typename T>
struct list_node {
  list_node* prev_;
  list_node* next_;
  T data_;
};

/*****************************************
 *                                       *
 *           list_iterator               *
 *                                       *
 *****************************************/

template <typename T, typename Reference, typename Pointer>
struct list_iterator {
  using   difference_type = std::ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;
  using           pointer = Pointer;
  using         reference = Reference;
  using        value_type = T;

  using       iterator = list_iterator<T, T&, T*>;
  using const_iterator = list_iterator<T, const T&, const T*>;
  using  self_iterator = list_iterator<T, Reference, Pointer>;

  list_node<T>* node_;

  list_iterator() : node_(nullptr) {}
  explicit list_iterator(list_node<T>* node) : node_(node) {}
  list_iterator(const iterator& other) : node_(other.node_) {}
  // if self_iterator ==       iterator, iterator --> iterator
  // if self_iterator == const_iterator, iterator --> const_iterator or
  // const_iterator --> const_iterator

  reference operator* () const { return   node_->data_; }
    pointer operator->() const { return &(operator*()); }

  self_iterator& operator++() {
    node_ = node_->next_;
    return *this;
  }
  self_iterator& operator--() {
    node_ = node_->prev_;
    return *this;
  }
  self_iterator operator++(int) {
    auto temp = *this;
    node_ = node_->next_;
    return temp;
  }
  self_iterator operator--(int) {
    auto temp = *this;
    node_ = node_->prev_;
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
 *                   list                      *
 *                                             *
 ***********************************************/

template <typename T, typename Allocator = std::allocator<T>>
class list {
 public:
  using             value_type = T;
  using         allocator_type = Allocator;
  using              size_type = std::size_t;
  using        difference_type = std::ptrdiff_t;
  using              reference = T&;
  using        const_reference = const T&;
  using                pointer = T*;
  using          const_pointer = const T*;
  using               iterator = detail::list_iterator<T,       T&,       T*>;
  using         const_iterator = detail::list_iterator<T, const T&, const T*>;
  using       reverse_iterator = std::reverse_iterator<      iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  /*********************************
   *                               *
   *          constructor          *
   *                               *
   *********************************/

  list() {
    node_ = allocate_node();
    node_->prev_ = node_->next_ = node_;
  }

  list(size_type count, const T& value) : list() {
    insert(begin(), count, value);
  }

  explicit list(size_type count) : list(count, T()) {}

  template <typename InputIt>
  list(InputIt first, InputIt last) : list() {
    insert(begin(), first, last);
  }

  list(const list& other) : list(other.begin(), other.end()) {}

  list(list&& other) noexcept { move_from(other); }

  list(std::initializer_list<T> ilist) : list(ilist.begin(), ilist.end()) {}

  /*********************************
   *                               *
   *          destructor           *
   *                               *
   *********************************/

  ~list() { delete_list(); }

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

         iterator end()       { return static_cast<      iterator>(node_); }
  const_iterator  end() const { return static_cast<const_iterator>(node_); }
  const_iterator cend() const { return static_cast<const_iterator>(node_); }

  /***********************************
   *                                 *
   *         rbegin     rend         *
   *                                 *
   *        crbegin    crend         *
   *                                 *
   ***********************************/

        reverse_iterator  rbegin()       { return static_cast<      reverse_iterator>( end()); }
  const_reverse_iterator  rbegin() const { return static_cast<const_reverse_iterator>( end()); }
  const_reverse_iterator crbegin() const { return static_cast<const_reverse_iterator>(cend()); }

        reverse_iterator  rend()       { return static_cast<      reverse_iterator>( begin()); }
  const_reverse_iterator  rend() const { return static_cast<const_reverse_iterator>( begin()); }
  const_reverse_iterator crend() const { return static_cast<const_reverse_iterator>(cbegin()); }

  /************************************
   *                                  *
   *             empty                *
   *                                  *
   *             size                 *
   *                                  *
   *             max_size             *
   *                                  *
   *             front                *
   *                                  *
   *             back                 *
   *                                  *
   ************************************/

  bool empty() const { return node_ == node_->next_; }

  size_type     size() const { return count_node_; }

  size_type max_size() const { return std::numeric_limits<size_type>::max(); }

        reference front()       { return *begin(); }
  const_reference front() const { return *begin(); }

        reference back()       { return *--end(); }
  const_reference back() const { return *--end(); }

  /*************************************
   *                                   *
   *             assign                *
   *                                   *
   *             =                     *
   *                                   *
   *************************************/

  list& operator=(list&& other) noexcept {
    if (this == &other) return *this;
    move_from(other);
    return *this;
  }

  list& operator=(const list& other) {
    if (this == &other) return *this;
    return *this = list(other);
  }

  list& operator=(std::initializer_list<T> ilist) {
    return *this = list(ilist);
  }

  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    *this = list(first, last);
  }
  void assign(size_type count, const T& value) { *this = list(count, value); }
  void assign(std::initializer_list<T> ilist) { *this = list(ilist); }

  /**************************************
   *                                    *
   *             insert                 *
   *                                    *
   *             emplace                *
   *                                    *
   **************************************/

  iterator insert(const_iterator pos, const T& value) {
    return insert_aux(pos, value);
  }
  iterator insert(const_iterator pos, T&& value) {
    return insert_aux(pos, std::move(value));
  }

  iterator insert(const_iterator pos, size_type count, const T& value) {
    while (count-- != 0) pos = insert(pos, value);
    return static_cast<iterator>(pos.node_);
  }

  template <typename InputIt>
  iterator insert(const_iterator pos, InputIt first, InputIt last) {
    return insert_range_aux(pos, first, last, std::is_integral<InputIt>());
  }

  iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
    return insert(pos, ilist.begin(), ilist.end());
  }

  template <typename... Args>
  iterator emplace(const_iterator pos, Args&&... args) {
    return insert(pos, T(std::forward<Args>(args)...));
  }

  /********************************************
   *                                          *
   *            push_back                     *
   *                                          *
   *            emplace_back                  *
   *                                          *
   *            push_front                    *
   *                                          *
   *            emplace_front                 *
   *                                          *
   ********************************************/

  void push_back(const T& value) { insert(end(), value); }
  void push_back(T&& value) { insert(end(), std::move(value)); }

  template <typename... Args>
  void emplace_back(Args&&... args) {
    emplace(end(), std::forward<Args>(args)...);
  }

  void push_front(const T&  value) { insert(begin(), value); }
  void push_front(      T&& value) { insert(begin(), std::move(value)); }

  template <typename... Args>
  void emplace_front(Args&&... args) {
    emplace(begin(), std::forward<Args>(args)...);
  }

  /*******************************************
   *                                         *
   *            erase                        *
   *                                         *
   *            clear                        *
   *                                         *
   *******************************************/

  iterator erase(const_iterator first, const_iterator last) {
    auto first_node = first.node_;
    auto last_node = last.node_;
    auto prev_node = first_node->prev_;
    while (first_node != last_node) {
      auto temp = first_node;
      first_node = first_node->next_;
      destroy_node(temp);
      --count_node_;
    }
    prev_node->next_ = last_node;
    last_node->prev_ = prev_node;
    return static_cast<iterator>(last_node);
  }

  iterator erase(const_iterator pos) {
    auto temp = pos;
    return erase(pos, ++temp);
  }

  void clear() { erase(cbegin(), cend()); }

  /***************************************
   *                                     *
   *             pop_back                *
   *                                     *
   *             pop_front               *
   *                                     *
   ***************************************/

  void pop_back() { erase(--end()); }

  void pop_front() { erase(begin()); }

  /***************************************
   *                                     *
   *          resize                     *
   *                                     *
   ***************************************/

  void resize(size_type count, const T& value) {
    if (count == size()) return;
    if (count < size())
      erase(std::next(begin(), count), end());
    else
      insert(end(), count - size(), value);
  }

  void resize(size_type count) { resize(count, T()); }

  /****************************************
   *                                      *
   *               swap                   *
   *                                      *
   ****************************************/

  void swap(list& other) {
    std::swap(node_, other.node_);
    std::swap(count_node_, other.count_node_);
  }

  /****************************************
   *                                      *
   *              remove                  *
   *                                      *
   *              remove_if               *
   *                                      *
   ****************************************/

  template <typename UnaryPredicate>
  size_type remove_if(UnaryPredicate p) {
    size_type prev_count_node = size();
    auto it = begin();
    while (it != end()) {
      if (p(*it))
        it = erase(it);
      else
        ++it;
    }
    return prev_count_node - size();
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
    if (size() <= 1) return 0;
    size_type prev_count_node = size();
    auto it = begin();
    while (it != end()) {
      auto next = it;
      if (++next == end()) break;
      if (p(*it, *next))
        erase(next);
      else
        ++it;
    }
    return prev_count_node - size();
  }

  size_type unique() { return unique(std::equal_to<T>()); }

  /**************************************
   *                                    *
   *            splice                  *
   *                                    *
   **************************************/

  void splice(const_iterator pos, list& other) {
    count_node_ += other.size();
    transfer(pos, other.begin(), other.end());
  }

  void splice(const_iterator pos, list&& other) { splice(pos, other); }

  void splice(const_iterator pos, list& other, const_iterator it) {
    if (this != &other) ++count_node_;
    if (it != pos) transfer(pos, it, std::next(it));
  }

  void splice(const_iterator pos, list&& other, const_iterator it) {
    splice(pos, other, it);
  }

  void splice(const_iterator pos, list& other, const_iterator first, const_iterator last) {
    if (this != &other) count_node_ += std::distance(first, last);
    transfer(pos, first, last);
  }

  void splice(const_iterator pos, list&& other, const_iterator first, const_iterator last) {
    splice(pos, other, first, last);
  }

  /**************************************
   *                                    *
   *               merge                *
   *                                    *
   **************************************/

  template <typename Compare>
  void merge(list& other, Compare comp) {
    if (this == &other) return;
    count_node_ += other.size();

    auto first1 = begin();
    auto  last1 = end();
    auto first2 = other.begin();
    auto  last2 = other.end();

    while (first1 != last1 && first2 != last2) {
      if (comp(*first2, *first1)) {
        auto it = std::next(first2);
        transfer(first1, first2, it);
        first2 = it;
      } else {
        ++first1;
      }
    }
    if (first2 != last2) transfer(first1, first2, last2);
  }

  template <typename Compare>
  void merge(list&& other, Compare comp) {
    merge(other, comp);
  }
  void merge(list&  other) { merge(other, std::less<T>()); }
  void merge(list&& other) { merge(other); }

  /******************************************
   *                                        *
   *              reverse                   *
   *                                        *
   ******************************************/
  // just swap prev_ and next_ for each node

  void reverse() {
    if (size() <= 1) return;
    std::swap(node_->prev_, node_->next_);
    auto it = node_->prev_;
    while (it != node_) {
      std::swap(it->prev_, it->next_);
      it = it->prev_;
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
    if (size() <= 1) return;
    list temp[64];  // 2^64 - 1
    list carry;
    size_type n = 0;
    while (!empty()) {
      carry.splice(carry.begin(), *this, begin());
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
  using list_node_allocator = typename Allocator::template rebind<detail::list_node<T>>::other;

  list_node_allocator alloc;

  detail::list_node<T>* node_ = nullptr;
  size_type count_node_ = 0;

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

  detail::list_node<T>* allocate_node() { return alloc.allocate(1); }

  void deallocate_node(detail::list_node<T>* p) { alloc.deallocate(p, 1); }

  detail::list_node<T>* create_node(const T& value) {
    auto new_node = allocate_node();
    alloc.construct(&new_node->data_, value);
    return new_node;
  }

  detail::list_node<T>* create_node(T&& value) {
    auto new_node = allocate_node();
    alloc.construct(&new_node->data_, std::move(value));
    return new_node;
  }

  void destroy_node(detail::list_node<T>* p) {
    alloc.destroy(&p->data_);
    deallocate_node(p);
  }

  /******************************************
   *                                        *
   *                 transfer               *
   *                                        *
   ******************************************/

  void transfer(const_iterator pos, const_iterator first, const_iterator last) {
    if (first == last || pos == last) return;
    auto pos_node = pos.node_;
    auto first_node = first.node_;
    auto last_node = last.node_->prev_;

    first_node->prev_->next_ = last_node->next_;
    last_node->next_->prev_ = first_node->prev_;

    last_node->next_ = pos_node;
    first_node->prev_ = pos_node->prev_;
    first_node->prev_->next_ = first_node;
    last_node->next_->prev_ = last_node;
  }

  /**************************************
   *                                    *
   *            insert_aux              *
   *                                    *
   **************************************/

  template <typename Y>
  iterator insert_aux(const_iterator pos, Y&& value) {
    auto current_node = pos.node_;
    auto new_node = create_node(std::forward<Y>(value));
    new_node->next_ = current_node;
    new_node->prev_ = current_node->prev_;
    new_node->prev_->next_ = new_node->next_->prev_ = new_node;
    ++count_node_;
    return static_cast<iterator>(new_node);
  }

  /**************************************
   *                                    *
   *         insert_range_aux           *
   *                                    *
   **************************************/

  template <typename InputIt>
  iterator insert_range_aux(const_iterator pos, InputIt first, InputIt last, std::true_type) {
    return insert(pos, static_cast<size_type>(first), static_cast<T>(last));
  }

  template <typename InputIt>
  iterator insert_range_aux(const_iterator pos, InputIt first, InputIt last, std::false_type) {
    if (first == last) return static_cast<iterator>(pos.node_);
    auto temp = insert(pos, *first);
    while (++first != last) insert(pos, *first);
    return static_cast<iterator>(temp.node_);
  }

  /******************************************
   *                                        *
   *             delete_list                *
   *                                        *
   ******************************************/

  void delete_list() {
    if (node_ == nullptr) return;
    clear();
    deallocate_node(node_);
    node_ = nullptr;
    count_node_ = 0;
  }

  /*******************************************
   *                                         *
   *            move_from                    *
   *                                         *
   *******************************************/

  void move_from(list& other) {
    delete_list();
    node_ = other.node_;
    count_node_ = other.count_node_;
    other.node_ = nullptr;
    other.count_node_ = 0;
  }

};  // class list

/*****************************
 *                           *
 *          swap             *
 *                           *
 *****************************/

template <typename T, typename Allocator>
void swap(list<T, Allocator>& left, list<T, Allocator>& right) {
  left.swap(right);
}

/************************************
 *                                  *
 *     ==   !=   <   <=   >   >=    *
 *                                  *
 ************************************/

template <typename T, typename Allocator>
bool operator==(const list<T, Allocator>& left, const list<T, Allocator>& right) {
  return left.size() == right.size() && std::equal(left.cbegin(), left.cend(), right.begin());
}

template <typename T, typename Allocator>
bool operator!=(const list<T, Allocator>& left, const list<T, Allocator>& right) {
  return left.size() != right.size() || !std::equal(left.cbegin(), left.cend(), right.begin());
}

template <typename T, typename Allocator>
bool operator<(const list<T, Allocator>& left, const list<T, Allocator>& right) {
  return std::lexicographical_compare(left.cbegin(), left.cend(), right.cbegin(), right.cend());
}

template <typename T, typename Allocator>
bool operator<=(const list<T, Allocator>& left, const list<T, Allocator>& right) {
  return !(right < left);
}

template <typename T, typename Allocator>
bool operator>(const list<T, Allocator>& left, const list<T, Allocator>& right) {
  return right < left;
}

template <typename T, typename Allocator>
bool operator>=(const list<T, Allocator>& left, const list<T, Allocator>& right) {
  return !(left < right);
}

}  // namespace liuyunbin

#endif
