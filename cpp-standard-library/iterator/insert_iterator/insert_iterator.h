#ifndef CPP_STANDARD_LIBRARY_ITERATOR_INSERT_ITERATOR_H_
#define CPP_STANDARD_LIBRARY_ITERATOR_INSERT_ITERATOR_H_

#include <iterator>

namespace liuyunbin {

/**************************************
 *                                    *
 *           insert_iterator          *
 *                                    *
 *           inserter                 *
 *                                    *
 **************************************/

template <typename Container>
class insert_iterator {
 private:
  using iterator = typename Container::iterator;

 public:
  using        value_type = void;
  using   difference_type = void;
  using           pointer = void;
  using         reference = void;
  using iterator_category = std::output_iterator_tag;

  using    container_type = Container;

  explicit insert_iterator(Container& container, iterator iter)
      : container_(&container), iter_(iter) {}

  insert_iterator& operator=(const typename Container::value_type& value) {
    iter_ = container_->insert(iter_, value);
    ++iter_;
    return *this;
  }

  insert_iterator& operator=(typename Container::value_type&& value) {
    iter_ = container_->insert(iter_, std::move(value));
    ++iter_;
    return *this;
  }

  insert_iterator& operator* ()    { return *this; }
  insert_iterator& operator++()    { return *this; }
  insert_iterator& operator++(int) { return *this; }

 private:
  Container* container_;
  iterator iter_;
};

template <typename Container, typename Iterator>
insert_iterator<Container> inserter(Container& x, Iterator it) {
  using iterator = typename Container::iterator;
  return insert_iterator<Container>(x, iterator(it));
}

}  // namespace liuyunbin

#endif
