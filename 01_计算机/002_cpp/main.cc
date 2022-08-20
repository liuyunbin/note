#include <iostream>
#include <typeinfo>
#include <ctime>
#include <type_traits>
#include <climits>

int main() {
    std::cout << std::boolalpha;
    std::cout << "int: " << std::is_same<int, std::time_t>::value << std::endl;
    std::cout << "long: " << std::is_same<long, std::time_t>::value << std::endl;
    std::cout << "long long: " << std::is_same<long long, std::time_t>::value << std::endl;
    std::cout << "unsigned long: " << std::is_same<unsigned long, std::time_t>::value << std::endl;
    std::cout << "unsigned long long: " << std::is_same<unsigned long long, std::time_t>::value << std::endl;
    std::time_t t = LONG_MIN;
    std::cout << t << std::endl;
    std::cout << sizeof(std::time_t) << std::endl;

    //std::cout << std::ctime(&t) << std::endl;
    std::cout << INT_MAX <<  std::endl;
    std::cout << LONG_MAX <<  std::endl;

    struct tm tm;
    strptime("1970-01-01 00:00:00", "%Y-%m-%d %H:%M:%S", &tm);
    std::cout << mktime(&tm) << std::endl;
    return 0;
}
