
#include <iostream>
#include <thread>
#include <chrono>

class singleton {
public:
    static singleton& instance() {
        return ins;
    }

    singleton(const singleton&) = delete;
    singleton(singleton&&) = delete;
    singleton& operator=(const singleton&) = delete;
    singleton& operator=(singleton&&) = delete;

    void hello() {
        std::cout << "Hello from singleton at " << this << std::endl;
    }

private:
    singleton() {
        // 模拟慢构造，让两个线程容易同时进入
        std::cout << "Constructing singleton at " << this << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    static singleton ins;  // 类静态成员，饿汉式
};

// 类外初始化
singleton singleton::ins;

void threadFunc(int id) {
    singleton& s = singleton::instance();
    std::cout << "Thread " << id << " got singleton at " << &s << std::endl;
    s.hello();
}

int main() {
    std::thread t1(threadFunc, 1);
    std::thread t2(threadFunc, 2);

    t1.join();
    t2.join();

    return 0;
}

