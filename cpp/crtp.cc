
#include <iostream>

template <typename T>
class Base {
public:
    Base() {
    }
    void test_base();
};

class Derived : public Base<Derived> {
public:
    Derived() {
    }

    void test_dervied() {
        std::cout << "这是子类: " << std::endl;
    }
};

template <typename T>
void Base<T>::test_base() {
    std::cout << "这是父类: " << std::endl;
    static_cast<Derived*>(this)->test_dervied();
}

int main() {
    Derived d;
    d.test_base();
    return 0;
}
