
#include <iostream>

class singleton {
public:
    static singleton& instance() {
        std::cout << "获取实例" << std::endl;
        return ins;
    }

protected:
    singleton() {
        std::cout << "构造函数" << std::endl;
    }

    singleton(const singleton&) = delete;
    singleton(singleton&&)      = delete;

    singleton& operator=(const singleton&) = delete;
    singleton& operator=(singleton&&)      = delete;

    static singleton ins;
};

singleton singleton::ins;

int main() {
    auto& v = singleton::instance();
    return 0;
}
