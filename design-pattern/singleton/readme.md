
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

## 实现
###  第一个版本
#### 实现
```
class singleton {
public:
    static singleton& instance() { return ins; }

protected:
    singleton() {}

    singleton(const singleton&) = delete;
    singleton(singleton&&)      = delete;

    singleton& operator=(const singleton&) = delete;
    singleton& operator=(singleton&&)      = delete;

    static singleton ins;
};

singleton singleton::ins;
```

#### 分析
1. main 之前就将单例构造好了, 可能导致资源浪费
2. 第一次访问不会有效率的问题, 因为提前构造好了
3. 类的静态变量的构造和析构的顺序不确定, 可能导致问题

### 第二个版本
#### 实现
```
class singleton {
public:
    static singleton* instance() {
        if (ptr == NULL)
            ptr = new singleton;
        return ptr;
    }

protected:
    singleton() {}

    singleton(const singleton&) = delete;
    singleton(singleton&&)      = delete;

    singleton operator=(const singleton&) = delete;
    singleton operator=(singleton&&)      = delete;

    static singleton* ptr;
};

singleton* singleton::ptr = NULL;
```

### 分析
1. 需要时才构造, 避免了资源浪费
2. 第一次访问时才构造, 效率要低一些
3. 构造析构的顺序是固定的
4. 多线程同时第一次访问时, 可能构造出多个对象, 造成内存泄露




















class singleton {
public:
    static singleton& instance() {
        static singleton ins;
        return ins;
    }

protected:
    singleton() {}

    singleton(const singleton&) = delete;
    singleton(singleton&&)      = delete;

    singleton& operator=(const singleton&) = delete;
    singleton& operator=(singleton&&)      = delete;
};
```





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

------------------------------------------------------------
#include <unistd.h>

#include <iostream>
#include <mutex>
#include <thread>

class singleton {
public:
    static singleton* instance() {
        if (ptr == NULL) {
            std::lock_guard<std::mutex> lock(mu);
            if (ptr == NULL) {
                std::cout << "构造单例模式中..." << std::endl;
                sleep(3);
                ptr = new singleton;
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

    static singleton* ptr;
    static std::mutex mu;
};

singleton* singleton::ptr = NULL;
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
