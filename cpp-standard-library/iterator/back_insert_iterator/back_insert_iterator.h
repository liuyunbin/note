#ifndef CPP_STANDARD_LIBRARY_ITERATOR_BACK_INSERT_ITERATOR_H_
#define CPP_STANDARD_LIBRARY_ITERATOR_BACK_INSERT_ITERATOR_H_

#include <iterator>

namespace liuyunbin {

/**************************************
 *                                    *
 *         back_insert_iterator       *
 *                                    *
 *         back_inserter              *
 *                                    *
 **************************************/

template <typename Container>
class back_insert_iterator {
 public:
  using        value_type = void;
  using   difference_type = void;
  using           pointer = void;
  using         reference = void;
  using iterator_category = std::output_iterator_tag;

  using container_type = Container;

  explicit back_insert_iterator(Container& container)
      : container_(&container) {}

  back_insert_iterator& operator=(const typename Container::value_type& value) {
    container_->push_back(value);
    return *this;
  }

  back_insert_iterator& operator=(typename Container::value_type&& value) {
    container_->push_back(std::move(value));
    return *this;
  }

  back_insert_iterator& operator* ()    { return *this; }
  back_insert_iterator& operator++()    { return *this; }
  back_insert_iterator& operator++(int) { return *this; }

 private:
  Container* container_;
};

template <typename Container>
back_insert_iterator<Container> back_inserter(Container& x) {
  return back_insert_iterator<Container>(x);
}

}  // namespace liuyunbin

#endif
