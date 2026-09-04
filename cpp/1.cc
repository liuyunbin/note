
#include "1.h"

#include <iostream>

#include "2.h"
#include "3.h"

int main() {
    std::cout << x << std::endl;
    std::cout << "get2: " << get2() << std::endl;
    std::cout << "get3: " << get3() << std::endl;

    std::cout << "set2: " << std::endl;
    set2(123);

    std::cout << x << std::endl;
    std::cout << "get2: " << get2() << std::endl;
    std::cout << "get3: " << get3() << std::endl;

    return 0;
}
