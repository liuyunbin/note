#ifndef CPP_STANDARD_LIBRARY_UNORDERED_MULTISET_H_
#define CPP_STANDARD_LIBRARY_UNORDERED_MULTISET_H_

#include "../hash_table.h"

#include <iostream>
#include <iterator>
#include <initializer_list>
#include <limits>
#include <vector>

namespace liuyunbin {

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
