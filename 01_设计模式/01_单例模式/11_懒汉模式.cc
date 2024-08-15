
#include <unistd.h>

#include <iostream>
#include <thread>

class singleton {
public:
    static singleton* instance() {
        if (ptr == NULL) {
            std::cout << "构造单例模式中..." << std::endl;
            ptr = new singleton;
            sleep(3);
            std::cout << "构造单例模式完成" << std::endl;
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
};

singleton* singleton::ptr = NULL;

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
