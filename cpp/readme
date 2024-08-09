
## 存储布局
* 正文段(text)
    * 存储程序本身, 只读, 可共享
    * 内存中只存储一份, 磁盘中需要存储
* 数据段(data)
    * 存储初始化的全局变量或静态变量
    * 内存中每个进程一份, 磁盘中需要存储
* bss
    * 存储未初始化的全局变量或静态变量
    * 内存中每个进程一份, 磁盘中不需要存储
    * 程序启动时初始化为 0
* 栈: 磁盘中不需要存储
* 堆: 磁盘中不需要存储
* 使用 size 可以查看各个部分的大小

## 申明和定义
* 变量使用前必须申明或定义
* 多个文件使用相同的变量时, 注意防止重复定义, 使用前确保初始化已完成

## 初始化
* 全局变量
    * 在 main 函数运行之前 或 动态库装载时初始化
    * 不同的文件的变量的初始化顺序不一定
* 静态全局变量
    * 同上
* 类静态变量
    * 同上
* 函数静态变量
    * 在第一次经过的时候才初始化
    * C++11 及以后是线程安全的

       const int i = 1; # 只在本文件内有效
extern const int i = 1; # 可以在其他文件中使用

std::getline(std::cin, str); // 读取一行, 包括换行符, str 不会存储换行符

整数除以整数, 无论正负, 小数部分直接舍弃
商的符号由除数和被除数决定
余数的符号只由被除数决定

     static_cast -- 不含底层const的转换, 明确定义, 比如, long -> int, void* -> int*
      const_cast --     底层const的转换, 比如, const int* => int*
reinterpret_cast -- 重新解释底层存储, 比如 long* -> double*
    dynamic_cast

mutable 类可变成员

explicit

string 短字符串优化, 所以 swap 可能会真正交换元素, 而不是拷贝指针

thread --------- 线程
  joinable() --- 判断线程是否可以回收
  join() ------- 等待线程退出
  detach() ----- 使线程处于分离状态
sleep_for() ---- 休眠
sleep_until() -- 休眠, 直到

atomic -------- 原子操作
mutex --------- 互斥锁, 需要手动加解锁
shared_mutex -- 共享锁, 应该很少用

lock_guard --- 构造函数对互斥锁加锁, 析构函数对互斥锁解锁, 一次只能针对一个互斥锁
unique_lock -- 一般和条件变量一起使用
scoped_lock -- 构造函数对互斥锁加锁, 析构函数对互斥锁解锁, 一次可以针对多个互斥锁 -- C++17
shared_lock -- 处理共享锁, 应该很少用

defer_lock --- 不加锁
try_to_lock -- 会尝试加锁, 失败就退出
adopt_lock --- 如果当前线程已加锁, 则不再加锁, 否则, 正常加锁

condition_variable -- 条件变量, 和 unique_lock 一起用
    notify_one ------ 通知一个
    notify_all ------ 通知所以
    wait ------------ 等待

std::shared_ptr
	* 初始化
	    * std::shared_ptr<T>(p)    -- p 指向动态分配的内存 -- 不建议
		* std::shared_ptr<T>(q, d) -- p 可以是普通指针, d 为析构时的处理
		* std::make_shared -- 建议
	p.use_count()
	p.unique()
	p.get()
	p.reset(...)
std::unique_ptr
	初始化
	    * std::unique_ptr<T>(p)    -- p 指向动态分配的内存 -- 不建议
		* std::shared_ptr<T, D>(q, d) -- p 可以是普通指针, d 为析构时的处理, 处于效率的考虑, 删除器使用模板
		* std::make_unique -- 建议, C++14
	p.release() -- 放弃指针的占用, 并返回
	p.reset(...)
std::weak_ptr -- 不影响引用计数
	w.reset()
	w.unique()
	w.use_count()
	w.expired() -- 所关联的智能指针是否存在
	w.lock() -- 返回智能指针

使用动态分配内存的场景
1. 不知道有多少元素(std::vector)
2. 不知道对象的准确类型
3. 多个对象共享数据

## 高级特性
* 对于普通程序员来说，模板元编程只需明白原理，实现能看懂即可, 一般也不会用到

## ubuntu 下设置生成 core
```
$ ulimit -c unlimited           # 设置允许生成的 core 文件大小不受限制
$                               # 可以考虑写入配置项 bashrc
$ echo "kernel.core_pattern=%e.%p" >> /etc/sysctl.conf
$                               # 将core命名方式写入配置文件: 文件名.进程号
$ sudo sysctl -p                # 使配置生效
$ sudo systemctl stop    apport # 停止此服务, 该服务会自动收集 core 文件
$ sudo systemctl disable apport # 禁止改服务自动启动
```

## core 不能生成的原因
* core 文件大小受 ulimit 的限制
* 当前进程没有权限在指定目录生成文件
* 指定目录的指定文件已存在, 但改进程无权修改

