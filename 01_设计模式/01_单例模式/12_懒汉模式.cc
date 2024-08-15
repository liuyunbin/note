
#include <unistd.h>

#include <iostream>
#include <mutex>
#include <thread>

class singleton {
public:
    static singleton* instance() {
        if (ptr == NULL) {
            std::lock_guard<std::mutex> lock(mu);
            if (ptr == NULL) {
                std::cout << "构造单例模式中..." << std::endl;
                sleep(3);
                ptr = new singleton;
                std::cout << "构造单例模式完成" << std::endl;
            }
        }

        std::cout << "获取单例模式" << std::endl;
        return ptr;
    }

protected:
    singleton() {
    }

    singleton(const singleton&) = delete;
    singleton(singleton&&)      = delete;

    singleton operator=(const singleton&) = delete;
    singleton operator=(singleton&&)      = delete;

    static singleton* ptr;
    static std::mutex mu;
};

singleton* singleton::ptr = NULL;
std::mutex singleton::mu;

void test() {
    singleton::instance();
}

int main() {
    std::thread t1(test);
    std::thread t2(test);

    t1.join();
    t2.join();

    return 0;
}
