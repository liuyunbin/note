
#include <unistd.h>

#include <iostream>
#include <thread>

class singleton {
public:
    static singleton& instance() {
        std::cout << "获取单例模式" << std::endl;
        if (ins == NULL) {
            std::cout << "构造单例模式中..." << std::endl;
            sleep(3);
            ins = new singleton;
            std::cout << "构造单例模式完成" << std::endl;
        }
        std::cout << "获取单例完成" << std::endl;
        return *ins;
    }

protected:
    singleton() {
        //        std::cout << "构造函数" << std::endl;
    }

    singleton(const singleton&) = delete;
    singleton(singleton&&)      = delete;

    singleton& operator=(const singleton&) = delete;
    singleton& operator=(singleton&&)      = delete;

    static singleton* ins;
};

singleton* singleton::ins;

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
