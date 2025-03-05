
#ifndef CPP_TEMPLATE_H_
#define CPP_TEMPLATE_H_

#include <iostream>

template <typename T>
class Base {
public:
    Base() {
    }
    void test_base();
};

extern template class Base<int>;

#endif
