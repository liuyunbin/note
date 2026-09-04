#ifndef CPP_STANDARD_LIBRARY_MEMORY_H_
#define CPP_STANDARD_LIBRARY_MEMORY_H_

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

/*******************************************
 *                                         *
 *      class shared_ptr_counted_base      *
 *                                         *
 *******************************************/

class default_delete {
 public:
  template <typename T>
  void operator()(T* ptr) const {
    delete ptr;
  }
};

class shared_ptr_counted_base {
 private:
  long use_count_;

  virtual void dispose() = 0;

 public:
  //    ~shared_ptr_counted_base() { release(); }

  long use_count() const { return use_count_; }

  void add_count() { ++use_count_; }

  void release() {
    if (--use_count_ == 0) dispose();
  }

 protected:
  explicit shared_ptr_counted_base(long use_count) : use_count_(use_count) {}
};

/****************************************************
 *                                                  *
 *      class shared_ptr_counted_base_implment      *
 *                                                  *
 ***************************************************/

template <typename P, typename Deleter>
class shared_ptr_counted_base_implement : public shared_ptr_counted_base {
 public:
  explicit shared_ptr_counted_base_implement(P* ptr, Deleter del)
      : shared_ptr_counted_base(1), ptr_(ptr), del_(del) {}

 private:
  P* ptr_;
  Deleter del_;

  virtual void dispose() override { del_(ptr_); }
};

/**********************************
 *                                *
 *      class shared_count        *
 *                                *
 **********************************/

class shared_count;

bool operator==(const shared_count& left, const shared_count& right);
bool operator< (const shared_count& left, const shared_count& right);

class shared_count {
  friend bool operator==(const shared_count& left, const shared_count& right);
  friend bool operator< (const shared_count& left, const shared_count& right);

 public:
  shared_count() : pi_(nullptr) {}

  template <typename Y, typename Deleter>
  shared_count(Y* p, Deleter d = Deleter())
      : pi_(new shared_ptr_counted_base_implement<Y, Deleter>(p, d)) {}

  shared_count(const shared_count& r) : pi_(r.pi_) {
    if (pi_ != nullptr) pi_->add_count();
  }

  shared_count(shared_count&& r) noexcept : pi_(r.pi_) { r.pi_ = nullptr; }

  ~shared_count() { release(); }

  void release() {
    if (pi_ != nullptr) {
      pi_->release();
      pi_ = nullptr;
    }
  }

  shared_count& operator=(const shared_count& r) {
    if (r.pi_ == pi_) return *this;
    if (r.pi_ != nullptr) r.pi_->add_count();
    release();
    pi_ = r.pi_;
    return *this;
  }

  shared_count& operator=(shared_count&& r) noexcept {
    if (r.pi_ == pi_) return *this;
    release();
    pi_ = r.pi_;
    r.pi_ = nullptr;
    return *this;
  }

  long use_count() const { return pi_ == nullptr ? 0 : pi_->use_count(); }

 private:
  shared_ptr_counted_base* pi_;
};

bool operator==(const shared_count& left, const shared_count& right) {
  return left.pi_ == right.pi_;
}
bool operator<(const shared_count& left, const shared_count& right) {
  return std::less<shared_ptr_counted_base*>()(left.pi_, right.pi_);
}

/**********************************
 *                                *
 *      class shared_ptr          *
 *                                *
 **********************************/

template <typename T>
class shared_ptr {
 public:
  using element_type = T;

  template <typename U>
  friend class shared_ptr;

 public:
  /**************************************************
   *                                                *
   *                constructor                     *
   *                                                *
   *                destructor                      *
   *                                                *
   **************************************************/

  shared_ptr() {}

  shared_ptr(std::nullptr_t) {}

  template <typename Y>
  explicit shared_ptr(Y* p) : px_(p), pn_(p) {}

  template <typename Y, typename Deleter>
  shared_ptr(Y* p, Deleter d) : px_(p), pn_(p, d) {}

  template <typename Deleter>
  shared_ptr(std::nullptr_t p, Deleter d) : px_(p), pn_(p, d) {}

  shared_ptr(const shared_ptr& r) : px_(r.px_), pn_(r.pn_) {}

  shared_ptr(shared_ptr&& r) noexcept
      : px_(r.px_), pn_(std::move(r.pn_)) {}

  template <typename Y>
  shared_ptr(const shared_ptr<Y>& r) : px_(r.px_), pn_(r.pn_) {}

  template <typename Y>
  shared_ptr(shared_ptr<Y>&& r) noexcept
      : px_(r.px_), pn_(std::move(r.pn_)) {}

  template <typename Y>
  shared_ptr(const shared_ptr<Y>& r, T* p) : px_(p), pn_(r.pn_) {}

  template <typename Y, typename Deleter>
  shared_ptr(std::unique_ptr<Y, Deleter>&& r) noexcept
      : px_(r.get()), pn_(r.get(), r.get_deleter()) {
    r.release();
  }

  ~shared_ptr() { release(); }

  /**************************************
   *                                    *
   *                  =                 *
   *                                    *
   **************************************/

  shared_ptr& operator=(const shared_ptr& r) {
    if (r.pn_ == pn_) return *this;
    release();
    pn_ = r.pn_;
    px_ = r.px_;
    return *this;
  }

  shared_ptr& operator=(shared_ptr&& r) noexcept {
    if (r.pn_ == pn_) return *this;
    release();
    pn_ = std::move(r.pn_);
    px_ = r.px_;
    return *this;
  }

  template <typename Y>
  shared_ptr& operator=(const shared_ptr<Y>& r) {
    release();
    pn_ = r.pn_;
    px_ = r.px_;
    return *this;
  }

  template <typename Y>
  shared_ptr& operator=(shared_ptr<Y>&& r) noexcept {
    release();
    pn_ = std::move(r.pn_);
    px_ = r.px_;
    return *this;
  }

  template <typename Y, typename Deleter>
  shared_ptr& operator=(std::unique_ptr<Y, Deleter>&& r) noexcept {
    release();
    pn_ = shared_count(r.get(), r.get_deleter());
    px_ = r.release();
    return *this;
  }

  /**************************************
   *                                    *
   *               reset                *
   *                                    *
   **************************************/

  void reset() {
    release();
    px_ = nullptr;
    pn_ = shared_count();
  }

  template <typename Y>
  void reset(Y* ptr) {
    release();
    px_ = ptr;
    pn_ = shared_count(ptr, default_delete());
  }

  template <typename Y, typename Deleter>
  void reset(Y* ptr, Deleter d) {
    release();
    px_ = ptr;
    pn_ = shared_count(ptr, d);
  }

  /**************************
   *                        *
   *      ower_before       *
   *                        *
   **************************/

  bool ower_before(const shared_ptr& r) const { return pn_ < r.pn_; }

  /**************************
   *                        *
   *          swap          *
   *                        *
   **************************/

  void swap(shared_ptr& r) {
    std::swap(px_, r.px_);
    std::swap(pn_, r.pn_);
  }

  /**************************
   *                        *
   *          get           *
   *                        *
   **************************/

  T* get() const { return px_; }

  /**************************
   *                        *
   *    *   ->   bool       *
   *                        *
   **************************/

  T& operator* () const { return *get(); }
  T* operator->() const { return  get(); }

  explicit operator bool() const { return px_ != nullptr; }

  /****************************
   *                          *
   *        use_count         *
   *                          *
   *        unique            *
   *                          *
   ****************************/

  long use_count() const { return pn_.use_count(); }

  bool unique() const { return use_count() == 1; }

 private:
  T* px_ = nullptr;
  shared_count pn_;

  void release() {
    pn_.release();
    px_ = nullptr;
  }
};

/**********************************
 *                                *
 *         make_shared            *
 *                                *
 **********************************/

template <typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args) {
  return shared_ptr<T>(new T(std::forward<Args>(args)...));
}

/**********************************
 *                                *
 *            swap                *
 *                                *
 **********************************/

template <typename T>
void swap(shared_ptr<T>& left, shared_ptr<T>& right) {
  left.swap(right);
}

/**********************************
 *                                *
 *   ==   !=   <   <=  >   >=     *
 *                                *
 **********************************/

template <typename T, typename U>
bool operator==(const shared_ptr<T>& left, const shared_ptr<U>& right) {
  return std::equal_to<T*>()(left.get(), right.get());
}

template <typename T, typename U>
bool operator!=(const shared_ptr<T>& left, const shared_ptr<U>& right) {
  return std::not_equal_to<T*>()(left.get(), right.get());
}

template <typename T, typename U>
bool operator<(const shared_ptr<T>& left, const shared_ptr<U>& right) {
  return std::less<T*>()(left.get(), right.get());
}

template <typename T, typename U>
bool operator<=(const shared_ptr<T>& left, const shared_ptr<U>& right) {
  return std::less_equal<T*>()(left.get(), right.get());
}

template <typename T, typename U>
bool operator>(const shared_ptr<T>& left, const shared_ptr<U>& right) {
  return std::greater<T*>()(left.get(), right.get());
}

template <typename T, typename U>
bool operator>=(const shared_ptr<T>& left, const shared_ptr<U>& right) {
  return std::greater_equal<T*>()(left.get(), right.get());
}

template <typename T>
bool operator==(const shared_ptr<T>& left, std::nullptr_t right) {
  return std::equal_to<T*>()(left.get(), nullptr);
}

template <typename T>
bool operator==(std::nullptr_t left, const shared_ptr<T>& right) {
  return std::equal_to<T*>()(nullptr, right.get());
}

template <typename T>
bool operator!=(const shared_ptr<T>& left, std::nullptr_t right) {
  return std::not_equal_to<T*>()(left.get(), nullptr);
}

template <typename T>
bool operator!=(std::nullptr_t left, const shared_ptr<T>& right) {
  return std::not_equal_to<T*>()(nullptr, right.get());
}

template <typename T>
bool operator<(const shared_ptr<T>& left, std::nullptr_t right) {
  return std::less<T*>()(left.get(), nullptr);
}

template <typename T>
bool operator<(std::nullptr_t left, const shared_ptr<T>& right) {
  return std::less<T*>()(nullptr, right.get());
}

template <typename T>
bool operator<=(const shared_ptr<T>& left, std::nullptr_t right) {
  return std::less_equal<T*>()(left.get(), nullptr);
}

template <typename T>
bool operator<=(std::nullptr_t left, const shared_ptr<T>& right) {
  return std::less_equal<T*>()(nullptr, right.get());
}

template <typename T>
bool operator>(const shared_ptr<T>& left, std::nullptr_t right) {
  return std::greater<T*>()(left.get(), nullptr);
}

template <typename T>
bool operator>(std::nullptr_t left, const shared_ptr<T>& right) {
  return std::greater<T*>()(nullptr, right.get());
}

template <typename T>
bool operator>=(const shared_ptr<T>& left, std::nullptr_t right) {
  return std::greater<T*>()(left.get(), nullptr);
}

template <typename T>
bool operator>=(std::nullptr_t left, const shared_ptr<T>& right) {
  return std::greater<T*>()(nullptr, right.get());
}

/************************************************
 *                                              *
 *                 <<                           *
 *                                              *
 ************************************************/

template <typename T>
std::ostream& operator<<(std::ostream& os, const shared_ptr<T>& ptr) {
  os << ptr.get();
  return os;
}

/**********************************
 *                                *
 *      class unique_ptr          *
 *                                *
 **********************************/

template <typename T, typename Deleter = std::default_delete<T>>
class unique_ptr {
  template <typename Y, typename Y_Deleter>
  friend class unique_ptr;

 public:
  /***************************************
   *                                     *
   *              construct              *
   *                                     *
   *              destruct               *
   *                                     *
   ***************************************/

  unique_ptr() {}

  unique_ptr(std::nullptr_t) {}

  template <typename Y>
  explicit unique_ptr(Y* ptr) : ptr_(ptr) {}

  template <typename Y, typename y_Deleter>
  unique_ptr(Y* ptr, y_Deleter del) : ptr_(ptr), del_(del) {}

  unique_ptr(const unique_ptr& r) = delete;
  unique_ptr(unique_ptr&& r) noexcept : ptr_(r.ptr_), del_(r.del_) {
    r.ptr_ = nullptr;
  }

  template <typename Y, typename y_Deleter>
  unique_ptr(const unique_ptr<Y, y_Deleter>& r) = delete;

  template <typename Y, typename y_Deleter>
  unique_ptr(unique_ptr<Y, y_Deleter>&& r) noexcept
      : ptr_(r.ptr_), del_(r.del_) {
    r.ptr_ = nullptr;
  }

  ~unique_ptr() {
    if (ptr_ != nullptr) del_(ptr_);
  }

  /****************************************************
   *                                                  *
   *                   =                              *
   *                                                  *
   ****************************************************/

  unique_ptr& operator=(const unique_ptr& r) = delete;
  unique_ptr& operator=(unique_ptr&& r) noexcept {
    if (ptr_ != nullptr) del_(ptr_);
    ptr_ = r.ptr_;
    del_ = r.del_;
    r.ptr_ = nullptr;
    return *this;
  }

  template <typename Y, typename y_Deleter>
  unique_ptr& operator=(const unique_ptr<Y, y_Deleter>& r) = delete;

  template <typename Y, typename y_Deleter>
  unique_ptr& operator=(unique_ptr<Y, y_Deleter>&& r) noexcept {
    if (ptr_ != nullptr) del_(ptr_);
    ptr_ = r.ptr_;
    del_ = r.del_;
    r.ptr_ = nullptr;
    return *this;
  }

  unique_ptr<T, Deleter>& operator=(std::nullptr_t) {
    if (ptr_ != nullptr) del_(ptr_);
    ptr_ = nullptr;
    return *this;
  }

  /*****************************
   *                           *
   *          release          *
   *                           *
   *****************************/

  T* release() {
    auto it = ptr_;
    ptr_ = nullptr;
    return it;
  }

  /******************************
   *                            *
   *          reset             *
   *                            *
   ******************************/

  void reset(T* ptr = nullptr) {
    if (ptr_ != nullptr) del_(ptr_);
    ptr_ = ptr;
  }

  /********************************
   *                              *
   *           swap               *
   *                              *
   ********************************/

  void swap(unique_ptr& r) {
    using std::swap;
    swap(ptr_, r.ptr_);
    swap(del_, r.del_);
  }

  /********************************
   *                              *
   *          get_deleter         *
   *                              *
   ********************************/

  Deleter& get_deleter() { return del_; }
  const Deleter& get_deleter() const { return del_; }

  /********************************
   *                              *
   *          get                 *
   *                              *
   ********************************/

  T* get() const { return ptr_; }

  /********************************
   *                              *
   *       *   ->   bool          *
   *                              *
   ********************************/

  T& operator*() const { return *ptr_; }
  T* operator->() const { return ptr_; }

  operator bool() const { return ptr_ != nullptr; }

 private:
  T* ptr_ = nullptr;
  Deleter del_ = Deleter();
};

/********************************
 *                              *
 *        make_unique           *
 *                              *
 ********************************/

template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
  return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

/********************************
 *                              *
 *           swap               *
 *                              *
 ********************************/

template <typename T, typename D>
void swap(unique_ptr<T, D>& left, unique_ptr<T, D>& right) {
  left.swap(right);
}

/********************************
 *                              *
 *  ==  !=   <   <=  >  >=      *
 *                              *
 ********************************/

template <typename T1, typename D1, typename T2, typename D2>
bool operator==(const unique_ptr<T1, D1>& left, const unique_ptr<T2, D2>& right) {
  return std::equal_to<T1*>()(left.get(), right.get());
}

template <typename T1, typename D1, typename T2, typename D2>
bool operator!=(const unique_ptr<T1, D1>& left, const unique_ptr<T2, D2>& right) {
  return std::not_equal_to<T1*>()(left.get(), right.get());
}

template <typename T1, typename D1, typename T2, typename D2>
bool operator<(const unique_ptr<T1, D1>& left, const unique_ptr<T2, D2>& right) {
  return std::less<T1*>()(left.get(), right.get());
}

template <typename T1, typename D1, typename T2, typename D2>
bool operator<=(const unique_ptr<T1, D1>& left, const unique_ptr<T2, D2>& right) {
  return std::less_equal<T1*>()(left.get(), right.get());
}

template <typename T1, typename D1, typename T2, typename D2>
bool operator>(const unique_ptr<T1, D1>& left, const unique_ptr<T2, D2>& right) {
  return std::greater<T1*>()(left.get(), right.get());
}

template <typename T1, typename D1, typename T2, typename D2>
bool operator>=(const unique_ptr<T1, D1>& left, const unique_ptr<T2, D2>& right) {
  return std::greater_equal<T1*>()(left.get(), right.get());
}

template <typename T, typename D>
bool operator==(const unique_ptr<T, D>& left, std::nullptr_t right) {
  return std::equal_to<T*>()(left.get(), nullptr);
}

template <typename T, typename D>
bool operator==(std::nullptr_t left, const unique_ptr<T, D>& right) {
  return std::equal_to<T*>()(nullptr, right.get());
}

template <typename T, typename D>
bool operator!=(const unique_ptr<T, D>& left, std::nullptr_t right) {
  return std::not_equal_to<T*>()(left.get(), nullptr);
}

template <typename T, typename D>
bool operator!=(std::nullptr_t left, const unique_ptr<T, D>& right) {
  return std::not_equal_to<T*>()(nullptr, right.get());
}

template <typename T, typename D>
bool operator<(const unique_ptr<T, D>& left, std::nullptr_t right) {
  return std::less<T*>()(left.get(), nullptr);
}

template <typename T, typename D>
bool operator<(std::nullptr_t left, const unique_ptr<T, D>& right) {
  return std::less<T*>()(nullptr, right.get());
}

template <typename T, typename D>
bool operator<=(const unique_ptr<T, D>& left, std::nullptr_t right) {
  return std::less_equal<T*>()(left.get(), nullptr);
}

template <typename T, typename D>
bool operator<=(std::nullptr_t left, const unique_ptr<T, D>& right) {
  return std::less_equal<T*>()(nullptr, right.get());
}

template <typename T, typename D>
bool operator>(const unique_ptr<T, D>& left, std::nullptr_t right) {
  return std::greater<T*>()(left.get(), nullptr);
}

template <typename T, typename D>
bool operator>(std::nullptr_t left, const unique_ptr<T, D>& right) {
  return std::greater<T*>()(nullptr, right.get());
}

template <typename T, typename D>
bool operator>=(std::nullptr_t left, const unique_ptr<T, D>& right) {
  return std::greater<T*>()(nullptr, right.get());
}

template <typename T, typename D>
bool operator>=(const unique_ptr<T, D>& left, std::nullptr_t right) {
  return std::greater<T*>()(left.get(), nullptr);
}

/*****************************************************
 *                                                   *
 *                   <<                              *
 *                                                   *
 *****************************************************/

template <typename T>
std::ostream& operator<<(std::ostream& os, const unique_ptr<T>& ptr) {
  os << ptr.get();
  return os;
}

}  // namespace liuyunbin

#endif
