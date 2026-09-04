
#include <iostream>
#include <mutex>

class singleton {
public:
    static singleton& instance() {
        std::cout << "获取实例" << std::endl;
        if (ins == NULL) {
            std::lock_guard<std::mutex> lock(mu);
            ins = new singleton;
        }
        return *ins;
    }

protected:
    singleton() {
        std::cout << "构造函数" << std::endl;
    }

    singleton(const singleton&) = delete;
    singleton(singleton&&)      = delete;

    singleton& operator=(const singleton&) = delete;
    singleton& operator=(singleton&&)      = delete;

    static singleton* ins;
    static std::mutex mu;
};

singleton* singleton::ins = NULL;
std::mutex singleton::mu;

int main() {
    auto& v = singleton::instance();
    return 0;
}
