
#include <unistd.h>

#include <iostream>
#include <mutex>
#include <thread>

class singleton {
public:
    static singleton& instance() {
        std::cout << "获取单例模式" << std::endl;
        if (ins == NULL) {
            std::lock_guard<std::mutex> lock(mu);
            if (ins == NULL) {
                std::cout << "构造单例模式中..." << std::endl;
                // ins = new singleton;
                void* mem = operator new(sizeof(singleton));  // 分配内存
                ins       = static_cast<singleton*>(mem);     // 发布指针
                new (ins) singleton();                        // 构造函数
                std::cout << "构造单例模式完成" << std::endl;
            }
        }
        std::cout << "获取单例完成" << std::endl;
        return *ins;
    }

protected:
    singleton() {
        std::cout << "构造函数执行中..." << std::endl;
        sleep(10);
        std::cout << "构造函数执行后" << std::endl;
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
