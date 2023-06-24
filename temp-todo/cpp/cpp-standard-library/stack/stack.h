#ifndef CPP_STANDARD_LIBRARY_STACK_H_
#define CPP_STANDARD_LIBRARY_STACK_H_

#include <iostream>
#include <iterator>
#include <deque>

namespace liuyunbin {

template <typename, typename>
class stack;

template <typename T, typename Container> bool operator==(const stack<T, Container>& left, const stack<T, Container>& right);
template <typename T, typename Container> bool operator!=(const stack<T, Container>& left, const stack<T, Container>& right);
template <typename T, typename Container> bool operator< (const stack<T, Container>& left, const stack<T, Container>& right);
template <typename T, typename Container> bool operator<=(const stack<T, Container>& left, const stack<T, Container>& right);
template <typename T, typename Container> bool operator> (const stack<T, Container>& left, const stack<T, Container>& right);
template <typename T, typename Container> bool operator>=(const stack<T, Container>& left, const stack<T, Container>& right);

template <typename T, typename Container = std::deque<T>>
class stack {
  friend bool operator==<>(const stack& left, const stack& right);
  friend bool operator!=<>(const stack& left, const stack& right);
  friend bool operator< <>(const stack& left, const stack& right);
  friend bool operator<=<>(const stack& left, const stack& right);
  friend bool operator> <>(const stack& left, const stack& right);
  friend bool operator>=<>(const stack& left, const stack& right);

 public:
  using  container_type = Container;
  using      value_type = typename Container::value_type;
  using       size_type = typename Container::size_type;
  using       reference = typename Container::reference;
  using const_reference = typename Container::const_reference;

  /*****************************************
   *                                       *
   *           constructor                 *
   *                                       *
   *****************************************/

  stack() {}

  explicit stack(const Container& cont) : c(cont) {}
  explicit stack(Container&& cont) : c(std::move(cont)) {}

  stack(const stack& other) : c(other.c) {}
  stack(stack&& other) : c(std::move(other.c)) {}

  /******************************************
   *                                        *
   *                =                       *
   *                                        *
   ******************************************/

  stack& operator=(stack&& other) {
    if (this != &other) c = std::move(other.c);
    return *this;
  }

  stack& operator=(const stack& other) {
    if (this != &other) c = other.c;
    return *this;
  }

  /*******************************************
   *                                         *
   *               top                       *
   *                                         *
   *******************************************/

        reference top()       { return c.back(); }
  const_reference top() const { return c.back(); }

  /*******************************************
   *                                         *
   *                empty                    *
   *                                         *
   *                size                     *
   *                                         *
   *******************************************/

      bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }

  /********************************************
   *                                          *
   *                push                      *
   *                                          *
   *                emplace                   *
   *                                          *
   ********************************************/

  void push(const T& value) { c.push_back(value); }
  void push(T&& value) { c.push_back(std::move(value)); }

  template <typename... Args>
  void emplace(Args... args) {
    c.emplace_back(std::forward<Args>(args)...);
  }

  /*********************************************
   *                                           *
   *                 pop                       *
   *                                           *
   *********************************************/

  void pop() { c.pop_back(); }

  /*********************************************
   *                                           *
   *                 swap                      *
   *                                           *
   *********************************************/

  void swap(stack& other) {
    using std::swap;
    swap(c, other.c);
  }

 private:
  Container c;
};

/*********************************************
 *                                           *
 *                 swap                      *
 *                                           *
 *********************************************/

template <typename T, typename Container>
void swap(stack<T, Container>& left, stack<T, Container>& right) {
  left.swap(right);
}

/*********************************************
 *                                           *
 *      == != < <= > >=                      *
 *                                           *
 *********************************************/

template <typename T, typename Container>
bool operator==(const stack<T, Container>& left, const stack<T, Container>& right) {
  return left.c == right.c;
}

template <typename T, typename Container>
bool operator!=(const stack<T, Container>& left, const stack<T, Container>& right) {
  return left.c != right.c;
}

template <typename T, typename Container>
bool operator< (const stack<T, Container>& left, const stack<T, Container>& right) {
  return left.c < right.c;
}

template <typename T, typename Container>
bool operator<=(const stack<T, Container>& left, const stack<T, Container>& right) {
  return left.c <= right.c;
}

template <typename T, typename Container>
bool operator> (const stack<T, Container>& left, const stack<T, Container>& right) {
  return left.c > right.c;
}

template <typename T, typename Container>
bool operator>=(const stack<T, Container>& left, const stack<T, Container>& right) {
  return left.c >= right.c;
}

}  // namespace liuyunbin

#endif
