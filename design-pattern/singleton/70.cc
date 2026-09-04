
#include <iostream>

template <typename T>
class singleton {
public:
    static T& instance() {
        std::cout << "获取实例" << std::endl;
        static T ins;
        return ins;
    }

protected:
    singleton() {
        std::cout << "构造函数 基类" << std::endl;
    }

    singleton(const singleton&) = delete;
    singleton(singleton&&)      = delete;

    singleton& operator=(const singleton&) = delete;
    singleton& operator=(singleton&&)      = delete;
};

class A : public singleton<A> {
    friend class singleton<A>;

private:
    A() {
        std::cout << "构造函数 子类" << std::endl;
    }
};

int main() {
    auto& v = A::instance();
    return 0;
}
