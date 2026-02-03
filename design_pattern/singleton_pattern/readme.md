
## 要求
1. 整个进程只有一个实例
    * 需要使用静态变量
2. 该实例不能赋值
    * 需要将 拷贝 移动 构造函数函数删除
    * 需要将 拷贝 移动 赋值运算函数删除

## 问题
1. 什么时候创建
    * 第一次使用的时才初始化 --- 懒汉模式
    * 程序加载的时候就初始化 --- 饿汉模式
2. 创建的时候是否线程安全, 是否需要锁, 效率怎么样
3. 使用的时候是否线程安全, 是否需要锁, 效率怎么样




* 需要使用互斥锁来保证线程安全
* 尽量减少互斥锁的使用来提高效率

01_饿汉模式.cc ----- 单个类(C++11 之前) -- 不建议使用
02_饿汉模式.cc ----- 模板类(C++11 之前) -- 不建议使用
03_饿汉模式.cc ----- 单个类(C++11) ------ 建议使用
04_饿汉模式.cc ----- 模板类(C++11) ------ 建议使用

11_懒汉模式.cc ----- 单个类(多线程可能出问题) -- 不建议使用
12_懒汉模式.cc ----- 单个类(多线程安全) -- 也可能出问题 -- 不建议使用
13_懒汉模式.cc ----- 模板类(多线程安全) -- 也可能出问题 -- 不建议使用


#include <iostream>

class singleton {
public:
    static singleton& instance() {
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

    static singleton ins;
};

singleton singleton::ins;

int main() {
    singleton& ptr = singleton::instance();
    return 0;
}

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

#include <iostream>

class singleton {
public:
    static singleton& instance() {
        static singleton ins;
        std::cout << "获取单例模式" << std::endl;
        return ins;
    }

private:
    singleton() {
        std::cout << "构造单例模式" << std::endl;
    }

    singleton(const singleton&) = delete;
    singleton(singleton&&)      = delete;

    singleton operator=(const singleton&) = delete;
    singleton operator=(singleton&&)      = delete;
};

int main() {
    singleton& ptr = singleton::instance();
    return 0;
}

#include <iostream>

template <typename T>
class singleton {
public:
    static T& instance() {
        static T ins;
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
};

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
