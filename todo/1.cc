
#include <tuple>
#include <cstddef>

// ===== 你的原始实现（一字不改） =====
template <size_t I, typename T>
struct tuple_n {
    template <typename... Args>
    using type =
        typename tuple_n<I - 1, T>::template type<T, Args...>;
};

template <typename T>
struct tuple_n<0, T> {
    template <typename... Args>
    using type = std::tuple<Args...>;
};

template <size_t I, typename T>
using tuple_of = typename tuple_n<I, T>::template type<>;
// ===== 原始实现结束 =====


// ===== 触发编译错误 =====
using bad = tuple_n<0, int>::type<double>;


int main() {
    // main 本身什么都不做
    return 0;
}

