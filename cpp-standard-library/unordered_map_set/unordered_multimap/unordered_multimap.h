#ifndef CPP_STANDARD_LIBRARY_UNORDERED_UNORDERED_MULTIMAP_H_
#define CPP_STANDARD_LIBRARY_UNORDERED_UNORDERED_MULTIMAP_H_

#include "../hash_table.h"

#include <iostream>
#include <iterator>
#include <initializer_list>
#include <limits>
#include <vector>

namespace liuyunbin {

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

}  // namespace liuyunbin

#endif
