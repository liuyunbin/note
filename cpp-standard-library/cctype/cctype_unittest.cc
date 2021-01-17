
#include "cctype.h"

#include <ctype.h>
#include <gtest/gtest.h>

TEST(test_cctype, test_isalnum) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::isalnum(i) == 0, liuyunbin::isalnum(i) == 0);
  EXPECT_EQ(::isalnum(EOF) == 0, liuyunbin::isalnum(EOF) == 0);
}

TEST(test_cctype, test_isalpha) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::isalpha(i) == 0, liuyunbin::isalpha(i) == 0);
  EXPECT_EQ(::isalpha(EOF) == 0, liuyunbin::isalpha(EOF) == 0);
}

TEST(test_cctype, test_isblank) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::isblank(i) == 0, liuyunbin::isblank(i) == 0);
  EXPECT_EQ(::isblank(EOF) == 0, liuyunbin::isblank(EOF) == 0);
}

TEST(test_cctype, test_iscntrl) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::iscntrl(i) == 0, liuyunbin::iscntrl(i) == 0);
  EXPECT_EQ(::iscntrl(EOF) == 0, liuyunbin::iscntrl(EOF) == 0);
}

TEST(test_cctype, test_isdigit) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::isdigit(i) == 0, liuyunbin::isdigit(i) == 0);
  EXPECT_EQ(::isdigit(EOF) == 0, liuyunbin::isdigit(EOF) == 0);
}

TEST(test_cctype, test_isgraph) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::isgraph(i) == 0, liuyunbin::isgraph(i) == 0);
  EXPECT_EQ(::isgraph(EOF) == 0, liuyunbin::isgraph(EOF) == 0);
}

TEST(test_cctype, test_islower) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::islower(i) == 0, liuyunbin::islower(i) == 0);
  EXPECT_EQ(::islower(EOF) == 0, liuyunbin::islower(EOF) == 0);
}

TEST(test_cctype, test_isprint) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::isprint(i) == 0, liuyunbin::isprint(i) == 0);
  EXPECT_EQ(::isprint(EOF) == 0, liuyunbin::isprint(EOF) == 0);
}

TEST(test_cctype, test_ispunct) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::ispunct(i) == 0, liuyunbin::ispunct(i) == 0);
  EXPECT_EQ(::ispunct(EOF) == 0, liuyunbin::ispunct(EOF) == 0);
}

TEST(test_cctype, test_isspace) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::isspace(i) == 0, liuyunbin::isspace(i) == 0);
  EXPECT_EQ(::isspace(EOF) == 0, liuyunbin::isspace(EOF) == 0);
}

TEST(test_cctype, test_isupper) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::isupper(i) == 0, liuyunbin::isupper(i) == 0);
  EXPECT_EQ(::isupper(EOF) == 0, liuyunbin::isupper(EOF) == 0);
}

TEST(test_cctype, test_isxdigit) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::isxdigit(i) == 0, liuyunbin::isxdigit(i) == 0);
  EXPECT_EQ(::isxdigit(EOF) == 0, liuyunbin::isxdigit(EOF) == 0);
}

TEST(test_cctype, test_tolower) {
  for (int i = 0; i != 256; ++i) EXPECT_EQ(::tolower(i), liuyunbin::tolower(i));
  EXPECT_EQ(::tolower(EOF), liuyunbin::tolower(EOF));
}

TEST(test_cctype, test_toupper) {
  for (int i = 0; i != 256; ++i) EXPECT_EQ(::toupper(i), liuyunbin::toupper(i));
  EXPECT_EQ(::toupper(EOF), liuyunbin::toupper(EOF));
}
