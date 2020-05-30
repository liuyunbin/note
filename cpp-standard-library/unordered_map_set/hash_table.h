#ifndef CPP_STANDARD_LIBRARY_HASH_TABLE_H_
#define CPP_STANDARD_LIBRARY_HASH_TABLE_H_

#include <iostream>
#include <iterator>
#include <initializer_list>
#include <limits>
#include <vector>

namespace liuyunbin {

namespace detail {

/********************************************
 *                                          *
 *           hash_table_node                *
 *                                          *
 ********************************************/

template <typename T>
struct hash_table_node {
  T data_;
  hash_table_node* next_;
};

/********************************************
 *                                          *
 *           hash_table_iterator            *
 *                                          *
 ********************************************/

template <typename Key, typename Value, typename Hash, typename KeyOfValue,
          typename KeyEqual, typename Allocator = std::allocator<Value>>
class hash_table;

template <typename Key, typename Value, typename Ref, typename Ptr,
          typename Hash, typename KeyOfValue, typename KeyEqual,
          typename Allocator>
struct hash_table_iterator {
  using        value_type = Value;
  using         reference = Ref;
  using           pointer = Ptr;
  using   difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;

  using       iterator = hash_table_iterator<Key, Value,       Value&,       Value*, Hash, KeyOfValue, KeyEqual, Allocator>;
  using const_iterator = hash_table_iterator<Key, Value, const Value&, const Value*, Hash, KeyOfValue, KeyEqual, Allocator>;
  using  self_iterator = hash_table_iterator<Key, Value,          Ref,          Ptr, Hash, KeyOfValue, KeyEqual, Allocator>;

  using hash_table_type = hash_table<Key, Value, Hash, KeyOfValue, KeyEqual, Allocator>;

  hash_table_node<Value>* node_;
  const hash_table_type* ht_;

  hash_table_iterator() : node_(nullptr), ht_(nullptr) {}

  hash_table_iterator(hash_table_node<Value>* node, const hash_table_type* ht)
      : node_(node), ht_(ht) {}

  hash_table_iterator(const iterator& other)
      : node_(other.node_), ht_(other.ht_) {}

  reference operator*() const { return   node_->data_; }
  pointer  operator->() const { return &(operator*()); }

  self_iterator& operator=(const iterator& other) {
    node_ = other.node_;
    ht_ = other.ht_;
    return *this;
  }

  self_iterator& operator++();
  self_iterator  operator++(int);

  bool operator==(const       iterator& right) const { return node_ == right.node_; }
  bool operator==(const const_iterator& right) const { return node_ == right.node_; }
  bool operator!=(const       iterator& right) const { return node_ != right.node_; }
  bool operator!=(const const_iterator& right) const { return node_ != right.node_; }
};

/********************************************
 *                                          *
 *               hash_table                 *
 *                                          *
 ********************************************/

template <typename Key, typename Value, typename Hash, typename KeyOfValue,
          typename KeyEqual, typename Allocator>
class hash_table {
  friend struct hash_table_iterator<Key, Value,       Value&,       Value*, Hash, KeyOfValue, KeyEqual, Allocator>;
  friend struct hash_table_iterator<Key, Value, const Value&, const Value*, Hash, KeyOfValue, KeyEqual, Allocator>;

 public:
  using        key_type = Key;
  using      value_type = Value;
  using  allocator_type = Allocator;
  using       size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using       reference = value_type&;
  using const_reference = const value_type&;
  using         pointer = value_type*;
  using   const_pointer = const value_type*;

  using    hasher = Hash;
  using key_equal = KeyEqual;

  using       iterator = hash_table_iterator<Key, Value,       Value&,       Value*, Hash, KeyOfValue, KeyEqual, Allocator>;
  using const_iterator = hash_table_iterator<Key, Value, const Value&, const Value*, Hash, KeyOfValue, KeyEqual, Allocator>;

  /***********************************
   *                                 *
   *         constructor             *
   *                                 *
   ***********************************/

  hash_table(size_type n = 100, const Hash& hash = Hash(), const KeyEqual& equals = KeyEqual())
      : hash_(hash), equals_(equals), buckets_(n, nullptr), num_elements_(0) {}

  hash_table(      hash_table&& other) { move_from(other); }
  hash_table(const hash_table&  other) { copy_from(other); }

  /**************************************
   *                                    *
   *           destructor               *
   *                                    *
   **************************************/

  ~hash_table() { delete_hash_table(); }

  /***********************************
   *                                 *
   *         begin     end           *
   *                                 *
   *        cbegin    cend           *
   *                                 *
   ***********************************/

  iterator begin() {
    for (size_type i = 0; i != buckets_.size(); ++i)
      if (buckets_[i] != nullptr) return iterator(buckets_[i], this);
    return iterator(nullptr, this);
  }

  const_iterator begin() const {
    for (size_type i = 0; i != buckets_.size(); ++i)
      if (buckets_[i] != nullptr) return const_iterator(buckets_[i], this);
    return const_iterator(nullptr, this);
  }

  const_iterator cbegin() const { return begin(); }

        iterator  end()       { return       iterator(nullptr, this); }
  const_iterator  end() const { return const_iterator(nullptr, this); }
  const_iterator cend() const { return const_iterator(nullptr, this); }

  /************************************
   *                                  *
   *             size                 *
   *                                  *
   *             empty                *
   *                                  *
   *             max_size             *
   *                                  *
   ************************************/

  size_type size() const { return num_elements_; }

  bool empty() const { return size() == 0; }

  size_type max_size() const { return std::numeric_limits<size_type>::max(); }

  /*************************************
   *                                   *
   *               =                   *
   *                                   *
   *************************************/

  hash_table& operator=(hash_table&& other) {
    if (this != &other) move_from(other);
    return *this;
  }

  hash_table& operator=(const hash_table& other) {
    if (this != &other) copy_from(other);
    return *this;
  }

  /*************************************
   *                                   *
   *             find                  *
   *                                   *
   *************************************/

  iterator find(const key_type& k) {
    auto index = bkt_num(k);
    for (auto cur = buckets_[index]; cur != nullptr; cur = cur->next_)
      if (equals_(KeyOfValue()(cur->data_), k)) return iterator(cur, this);
    return iterator(nullptr, this);
  }

  const_iterator find(const key_type& k) const {
    auto index = bkt_num(k);
    for (auto cur = buckets_[index]; cur != nullptr; cur = cur->next_)
      if (equals_(KeyOfValue()(cur->data_), k))
        return const_iterator(cur, this);
    return const_iterator(nullptr, this);
  }

  /*************************************
   *                                   *
   *           equal_range             *
   *                                   *
   *************************************/

  std::pair<iterator, iterator> equal_range(const key_type& k) {
    auto first = find(k);
    auto last = first;
    while (last != end() && equals_(k, KeyOfValue()(*last))) ++last;
    return {first, last};
  }

  std::pair<const_iterator, const_iterator> equal_range(
      const key_type& k) const {
    auto first = find(k);
    auto last = first;
    while (last != end() && equals_(k, KeyOfValue()(*last))) ++last;
    return {first, last};
  }

  /*************************************
   *                                   *
   *          count                    *
   *                                   *
   *************************************/

  size_type count(const key_type& k) const {
    auto temp = equal_range(k);
    return std::distance(temp.first, temp.second);
  }

  /*************************************
   *                                   *
   *           insert_equal            *
   *                                   *
   *          emplace_equal            *
   *                                   *
   *           insert_unique           *
   *                                   *
   *          emplace_unique           *
   *                                   *
   *************************************/

  iterator insert_equal(const value_type& value) {
    return insert_equal_aux(value);
  }

  iterator insert_equal(value_type&& value) {
    return insert_equal_aux(std::move(value));
  }

  template <typename InputIt>
  void insert_equal(InputIt first, InputIt last) {
    while (first != last) insert_equal(*first++);
  }

  void insert_equal(std::initializer_list<value_type> ilist) {
    for (auto it = ilist.begin(); it != ilist.end(); ++it) insert_equal(*it);
  }

  template <typename... Args>
  iterator emplace_equal(Args&&... args) {
    return insert_equal(value_type(std::forward<Args>(args)...));
  }

  std::pair<iterator, bool> insert_unique(const value_type& value) {
    return insert_unique_aux(value);
  }
  std::pair<iterator, bool> insert_unique(value_type&& value) {
    return insert_unique_aux(std::move(value));
  }

  template <typename InputIt>
  void insert_unique(InputIt first, InputIt last) {
    while (first != last) insert_unique(*first++);
  }

  void insert_unique(std::initializer_list<value_type> ilist) {
    for (auto it = ilist.begin(); it != ilist.end(); ++it) insert_unique(*it);
  }

  template <typename... Args>
  std::pair<iterator, bool> emplace_unique(Args&&... args) {
    return insert_unique(value_type(std::forward<Args>(args)...));
  }

  /********************************************
   *                                          *
   *               erase                      *
   *                                          *
   *               clear                      *
   *                                          *
   ********************************************/

  iterator erase(const_iterator pos) {
    auto return_iterator = iterator(pos.node_, this);
    ++return_iterator;
    --num_elements_;

    auto index = bkt_num(KeyOfValue()(*pos));
    if (pos.node_ == buckets_[index]) {
      buckets_[index] = (pos.node_)->next_;
      destroy_node(pos.node_);
      return return_iterator;
    }

    for (auto cur = buckets_[index]; cur->next_ != nullptr; cur = cur->next_)
      if (cur->next_ == pos.node_) {
        cur->next_ = (pos.node_)->next_;
        destroy_node(pos.node_);
        return return_iterator;
      }
    return return_iterator;
  }

  iterator erase(const_iterator first, const_iterator last) {
    while (first != last) first = erase(first);
    return iterator(first.node_, this);
  }

  size_type erase(const key_type& key) {
    size_type count = 0;
    auto it = find(key);
    while (it != end() && equals_(key, KeyOfValue()(*it))) {
      it = erase(it);
      ++count;
    }
    return count;
  }

  void clear() { erase(cbegin(), cend()); }

  /***************************************************
   *                                                 *
   *                 swap                            *
   *                                                 *
   ***************************************************/

  void swap(hash_table& other) {
    using std::swap;
    swap(hash_, other.hash_);
    swap(equals_, other.equals_);
    swap(buckets_, other.buckets_);
    swap(num_elements_, other.num_elements_);
  }

  /******************************************
   *                                        *
   *              bucket_count              *
   *                                        *
   *          max_bucket_count              *
   *                                        *
   *              bucket_size               *
   *                                        *
   *                                        *
   ******************************************/

  size_type bucket_count() const { return buckets_.size(); }
  size_type max_bucket_count() const { return buckets_.max_size(); }

  size_type bucket_size(size_type n) const {
    size_type count = 0;
    for (auto cur = buckets_[n]; cur != nullptr; cur = cur->next_) ++count;
    return count;
  }

  size_type bucket(const key_type& k) const { return bkt_num(k); }

  /******************************************
   *                                        *
   *             hash_function              *
   *                                        *
   *             key_eq                     *
   *                                        *
   ******************************************/

  hasher hash_function() const { return hash_; }
  key_equal key_eq() const { return equals_; }

 private:
  hasher hash_;
  key_equal equals_;

  using hash_table_node_allocator =
      typename Allocator::template rebind<hash_table_node<value_type>>::other;
  using hash_table_node_pointer_allocator =
      typename Allocator::template rebind<hash_table_node<value_type>*>::other;

  hash_table_node_allocator alloc;

  std::vector<hash_table_node<value_type>*, hash_table_node_pointer_allocator> buckets_;

  size_type num_elements_;

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

  hash_table_node<value_type>* allocate_node() { return alloc.allocate(1); }

  void deallocate_node(hash_table_node<value_type>* p) {
    alloc.deallocate(p, 1);
  }

  hash_table_node<value_type>* create_node(const value_type& value) {
    auto new_node = allocate_node();
    alloc.construct(&new_node->data_, value);
    return new_node;
  }

  hash_table_node<value_type>* create_node(value_type&& value) {
    auto new_node = allocate_node();
    alloc.construct(&new_node->data_, std::move(value));
    return new_node;
  }

  void destroy_node(hash_table_node<value_type>* p) {
    alloc.destroy(&p->data_);
    deallocate_node(p);
  }

  /*************************************************
   *                                               *
   *                    bkt_num                    *
   *                                               *
   *************************************************/

  size_type bkt_num(const key_type& k, size_type n) const {
    return hash_(k) % n;
  }
  
  size_type bkt_num(const key_type& k) const {
    return bkt_num(k, bucket_count());
  }

  /**************************************************
   *                                                *
   *                    resize                      *
   *                                                *
   **************************************************/

  void resize(size_type new_num_elements) {
    if (new_num_elements <= buckets_.size()) return;
    size_type new_size =
        buckets_.size() + std::max(new_num_elements, buckets_.size());
    decltype(buckets_) temp(new_size, nullptr);
    for (size_type i = 0; i != buckets_.size(); ++i) {
      auto first = buckets_[i];
      while (first != nullptr) {
        auto new_index = bkt_num(KeyOfValue()(first->data_), new_size);
        buckets_[i] = first->next_;
        first->next_ = temp[new_index];
        temp[new_index] = first;
        first = buckets_[i];
      }
    }
    temp.swap(buckets_);
  }

  /**************************************************
   *                                                *
   *              insert_equal_aux                  *
   *                                                *
   **************************************************/

  template <typename Y>
  iterator insert_equal_aux(Y&& value) {
    resize(num_elements_ + 1);

    auto index = bkt_num(KeyOfValue()(value));
    for (auto cur = buckets_[index]; cur != nullptr; cur = cur->next_)
      if (equals_(KeyOfValue()(value), KeyOfValue()(cur->data_))) {
        auto new_node = create_node(std::forward<Y>(value));
        new_node->next_ = cur->next_;
        cur->next_ = new_node;
        ++num_elements_;
        return iterator(new_node, this);
      }
    auto new_node = create_node(std::forward<Y>(value));
    new_node->next_ = buckets_[index];
    buckets_[index] = new_node;
    ++num_elements_;
    return iterator(new_node, this);
  }

  /**************************************************
   *                                                *
   *              insert_unique_aux                 *
   *                                                *
   **************************************************/

  template <typename Y>
  std::pair<iterator, bool> insert_unique_aux(Y&& value) {
    resize(num_elements_ + 1);

    auto index = bkt_num(KeyOfValue()(value));
    for (auto cur = buckets_[index]; cur != nullptr; cur = cur->next_)
      if (equals_(KeyOfValue()(value), KeyOfValue()(cur->data_)))
        return {iterator(cur, this), false};
    auto new_node = create_node(std::forward<Y>(value));
    new_node->next_ = buckets_[index];
    buckets_[index] = new_node;
    ++num_elements_;
    return {iterator(new_node, this), true};
  }

  /*************************************************
   *                                               *
   *             delete_hash_table                 *
   *                                               *
   *************************************************/

  void delete_hash_table() { clear(); }

  /**************************************************
   *                                                *
   *             move_from                          *
   *                                                *
   **************************************************/

  void move_from(hash_table& other) {
    delete_hash_table();

    hash_ = other.hash_;
    equals_ = other.equals_;
    buckets_ = std::move(other.buckets_);
    num_elements_ = other.num_elements_;
  }

  /**************************************************
   *                                                *
   *             copy_from                          *
   *                                                *
   **************************************************/

  void copy_from(const hash_table& other) {
    delete_hash_table();

    hash_ = other.hash_;
    equals_ = other.equals_;
    num_elements_ = other.num_elements_;
    buckets_.reserve(other.bucket_count());
    buckets_.resize(other.bucket_count(), nullptr);
    for (size_type i = 0; i != other.bucket_count(); ++i) {
      auto cur = other.buckets_[i];
      if (cur != nullptr) {
        auto copy = create_node(cur->data_);
        buckets_[i] = copy;
        for (cur = cur->next_; cur != nullptr; cur = cur->next_)
          copy = copy->next_ = create_node(cur->data_);
        copy->next_ = nullptr;
      }
    }
  }
};

/**************************************************
 *                                                *
 *         hash_table_iterator     ++             *
 *                                                *
 **************************************************/

template <typename Key, typename Value, typename Ref, typename Ptr,
          typename Hash, typename KeyOfValue, typename KeyEqual,
          typename Allocator>
typename hash_table_iterator<Key, Value, Ref, Ptr, Hash, KeyOfValue, KeyEqual,
                             Allocator>::self_iterator&
hash_table_iterator<Key, Value, Ref, Ptr, Hash, KeyOfValue, KeyEqual,
                    Allocator>::operator++() {
  auto old = node_;
  node_ = node_->next_;
  if (node_ == nullptr) {
    auto index = ht_->bucket(KeyOfValue()(old->data_));
    while (node_ == nullptr && ++index < ht_->bucket_count())
      node_ = ht_->buckets_[index];
  }
  return *this;
}

template <typename Key, typename Value, typename Ref, typename Ptr,
          typename Hash, typename KeyOfValue, typename KeyEqual,
          typename Allocator>
typename hash_table_iterator<Key, Value, Ref, Ptr, Hash, KeyOfValue, KeyEqual,
                             Allocator>::self_iterator
hash_table_iterator<Key, Value, Ref, Ptr, Hash, KeyOfValue, KeyEqual,
                    Allocator>::operator++(int) {
  auto temp = *this;
  ++*this;
  return temp;
}

}  // namespace detail

}  // namespace liuyunbin

#endif
