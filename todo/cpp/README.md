
## 简介

## 申明和定义
* 变量使用前必须申明或定义
* 多个文件使用相同的变量时, 注意防止重复定义, 使用前确保初始化已完成

## 赋值和初始化
* 初始化使用构造函数
* 赋值使用重载的赋值运算符

## 循环
* 普通循环: for(int i = 0; i < 10; ++i)
* 普通循环: for(.. it = ve.begin(); it != ve.end(); ++it)
* 范围for:  for(auto& v : ve)
* 范围for:  for(const auto& v : ve)
* 推荐使用范围for, 更方便

## 函数
* 参数传递即可以使用值传递也可以使用引用传递
* 使用 tuple 可以返回多个值

## 类
* 使用 `.` 获取成员变量或函数

## 常用库
* vector<int>
* list<int>
* map<string, int>
* set<string>
* unordered_map<string, int>
* unordered_set<string>
* queue<string>
* stack<string>

要使用常量时, 直接在前添加 const 即可, 比如 const vector<int>

## 常用函数
* all_of, any_of, none_of
* find, find_if, find_if_not
* copy, copy_if, copy_n, copy_backward
* fill, fill_n
* remove, remove_if, remove_copy, remove_copy_if
* replace, replace_if, replace_copy, replace_copy_if
* swap, swap_ranges, iter_swap
* reverse, reverse_copy
* generate, generate_n 生成区间
* rotate, rotate_copy 轮询
* unique, unique_copy
* count, count_if: 统计出现的次数
* is_sorted, is_sorted_until, sort, partial_sort, partial_sort_copy, stable_sort, nth_element
* set_difference, set_intersection, set_symmetric_difference, set_union 集合
* is_heap, is_heap_until, make_heap, push_heap, pop_heap, sort_heap
* max, max_element, min, min_element, minmax, minmax_element
* lexicographical_compare 区间比较大小
* is_permutation, next_permutation, prev_permutation 全排序
* is_partitioned, partition, partition_copy, stable_partition, partition_point 区间分成两半
* merge, inplace_merge
* for_each: 对区间内的元素执行谓词
* binary_search
* lower_bound, upper_bound, equal_range
* equal
* iota
* accumulate
* transform 转换结果到指定区间
* inner_product 内积
* adjacent_difference 连续元素的差值
* adjacent_find 查找相邻元素里, 第一个相同的元素
* partial_sum 前 n 项的和
* mismatch: 判断两个区间第一个不相同的位置
* includes 子序列
* find_end 最后一个子区间
* find_first_of 查找后区间内的任何元素在前区间第一次出现的位置
* search 第一个子区间
* search_n 查找前者包不包括几个连续的值

## 高级特性
* 对于普通程序员来说，模板元编程只需明白原理，实现能看懂即可, 一般也不会用到


cpp

定义
声明

赋值
初始化

## 面向过程
## 基于对象
## 面向对象
## 泛型
## 函数式


       const int i = 1; # 只在本文件内有效
extern const int i = 1; # 可以在其他文件中使用

顶层const: 变量本身是个常量
底层const: 变量所指向的值是个常量

std::getline(std::cin, str); // 读取一行, 包括换行符, str 不会存储换行符

整数除以整数, 无论正负, 小数部分直接舍弃
商的符号由除数和被除数决定
余数的符号只由被除数决定

     static_cast -- 不含底层const的转换, 明确定义, 比如, long -> int, void* -> int*
      const_cast --     底层const的转换, 比如, const int* => int*
reinterpret_cast -- 重新解释底层存储, 比如 long* -> double*
    dynamic_cast

std::initializer_list<> 可变参数

函数重载和默认参数

mutable 类可变成员

explicit

string 短字符串优化, 所以 swap 可能会真正交换元素, 而不是拷贝指针

## IO
iostream(istream, ostream)(控制台)
fstream(ifstream, ofstream)(文件)
sstream(istringstream, ostringstream)(string)

全缓冲(文件)
行缓冲(终端)
无焕冲(错误)

刷新缓冲
1. 程序正常结束
2. 缓冲区满
3. 使用 std::endl
4. 使用 flush
4. 使用 unitbuf , 使用 nounitbuf 重置流
5. 关联的流使用时, 会刷新缓冲, 比如, 输入输出关联到终端, 输入时会刷新输出流



## 迭代器
输入迭代器
输出迭代器
前向迭代器
双向迭代器
随机访问迭代器

插入迭代器(back_inserter, front_inserter, inserter)
流迭代器(istrean_iterator, ostrean_iterator)
反向迭代器

## 异常安全

## 可调用对象
函数
函数指针
lambda
std::bind (ref, cref 引用)
std::function

## 智能指针(引用计数)
* std::shared_ptr
	* 初始化
	    * std::shared_ptr<T>(p)    -- p 指向动态分配的内存 -- 不建议
		* std::shared_ptr<T>(q, d) -- p 可以是普通指针, d 为析构时的处理
		* std::make_shared -- 建议
	p.use_count()
	p.unique()
	p.get()
	p.reset(...)
std::unique_ptr
	* 初始化
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


* 申请了内存, 没有释放(内存泄漏)
* 释放了内存, 还在使用(野指针)
* 使用空指针
* 多次释放内存

## 类
delete
default
override
final
