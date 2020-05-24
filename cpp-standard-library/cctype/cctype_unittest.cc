
#include "cctype.h"

#include <cctype>

#include <gtest/gtest.h>

TEST(test_cctype, test_islower) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(std::islower(i) == 0, liuyunbin::islower(i) == 0);
  EXPECT_EQ(std::islower(EOF) == 0, liuyunbin::islower(EOF) == 0);
}

TEST(test_cctype, test_isupper) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(std::isupper(i) == 0, liuyunbin::isupper(i) == 0);
  EXPECT_EQ(std::isupper(EOF) == 0, liuyunbin::isupper(EOF) == 0);
}

TEST(test_cctype, test_isalpha) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(std::isalpha(i) == 0, liuyunbin::isalpha(i) == 0);
  EXPECT_EQ(std::isalpha(EOF) == 0, liuyunbin::isalpha(EOF) == 0);
}

TEST(test_cctype, test_isdigit) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(std::isdigit(i) == 0, liuyunbin::isdigit(i) == 0);
  EXPECT_EQ(std::isdigit(EOF) == 0, liuyunbin::isdigit(EOF) == 0);
}

TEST(test_cctype, test_isxdigit) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(std::isxdigit(i) == 0, liuyunbin::isxdigit(i) == 0);
  EXPECT_EQ(std::isxdigit(EOF) == 0, liuyunbin::isxdigit(EOF) == 0);
}

TEST(test_cctype, test_isalnum) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(std::isalnum(i) == 0, liuyunbin::isalnum(i) == 0);
  EXPECT_EQ(std::isalnum(EOF) == 0, liuyunbin::isalnum(EOF) == 0);
}

TEST(test_cctype, test_isblank) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(std::isblank(i) == 0, liuyunbin::isblank(i) == 0);
  EXPECT_EQ(std::isblank(EOF) == 0, liuyunbin::isblank(EOF) == 0);
}

TEST(test_cctype, test_isspace) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(std::isspace(i) == 0, liuyunbin::isspace(i) == 0);
  EXPECT_EQ(std::isspace(EOF) == 0, liuyunbin::isspace(EOF) == 0);
}

TEST(test_cctype, test_iscntrl) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(std::iscntrl(i) == 0, liuyunbin::iscntrl(i) == 0);
  EXPECT_EQ(std::iscntrl(EOF) == 0, liuyunbin::iscntrl(EOF) == 0);
}

TEST(test_cctype, test_ispunct) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(std::ispunct(i) == 0, liuyunbin::ispunct(i) == 0);
  EXPECT_EQ(std::ispunct(EOF) == 0, liuyunbin::ispunct(EOF) == 0);
}

TEST(test_cctype, test_isgraph) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(std::isgraph(i) == 0, liuyunbin::isgraph(i) == 0);
  EXPECT_EQ(std::isgraph(EOF) == 0, liuyunbin::isgraph(EOF) == 0);
}

TEST(test_cctype, test_isprint) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(std::isprint(i) == 0, liuyunbin::isprint(i) == 0);
  EXPECT_EQ(std::isprint(EOF) == 0, liuyunbin::isprint(EOF) == 0);
}

TEST(test_cctype, test_tolower) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(std::tolower(i), liuyunbin::tolower(i));
  EXPECT_EQ(std::tolower(EOF), liuyunbin::tolower(EOF));
}

TEST(test_cctype, test_toupper) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(std::toupper(i), liuyunbin::toupper(i));
  EXPECT_EQ(std::toupper(EOF), liuyunbin::toupper(EOF));
}

