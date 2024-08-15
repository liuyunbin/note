
#include <unistd.h>

#include <iostream>
#include <mutex>
#include <thread>

template <typename T>
class singleton {
public:
    static T* instance() {
        if (ptr == NULL) {
            std::lock_guard<std::mutex> lock(mu);
            if (ptr == NULL) {
                std::cout << "构造单例模式中..." << std::endl;
                ptr = new T;
                sleep(3);
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

    static T*         ptr;
    static std::mutex mu;
};

template <typename T>
T* singleton<T>::ptr = NULL;

template <typename T>
std::mutex singleton<T>::mu;

class A : public singleton<A> {
    friend class singleton<A>;

protected:
    A() {
    }
};

void test() {
    A::instance();
}

int main() {
    std::thread t1(test);
    std::thread t2(test);

    t1.join();
    t2.join();

    return 0;
}
