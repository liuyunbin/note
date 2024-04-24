
#include "is_enum.h"

#include <gtest/gtest.h>

#include <type_traits>

enum A {};

enum B {};

enum class C {};

class D {};

class E {
    virtual int f() = 0;
};

class F {
   public:
    ~F() = delete;
};

class G final {};

class H final {
    virtual int f() = 0;
};

class I final {
   public:
    ~I() = delete;
};

union J {};

TEST(test_type_traits, test_is_enum) {
    EXPECT_EQ(liuyunbin::is_enum<void>::value, std::is_enum<void>::value);

    EXPECT_EQ(liuyunbin::is_enum<int>::value, std::is_enum<int>::value);
    EXPECT_EQ(liuyunbin::is_enum<const int>::value,
              std::is_enum<const int>::value);

    EXPECT_EQ(liuyunbin::is_enum<float>::value, std::is_enum<float>::value);
    EXPECT_EQ(liuyunbin::is_enum<const float>::value,
              std::is_enum<const float>::value);

    EXPECT_EQ(liuyunbin::is_enum<double>::value, std::is_enum<double>::value);
    EXPECT_EQ(liuyunbin::is_enum<const double>::value,
              std::is_enum<const double>::value);

    EXPECT_EQ(liuyunbin::is_enum<A>::value, std::is_enum<A>::value);
    EXPECT_EQ(liuyunbin::is_enum<B>::value, std::is_enum<B>::value);
    EXPECT_EQ(liuyunbin::is_enum<C>::value, std::is_enum<C>::value);
    EXPECT_EQ(liuyunbin::is_enum<D>::value, std::is_enum<D>::value);
    EXPECT_EQ(liuyunbin::is_enum<E>::value, std::is_enum<E>::value);
    EXPECT_EQ(liuyunbin::is_enum<F>::value, std::is_enum<F>::value);
    EXPECT_EQ(liuyunbin::is_enum<G>::value, std::is_enum<G>::value);

    EXPECT_EQ(liuyunbin::is_enum<const A>::value, std::is_enum<const A>::value);
    EXPECT_EQ(liuyunbin::is_enum<const B>::value, std::is_enum<const B>::value);
    EXPECT_EQ(liuyunbin::is_enum<const C>::value, std::is_enum<const C>::value);
    EXPECT_EQ(liuyunbin::is_enum<const D>::value, std::is_enum<const D>::value);
    EXPECT_EQ(liuyunbin::is_enum<const E>::value, std::is_enum<const E>::value);
    EXPECT_EQ(liuyunbin::is_enum<const F>::value, std::is_enum<const F>::value);
    EXPECT_EQ(liuyunbin::is_enum<const G>::value, std::is_enum<const G>::value);
}
