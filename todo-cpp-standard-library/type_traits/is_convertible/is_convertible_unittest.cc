
#include "is_convertible.h"

#include <gtest/gtest.h>

#include <type_traits>

class A {};

class B : public A {};

class C : protected A {};

class D : private A {};

TEST(test_type_traits, test_is_convertible) {
    using std_is_convertible_A_A = std::is_convertible<A, A>;
    using std_is_convertible_A_B = std::is_convertible<A, B>;
    using std_is_convertible_B_A = std::is_convertible<B, A>;
    using std_is_convertible_A_C = std::is_convertible<A, C>;
    using std_is_convertible_C_A = std::is_convertible<C, A>;
    using std_is_convertible_A_D = std::is_convertible<A, D>;
    using std_is_convertible_D_A = std::is_convertible<D, A>;
    using std_is_convertible_B_D = std::is_convertible<B, D>;
    using std_is_convertible_D_B = std::is_convertible<D, B>;

    using liuyunbin_is_convertible_A_A = liuyunbin::is_convertible<A, A>;
    using liuyunbin_is_convertible_A_B = liuyunbin::is_convertible<A, B>;
    using liuyunbin_is_convertible_B_A = liuyunbin::is_convertible<B, A>;
    using liuyunbin_is_convertible_A_C = liuyunbin::is_convertible<A, C>;
    using liuyunbin_is_convertible_C_A = liuyunbin::is_convertible<C, A>;
    using liuyunbin_is_convertible_A_D = liuyunbin::is_convertible<A, D>;
    using liuyunbin_is_convertible_D_A = liuyunbin::is_convertible<D, A>;
    using liuyunbin_is_convertible_B_D = liuyunbin::is_convertible<B, D>;
    using liuyunbin_is_convertible_D_B = liuyunbin::is_convertible<D, B>;

    EXPECT_EQ(liuyunbin_is_convertible_A_A::value,
              std_is_convertible_A_A::value);

    EXPECT_EQ(liuyunbin_is_convertible_A_B::value,
              std_is_convertible_A_B::value);
    EXPECT_EQ(liuyunbin_is_convertible_B_A::value,
              std_is_convertible_B_A::value);

    EXPECT_EQ(liuyunbin_is_convertible_A_C::value,
              std_is_convertible_A_C::value);
    EXPECT_EQ(liuyunbin_is_convertible_C_A::value,
              std_is_convertible_C_A::value);

    EXPECT_EQ(liuyunbin_is_convertible_A_D::value,
              std_is_convertible_A_D::value);
    EXPECT_EQ(liuyunbin_is_convertible_D_A::value,
              std_is_convertible_D_A::value);

    EXPECT_EQ(liuyunbin_is_convertible_B_D::value,
              std_is_convertible_B_D::value);
    EXPECT_EQ(liuyunbin_is_convertible_D_B::value,
              std_is_convertible_D_B::value);
}
