
#include <unistd.h>

#include <iostream>
#include <thread>

class singleton {
  public:
    static singleton* instance() {
        if (ptr == NULL) {
            ptr = new singleton;
        }

        std::cout << "获取单例模式" << std::endl;
        return ptr;
    }

  protected:
    singleton() {
        std::cout << "构造单例模式中..." << std::endl;
        sleep(3);
        std::cout << "构造单例模式完成" << std::endl;
    }

    static singleton* ptr;
};

singleton* singleton::ptr = NULL;

void test() {
    singleton::instance();
}

int main() {
    std::cout << "休眠 3 秒" << std::endl;
    sleep(3);

    std::thread t1(test);
    std::thread t2(test);

    t1.join();
    t2.join();

    return 0;
}
