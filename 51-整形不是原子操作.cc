
#include <functional>
#include <iostream>
#include <thread>

int count = 0;
int n     = 100000;

void add() {
    for (int i = 0; i != n; ++i)
        ++count;
}

void sub() {
    for (int i = 0; i != n; ++i)
        --count;
}
int main() {
    std::thread thread1(add);
    std::thread thread2(sub);

    thread1.join();
    thread2.join();

    std::cout << count << std::endl;

    return 0;
}
