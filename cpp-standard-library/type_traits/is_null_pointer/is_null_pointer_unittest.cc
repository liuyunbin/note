
#include "is_null_pointer.h"

#include <type_traits>

#include <gtest/gtest.h>

TEST(test_type_traits, test_is_null_pointer) {
  EXPECT_EQ(liuyunbin::is_null_pointer<std::nullptr_t>::value,
            std::is_null_pointer<std::nullptr_t>::value);

  EXPECT_EQ(liuyunbin::is_null_pointer<std::nullptr_t const>::value,
            std::is_null_pointer<std::nullptr_t const>::value);

  EXPECT_EQ(liuyunbin::is_null_pointer<std::nullptr_t volatile>::value,
            std::is_null_pointer<std::nullptr_t volatile>::value);

  EXPECT_EQ(liuyunbin::is_null_pointer<std::nullptr_t const volatile>::value,
            std::is_null_pointer<std::nullptr_t const volatile>::value);

  EXPECT_EQ(liuyunbin::is_null_pointer<int>::value,
            std::is_null_pointer<int>::value);
}
