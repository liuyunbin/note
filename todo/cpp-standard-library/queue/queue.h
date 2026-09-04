#ifndef CPP_STANDARD_LIBRARY_QUEUE_H_
#define CPP_STANDARD_LIBRARY_QUEUE_H_

#include <algorithm>
#include <iostream>
#include <iterator>
#include <deque>
#include <vector>

namespace liuyunbin {

template <typename, typename>
class queue;

template <typename T, typename Container> bool operator==(const queue<T, Container>& left, const queue<T, Container>& right);
template <typename T, typename Container> bool operator!=(const queue<T, Container>& left, const queue<T, Container>& right);
template <typename T, typename Container> bool operator< (const queue<T, Container>& left, const queue<T, Container>& right);
template <typename T, typename Container> bool operator<=(const queue<T, Container>& left, const queue<T, Container>& right);
template <typename T, typename Container> bool operator> (const queue<T, Container>& left, const queue<T, Container>& right);
template <typename T, typename Container> bool operator>=(const queue<T, Container>& left, const queue<T, Container>& right);

template <typename T, typename Container = std::deque<T>>
class queue {
  friend bool operator==<>(const queue& left, const queue& right);
  friend bool operator!=<>(const queue& left, const queue& right);
  friend bool operator< <>(const queue& left, const queue& right);
  friend bool operator<=<>(const queue& left, const queue& right);
  friend bool operator> <>(const queue& left, const queue& right);
  friend bool operator>=<>(const queue& left, const queue& right);

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

  queue() {}

  explicit queue(const Container& cont) : c(cont) {}
  explicit queue(Container&& cont) : c(std::move(cont)) {}

  queue(const queue& other) : c(other.c) {}
  queue(queue&& other) : c(std::move(other.c)) {}

  /******************************************
   *                                        *
   *                =                       *
   *                                        *
   ******************************************/

  queue& operator=(queue&& other) {
    if (this != &other) c = std::move(other.c);
    return *this;
  }

  queue& operator=(const queue& other) {
    if (this != &other) c = other.c;
    return *this;
  }

  /*******************************************
   *                                         *
   *               back                      *
   *                                         *
   *               front                     *
   *                                         *
   *******************************************/

        reference back()       { return c.back(); }
  const_reference back() const { return c.back(); }

        reference front()       { return c.front(); }
  const_reference front() const { return c.front(); }

  /*******************************************
   *                                         *
   *                empty                    *
   *                                         *
   *                size                     *
   *                                         *
   *******************************************/

  bool     empty() const { return c.empty(); }
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

  void pop() { c.pop_front(); }

  /*********************************************
   *                                           *
   *                 swap                      *
   *                                           *
   *********************************************/

  void swap(queue& other) {
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
void swap(queue<T, Container>& left, queue<T, Container>& right) {
  left.swap(right);
}

/*********************************************
 *                                           *
 *      == != < <= > >=                      *
 *                                           *
 *********************************************/

template <typename T, typename Container>
bool operator==(const queue<T, Container>& left, const queue<T, Container>& right) {
  return left.c == right.c;
}

template <typename T, typename Container>
bool operator!=(const queue<T, Container>& left, const queue<T, Container>& right) {
  return left.c != right.c;
}

template <typename T, typename Container>
bool operator< (const queue<T, Container>& left, const queue<T, Container>& right) {
  return left.c < right.c;
}

template <typename T, typename Container>
bool operator<=(const queue<T, Container>& left, const queue<T, Container>& right) {
  return left.c <= right.c;
}

template <typename T, typename Container>
bool operator> (const queue<T, Container>& left, const queue<T, Container>& right) {
  return left.c > right.c;
}

template <typename T, typename Container>
bool operator>=(const queue<T, Container>& left, const queue<T, Container>& right) {
  return left.c >= right.c;
}

template <typename T, typename Container = std::vector<T>,
          typename Compare = std::less<typename Container::value_type>>
class priority_queue {
 public:
  using  container_type = Container;
  using   value_compare = Compare;
  using      value_type = typename Container::value_type;
  using       size_type = typename Container::size_type;
  using       reference = typename Container::reference;
  using const_reference = typename Container::const_reference;

  /*****************************************
   *                                       *
   *           constructor                 *
   *                                       *
   *****************************************/

  priority_queue() {}

  explicit priority_queue(const Compare& compare) : comp(compare) {}
  priority_queue(const Compare& compare, const Container& cont)
      : comp(compare), c(cont) {
    std::make_heap(c.begin(), c.end(), comp);
  }

  priority_queue(const Compare& compare, Container&& cont)
      : comp(compare), c(std::move(cont)) {
    std::make_heap(c.begin(), c.end(), comp);
  }

  priority_queue(const priority_queue& other) : comp(other.comp), c(other.c) {}
  priority_queue(priority_queue&& other)
      : comp(std::move(other.comp)), c(std::move(other.c)) {}

  template <typename InputIt>
  priority_queue(InputIt first, InputIt last, const Compare& compare,
                 const Container& cont)
      : comp(compare), c(cont) {
    c.insert(c.end(), first, last);
    std::make_heap(c.begin(), c.end(), comp);
  }

  template <typename InputIt>
  priority_queue(InputIt first, InputIt last,
                 const Compare& compare = Compare(),
                 Container&& cont = Container())
      : comp(compare), c(std::move(cont)) {
    c.insert(c.end(), first, last);
    std::make_heap(c.begin(), c.end(), comp);
  }

  /******************************************
   *                                        *
   *                =                       *
   *                                        *
   ******************************************/

  priority_queue& operator=(priority_queue&& other) {
    if (this != &other) {
      comp = std::move(other.comp);
      c = std::move(other.c);
    }
    return *this;
  }

  priority_queue& operator=(const priority_queue& other) {
    if (this != &other) {
      comp = other.comp;
      c = other.c;
    }
    return *this;
  }

  /*******************************************
   *                                         *
   *                top                      *
   *                                         *
   *******************************************/

  const_reference top() const { return c.front(); }

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

  void push(const T& value) {
    c.push_back(value);
    std::push_heap(c.begin(), c.end(), comp);
  }

  void push(T&& value) {
    c.push_back(std::move(value));
    std::push_heap(c.begin(), c.end(), comp);
  }

  template <typename... Args>
  void emplace(Args... args) {
    c.emplace_back(std::forward<Args>(args)...);
    std::push_heap(c.begin(), c.end(), comp);
  }

  /*********************************************
   *                                           *
   *                 pop                       *
   *                                           *
   *********************************************/

  void pop() {
    std::pop_heap(c.begin(), c.end(), comp);
    c.pop_back();
  }

  /*********************************************
   *                                           *
   *                 swap                      *
   *                                           *
   *********************************************/

  void swap(priority_queue& other) {
    using std::swap;
    swap(comp, other.comp);
    swap(c, other.c);
  }

 private:
  Compare comp;
  Container c;
};

/*********************************************
 *                                           *
 *                 swap                      *
 *                                           *
 *********************************************/

template <typename T, typename Container, typename Compare>
void swap(priority_queue<T, Container, Compare>& left, priority_queue<T, Container, Compare>& right) {
  left.swap(right);
}

}  // namespace liuyunbin

#endif
