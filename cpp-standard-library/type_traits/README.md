
**个人建议：对于普通程序员来说，对于模板元编程只要能看懂即可**

头文件 `type_traits` 里的结构体，按实现的难度，可以分为以下几类：

注意：
* 本文主要讨论 `C++11` 和 `C++14` 以及个别的 `C++17` 和 `C++20`
* 本文不讨论和对齐有关的结构体
* 本节只是实现了几个典型的例子

## 第一类：可以完全手工实现的
#### 辅助结构体
直接实现
* `integral_constant`
* `bool_constant` C++17
* `true_type`
* `false_type`
* `void_t` C++17

通过偏特化实现
* `is_same`
* `enable_if`
* `conditional`

通过 `conditional` 实现
* `decay`

#### 和 CV 有关的结构体
通过偏特化可以实现
* `is_const`
* `is_volatole`
* `add_const`
* `add_volatole`
* `add_cv`
* `remove_const`
* `remove_volatole`
* `remove_cv`

#### 和引用有关的结构体
通过偏特化或函数重载决议可以实现
* `is_lvalue_reference`
* `is_rvalue_reference`
* `is_reference`
* `add_lvalue_reference` 注意：`void` 要特殊处理，可能会引用折叠
* `add_rvalue_reference` 注意：`void` 要特殊处理，可能会引用折叠
* `remove_reference`
* `remove_cvref` C++20

#### 和指针有关的结构体
通过偏特化或函数重载决议可以实现
* `is_pointer`     注意：可能包括 `CV`
* `add_pointer`    注意：并不是所有的类型都可以添加指针
* `remove_pointer` 注意：包括顶层的 `CV`

#### 和数组有关的结构体
通过偏特化可以实现
* `is_bounded_array` C++20
* `is_unbounded_array` C++20
* `is_array`
* `remove_extent`
* `remove_all_extents`
* `rank`
* `extent`

#### 和算数类型有关的结构体：
通过偏特化可以实现
* `is_integral`
* `is_floating_point`
* `is_signed`
* `is_unsigned`
* `make_signed`
* `make_unsigned`

#### 和 void 类型有关的结构体
通过偏特化可以实现
* `is_void`

#### 和空指针类型有关的结构体
通过偏特化可以实现
* `is_null_pointer`

#### 和函数类型有关的结构体
通过偏特化可以实现
* `is_function`

#### 和枚举有关的结构体
* `is_enum` 使用排除法判断，需要辅助判断是类或共同体

#### 和指向类成员有关的结构体
通过偏特化可以实现
* `is_member_object_pointer`   注意：可能包括 `CV`
* `is_member_function_pointer` 注意：可能包括 `CV`
* `is_member_pointer`          注意：可能包括 `CV`

#### 几种类型结合起来
* `is_fundamental`
* `is_arithmetic`
* `is_scalar`
* `is_object` 需要辅助判断是类或结构体
* `is_compound`

#### 和类构造函数有关的结构体
* `is_constructible` 利用偏特化和函数重载，对于引用使用 `static_cast` 判断
* `is_default_constructible`
* `is_copy_constructible`
* `is_move_constructible`
* `is_nothrow_constructible` 使用 `noexcept` 判断
* `is_nothrow_default_constructible`
* `is_nothrow_copy_constructible`
* `is_nothrow_move_constructible`

#### 和类赋值运算符有关的结构体
* `is_assignable`  通过函数重载实现
* `is_copy_assignable`
* `is_move_assignable`
* `is_nothrow_assignable` 运用 `noexcept` 实现
* `is_nothrow_copy_assignable`
* `is_nothrow_move_assignable`

#### 和类析构函数有关的结构体
* `is_destructible` 通过偏特化可以实现
* `is_nothrow_destructible` 运用 `noexcept` 实现

#### 和类 swap 有关的结构体
* `is_swappable_with` 函数重载和偏特化实现
* `is_swappable`
* `is_nothrow_swappable_with` 运用 `noexcept` 实现
* `is_nothrow_swappable`

#### 和转换有关的结构体
* `is_convertible` 通过重载决议和偏特化实现
* `is_nothrow_convertible` 运用 `noexcept` 实现 C++20

## 和公共类型有关的结构体
使用 `decltype` 和偏特化实现
* `common_type`

#### 和 与 或 非有关的结构体 C++17
通过偏特化即可实现
* `conjunction`
* `disjunction`
* `negation`

#### 和 invoke 有关的结构体 C++17
利用偏特化区分是否是指向类成员的指针， `std::reference_wrapper` 等等
* `result_of` 和 `invoke_result`
* `is_invocable`
* `is_invocable_r`
* `is_nothrow_invocable`
* `is_nothrow_invocable_r`

## 第二类：需要调用其它结构体实现
* `is_union` 需要调用 `is_class`
* `is_class` 需要调用 `is_union`

有就是说可以确定是 类 或 共同体，但无法再进一步判断

* `is_base_of` 需要调用 `is_class`

* `is_trivial` 需要调用 `is_trivially_copyable` 和 `is_trivially_constructible`
* `is_pod`     需要调用 `is_trivial` 和 `is_standard_layout`

* `is_polymorphic` 利用重载决议和 `dynamic_cast` 实现

* `is_trivially_default_constructible` 需要调用 `is_trivially_constructible`
* `is_trivially_copy_constructible`    需要调用 `is_trivially_constructible`
* `is_trivially_move_constructible`    需要调用 `is_trivially_constructible`

* `is_trivially_copy_assignable` 需要调用 `is_trivially_assignable`
* `is_trivially_move_assignable` 需要调用 `is_trivially_assignable`

## 第三类：无法手工实现，需要编译器支持
* `is_standard_layout`

* `is_literal_type`

* `is_trivially_constructible`
* `is_trivially_assignable`
* `is_trivially_destructible`
* `is_trivially_copyable`

* `has_virtual_destructor`

* `is_empty` 无法判断 `final` 类是否为 `empty`

* `is_abstract`
* `is_final`
* `is_aggregate` C++17

* `underlying_type`

