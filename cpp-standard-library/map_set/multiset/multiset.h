#ifndef CPP_STANDARD_LIBRARY_MULTISET_H_
#define CPP_STANDARD_LIBRARY_MULTISET_H_

#include "../rb_tree.h"

#include <iostream>
#include <iterator>
#include <cstddef>
#include <initializer_list>
#include <limits>

namespace liuyunbin {

/***********************************************
 *                                             *
 *                multiset                     *
 *                                             *
 ***********************************************/

template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Key>>
class multiset {
public:
  using allocator_type = Allocator;
  using       key_type = Key;
  using     value_type = Key;
  using    key_compare = Compare;
  using  value_compare = Compare;

 private:
   struct fun {
     Key operator()(const value_type &ve) { return ve; }
   };

   using rb_tree_type =
       detail::rb_tree<key_type, value_type, fun, key_compare, Allocator>;

   rb_tree_type t_;

 public:
  using              size_type = typename rb_tree_type::size_type;
  using        difference_type = typename rb_tree_type::difference_type;
  using              reference = typename rb_tree_type::const_reference;
  using        const_reference = typename rb_tree_type::const_reference;
  using                pointer = typename rb_tree_type::const_pointer;
  using          const_pointer = typename rb_tree_type::const_pointer;
  using               iterator = typename rb_tree_type::const_iterator;
  using         const_iterator = typename rb_tree_type::const_iterator;
  using       reverse_iterator = typename rb_tree_type::const_reverse_iterator;
  using const_reverse_iterator = typename rb_tree_type::const_reverse_iterator;

 public:
  /************************************************************
   *                                                          *
   *                       construct                          *
   *                                                          *
   ************************************************************/

   multiset() {}

   explicit multiset(const Compare &comp) : t_(comp) {}

   multiset(const multiset &other) : t_(other.t_) {}
   multiset(multiset &&other) noexcept : t_(std::move(other.t_)) {}

   template <typename InputIt>
   multiset(InputIt first, InputIt last, const Compare &comp = Compare())
       : t_(comp) {
     t_.insert_equal(first, last);
   }
   multiset(std::initializer_list<Key> ilist, const Compare &comp = Compare())
       : t_(comp) {
     t_.insert_equal(ilist.begin(), ilist.end());
   }

  /************************************************************
   *                                                          *
   *                       destruct                           *
   *                                                          *
   ************************************************************/

   ~multiset() {}

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

   /************************************************************
    *                                                          *
    *                      rbegin                              *
    *                     crbegin                              *
    *                                                          *
    *                       rend                               *
    *                      crend                               *
    *                                                          *
    ************************************************************/

   reverse_iterator rbegin() { return t_.crbegin(); }
   const_reverse_iterator rbegin() const { return t_.crbegin(); }
   const_reverse_iterator crbegin() const { return t_.crbegin(); }

   reverse_iterator rend() { return t_.crend(); }
   const_reverse_iterator rend() const { return t_.crend(); }
   const_reverse_iterator crend() const { return t_.crend(); }

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

   void swap(multiset &other) { t_.swap(other.t_); }

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

  multiset &operator=(multiset &&other) noexcept {
    t_ = std::move(other.t_);
    return *this;
  }
  multiset &operator=(const multiset &other) {
    t_ = other.t_;
    return *this;
  }
  multiset &operator=(std::initializer_list<value_type> ilist) {
    return *this = multiset(ilist);
  }

  /********************************************
   *                                          *
   *              count                       *
   *                                          *
   *              find                        *
   *                                          *
   ********************************************/

  size_type     count(const key_type& key) const { return t_.count(key); }
  iterator       find(const key_type& key)       { return t_.find(key); }
  const_iterator find(const key_type& key) const { return t_.find(key); }

  /*********************************************
   *                                           *
   *                equal_range                *
   *                                           *
   *                lower_bound                *
   *                                           *
   *                upper_bound                *
   *                                           *
   *********************************************/

  std::pair<iterator, iterator> equal_range(const key_type& key) {
    return t_.equal_range(key);
  }
  std::pair<const_iterator, const_iterator> equal_range(
      const key_type& key) const {
    return t_.equal_range(key);
  }

  iterator lower_bound(const key_type& key) { return t_.lower_bound(key); }
  const_iterator lower_bound(const key_type& key) const {
    return t_.lower_bound(key);
  }

  iterator upper_bound(const key_type& key) { return t_.upper_bound(key); }
  const_iterator upper_bound(const key_type& key) const {
    return t_.upper_bound(key);
  }

  /***********************************************
   *                                             *
   *                key_comp                     *
   *                                             *
   *              value_comp                     *
   *                                             *
   ***********************************************/

  key_compare key_comp() const { return t_.key_comp(); }
  value_compare value_comp() const { return t_.key_comp(); }

}; // class multiset

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

template <typename Key, typename Compare, typename Allocator>
void swap(multiset<Key, Compare, Allocator> &left,
          multiset<Key, Compare, Allocator> &right) {
  left.swap(right);
}

/************************************************************
 *                                                          *
 *                 == != < <= > >=                          *
 *                                                          *
 ************************************************************/

template <typename Key, typename Compare, typename Allocator>
bool operator==(const multiset<Key, Compare, Allocator>& left, const multiset<Key, Compare, Allocator>& right) {
  return left.size() == right.size() && std::equal(left.cbegin(), left.cend(), right.cbegin());
}

template <typename Key, typename Compare, typename Allocator>
bool operator!=(const multiset<Key, Compare, Allocator>& left, const multiset<Key, Compare, Allocator>& right) {
  return left.size() != right.size() || !std::equal(left.cbegin(), left.cend(), right.cbegin());
}

template <typename Key, typename Compare, typename Allocator>
bool operator<(const multiset<Key, Compare, Allocator>& left, const multiset<Key, Compare, Allocator>& right) {
  return std::lexicographical_compare(left.cbegin(), left.cend(), right.cbegin(), right.cend());
}

template <typename Key, typename Compare, typename Allocator>
bool operator<=(const multiset<Key, Compare, Allocator>& left, const multiset<Key, Compare, Allocator>& right) {
  return !(right < left);
}

template <typename Key, typename Compare, typename Allocator>
bool operator>(const multiset<Key, Compare, Allocator>& left, const multiset<Key, Compare, Allocator>& right) {
  return right < left;
}

template <typename Key, typename Compare, typename Allocator>
bool operator>=(const multiset<Key, Compare, Allocator>& left, const multiset<Key, Compare, Allocator>& right) {
  return !(left < right);
}

}  // namespace liuyunbin

#endif
