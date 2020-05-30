#ifndef CPP_STANDARD_LIBRARY_MEMORY_ALLOCATOR_H_
#define CPP_STANDARD_LIBRARY_MEMORY_ALLOCATOR_H_

#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstddef>
#include <new>
#include <type_traits>
#include <memory>

namespace liuyunbin {

namespace detail {

// memory pool
union memory_pool_union_node {
  char data[1];
  union memory_pool_union_node* next;
};

class memory_pool {
 public:
  static void deallocate(void* p, std::size_t size) {
    if (size == 0) return;
    if (size > MAX_BYTES_)
      deallocate_large(p);
    else
      deallocate_small(p, round_up(size));
  }

  static void* allocate(std::size_t size) {
    if (size == 0) return nullptr;
    if (size > MAX_BYTES_)
      return allocate_large(size);
    else
      return allocate_small(round_up(size));
  }

 private:
  static constexpr std::size_t      ALIGN_ = 8;
  static constexpr std::size_t  MAX_BYTES_ = 1024;
  static constexpr std::size_t NFREENODES_ = MAX_BYTES_ / ALIGN_;
  static constexpr std::size_t     NNODES_ = 4;
  static constexpr std::size_t  BLOCKSIZE_ = 4096;

  static char* free_start_;
  static char* free_end_;

  static memory_pool_union_node* free_node_[NFREENODES_];

  static std::size_t round_up(std::size_t n) {
    return (n + ALIGN_ - 1) & ~(ALIGN_ - 1);
  }
  static std::size_t free_node_index(std::size_t n) {
    return (n + ALIGN_ - 1) / ALIGN_ - 1;
  }

  static void deallocate_large(void* p) { ::operator delete(p); }
  static void* allocate_large(std::size_t size) { return ::operator new(size); }

  static void deallocate_small(void* p, std::size_t size) {
    auto index = free_node_index(size);
    auto q = reinterpret_cast<memory_pool_union_node*>(p);
    q->next = free_node_[index];
    free_node_[index] = q;
  }

  static void* allocate_small(std::size_t size) {
    auto index = free_node_index(size);
    if (free_node_[index] != nullptr) {
      auto result = free_node_[index];
      free_node_[index] = result->next;
      return result;
    }
    int n = NNODES_;
    auto result = chunk_alloc(size, n);
    if (n == 1) return result;
    auto next_node = reinterpret_cast<memory_pool_union_node*>(result + size);
    free_node_[index] = next_node;
    for (int i = 1; i != n; ++i) {
      auto current_node = next_node;
      next_node =
          reinterpret_cast<memory_pool_union_node*>(current_node->data + size);
      if (i == n - 1)
        current_node->next = nullptr;
      else
        current_node->next = next_node;
    }
    return result;
  }

  static char* chunk_alloc(std::size_t size, int& n) {
    std::size_t bytes_need = size * n;
    std::size_t bytes_left = free_end_ - free_start_;

    if (bytes_left >= bytes_need) {
      auto result = free_start_;
      free_start_ += bytes_need;
      return result;
    }
    if (bytes_left >= size) {
      n = bytes_left / size;
      bytes_need = size * n;
      auto result = free_start_;
      free_start_ += bytes_need;
      return result;
    }
    if (bytes_left > 0) deallocate_small(free_start_, bytes_left);
    free_start_ = reinterpret_cast<char*>(allocate_large(BLOCKSIZE_));
    if (free_start_ == nullptr) {
      for (std::size_t i = size; i <= MAX_BYTES_; i += ALIGN_) {
        auto index = free_node_index(i);
        if (free_node_[index] == nullptr) continue;
        free_start_ = reinterpret_cast<char*>(allocate_small(i));
        free_end_ = free_start_ + i;
        return chunk_alloc(size, n);
      }
      // out of memory
      exit(-1);
    }
    free_end_ = free_start_ + BLOCKSIZE_;
    return chunk_alloc(size, n);
  }
};  // class memory_pool

char* memory_pool::free_start_ = nullptr;
char* memory_pool::free_end_ = nullptr;
memory_pool_union_node* memory_pool::free_node_[NFREENODES_] = {
    nullptr,
};

}  // namespace detail

template <typename T>
class allocator {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  template <typename U>
  struct rebind {
    using other = allocator<U>;
  };

 public:
  /*****************************************************
   *                                                   *
   *                    constructor                    *
   *                                                   *
   *****************************************************/

  allocator() {}
  allocator(const allocator&) {}
  template <typename U>
  allocator(const allocator<U>&) {}

  /*****************************************************
   *                                                   *
   *                       allocate                    *
   *                                                   *
   *****************************************************/

  static T* allocate(std::size_t n = 1) {
    return reinterpret_cast<T*>(detail::memory_pool::allocate(n * sizeof(T)));
  }

  /*****************************************************
   *                                                   *
   *                     deallocate                    *
   *                                                   *
   *****************************************************/

  static void deallocate(T* p, size_type n = 1) {
    detail::memory_pool::deallocate(p, n * sizeof(T));
  }

};  // class allocator

/***********************************
 *                                 *
 *           construct             *
 *                                 *
 ***********************************/
// placement new
template <typename T, typename... Args>
void construct(T* p, Args&&... args) {
  new (p) T(std::forward<Args>(args)...);
}
template <typename T>
void construct(T* p) {
  new (p) T();
}

/***********************************
 *                                 *
 *           destroy               *
 *                                 *
 ***********************************/

/*************************************************************************************************
 *                                                                                               *
 *  it could work even if T == int, char and so on * see <
 *https://stackoverflow.com/questions/456310/destructors-of-builtin-types-int-char-etc>
 **
 *                                                                                               *
 *************************************************************************************************/

template <typename T>
void destroy(T* p) {
  p->~T();
}

namespace detail {

template <typename ForwardIt>
void __destroy(ForwardIt first, ForwardIt last, std::true_type) {}

template <typename ForwardIt>
void __destroy(ForwardIt first, ForwardIt last, std::false_type) {
  while (first != last) destroy(&*first++);
}

}  // namespace detail

template <typename ForwardIt>
void destroy(ForwardIt first, ForwardIt last) {
  using value_type = typename std::iterator_traits<ForwardIt>::value_type;
  using trivial_destructor = std::is_trivially_destructible<value_type>;
  detail::__destroy(first, last, trivial_destructor());
}

/****************************************
 *                                      *
 *          uninitialized_copy          *
 *                                      *
 ****************************************/

namespace detail {

template <typename InputIt, typename ForwardIt>
ForwardIt __uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first,
                               std::__true_type) {
  return std::copy(first, last, d_first);
}

template <typename InputIt, typename ForwardIt>
ForwardIt __uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first,
                               std::__false_type) {
  while (first != last) construct(&*d_first++, *first++);
  return d_first;
}

}  // namespace detail

template <typename InputIt, typename ForwardIt>
ForwardIt uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first) {
  using value_type = typename std::iterator_traits<InputIt>::value_type;
  using POD_type = typename std::is_pod<value_type>;
  return detail::__uninitialized_copy(first, last, d_first, POD_type());
}

/******************************************
 *                                        *
 *          uninitialized_copy_n          *
 *                                        *
 ******************************************/

namespace detail {

template <typename InputIt, typename Size, typename ForwardIt>
ForwardIt __uninitialized_copy_n(InputIt first, Size n, ForwardIt d_first,
                                 std::__true_type) {
  return std::copy_n(first, n, d_first);
}

template <typename InputIt, typename Size, typename ForwardIt>
ForwardIt __uninitialized_copy_n(InputIt first, Size n, ForwardIt d_first,
                                 std::__false_type) {
  while (n-- != 0) construct(&*d_first++, *first++);
  return d_first;
}

}  // namespace detail

template <typename InputIt, typename Size, typename ForwardIt>
ForwardIt uninitialized_copy_n(InputIt first, Size n, ForwardIt d_first) {
  using value_type = typename std::iterator_traits<InputIt>::value_type;
  using POD_type = typename std::is_pod<value_type>;
  return detail::__uninitialized_copy_n(first, n, d_first, POD_type());
}

/****************************************
 *                                      *
 *          uninitialized_fill          *
 *                                      *
 ****************************************/

namespace detail {

template <typename ForwardIt, typename T>
void __uninitialized_fill(ForwardIt first, ForwardIt last, const T& value,
                          std::__true_type) {
  std::fill(first, last, value);
}

template <typename ForwardIt, typename T>
void __uninitialized_fill(ForwardIt first, ForwardIt last, const T& value,
                          std::__false_type) {
  while (first != last) construct(&*first++, value);
}

}  // namespace detail

template <typename ForwardIt, typename T>
void uninitialized_fill(ForwardIt first, ForwardIt last, const T& value) {
  using value_type = typename std::iterator_traits<ForwardIt>::value_type;
  using POD_type = typename std::is_pod<value_type>;
  detail::__uninitialized_fill(first, last, value, POD_type());
}

/******************************************
 *                                        *
 *          uninitialized_fill_n          *
 *                                        *
 ******************************************/

namespace detail {

template <typename ForwardIt, typename Size, typename T>
ForwardIt __uninitialized_fill_n(ForwardIt first, Size n, const T& value,
                                 std::__true_type) {
  return std::fill_n(first, n, value);
}

template <typename ForwardIt, typename Size, typename T>
ForwardIt __uninitialized_fill_n(ForwardIt first, Size n, const T& value,
                                 std::__false_type) {
  while (n-- != 0) construct(&*first++, value);
  return first;
}

}  // namespace detail

template <typename ForwardIt, typename Size, typename T>
ForwardIt uninitialized_fill_n(ForwardIt first, Size n, const T& value) {
  using value_type = typename std::iterator_traits<ForwardIt>::value_type;
  using POD_type = typename std::is_pod<value_type>;
  return detail::__uninitialized_fill_n(first, n, value, POD_type());
}

}  // namespace liuyunbin

#endif
