
#include "is_base_of.h"

#include <type_traits>

#include <gtest/gtest.h>

class A {};

class B : public A {};

class C : protected A {};

class D : private A {};

TEST(test_type_traits, test_is_base_of) {
  using std_is_base_of_A_A = std::is_base_of<A, A>;
  using std_is_base_of_A_B = std::is_base_of<A, B>;
  using std_is_base_of_B_A = std::is_base_of<B, A>;
  using std_is_base_of_A_C = std::is_base_of<A, C>;
  using std_is_base_of_C_A = std::is_base_of<C, A>;
  using std_is_base_of_A_D = std::is_base_of<A, D>;
  using std_is_base_of_D_A = std::is_base_of<D, A>;
  using std_is_base_of_B_D = std::is_base_of<B, D>;
  using std_is_base_of_D_B = std::is_base_of<D, B>;

  using liuyunbin_is_base_of_A_A = liuyunbin::is_base_of<A, A>;
  using liuyunbin_is_base_of_A_B = liuyunbin::is_base_of<A, B>;
  using liuyunbin_is_base_of_B_A = liuyunbin::is_base_of<B, A>;
  using liuyunbin_is_base_of_A_C = liuyunbin::is_base_of<A, C>;
  using liuyunbin_is_base_of_C_A = liuyunbin::is_base_of<C, A>;
  using liuyunbin_is_base_of_A_D = liuyunbin::is_base_of<A, D>;
  using liuyunbin_is_base_of_D_A = liuyunbin::is_base_of<D, A>;
  using liuyunbin_is_base_of_B_D = liuyunbin::is_base_of<B, D>;
  using liuyunbin_is_base_of_D_B = liuyunbin::is_base_of<D, B>;

  EXPECT_EQ(liuyunbin_is_base_of_A_A::value, std_is_base_of_A_A::value);

  EXPECT_EQ(liuyunbin_is_base_of_A_B::value, std_is_base_of_A_B::value);
  EXPECT_EQ(liuyunbin_is_base_of_B_A::value, std_is_base_of_B_A::value);

  EXPECT_EQ(liuyunbin_is_base_of_A_C::value, std_is_base_of_A_C::value);
  EXPECT_EQ(liuyunbin_is_base_of_C_A::value, std_is_base_of_C_A::value);

  EXPECT_EQ(liuyunbin_is_base_of_A_D::value, std_is_base_of_A_D::value);
  EXPECT_EQ(liuyunbin_is_base_of_D_A::value, std_is_base_of_D_A::value);

  EXPECT_EQ(liuyunbin_is_base_of_B_D::value, std_is_base_of_B_D::value);
  EXPECT_EQ(liuyunbin_is_base_of_D_B::value, std_is_base_of_D_B::value);

  //    EXPECT_EQ(liuyunbin_is_base_of_const A, B>_value,
  //            std_is_base_of<const A, B>_value);
  // EXPECT_EQ(liuyunbin_is_base_of<const B, A>_value,
  //        std_is_base_of<const B, A>_value);

  //    EXPECT_EQ(liuyunbin_is_base_of A, const B>_value,
  //            std_is_base_of<A, const B>_value);
  // EXPECT_EQ(liuyunbin_is_base_of<B, const A>_value,
  //        std_is_base_of<B, const A>_value);
}
