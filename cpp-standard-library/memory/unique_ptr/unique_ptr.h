#ifndef CPP_STANDARD_LIBRARY_MEMORY_UNIQUE_PTR_H_
#define CPP_STANDARD_LIBRARY_MEMORY_UNIQUE_PTR_H_

#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstddef>
#include <new>
#include <type_traits>
#include <memory>

namespace liuyunbin {

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
