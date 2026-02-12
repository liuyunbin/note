
## 说明
单例模式

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
4. 第一次使用的时候会不会有效率的问题

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
1. main 之前就将单例构造好了, 导致启动变慢, 如果后续不用会导致资源浪费
2. 第一次访问不会有效率的问题, 因为提前构造好了
3. 不同文件类的静态变量的构造和析构的顺序不确定, 可能导致问题

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
1. 需要时才构造, 避免了资源浪费
2. 第一次访问时才构造, 效率要低一些
3. 构造析构的顺序是固定的
4. 多线程同时第一次访问时, 可能构造出多个对象, 造成内存泄露 -- 21.cc


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
1. 使用锁保证只能产生一个实例
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
1. 缩小了锁的范围, 只有实例未初始化时才使用锁
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
1. 完美的解决了之前的问题 -- 51.cc
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
1. 完美的解决了之前的问题
2. 但需要 C++11, 因为 C++11 保证函数静态变量线程安全
3. 第一次使用的时候, 由于要实例化变量, 效率会低一些 -- 可以通过在主函数提取初始化提高效率

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

