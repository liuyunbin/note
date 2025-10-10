
#include <iostream>

class A {
public:
    A() {
        std::cout << "A 构造函数" << std::endl;
    }

    //    virtual ~A() {
    //        std::cout << "A 析构函数" << std::endl;
    //    }
};

class B : public A {
public:
    B() {
        std::cout << "B 构造函数" << std::endl;
    }

    ~B() {
        std::cout << "B 析构函数" << std::endl;
    }
};

int main() {
    for (;;)
        ;
    return 0;
}
