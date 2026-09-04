
#include "test_template.h"

template <typename T>
void Base<T>::test_base() {
    std::cout << "test" << std::endl;
}

template class Base<int>;
