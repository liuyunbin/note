
# 程序内存结构
```
* 正文段(text)
    * 存储程序本身, 包括函数, 常量等
    * 磁盘中需要存储
    * 内存中只存储一份, 不同的进程可以共享
    * 只读
* 数据段(data)
    * 存储初始化的全局变量或静态变量
    * 磁盘中需要存储
    * 内存中每个进程一份, 不同的进程有自己的数据段
    * 可修改
* bss
    * 存储未初始化的全局变量或静态变量
    * 磁盘中不需要存储
    * 内存中每个进程一份, 不同的进程有自己的数据段
    * 程序启动时初始化为 0
    * 可修改
* 栈: 磁盘中不需要存储
* 堆: 磁盘中不需要存储
* 使用 size 可以查看各个部分的大小
```

# 常量 变量 作用域 存储
```
* 普通全局变量
    * 作用域: 全局
    *   存储:
        * data -- 已初始化, 可写
        * bss --- 未初始化, 程序启动时将初始化为0
        * rodata -- 只读
    * 静态存储期
* 静态全局变量
    * 作用域: 文件内
    *   存储: data/bss/rodata
    * 静态存储期
* 普通局部变量
    * 作用域: 块内
    *   存储: 栈
    * 自动存储期
* 静态局部变量
    * 作用域: 块内
    *   存储: data/bss/rodata
    * 静态存储期
* 堆
    * 动态存储期



* constexpr: 常量, 在编译期确定
* const: 只读变量, 可能在编译期确定, 也可能在允许期确定

       int a1;
static int a2;
       const int a3 = 123;
static const int a4 = 123;

void test() {
    int e;
    static int f;



}




# const, constexpr 和 static
* 在哪儿存储
    * 自动存储期: 非静态局部变量 --- 栈
    * 静态存储期: 静态或全局变量 --- rodata 或 data 或 bss
* 是否存在, 是否会被编译器优化
    * 有没有取地址或绑定引用
* 是否是编译期常量
    * const 可能是编译期常量, 也可能是运行期常量
    * constexpr 只可能是编译期常量
* static 作用
    * 将 全局变量或函数 的作用域局限在文件中
    * 将 函数内变量 的存储位置由 栈 转换到 data 或 rodata 或 bss, 变量的作用域不变
    * 将 类的成员变量或函数 和类绑定, 而不是具体的对象绑定
```






拷贝赋值运算符为什么要返回引用: 赋值是为了修改对象而不是创建对象


crtp
将派生类作为模板参数传递给它自己的基类
实现静态多态

c++模板并实现可以放到cpp文件中的, 需要显示实例化


类: 具有相同属性和功能的对象的抽象集合
      对对象的抽象
抽象类: 对类的抽象
             包含纯虚函数
接口: 对行为的抽象

## 申明和定义
* 变量使用前必须申明或定义
* 多个文件使用相同的变量时, 注意防止重复定义, 使用前确保初始化已完成

## 初始化
* 全局变量
    * 在 main 函数运行之前 或 动态库装载时初始化
    * 不同的文件的变量的初始化顺序不一定
* 静态全局变量
    *同上
* 类静态变量
    * 同上
* 函数静态变量
    *在第一次经过的时候才初始化
    * C++ 11 及以后是线程安全的

## 构造函数
* 默认构造函数
* 拷贝构造函数
* 移动构造函数

## 析构函数
多态时, 要使用虚析构函数

深拷贝和浅拷贝
拷贝赋值运算
移动赋值运算

RAII

const int i = 1;        # 只在本文件内有效
extern const int i = 1; # 可以在其他文件中使用

std::getline(std::cin, str);  // 读取一行, 包括换行符, str 不会存储换行符

整数除以整数 -- C++11
* 无论正负, 小数部分直接舍弃
* 商的符号由除数和被除数决定
* 余数的符号只由被除数决定

浮点数要注意精度

static_cast      -- 不含底层 const 的转换, 明确定义
const_cast       -- 添加或删除底层 const 的转换 -- 很少用
reinterpret_cast -- 重新解释底层存储 -- 很少用
dynamic_cast     -- 运行时, 基类 => 派生类 -- 可能损失效率

mutable 类可变成员

explicit

string
* 短字符串优化,
* 所以 swap 可能会真正交换元素,
* 而不是拷贝指针

atomic -------- 原子操作
mutex --------- 互斥锁
lock_guard ---- 构造函数加锁, 析构函数解锁, 一次只能针对一个互斥锁
scoped_lock --- 构造函数加锁, 析构函数解锁, 一次可以针对多个互斥锁 -- C++ 17
unique_lock --- 一般和条件变量一起使用

condition_variable -- 条件变量和 unique_lock 一起用
notify_one ---------- 通知一个
notify_all ---------- 通知所有
wait ---------------- 等待

thread --------- 线程
  joinable() --- 判断线程是否可以回收
  join() ------- 等待线程退出
  detach()------ 使线程处于分离状态

sleep_for()----休眠
sleep_until()--休眠, 直到

std::chrono::duration<double>
std::chrono::seconds

const std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
const std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
   std::chrono::duration_cast<std::chrono::microseconds>(end - now)

std::shared_ptr<T> p = std::make_shared...
std::shared_ptr<T>(q, d)-- p 可以是普通指针, d 为析构时的处理
p.use_count()
p.unique() ----- C++20
p.get()
p.reset(...)
p.owner_before() --- 可用于排序

std::unique_ptr<T> p = std::make_unique... C++14
std::unique_ptr<T, D>(q, d) -- p 可以是普通指针, d 为析构时的处理
p.release()------------------- 放弃指针的占用, 并返回
p.reset(...)

std::weak_ptr -- 不影响引用计数
w.reset()
w.unique()
w.use_count()
w.expired()-- 所关联的智能指针是否存在
w.lock()----- 返回智能指针
p.owner_before() --- 可用于排序

std::enable_shared_from_this -- 返回自身对应的智能指针
shared_from_this -------------- 返回自身对应的智能指针

使用动态分配内存的场景
1. 不知道有多少元素(std::vector)
2. 不知道对象的准确类型
3. 多个对象共享数据

## 高级特性
* 对于普通程序员来说，模板元编程只需明白原理，实现能看懂即可, 一般也不会用到

