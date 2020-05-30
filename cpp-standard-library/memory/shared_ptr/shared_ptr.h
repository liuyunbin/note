#ifndef CPP_STANDARD_LIBRARY_MEMORY_SHARED_PTR_H_
#define CPP_STANDARD_LIBRARY_MEMORY_SHARED_PTR_H_

#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstddef>
#include <new>
#include <type_traits>
#include <memory>

namespace liuyunbin {

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

}  // namespace liuyunbin

#endif
