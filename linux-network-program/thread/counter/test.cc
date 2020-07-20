
#include "counter.h"

#include <functional>
#include <iostream>
#include <thread>

void function(Counter& count) {
    for (int i = 0; i != 100; ++i)
        ++count;
}

int main() {
    Counter count;

    std::thread thread1(function, std::ref(count));
    std::thread thread2(function, std::ref(count));

    thread1.join();
    thread2.join();

    std::cout << count.get_value() << std::endl;

    return 0;
}
