#include <iostream>

#include "log.h"

int main() {
    double x = 9007199254740995;
    std::cout << std::fixed << x << std::endl;
    test_double("", x);
    return 0;
}
