#ifndef CPP_STANDARD_LIBRARY_UNORDERED_MAP_SET_H_
#define CPP_STANDARD_LIBRARY_UNORDERED_MAP_SET_H_

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

/***********************************************
 *                                             *
 *              unordered_map                  *
 *                                             *
 ***********************************************/

template <typename Key, typename T, typename Hash = std::hash<Key>,
          typename KeyEqual = std::equal_to<Key>,
          typename Allocator = std::allocator<std::pair<const Key, T>>>
class unordered_map {
 public:
  using allocator_type = Allocator;
  using       key_type = Key;
  using    mapped_type = T;
  using     value_type = std::pair<const Key, T>;

 private:
   struct fun {
     Key operator()(const value_type &ve) { return ve.first; }
   };

   using hash_table_type =
       detail::hash_table<key_type, value_type, Hash, fun, KeyEqual, Allocator>;

   hash_table_type t_;

 public:
  using          hasher = typename hash_table_type::hasher;
  using       key_equal = typename hash_table_type::key_equal;

  using       size_type = typename hash_table_type::size_type;
  using difference_type = typename hash_table_type::difference_type;
  using       reference = typename hash_table_type::reference;
  using const_reference = typename hash_table_type::const_reference;
  using         pointer = typename hash_table_type::pointer;
  using   const_pointer = typename hash_table_type::const_pointer;
  using        iterator = typename hash_table_type::iterator;
  using  const_iterator = typename hash_table_type::const_iterator;

 public:
  /************************************************************
   *                                                          *
   *                       construct                          *
   *                                                          *
   ************************************************************/

  unordered_map() {}

  explicit unordered_map(const size_type& n, const Hash& hash = Hash(), const KeyEqual& equal = KeyEqual())
      : t_(n, hash, equal) {}

  unordered_map(const unordered_map& other) : t_(other.t_) {}
  unordered_map(unordered_map&& other) noexcept
      : t_(std::move(other.t_)) {}

  template <typename InputIt>
  unordered_map(InputIt first, InputIt last, const size_type& n = 100,
                const Hash& hash = Hash(), const KeyEqual& equal = KeyEqual())
      : t_(n, hash, equal) {
    t_.insert_unique(first, last);
  }

  unordered_map(std::initializer_list<value_type> ilist,
                const size_type& n = 100, const Hash& hash = Hash(),
                const KeyEqual& equal = KeyEqual())
      : t_(n, hash, equal) {
    t_.insert_unique(ilist.begin(), ilist.end());
  }

  /************************************************************
   *                                                          *
   *                       destruct                           *
   *                                                          *
   ************************************************************/

  ~unordered_map() {}

  /************************************************************
   *                                                          *
   *                      begin                               *
   *                     cbegin                               *
   *                                                          *
   *                        end                               *
   *                       cend                               *
   *                                                          *
   ************************************************************/

        iterator  begin()       { return t_.begin(); }
  const_iterator  begin() const { return t_.begin(); }
  const_iterator cbegin() const { return t_.cbegin(); }

        iterator  end()       { return t_.end(); }
  const_iterator  end() const { return t_.end(); }
  const_iterator cend() const { return t_.cend(); }

  /*************************************************
   *                                               *
   *                   empty                       *
   *                   size                        *
   *                   max_size                    *
   *                                               *
   *************************************************/

  bool empty() const { return t_.empty(); }

  size_type size() const { return t_.size(); }

  size_type max_size() const { return t_.max_size(); }

  /************************************************************
   *                                                          *
   *                       swap                               *
   *                                                          *
   ************************************************************/

  void swap(unordered_map& other) { t_.swap(other.t_); }

  /******************************************************
   *                                                    *
   *                   insert                           *
   *                                                    *
   *                   emplace                          *
   *                                                    *
   ******************************************************/

  std::pair<iterator, bool> insert(const value_type& value) {
    return t_.insert_unique(value);
  }

  std::pair<iterator, bool> insert(value_type&& value) {
    return t_.insert_unique(std::move(value));
  }

  template <typename Y>
  std::pair<iterator, bool> insert(Y&& value) {
    return t_.insert_unique(std::forward<Y>(value));
  }

  template <typename InputIt>
  void insert(InputIt first, InputIt last) {
    t_.insert_unique(first, last);
  }

  void insert(std::initializer_list<value_type> ilist) {
    t_.insert_unique(ilist.begin(), ilist.end());
  }

  template <typename... Args>
  std::pair<iterator, bool> emplace(Args&&... args) {
    return t_.emplace_unique(std::forward<Args>(args)...);
  }

  /**********************************************
   *                                            *
   *                    erase                   *
   *                                            *
   *                    clear                   *
   *                                            *
   **********************************************/

  iterator erase(const_iterator first, const_iterator last) {
    return t_.erase(first, last);
  }

  iterator erase(const_iterator p) { return t_.erase(p); }
  size_type erase(const key_type& key) { return t_.erase(key); }

  void clear() { t_.clear(); }

  /*****************************************
   *                                       *
   *          []         at                *
   *                                       *
   *****************************************/

  T& operator[](const key_type& k) {
    auto it = emplace(k, T()).first;
    return it->second;
  }

  T& operator[](key_type&& k) { return operator[](k); }

        T& at(const key_type& k)       { return find(k)->second; }
  const T& at(const key_type& k) const { return find(k)->second; }

  /****************************************
   *                                      *
   *                =                     *
   *                                      *
   ****************************************/

  unordered_map& operator=(unordered_map&& other) noexcept {
    t_ = std::move(other.t_);
    return *this;
  }

  unordered_map& operator=(const unordered_map& other) {
    t_ = other.t_;
    return *this;
  }

  unordered_map& operator=(std::initializer_list<value_type> ilist) {
    return *this = unordered_map(ilist);
  }

  /********************************************
   *                                          *
   *              count                       *
   *                                          *
   *              find                        *
   *                                          *
   ********************************************/

      size_type count(const key_type& key) const { return t_.count(key); }
        iterator find(const key_type& key)       { return t_.find(key); }
  const_iterator find(const key_type& key) const { return t_.find(key); }

  /*********************************************
   *                                           *
   *                equal_range                *
   *                                           *
   *                                           *
   *********************************************/

  std::pair<iterator, iterator> equal_range(const key_type& key) {
    return t_.equal_range(key);
  }

  std::pair<const_iterator, const_iterator> equal_range(
      const key_type& key) const {
    return t_.equal_range(key);
  }

  /**********************************************
   *                                            *
   *                 bucket_count               *
   *                                            *
   *             max_bucket_count               *
   *                                            *
   *                 bucket_size                *
   *                                            *
   *                 bucket                     *
   *                                            *
   **********************************************/

  size_type     bucket_count() const { return t_.bucket_count(); }
  size_type nax_bucket_count() const { return t_.max_bucket_count(); }

  size_type bucket_size(size_type n) const { return t_.bucket_size(n); }
  size_type bucket(const key_type& k) const { return t_.bucket(k); }

  /***********************************************
   *                                             *
   *               hash_funcion                  *
   *                                             *
   *               key_eq                        *
   *                                             *
   ***********************************************/

  hasher hash_function() const { return t_.hash_function(); }
  key_equal key_eq() const { return t_.key_eq(); }

};  // class unordered_map

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

template <typename Key, typename T, typename Hash, typename KeyEqual, typename Allocator>
void swap(unordered_map<Key, T, Hash, KeyEqual, Allocator>& left, unordered_map<Key, T, Hash, KeyEqual, Allocator>& right) {
  left.swap(right);
}

/************************************************************
 *                                                          *
 *                 ==          !=                           *
 *                                                          *
 ************************************************************/

template <typename Key, typename T, typename Hash, typename KeyEqual, typename Allocator>
bool operator==(const unordered_map<Key, T, Hash, KeyEqual, Allocator>& left,
                const unordered_map<Key, T, Hash, KeyEqual, Allocator>& right) {
  return left.size() == right.size() && std::equal(left.cbegin(), left.cend(), right.cbegin());
}

template <typename Key, typename T, typename Hash, typename KeyEqual, typename Allocator>
bool operator!=(const unordered_map<Key, T, Hash, KeyEqual, Allocator>& left,
                const unordered_map<Key, T, Hash, KeyEqual, Allocator>& right) {
  return left.size() != right.size() || !std::equal(left.cbegin(), left.cend(), right.cbegin());
}

/***********************************************
 *                                             *
 *            unordered_multimap               *
 *                                             *
 ***********************************************/

template <typename Key, typename T, typename Hash = std::hash<Key>,
          typename KeyEqual = std::equal_to<Key>,
          typename Allocator = std::allocator<std::pair<const Key, T>>>
class unordered_multimap {
 public:
  using   allocator_type = Allocator;
  using         key_type = Key;
  using multimapped_type = T;
  using       value_type = std::pair<const Key, T>;

 private:
   struct fun {
     Key operator()(const value_type &ve) { return ve.first; }
   };

   using hash_table_type =
       detail::hash_table<key_type, value_type, Hash, fun, KeyEqual, Allocator>;

   hash_table_type t_;

 public:
  using    hasher = typename hash_table_type::hasher;
  using key_equal = typename hash_table_type::key_equal;

  using       size_type = typename hash_table_type::size_type;
  using difference_type = typename hash_table_type::difference_type;
  using       reference = typename hash_table_type::reference;
  using const_reference = typename hash_table_type::const_reference;
  using         pointer = typename hash_table_type::pointer;
  using   const_pointer = typename hash_table_type::const_pointer;
  using        iterator = typename hash_table_type::iterator;
  using  const_iterator = typename hash_table_type::const_iterator;

 public:
  /************************************************************
   *                                                          *
   *                       construct                          *
   *                                                          *
   ************************************************************/

  unordered_multimap() {}

  explicit unordered_multimap(const size_type& n, const Hash& hash = Hash(),
                              const KeyEqual& equal = KeyEqual())
      : t_(n, hash, equal) {}

  unordered_multimap(const unordered_multimap& other) : t_(other.t_) {}
  unordered_multimap(unordered_multimap&& other) noexcept
      : t_(std::move(other.t_)) {}

  template <typename InputIt>
  unordered_multimap(InputIt first, InputIt last, const size_type& n = 100,
                     const Hash& hash = Hash(),
                     const KeyEqual& equal = KeyEqual())
      : t_(n, hash, equal) {
    t_.insert_equal(first, last);
  }

  unordered_multimap(std::initializer_list<value_type> ilist,
                     const size_type& n = 100, const Hash& hash = Hash(),
                     const KeyEqual& equal = KeyEqual())
      : t_(n, hash, equal) {
    t_.insert_equal(ilist.begin(), ilist.end());
  }

  /************************************************************
   *                                                          *
   *                       destruct                           *
   *                                                          *
   ************************************************************/

  ~unordered_multimap() {}

  /************************************************************
   *                                                          *
   *                      begin                               *
   *                     cbegin                               *
   *                                                          *
   *                        end                               *
   *                       cend                               *
   *                                                          *
   ************************************************************/

        iterator  begin()       { return t_.begin(); }
  const_iterator  begin() const { return t_.begin(); }
  const_iterator cbegin() const { return t_.cbegin(); }

        iterator  end()       { return t_.end(); }
  const_iterator  end() const { return t_.end(); }
  const_iterator cend() const { return t_.cend(); }

  /*************************************************
   *                                               *
   *                   empty                       *
   *                   size                        *
   *                   max_size                    *
   *                                               *
   *************************************************/

  bool empty() const { return t_.empty(); }

  size_type size() const { return t_.size(); }

  size_type max_size() const { return t_.max_size(); }

  /************************************************************
   *                                                          *
   *                       swap                               *
   *                                                          *
   ************************************************************/

  void swap(unordered_multimap& other) { t_.swap(other.t_); }

  /******************************************************
   *                                                    *
   *                   insert                           *
   *                                                    *
   *                   emplace                          *
   *                                                    *
   ******************************************************/

  iterator insert(const value_type& value) { return t_.insert_equal(value); }
  iterator insert(value_type&& value) {
    return t_.insert_equal(std::move(value));
  }

  template <typename Y>
  iterator insert(Y&& value) {
    return t_.insert_equal(std::forward<Y>(value));
  }

  template <typename InputIt>
  void insert(InputIt first, InputIt last) {
    t_.insert_equal(first, last);
  }

  void insert(std::initializer_list<value_type> ilist) {
    t_.insert_equal(ilist.begin(), ilist.end());
  }

  template <typename... Args>
  iterator emplace(Args&&... args) {
    return t_.emplace_equal(std::forward<Args>(args)...);
  }

  /**********************************************
   *                                            *
   *                    erase                   *
   *                                            *
   *                    clear                   *
   *                                            *
   **********************************************/

  iterator erase(const_iterator first, const_iterator last) {
    return t_.erase(first, last);
  }

   iterator erase(const_iterator p) { return t_.erase(p); }
  size_type erase(const key_type& key) { return t_.erase(key); }

  void clear() { t_.clear(); }

  /****************************************
   *                                      *
   *                =                     *
   *                                      *
   ****************************************/

  unordered_multimap& operator=(unordered_multimap&& other) noexcept {
    t_ = std::move(other.t_);
    return *this;
  }

  unordered_multimap& operator=(const unordered_multimap& other) {
    t_ = other.t_;
    return *this;
  }

  unordered_multimap& operator=(std::initializer_list<value_type> ilist) {
    return *this = unordered_multimap(ilist);
  }

  /********************************************
   *                                          *
   *              count                       *
   *                                          *
   *              find                        *
   *                                          *
   ********************************************/

      size_type count(const key_type& key) const { return t_.count(key); }
        iterator find(const key_type& key)       { return t_.find(key); }
  const_iterator find(const key_type& key) const { return t_.find(key); }

  /*********************************************
   *                                           *
   *                equal_range                *
   *                                           *
   *                                           *
   *********************************************/

  std::pair<iterator, iterator> equal_range(const key_type& key) {
    return t_.equal_range(key);
  }

  std::pair<const_iterator, const_iterator> equal_range(
      const key_type& key) const {
    return t_.equal_range(key);
  }

  /**********************************************
   *                                            *
   *                 bucket_count               *
   *                                            *
   *             max_bucket_count               *
   *                                            *
   *                 bucket_size                *
   *                                            *
   *                 bucket                     *
   *                                            *
   **********************************************/

  size_type     bucket_count() const { return t_.bucket_count(); }
  size_type nax_bucket_count() const { return t_.max_bucket_count(); }

  size_type bucket_size(size_type n) const { return t_.bucket_size(n); }
  size_type bucket(const key_type& k) const { return t_.bucket(k); }

  /***********************************************
   *                                             *
   *               hash_funcion                  *
   *                                             *
   *               key_eq                        *
   *                                             *
   ***********************************************/

  hasher hash_function() const { return t_.hash_function(); }
  key_equal key_eq() const { return t_.key_eq(); }

};  // class unordered_multimap

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

template <typename Key, typename T, typename Hash, typename KeyEqual, typename Allocator>
void swap(unordered_multimap<Key, T, Hash, KeyEqual, Allocator>& left,
          unordered_multimap<Key, T, Hash, KeyEqual, Allocator>& right) {
  left.swap(right);
}

/************************************************************
 *                                                          *
 *                 ==          !=                           *
 *                                                          *
 ************************************************************/

template <typename Key, typename T, typename Hash, typename KeyEqual, typename Allocator>
bool operator==(const unordered_multimap<Key, T, Hash, KeyEqual, Allocator>& left,
                const unordered_multimap<Key, T, Hash, KeyEqual, Allocator>& right) {
  return left.size() == right.size() && std::equal(left.cbegin(), left.cend(), right.cbegin());
}

template <typename Key, typename T, typename Hash, typename KeyEqual, typename Allocator>
bool operator!=(const unordered_multimap<Key, T, Hash, KeyEqual, Allocator>& left,
                const unordered_multimap<Key, T, Hash, KeyEqual, Allocator>& right) {
  return left.size() != right.size() || !std::equal(left.cbegin(), left.cend(), right.cbegin());
}

/***********************************************
 *                                             *
 *            unordered_multiset               *
 *                                             *
 ***********************************************/

template <typename Key, typename Hash = std::hash<Key>,
          typename KeyEqual = std::equal_to<Key>,
          typename Allocator = std::allocator<Key>>
class unordered_multiset {
public:
  using allocator_type = Allocator;
  using       key_type = Key;
  using     value_type = Key;

 private:
   struct fun {
     Key operator()(const value_type &ve) { return ve; }
   };

   using hash_table_type =
       detail::hash_table<key_type, value_type, Hash, fun, KeyEqual, Allocator>;

   hash_table_type t_;

 public:
  using    hasher = typename hash_table_type::hasher;
  using key_equal = typename hash_table_type::key_equal;

  using       size_type = typename hash_table_type::size_type;
  using difference_type = typename hash_table_type::difference_type;
  using       reference = typename hash_table_type::const_reference;
  using const_reference = typename hash_table_type::const_reference;
  using         pointer = typename hash_table_type::const_pointer;
  using   const_pointer = typename hash_table_type::const_pointer;
  using        iterator = typename hash_table_type::const_iterator;
  using  const_iterator = typename hash_table_type::const_iterator;

 public:
  /************************************************************
   *                                                          *
   *                       construct                          *
   *                                                          *
   ************************************************************/

   unordered_multiset() {}

   explicit unordered_multiset(const size_type &n, const Hash &hash = Hash(),
                               const KeyEqual &equal = KeyEqual())
       : t_(n, hash, equal) {}

   unordered_multiset(const unordered_multiset &other) : t_(other.t_) {}
   unordered_multiset(unordered_multiset &&other) noexcept
       : t_(std::move(other.t_)) {}

   template <typename InputIt>
   unordered_multiset(InputIt first, InputIt last, const size_type &n = 100,
                      const Hash &hash = Hash(),
                      const KeyEqual &equal = KeyEqual())
       : t_(n, hash, equal) {
     t_.insert_equal(first, last);
   }

   unordered_multiset(std::initializer_list<Key> ilist,
                      const size_type &n = 100, const Hash &hash = Hash(),
                      const KeyEqual &equal = KeyEqual())
       : t_(n, hash, equal) {
     t_.insert_equal(ilist.begin(), ilist.end());
   }

  /************************************************************
   *                                                          *
   *                       destruct                           *
   *                                                          *
   ************************************************************/

   ~unordered_multiset() {}

   /************************************************************
    *                                                          *
    *                      begin                               *
    *                     cbegin                               *
    *                                                          *
    *                        end                               *
    *                       cend                               *
    *                                                          *
    ************************************************************/

   iterator begin() { return t_.cbegin(); }
   const_iterator begin() const { return t_.cbegin(); }
   const_iterator cbegin() const { return t_.cbegin(); }

   iterator end() { return t_.cend(); }
   const_iterator end() const { return t_.cend(); }
   const_iterator cend() const { return t_.cend(); }

   /*************************************************
    *                                               *
    *                   empty                       *
    *                   size                        *
    *                   max_size                    *
    *                                               *
    *************************************************/

   bool empty() const { return t_.empty(); }

   size_type size() const { return t_.size(); }

   size_type max_size() const { return t_.max_size(); }

   /************************************************************
    *                                                          *
    *                       swap                               *
    *                                                          *
    ************************************************************/

   void swap(unordered_multiset &other) { t_.swap(other.t_); }

   /******************************************************
    *                                                    *
    *                   insert                           *
    *                                                    *
    *                   emplace                          *
    *                                                    *
    ******************************************************/

   iterator insert(const value_type &value) { return t_.insert_equal(value); }
   iterator insert(value_type &&value) {
     return t_.insert_equal(std::move(value));
   }

  template <typename InputIt>
  void insert(InputIt first, InputIt last) {
    t_.insert_equal(first, last);
  }

  void insert(std::initializer_list<value_type> ilist) {
    t_.insert_equal(ilist.begin(), ilist.end());
  }

  template <typename... Args> iterator emplace(Args &&... args) {
    return t_.emplace_equal(std::forward<Args>(args)...);
  }

  /**********************************************
   *                                            *
   *                    erase                   *
   *                                            *
   *                    clear                   *
   *                                            *
   **********************************************/

  iterator erase(const_iterator first, const_iterator last) {
    return t_.erase(first, last);
  }

  iterator erase(const_iterator p) { return t_.erase(p); }
  size_type erase(const key_type& key) { return t_.erase(key); }

  void clear() { t_.clear(); }

  /****************************************
   *                                      *
   *                =                     *
   *                                      *
   ****************************************/

  unordered_multiset &operator=(unordered_multiset &&other) noexcept {
    t_ = std::move(other.t_);
    return *this;
  }
  unordered_multiset &operator=(const unordered_multiset &other) {
    t_ = other.t_;
    return *this;
  }
  unordered_multiset &operator=(std::initializer_list<value_type> ilist) {
    return *this = unordered_multiset(ilist);
  }

  /********************************************
   *                                          *
   *              count                       *
   *                                          *
   *              find                        *
   *                                          *
   ********************************************/

  size_type count(const key_type& key) const { return t_.count(key); }
  iterator find(const key_type& key) { return t_.find(key); }
  const_iterator find(const key_type& key) const { return t_.find(key); }

  /*********************************************
   *                                           *
   *                equal_range                *
   *                                           *
   *                                           *
   *********************************************/

  std::pair<iterator, iterator> equal_range(const key_type& key) {
    return t_.equal_range(key);
  }

  std::pair<const_iterator, const_iterator> equal_range(
      const key_type& key) const {
    return t_.equal_range(key);
  }

  /**********************************************
   *                                            *
   *                 bucket_count               *
   *                                            *
   *             max_bucket_count               *
   *                                            *
   *                 bucket_size                *
   *                                            *
   *                 bucket                     *
   *                                            *
   **********************************************/

  size_type     bucket_count() const { return t_.bucket_count(); }
  size_type nax_bucket_count() const { return t_.max_bucket_count(); }

  size_type bucket_size(size_type n) const { return t_.bucket_size(n); }
  size_type bucket(const key_type& k) const { return t_.bucket(k); }

  /***********************************************
   *                                             *
   *               hash_funcion                  *
   *                                             *
   *               key_eq                        *
   *                                             *
   ***********************************************/

  hasher hash_function() const { return t_.hash_function(); }
  key_equal key_eq() const { return t_.key_eq(); }

}; // class unordered_multiset

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

template <typename Key, typename Hash, typename KeyEqual, typename Allocator>
void swap(unordered_multiset<Key, Hash, KeyEqual, Allocator>& left,
          unordered_multiset<Key, Hash, KeyEqual, Allocator>& right) {
  left.swap(right);
}

/************************************************************
 *                                                          *
 *                 ==          !=                           *
 *                                                          *
 ************************************************************/

template <typename Key, typename Hash, typename KeyEqual, typename Allocator>
bool operator==(const unordered_multiset<Key, Hash, KeyEqual, Allocator>& left,
                const unordered_multiset<Key, Hash, KeyEqual, Allocator>& right) {
  return left.size() == right.size() && std::equal(left.cbegin(), left.cend(), right.cbegin());
}

template <typename Key, typename Hash, typename KeyEqual, typename Allocator>
bool operator!=(const unordered_multiset<Key, Hash, KeyEqual, Allocator>& left,
                const unordered_multiset<Key, Hash, KeyEqual, Allocator>& right) {
  return left.size() != right.size() || !std::equal(left.cbegin(), left.cend(), right.cbegin());
}

/***********************************************
 *                                             *
 *              unordered_set                  *
 *                                             *
 ***********************************************/

template <typename Key, typename Hash = std::hash<Key>,
          typename KeyEqual = std::equal_to<Key>,
          typename Allocator = std::allocator<Key>>
class unordered_set {
 public:
  using allocator_type = Allocator;
  using       key_type = Key;
  using     value_type = Key;

 private:
   struct fun {
     Key operator()(const value_type &ve) { return ve; }
   };

   using hash_table_type =
       detail::hash_table<key_type, value_type, Hash, fun, KeyEqual, Allocator>;

   hash_table_type t_;

 public:
  using    hasher = typename hash_table_type::hasher;
  using key_equal = typename hash_table_type::key_equal;

  using       size_type = typename hash_table_type::size_type;
  using difference_type = typename hash_table_type::difference_type;
  using       reference = typename hash_table_type::const_reference;
  using const_reference = typename hash_table_type::const_reference;
  using         pointer = typename hash_table_type::const_pointer;
  using   const_pointer = typename hash_table_type::const_pointer;
  using        iterator = typename hash_table_type::const_iterator;
  using  const_iterator = typename hash_table_type::const_iterator;

 public:
  /************************************************************
   *                                                          *
   *                       construct                          *
   *                                                          *
   ************************************************************/

  unordered_set() {}

  explicit unordered_set(const size_type& n, const Hash& hash = Hash(),
                         const KeyEqual& equal = KeyEqual())
      : t_(n, hash, equal) {}

  unordered_set(const unordered_set& other) : t_(other.t_) {}
  unordered_set(unordered_set&& other) noexcept
      : t_(std::move(other.t_)) {}

  template <typename InputIt>
  unordered_set(InputIt first, InputIt last, const size_type& n = 100,
                const Hash& hash = Hash(), const KeyEqual& equal = KeyEqual())
      : t_(n, hash, equal) {
    t_.insert_unique(first, last);
  }

  unordered_set(std::initializer_list<Key> ilist, const size_type& n = 100,
                const Hash& hash = Hash(), const KeyEqual& equal = KeyEqual())
      : t_(n, hash, equal) {
    t_.insert_unique(ilist.begin(), ilist.end());
  }

  /************************************************************
   *                                                          *
   *                       destruct                           *
   *                                                          *
   ************************************************************/

  ~unordered_set() {}

  /************************************************************
   *                                                          *
   *                      begin                               *
   *                     cbegin                               *
   *                                                          *
   *                        end                               *
   *                       cend                               *
   *                                                          *
   ************************************************************/

        iterator  begin()       { return t_.cbegin(); }
  const_iterator  begin() const { return t_.cbegin(); }
  const_iterator cbegin() const { return t_.cbegin(); }

        iterator  end()       { return t_.cend(); }
  const_iterator  end() const { return t_.cend(); }
  const_iterator cend() const { return t_.cend(); }

  /*************************************************
   *                                               *
   *                   empty                       *
   *                   size                        *
   *                   max_size                    *
   *                                               *
   *************************************************/

  bool empty() const { return t_.empty(); }

  size_type size() const { return t_.size(); }

  size_type max_size() const { return t_.max_size(); }

  /************************************************************
   *                                                          *
   *                       swap                               *
   *                                                          *
   ************************************************************/

  void swap(unordered_set& other) { t_.swap(other.t_); }

  /******************************************************
   *                                                    *
   *                   insert                           *
   *                                                    *
   *                   emplace                          *
   *                                                    *
   ******************************************************/

  std::pair<iterator, bool> insert(const value_type& value) {
    return t_.insert_unique(value);
  }

  std::pair<iterator, bool> insert(value_type&& value) {
    return t_.insert_unique(std::move(value));
  }

  template <typename InputIt>
  void insert(InputIt first, InputIt last) {
    t_.insert_unique(first, last);
  }

  void insert(std::initializer_list<value_type> ilist) {
    t_.insert_unique(ilist.begin(), ilist.end());
  }

  template <typename... Args>
  std::pair<iterator, bool> emplace(Args&&... args) {
    return t_.emplace_unique(std::forward<Args>(args)...);
  }

  /**********************************************
   *                                            *
   *                    erase                   *
   *                                            *
   *                    clear                   *
   *                                            *
   **********************************************/

  iterator erase(const_iterator first, const_iterator last) {
    return t_.erase(first, last);
  }

  iterator erase(const_iterator p) { return t_.erase(p); }
  size_type erase(const key_type& key) { return t_.erase(key); }

  void clear() { t_.clear(); }

  /****************************************
   *                                      *
   *                =                     *
   *                                      *
   ****************************************/

  unordered_set& operator=(unordered_set&& other) noexcept {
    t_ = std::move(other.t_);
    return *this;
  }
  unordered_set& operator=(const unordered_set& other) {
    t_ = other.t_;
    return *this;
  }
  unordered_set& operator=(std::initializer_list<value_type> ilist) {
    return *this = unordered_set(ilist);
  }

  /********************************************
   *                                          *
   *              count                       *
   *                                          *
   *              find                        *
   *                                          *
   ********************************************/

  size_type count(const key_type& key) const { return t_.count(key); }
  iterator find(const key_type& key) { return t_.find(key); }
  const_iterator find(const key_type& key) const { return t_.find(key); }

  /*********************************************
   *                                           *
   *                equal_range                *
   *                                           *
   *                                           *
   *********************************************/

  std::pair<iterator, iterator> equal_range(const key_type& key) {
    return t_.equal_range(key);
  }

  std::pair<const_iterator, const_iterator> equal_range(
      const key_type& key) const {
    return t_.equal_range(key);
  }

  /**********************************************
   *                                            *
   *                 bucket_count               *
   *                                            *
   *             max_bucket_count               *
   *                                            *
   *                 bucket_size                *
   *                                            *
   *                 bucket                     *
   *                                            *
   **********************************************/

  size_type     bucket_count() const { return t_.bucket_count(); }
  size_type nax_bucket_count() const { return t_.max_bucket_count(); }

  size_type bucket_size(size_type n) const { return t_.bucket_size(n); }
  size_type bucket(const key_type& k) const { return t_.bucket(k); }

  /***********************************************
   *                                             *
   *               hash_funcion                  *
   *                                             *
   *               key_eq                        *
   *                                             *
   ***********************************************/

  hasher hash_function() const { return t_.hash_function(); }
  key_equal key_eq() const { return t_.key_eq(); }

};  // class unordered_set

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

template <typename Key, typename Hash, typename KeyEqual, typename Allocator>
void swap(unordered_set<Key, Hash, KeyEqual, Allocator>& left, unordered_set<Key, Hash, KeyEqual, Allocator>& right) {
  left.swap(right);
}

/************************************************************
 *                                                          *
 *                 ==          !=                           *
 *                                                          *
 ************************************************************/

template <typename Key, typename Hash, typename KeyEqual, typename Allocator>
bool operator==(const unordered_set<Key, Hash, KeyEqual, Allocator>& left,
                const unordered_set<Key, Hash, KeyEqual, Allocator>& right) {
  return left.size() == right.size() && std::equal(left.cbegin(), left.cend(), right.cbegin());
}

template <typename Key, typename Hash, typename KeyEqual, typename Allocator>
bool operator!=(const unordered_set<Key, Hash, KeyEqual, Allocator>& left,
                const unordered_set<Key, Hash, KeyEqual, Allocator>& right) {
  return left.size() != right.size() || !std::equal(left.cbegin(), left.cend(), right.cbegin());
}

}  // namespace liuyunbin

#endif
