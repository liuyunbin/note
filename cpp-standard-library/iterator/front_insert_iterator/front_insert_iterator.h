#ifndef CPP_STANDARD_LIBRARY_ITERATOR_FRONT_INSERT_ITERSTOR_H_
#define CPP_STANDARD_LIBRARY_ITERATOR_FRONT_INSERT_ITERATOR_H_

#include <iterator>

namespace liuyunbin {

/**************************************
 *                                    *
 *        front_insert_iterator       *
 *                                    *
 *        front_inserter              *
 *                                    *
 **************************************/

template <typename Container>
class front_insert_iterator {
 public:
  using        value_type = void;
  using   difference_type = void;
  using           pointer = void;
  using         reference = void;
  using iterator_category = std::output_iterator_tag;

  using container_type = Container;

  explicit front_insert_iterator(Container& container)
      : container_(&container) {}

  front_insert_iterator& operator=(
      const typename Container::value_type& value) {
    container_->push_front(value);
    return *this;
  }

  front_insert_iterator& operator=(typename Container::value_type&& value) {
    container_->push_front(std::move(value));
    return *this;
  }

  front_insert_iterator& operator* ()    { return *this; }
  front_insert_iterator& operator++()    { return *this; }
  front_insert_iterator& operator++(int) { return *this; }

 private:
  Container* container_;
};

template <typename Container>
front_insert_iterator<Container> front_inserter(Container& x) {
  return front_insert_iterator<Container>(x);
}

}  // namespace liuyunbin

#endif
