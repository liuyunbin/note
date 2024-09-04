
#include <time.h>

#include <chrono>
#include <iostream>

using namespace std::chrono;

int main() {
    time_point<system_clock> t1 = system_clock::now();
    for (int i = 0; i < 10000; ++i)
        tzset();
    time_point<system_clock> t2 = system_clock::now();

    duration<double> diff = t2 - t1;

    std::cout << diff.count() << std::endl;
    return 0;
}
