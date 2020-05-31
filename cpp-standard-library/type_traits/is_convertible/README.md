
```
template <typename From, typename To>
is_convertible;
```

首先，如果满足下列条件，则 `std::is_convertible<From, To>::value` 为 `true`，否则为 `false`
1. `From` 和 `To` 均为 `void` 类型（可含有 `cv` 限定）
2. `std::declval<From>()` 可隐式转换为 `To` 类型

接下来一步一步实现，

第一步，实现条件 1，这个很简单，为使下文方便，使用偏特化实现，代码如下：

```
template <typename From, 
         typename To,
         bool = std::is_void<From>::value && std::is_void<To>::value>
struct is_convertible : std::false_type {};

template <typename From, typename To>
struct is_convertible<From, To, true> : std::true_type {};
```

第二步，实现条件 2，我们可以使用函数重载，来判断是否可以隐式转化，代码如下，

```
template <typename T> std::true_type test(T);

template <typename T> std::false_type test(...);

template <typename From, 
         typename To,
         bool = std::is_void<From>::value && std::is_void<To>::value>
struct is_convertible : decltype(test<To>(std::declval<From>())) {};

template <typename From, typename To>
struct is_convertible<From, To, true> : std::true_type {};
```

如果，`std::declval<From>()` 可以隐式转换为 `To`，
则，会选择第一个 `test` 版本，因为它的优先级高，
即，最终，`is_convertible<From, To>::value` 将为 `true`，
否则，将为 `false`。
在这里说明一下，为什么不用 `From()` 而用 `std::declval<From>()` ，
因为前者要求 `From` 是内置类型 或 是拥有默认构造函数的类（包括共同体），
而后者不需要，作为交换，后者只能用于不求值的地方。

遗憾的是，此版本是错误的，
我们仅仅考虑了 `From` 和 `to` 都为 `void` 的情况，
并未考虑，其中只有一个为 `void` 的情况，

现在，我们考虑一下，`From` 为 `void`，`To` 为 `int` 的情况，
`std::declval<From>()` 将返回 `void` 类型，即 `decltype(test<int>(void))` ，
而 `C++` 不允许实参是 `void` ，将直接编译错误， 
而 `void` 类型也不能隐式再转化为其它的非 `void` 类型，
所以，现在，我们把 `From` 和 `To` 的情况拆开，

代码如下：

```
template <typename T> std::true_type test(T);

template <typename T> std::false_type test(...);

template <typename From, 
         typename To, 
         bool = std::is_void<From>::value,
         bool = std::is_void<To>::value>
struct is_convertible : decltype(test<To>(std::declval<From>())) {};

template <typename From, typename To>
struct is_convertible<From, To, true, true> : std::true_type {};

template <typename From, typename To>
struct is_convertible<From, To, false, true> : std::false_type {};

template <typename From, typename To>
struct is_convertible<From, To, true, false> : std::false_type {};
```

现在，我们解决了有且仅有一个是 void 的情况，已经两个都是 void 的情况，

遗憾的是，我们的程序依然不对，
现在考虑 `From` 为 `int*` 而 `To` 为 `int[5]` 的情况，
`std::declval<int*>()` 将返回 `int*&`，
而第一个 `test<int[5]>(int[5])`，因为非引用数组形参将隐式转化为指针，
所以，第一个 `test` 将推导为 `std::true_type test(int*);` 
显然，实参 `int*&` 可以转化为 `int*`，
即，最终 `is_convertible<int*, int[5]>::value` 将为 `true`，
但是，`int*` 到 `int[5]` 显然是不能转化的，
所以对于 `To` 为 数组的情况必须特殊处理，函数也一样，
这里是因为非引用类型的数组 或 函数参数，将在转化为对应的指针类型，
由于任何类型都不能隐式转化为数组和函数，所以 `To` 只要是数组或函数，
即，转换失败，

现在，我们先整理一下情况：

情况一：`From` 和 `To` 都为 `void` 类型，此时 `std::is_convertible<From, To>::value` 为 `true`

情况二：`Form` 不是 `void` 类型，`To` 不是 `void` 或 数组 或 函数类型，此时，直接利用重载决议，隐式推导即可

情况三：其他情况都将转换失败，即，`std::is_convertible<From, To>::value` 为 `false`

代码如下：

```
template <typename T> std::true_type test(T);

template <typename T> std::false_type test(...);

template <typename From, 
         typename To, 
         bool = std::is_void<From>::value,
         bool = std::is_void<To>::value,
         bool = std::is_array<To>::value || std::is_function<To>::value>
struct is_convertible : std::false_type {};

template <typename From, typename To>
struct is_convertible<From, To, true, true, false> : std::true_type {};

template <typename From, typename To>
struct is_convertible<From, To, false, false, false> : decltype(test<To>(std::declval<From>()))
{};
```

遗憾的是，我们现在的实现还是错误的，
现在，假设，类 `A` 的析构函数被删除
考虑 `From` 和 `To` 均为 `A` 的情况，
`std::declval<A>()` 将返回 `A&`，
所以，第一个 `test` 将推导为 `std::true_type test(A);` 
显然，实参 `A&` 可以转化为 `A`，所以，选择第一个 `test`，
但是，之后会判断 `A` 是不完整类型（析构函数被删除）而失败，导致编译错误

此种情况包括，假设 `From` 和 `To` 相同，或 `From` 是 `To` 的子类
* `To` 类型的析构函数删除 或 不是公有访问权限
* 从 `To` 到 `From` 至少存在一个继承不是公有继承

感谢 @暮无井见铃 指出这种情况

我们可以利用 `SFINAE` 解决这个问题

代码如下：

```
template <typename T>
void test_convertion(T);

template <typename From, 
         typename To, 
         typename = decltype(test_convertion<To>(std::declval<From>()))>
std::true_type test(int);

template <typename From, typename To>
std::false_type test(...);

template <typename From, 
         typename To, 
         bool = std::is_void<From>::value,
         bool = std::is_void<To>::value,
         bool = std::is_array<To>::value || std::is_function<To>::value>
struct is_convertible : std::false_type {};

template <typename From, typename To>
struct is_convertible<From, To, true, true, false> : std::true_type {};

template <typename From, typename To>
struct is_convertible<From, To, false, false, false> : decltype(test<From, To>(1))
{};
```

主要将测试转换部分移到了模板的默认实参，以便利用 `SFINAE`

现在，我们已经完成了所有功能，但，程序可以进一步简化，只有一个 `void` 的情况，可以并入 `SFINAE`

我们总结一下所有情况：

情况一：`From` 和 `To` 都为 `void` 的情况，成功

情况二：`To` 为数组 或 函数的情况，失败

情况三：其他情况，使用 `SFINAE` 检测

最终代码如下：

```
template <typename T>
void test_convertion(T);

template <typename From, 
         typename To, 
         typename = decltype(test_convertion<To>(std::declval<From>()))>
std::true_type test(int);

template <typename From, typename To>
std::false_type test(...);

template <typename From, 
         typename To, 
         bool = std::is_void<From>::value && std::is_void<To>::value,
         bool = std::is_array<To>::value || std::is_function<To>::value>
struct is_convertible : std::false_type {};

template <typename From, typename To>
struct is_convertible<From, To, true, false> : std::true_type {};

template <typename From, typename To>
struct is_convertible<From, To, false, false> : decltype(test<From, To>(1))
{};
```

### 扩展：

接下来我们可以实现不抛出异常的转换判断 `is_nothrow_convertible`，由上可知，`From` 可转换为 `To`，只有两种情况，

情况一：`From` 和 `To` 均为 `void` 类型，显然这种情况不会抛出异常

情况二：`std::declval<From>()` 可隐式转换为 To 类型，在此我们用函数和 `noexcept` 来测试它，

我们使用偏特化区分上面两种情况，代码如下：

```
template <typename T>
void test_noexcept(T) noexcept;

template <typename From, typename To, bool = std::is_void<From>::value>
struct is_nothrow_convertible_helper : std::true_type {};

template <typename From, typename To>
struct is_nothrow_convertible_helper<From, To, false>
  : std::integral_constant<bool, noexcept(::test_noexcept<To>(std::declval<From>()))>
{};

template <typename From, 
         typename To,
         bool = ::is_convertible<From, To>::value>
struct is_nothrow_convertible : std::false_type {};

template <typename From, typename To>
struct is_nothrow_convertible<From, To, true> 
  : ::is_nothrow_convertible_helper<From, To> {};
```

由于我们已经标明函数体不会抛出异常，所以，如果

`noexcept(::test_noexcept<To>(std::declval<From>()))` 抛出异常，一定是在参数初始化，即，隐式类型转换的时候抛出的

完整代码及其测试，参见源文件

