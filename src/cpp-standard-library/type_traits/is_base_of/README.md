
```
template <typename B, typename D>
is_base_of;
```

首先，如果满足下列条件，则 `std::is_base_of<B, D>::value` 为 `true`，否则为 `false`
1. `B` 和 `D` 都是类类型
2. `B` 是 `D` 的基类（包括直接基类和间接基类）或 `B` 和 `D` 类型相同

接下来一步一步实现，
第一步，实现条件 1，即如果 `B` 和 `D` 都是类类型，则 `is_base_of<B,D>::value` 为 `true`，否则为 `false`，
这一条件很好满足，为以后方便，使用 `std::condition` 实现，代码如下：

```
template <typename B, typename D>
struct is_base_of 
  : public std::conditional <
  std::is_class<B>::value && std::is_class<D>::value,
  std::true_type,
  std::false_type>::type 
{};
```

第二步，实现条件 2，最容易想到的方法就是利用，子类指针可以赋值给父类指针的特性来实现，代码如下：

```
template<typename T> std::true_type  test(T*);
template<typename T> std::false_type test(void*);

template <typename B, typename D>
struct is_base_of 
  : public std::conditional <
  std::is_class<B>::value && std::is_class<D>::value,
  decltype(test<B>(std::declval<D*>())),
  std::false_type>::type 
{};
```

如果，指向 `D` 类型的指针可以赋值给指向 `B` 类型的指针，
则根据重载决议，第一个 `test` 更特殊，优先级也更高，
即 `is_base_of<B, D>` 将继承自 `std::true_type`，
最终 `is_base_of<B,D>::value` 为 `true`，
否则，只能匹配到第二个 `test`，
即，`is_base_of<B,D>` 将继承自 `std::false_type`，
最终 `is_base_of<B, D>::value` 为 `false`.

顺便说一句，`std::declval` 是对任意类型添加右值引用，
其中不涉及任何构造函数，也就是说类可以没有构造函数，但只能用于不求值的地方。

遗憾的是，这个实现并不正确，这个实现仅仅处理了
`D` 没有继承自 `B`，`B` 和 `D` 相同以及 `D` 公有继承 `B` 的情况，
并没有没有考虑到私有继承和受保护继承，
在后者的情况下，在类外部，子类的指针不能隐式转换为父类的指针。

现在，我们考虑如果，`D` 类是私有继承自 `B` 类会发生什么情况，
首先要明白一点，重载决议的时候不会考虑访问权限，在这里多谢 @小纸条 的回答，
即，重载决议的最佳匹配还是第一个 `test`，
但之后判断访问权限则会失败，直接报编译错误，
对于这个问题，我们就可以使用 `SFINAE` 和 偏特化来处理这个问题

现在我们先把情况分类：
* 第一种情况：`B` 或 `D` 不是类
* 第二种情况：`D` 没有继承自 `B` 且 `D` 和 `B` 类型不同
* 第三种情况：`B` 和 `D` 类型相同 或 `D` 公有继承自 `B`（从 `B` 到 `D` 的所有继承都为公有继承）
* 第四种情况：`D` 私有或受保护继承自 `B`（从 `B` 到 `D` 的所有继承中，至少有一个不是公有继承）

如上所说，上面的程序已经可以解决前三种情况，
而对于第四种情况将导致编译错误，在这里，我们使用 `SFINAE` 来避免编译器报错，
由于在前三种情况中，`is_base_of<B,D>` 
既可能继承自 `std::true_type`，又可能继承自 `std::false_type`，
所以，在这里，我们使用 `C++17` 的 `std::void_t` 来统一偏特化时的这两种情况，
使用偏特化的版本处理前三种情况，使用一般版本处理第四种情况，代码如下：

```
template <typename...> using void_t = void;

template<typename T> std::true_type  test(T*);
template<typename T> std::false_type test(void*);

template <typename B, typename D>
using test_same_or_public_inheritance = decltype(test<B>(std::declval<D*>()));

template <typename B, typename D, typename = void>
struct is_base_of_helper : public std::true_type {}; // 处理私有继承 或 受保护继承

template <typename B, typename D>
struct is_base_of_helper<B, D, void_t<test_same_or_public_inheritance<B, D>>>
  :  public test_same_or_public_inheritance<B, D> 
{};

template <typename B, typename D>
struct is_base_of 
  : public std::conditional <
  std::is_class<B>::value && std::is_class<D>::value,
  is_base_of_helper<B, D>,
  std::false_type>::type 
{};
```

详细分析如下：
第一种情况：`B` 或 `D` 不是类，
显然，`is_base_of<B, D>::value` 为 `false`

对于以下三种情况，由于 `is_base_of_helper` 有默认参数，
所以，调用 `is_base_of_helper<B, D>` 相当于调用 `is_base_of_helper<B, D, void>`   

第二种情况：`D` 没有继承自 `B`，
由于 `D` 类指针不能转化为 `B` 类指针，
所以通过重载决议，将选择第二个 `test`，
所以，偏特化版本推断为 `is_base_of_helper<B, D, void>`，
所以选择 `is_base_of_helper` 的偏特化版本，
`is_base_of_helper<B, D>` 将继承自 `std::false_type`，
即最终 `is_base_of<B, D>::value` 为 `false`

第三种情况：`B` 和 `D` 类型相同 或 `D` 公有继承自 `B`（从 `B` 到 `D` 的所有继承都为公有继承），
通过重载决议，选择第一个 `test`，访问权限也没问题，
所以，偏特化版本推断为 `is_base_of_helper<B, D, void>`，
所以选择，`is_base_of_helper` 的偏特化版本，
`is_base_of_helper<B, D>` 将继承自 `std::true_type`，
即 `is_base_of<B, D>::value` 为 `true`

第四种情况：`D` 私有或受保护继承自 `B`（从 `B` 到 `D` 的所有继承中，至少有一个不是公有继承），
通过重载决议，选择第一个 `test`，但之后的访问权限判断失败，
偏特化版本推断失败，但不会报编译错误，
因为 `SFINAE`，还可以选择 `is_base_of_helper` 的普通版本，
即，`is_base_of_helper<B, D>` 将继承自 `std::true_type`，
即 `is_base_of<B, D>::value` 为 `true`

遗憾的是，现在还有一个小问题，未考虑 `D` 含有 `const` 的情况，
解决方法也很简单，给 `test` 参数添加 底层 `CV` 属性即可。

完整代码及其测试，参见源文件

