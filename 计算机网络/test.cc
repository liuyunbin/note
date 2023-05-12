
#include <iostream>

int main() {
    int a = 10;
    std::cout << typeid(a).name() << std::endl;
    std::cout << sizeof(int*) << std::endl;
    std::cout << sizeof(int) << std::endl;
    return 0;
}
