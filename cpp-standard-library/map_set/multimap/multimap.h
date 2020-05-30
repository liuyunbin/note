#ifndef CPP_STANDARD_LIBRARY_MULTIMAP_H_
#define CPP_STANDARD_LIBRARY_MULTIMAP_H_

#include "../rb_tree.h"

#include <iostream>
#include <iterator>
#include <cstddef>
#include <initializer_list>
#include <limits>

namespace liuyunbin {

/***********************************************
 *                                             *
 *               multimap                      *
 *                                             *
 ***********************************************/

template <typename Key, typename T, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<std::pair<const Key, T>>>
class multimap {
public:
  using allocator_type = Allocator;
  using       key_type = Key;
  using    mapped_type = T;
  using     value_type = std::pair<const Key, T>;
  using    key_compare = Compare;

  class value_compare
      : public std::binary_function<value_type, value_type, bool> {
    friend class multimap<Key, T, Compare, Allocator>;

  private:
    Compare comp_;
    value_compare(Compare comp) : comp_(comp) {}

   public:
    bool operator()(const value_type& left, const value_type& right) const {
      return comp_(left.first, right.first);
    }
  };

 private:
   struct fun {
     Key operator()(const value_type &ve) { return ve.first; }
   };

   using rb_tree_type =
       detail::rb_tree<key_type, value_type, fun, key_compare, Allocator>;

   rb_tree_type t_;

 public:
  using              size_type = typename rb_tree_type::size_type;
  using        difference_type = typename rb_tree_type::difference_type;
  using              reference = typename rb_tree_type::reference;
  using        const_reference = typename rb_tree_type::const_reference;
  using                pointer = typename rb_tree_type::pointer;
  using          const_pointer = typename rb_tree_type::const_pointer;
  using               iterator = typename rb_tree_type::iterator;
  using         const_iterator = typename rb_tree_type::const_iterator;
  using       reverse_iterator = typename rb_tree_type::reverse_iterator;
  using const_reverse_iterator = typename rb_tree_type::const_reverse_iterator;

 public:
  /************************************************************
   *                                                          *
   *                       construct                          *
   *                                                          *
   ************************************************************/

   multimap() {}

   explicit multimap(const Compare &comp) : t_(comp) {}

   multimap(const multimap &other) : t_(other.t_) {}
   multimap(multimap &&other) noexcept : t_(std::move(other.t_)) {}

   template <typename InputIt>
   multimap(InputIt first, InputIt last, const Compare &comp = Compare())
       : t_(comp) {
     t_.insert_equal(first, last);
   }

   multimap(std::initializer_list<value_type> ilist,
            const Compare &comp = Compare())
       : t_(comp) {
     t_.insert_equal(ilist.begin(), ilist.end());
   }

  /************************************************************
   *                                                          *
   *                       destruct                           *
   *                                                          *
   ************************************************************/

   ~multimap() {}

   /************************************************************
    *                                                          *
    *                      begin                               *
    *                     cbegin                               *
    *                                                          *
    *                        end                               *
    *                       cend                               *
    *                                                          *
    ************************************************************/

   iterator begin() { return t_.begin(); }
   const_iterator begin() const { return t_.begin(); }
   const_iterator cbegin() const { return t_.cbegin(); }

   iterator end() { return t_.end(); }
   const_iterator end() const { return t_.end(); }
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

   reverse_iterator rbegin() { return t_.rbegin(); }
   const_reverse_iterator rbegin() const { return t_.rbegin(); }
   const_reverse_iterator crbegin() const { return t_.crbegin(); }

   reverse_iterator rend() { return t_.rend(); }
   const_reverse_iterator rend() const { return t_.rend(); }
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

   void swap(multimap &other) { t_.swap(other.t_); }

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
   template <typename Y> iterator insert(Y &&value) {
     return t_.insert_equal(std::forward<Y>(value));
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

  multimap &operator=(multimap &&other) noexcept {
    t_ = std::move(other.t_);
    return *this;
  }
  multimap &operator=(const multimap &other) {
    t_ = other.t_;
    return *this;
  }
  multimap &operator=(std::initializer_list<value_type> ilist) {
    return *this = multimap(ilist);
  }

  /********************************************
   *                                          *
   *              count                       *
   *                                          *
   *              find                        *
   *                                          *
   ********************************************/

  size_type count(const key_type &key) const { return t_.count(key); }
  iterator find(const key_type &key) { return t_.find(key); }
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
  value_compare value_comp() const {
    return static_cast<value_compare>(t_.key_comp());
  }

}; // class multimap

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

template <typename Key, typename T, typename Compare, typename Allocator>
void swap(multimap<Key, T, Compare, Allocator> &left,
          multimap<Key, T, Compare, Allocator> &right) {
  left.swap(right);
}

/************************************************************
 *                                                          *
 *                 == != < <= > >=                          *
 *                                                          *
 ************************************************************/

template <typename Key, typename T, typename Compare, typename Allocator>
bool operator==(const multimap<Key, T, Compare, Allocator>& left, const multimap<Key, T, Compare, Allocator>& right) {
  return left.size() == right.size() && std::equal(left.cbegin(), left.cend(), right.cbegin());
}

template <typename Key, typename T, typename Compare, typename Allocator>
bool operator!=(const multimap<Key, T, Compare, Allocator>& left, const multimap<Key, T, Compare, Allocator>& right) {
  return left.size() != right.size() || !std::equal(left.cbegin(), left.cend(), right.cbegin());
}

template <typename Key, typename T, typename Compare, typename Allocator>
bool operator<(const multimap<Key, T, Compare, Allocator>& left, const multimap<Key, T, Compare, Allocator>& right) {
  return std::lexicographical_compare(left.cbegin(), left.cend(), right.cbegin(), right.cend());
}

template <typename Key, typename T, typename Compare, typename Allocator>
bool operator<=(const multimap<Key, T, Compare, Allocator>& left, const multimap<Key, T, Compare, Allocator>& right) {
  return !(right < left);
}

template <typename Key, typename T, typename Compare, typename Allocator>
bool operator>(const multimap<Key, T, Compare, Allocator>& left, const multimap<Key, T, Compare, Allocator>& right) {
  return right < left;
}

template <typename Key, typename T, typename Compare, typename Allocator>
bool operator>=(const multimap<Key, T, Compare, Allocator>& left, const multimap<Key, T, Compare, Allocator>& right) {
  return !(left < right);
}

}  // namespace liuyunbin

#endif
