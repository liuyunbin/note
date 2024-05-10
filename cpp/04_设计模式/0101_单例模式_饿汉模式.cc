
#include <unistd.h>

#include <iostream>

class singleton {
  public:
    static singleton* instance() {
        std::cout << "获取单例模式" << std::endl;
        return ptr;
    }

  protected:
    singleton() {
        std::cout << "构造单例模式" << std::endl;
    }

    static singleton* ptr;
};

singleton* singleton::ptr = new singleton();

int main() {
    std::cout << "休眠 3 秒" << std::endl;
    sleep(3);

    singleton* ptr = singleton::instance();

    return 0;
}
