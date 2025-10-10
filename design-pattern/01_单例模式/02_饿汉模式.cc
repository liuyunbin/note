
#include <iostream>

template <typename T>
class singleton {
public:
    static T& instance() {
        std::cout << "获取单例模式" << std::endl;
        return ins;
    }

protected:
    singleton() {
        std::cout << "构造单例模式" << std::endl;
    }
    singleton(const singleton&) = delete;
    singleton(singleton&&)      = delete;

    singleton operator=(const singleton&) = delete;
    singleton operator=(singleton&&)      = delete;

    static T ins;
};

template <typename T>
T singleton<T>::ins;

class A : public singleton<A> {
    friend class singleton<A>;

protected:
    A() {
    }
};

int main() {
    A& ptr = A::instance();
    return 0;
}
