
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

