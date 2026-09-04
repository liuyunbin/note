
# 单例模式
## 需求
* 为了使资源在整个程序运行的过程中只要一份, 例如, 日志系统, 配置系统等

## 具体要求
1. 整个进程只有一个实例
    * 需要使用 全局变量 或 全局静态变量 或 类静态变量 或 函数静态变量
2. 该实例不能赋值以及从外部构建
    * 需要将 拷贝 移动 构造函数函数删除
    * 需要将 拷贝 移动 赋值运算函数删除

## 需要考虑的问题
1. 创建
    * 第一次使用的时才创建 --- 懒汉模式
        * 第一次调用的时候会慢一些
        * 是否线程安全, 效率怎么样
    * 程序加载的时候就创建 --- 饿汉模式
        * 不同文件的文件构造和析构顺序可能导致问题
        * 如果不使用会不会导致资源浪费
        * 程序启动会变慢
2. 使用
    * 是否线程安全, 效率怎么样
3. 销毁
    * 是否可以主动销毁释放资源

## 实现
###  第一个版本
#### 实现 -- 10.cc
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
1. 创建: 程序加载的时候就创建 --- 饿汉模式
    * 不同文件的文件构造顺序可能导致问题
    * 如果不使用会不会导致资源浪费
    * 程序启动会变慢
2. 使用: 线程安全, 效率很高
3. 销毁: 不同文件的文件析构顺序可能导致问题

### 第二个版本
#### 实现 -- 20.cc
```
class singleton {
public:
    static singleton& instance() {
        if (ins == NULL)
            ins = new singleton;
        return *ins;
    }

protected:
    singleton() {
    }

    singleton(const singleton&) = delete;
    singleton(singleton&&)      = delete;

    singleton& operator=(const singleton&) = delete;
    singleton& operator=(singleton&&)      = delete;

    static singleton* ins;
};

singleton* singleton::ins;
```

#### 分析
1. 创建:
    * 第一次使用的时才创建 --- 懒汉模式
    * 第一次调用的时候会慢一些
    * 线程不安全, 多线程同时第一次访问时, 可能构造多个对象 -- 21.cc
2. 使用
    * 线程不安全, 构造过程的赋值操作不是原子操作
    * 多个 if 判断, 效率变化不大
3. 销毁: 析构的顺序是固定的

### 第三个版本
#### 实现 -- 30.cc
```
class singleton {
public:
    static singleton& instance() {
        std::lock_guard<std::mutex> lock(mu);
        if (ins == NULL)
            ins = new singleton;
        return *ins;
    }

protected:
    singleton() {
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
```

#### 分析
1. 使用锁保证只能产生一个实例 -- 解决线程安全
2. 但每次访问实例都使用锁, 导致效率低

### 第四个版本
#### 实现 -- 40.cc
```
class singleton {
public:
    static singleton* instance() {
    static singleton& instance() {
        if (ins == NULL) {
            std::lock_guard<std::mutex> lock(mu);
            ins = new singleton;
        }
        return *ins;
    }

protected:
    singleton() {}

    singleton(const singleton&) = delete;
    singleton(singleton&&)      = delete;

    singleton& operator=(const singleton&) = delete;
    singleton& operator=(singleton&&)      = delete;

    static singleton* ins;
    static std::mutex mu;
};

singleton* singleton::ins = NULL;
std::mutex singleton::mu;
```

#### 分析
1. 缩小了锁的范围, 只有实例未初始化时才使用锁 -- 优化
2. 多个线程同时实例化时, 可能导致内存泄漏 -- 41.cc

### 第五个版本 --- 双重检查锁
#### 实现 -- 50.cc
```
class singleton {
public:
    static singleton* instance() {
    static singleton& instance() {
        if (ins == NULL) {
            std::lock_guard<std::mutex> lock(mu);
            if (ins == NULL)
                ins = new singleton;
        }
        return *ins;
    }

protected:
    singleton() {}

    singleton(const singleton&) = delete;
    singleton(singleton&&)      = delete;

    singleton& operator=(const singleton&) = delete;
    singleton& operator=(singleton&&)      = delete;

    static singleton* ins;
    static std::mutex mu;
};

singleton* singleton::ins = NULL;
std::mutex singleton::mu;
```

#### 分析
1. 完美的解决了之前的问题 -- 优化 -- 51.cc
2. 系统的优化以及赋值操作不是原子操作, 多线程还是可能有问题 -- 52.cc

### 第六个版本
#### 实现 -- 60.cc
```
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

#### 分析
1. 完美的解决了之前的问题 -- 优化
2. 但需要 C++11, 因为 C++11 保证函数静态变量线程安全
3. 第一次使用的时候, 由于要实例化变量, 效率会低一些 -- 可以通过在主函数提前初始化提高效率

### 第七个版本
#### 实现 -- 70.cc
```
template <typename T>
class singleton {
public:
    static T& instance() {
        static T ins;
        return ins;
    }

protected:
    singleton() {}

    singleton(const singleton&) = delete;
    singleton(singleton&&)      = delete;

    singleton& operator=(const singleton&) = delete;
    singleton& operator=(singleton&&)      = delete;
};

class A : public singleton<A> {
    friend class singleton<A>;

private:
    A() {}
};
```

#### 分析
1. 使用模板便于子类使用单例模式
2. 子类的构造函数的访问控制
    * public, 可以从外部构造和子类对象 -- 禁止
    * private, 禁止从外部和子类构造对象 -- 最好
    * protected, 禁止从外部构造对象, 子类可以构造 -- 一般不要
3. 为什么使用友元
    * 便于父类使用子类的构造函数

## 参考资源
* https://www.aristeia.com/Papers/DDJ_Jul_Aug_2004_revised.pdf

