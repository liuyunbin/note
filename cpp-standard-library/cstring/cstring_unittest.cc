
#include "cstring.h"

#include <gtest/gtest.h>
#include <string.h>

TEST(test_cstring, test_memchr) {
    {
        const char *ptr = "12345678\0 90123";
        const int n = 15;
        const char ch = '1';
        EXPECT_EQ(::memchr(ptr, n, ch), liuyunbin::memchr(ptr, n, ch));
    }
    {
        const char *ptr = "12345678\0 90123";
        const int n = 15;
        const char ch = '9';
        EXPECT_EQ(::memchr(ptr, n, ch), liuyunbin::memchr(ptr, n, ch));
    }
    {
        const char *ptr = "12345678\0 90123";
        const int n = 15;
        const char ch = '\0';
        EXPECT_EQ(::memchr(ptr, n, ch), liuyunbin::memchr(ptr, n, ch));
    }
    {
        const char *ptr = "12345678\0 90123";
        const int n = 15;
        const char ch = 'a';
        EXPECT_EQ(::memchr(ptr, n, ch), liuyunbin::memchr(ptr, n, ch));
    }
}

TEST(test_cstring, test_memcmp) {
    {
        const char *lhs = "12345678\0 90123";
        const char *rhs = "12345677\0 90123";
        const int n = 15;
        EXPECT_EQ(::memcmp(lhs, rhs, n) > 0,
                  liuyunbin::memcmp(lhs, rhs, n) > 0);
        EXPECT_EQ(::memcmp(lhs, rhs, n) == 0,
                  liuyunbin::memcmp(lhs, rhs, n) == 0);
        EXPECT_EQ(::memcmp(lhs, rhs, n) < 0,
                  liuyunbin::memcmp(lhs, rhs, n) < 0);
    }
    {
        const char *lhs = "12345678\0 90123";
        const char *rhs = "12345679\0 90123";
        const int n = 15;
        EXPECT_EQ(::memcmp(lhs, rhs, n) > 0,
                  liuyunbin::memcmp(lhs, rhs, n) > 0);
        EXPECT_EQ(::memcmp(lhs, rhs, n) == 0,
                  liuyunbin::memcmp(lhs, rhs, n) == 0);
        EXPECT_EQ(::memcmp(lhs, rhs, n) < 0,
                  liuyunbin::memcmp(lhs, rhs, n) < 0);
    }
    {
        const char *lhs = "12345678\0 90123";
        const char *rhs = "12345678\0 90223";
        const int n = 15;
        EXPECT_EQ(::memcmp(lhs, rhs, n) > 0,
                  liuyunbin::memcmp(lhs, rhs, n) > 0);
        EXPECT_EQ(::memcmp(lhs, rhs, n) == 0,
                  liuyunbin::memcmp(lhs, rhs, n) == 0);
        EXPECT_EQ(::memcmp(lhs, rhs, n) < 0,
                  liuyunbin::memcmp(lhs, rhs, n) < 0);
    }
}

TEST(test_cstring, test_memcpy) {
    const char *src = "12345678\0 90123";
    char to_1[100];
    char to_2[100];
    const int n = 15;
    ::memcpy(to_1, src, n);
    liuyunbin::memcpy(to_2, src, n);
    for (int i = 0; i != n; ++i) EXPECT_EQ(to_1[i], to_2[i]);
}

TEST(test_cstring, test_memmove) {
    {
        char src_1[100] = "12345678\0 90123";
        char src_2[100] = "12345678\0 90123";
        char to_1[100];
        char to_2[100];
        const int n = 11;
        ::memmove(to_1, src_1, n);
        liuyunbin::memmove(to_2, src_2, n);
        for (int i = 0; i != n; ++i) EXPECT_EQ(to_1[i], to_2[i]);
    }
    {
        char src_1[100] = "12345678\0 90123";
        char src_2[100] = "12345678\0 90123";
        const int n = 11;
        ::memmove(src_1, src_1, n);
        liuyunbin::memmove(src_2, src_2, n);
        for (int i = 0; i != n; ++i) EXPECT_EQ(src_1[i], src_2[i]);
    }
    {
        char src_1[100] = "12345678\0 90123";
        char src_2[100] = "12345678\0 90123";
        const int n = 11;
        ::memmove(src_1, src_1 + 1, n);
        liuyunbin::memmove(src_2, src_2 + 1, n);
        for (int i = 0; i != n; ++i) EXPECT_EQ(src_1[i], src_2[i]);
    }
    {
        char src_1[100] = "12345678\0 90123";
        char src_2[100] = "12345678\0 90123";
        const int n = 11;
        ::memmove(src_1 + 1, src_1, n);
        liuyunbin::memmove(src_2 + 1, src_2, n);
        for (int i = 0; i != n; ++i) EXPECT_EQ(src_1[i + 1], src_2[i + 1]);
    }
}

TEST(test_cstring, test_memset) {
    char dest_1[100];
    char dest_2[100];
    const int n = 15;
    ::memset(dest_1, '\0', n);
    liuyunbin::memset(dest_2, '\0', n);
    for (int i = 0; i != n; ++i) EXPECT_EQ(dest_1[i], dest_2[i]);
}

TEST(test_cstring, test_strcat) {
    {
        const char *src = "";
        char to_1[100] = "";
        char to_2[100] = "";
        EXPECT_STREQ(::strcat(to_1, src), liuyunbin::strcat(to_2, src));
    }
    {
        const char *src = "1234567890";
        char to_1[100] = "123";
        char to_2[100] = "123";
        EXPECT_STREQ(::strcat(to_1, src), liuyunbin::strcat(to_2, src));
    }
}

TEST(test_cstring, test_strchr) {
    {
        const char *str = "1234567890123";
        const char ch = '1';
        EXPECT_EQ(::strchr(str, ch), liuyunbin::strchr(str, ch));
    }
    {
        const char *str = "1234567890123";
        const char ch = 'a';
        EXPECT_EQ(::strchr(str, ch), liuyunbin::strchr(str, ch));
    }
    {
        const char *str = "1234567890123";
        const char ch = '\0';
        EXPECT_EQ(::strchr(str, ch), liuyunbin::strchr(str, ch));
    }
}

TEST(test_cstring, test_strcmp) {
    {
        const char *lhs = "";
        const char *rhs = "";
        EXPECT_EQ(::strcmp(lhs, rhs) > 0, liuyunbin::strcmp(lhs, rhs) > 0);
        EXPECT_EQ(::strcmp(lhs, rhs) == 0, liuyunbin::strcmp(lhs, rhs) == 0);
        EXPECT_EQ(::strcmp(lhs, rhs) < 0, liuyunbin::strcmp(lhs, rhs) < 0);
    }
    {
        const char *lhs = "123";
        const char *rhs = "1234";
        EXPECT_EQ(::strcmp(lhs, rhs) > 0, liuyunbin::strcmp(lhs, rhs) > 0);
        EXPECT_EQ(::strcmp(lhs, rhs) == 0, liuyunbin::strcmp(lhs, rhs) == 0);
        EXPECT_EQ(::strcmp(lhs, rhs) < 0, liuyunbin::strcmp(lhs, rhs) < 0);
    }
    {
        const char *lhs = "1234";
        const char *rhs = "123";
        EXPECT_EQ(::strcmp(lhs, rhs) > 0, liuyunbin::strcmp(lhs, rhs) > 0);
        EXPECT_EQ(::strcmp(lhs, rhs) == 0, liuyunbin::strcmp(lhs, rhs) == 0);
        EXPECT_EQ(::strcmp(lhs, rhs) < 0, liuyunbin::strcmp(lhs, rhs) < 0);
    }
}

TEST(test_cstring, test_strcpy) {
    {
        const char *src = "";
        char to_1[100];
        char to_2[100];
        EXPECT_STREQ(::strcpy(to_1, src), liuyunbin::strcpy(to_2, src));
    }
    {
        const char *src = "1234567890";
        char to_1[100];
        char to_2[100];
        EXPECT_STREQ(::strcpy(to_1, src), liuyunbin::strcpy(to_2, src));
    }
}

TEST(test_cstring, test_strcspn) {
    {
        const char *dest = "1234567890123";
        const char *src = "13";
        EXPECT_EQ(::strcspn(dest, src), liuyunbin::strcspn(dest, src));
    }
    {
        const char *dest = "1234567890123";
        const char *src = "abc";
        EXPECT_EQ(::strcspn(dest, src), liuyunbin::strcspn(dest, src));
    }
    {
        const char *dest = "1234567890123";
        const char *src = "123abc";
        EXPECT_EQ(::strcspn(dest, src), liuyunbin::strcspn(dest, src));
    }
}

TEST(test_cstring, test_strlen) {
    {
        const char *str = "";
        EXPECT_EQ(::strlen(str), liuyunbin::strlen(str));
    }
    {
        const char *str = "1234567890";
        EXPECT_EQ(::strlen(str), liuyunbin::strlen(str));
    }
}

TEST(test_cstring, test_strncat) {
    {
        const char *src = "";
        char to_1[100] = "";
        char to_2[100] = "";
        const int n = 100;
        EXPECT_STREQ(::strncat(to_1, src, n), liuyunbin::strncat(to_2, src, n));
    }
    {
        const char *src = "1234567890";
        char to_1[100] = "123";
        char to_2[100] = "123";
        const int n = 3;
        EXPECT_STREQ(::strncat(to_1, src, n), liuyunbin::strncat(to_2, src, n));
    }
    {
        const char *src = "1234567890";
        char to_1[100] = "123";
        char to_2[100] = "123";
        const int n = 30;
        EXPECT_STREQ(::strncat(to_1, src, n), liuyunbin::strncat(to_2, src, n));
    }
}

TEST(test_cstring, test_strncmp) {
    {
        const char *lhs = "";
        const char *rhs = "";
        const int n = 10;
        EXPECT_EQ(::strncmp(lhs, rhs, n) > 0,
                  liuyunbin::strncmp(lhs, rhs, n) > 0);
        EXPECT_EQ(::strncmp(lhs, rhs, n) == 0,
                  liuyunbin::strncmp(lhs, rhs, n) == 0);
        EXPECT_EQ(::strncmp(lhs, rhs, n) < 0,
                  liuyunbin::strncmp(lhs, rhs, n) < 0);
    }
    {
        const char *lhs = "123";
        const char *rhs = "1234";
        const int n = 3;
        EXPECT_EQ(::strncmp(lhs, rhs, n) > 0,
                  liuyunbin::strncmp(lhs, rhs, n) > 0);
        EXPECT_EQ(::strncmp(lhs, rhs, n) == 0,
                  liuyunbin::strncmp(lhs, rhs, n) == 0);
        EXPECT_EQ(::strncmp(lhs, rhs, n) < 0,
                  liuyunbin::strncmp(lhs, rhs, n) < 0);
    }
    {
        const char *lhs = "1234";
        const char *rhs = "123";
        const int n = 10;
        EXPECT_EQ(::strncmp(lhs, rhs, n) > 0,
                  liuyunbin::strncmp(lhs, rhs, n) > 0);
        EXPECT_EQ(::strncmp(lhs, rhs, n) == 0,
                  liuyunbin::strncmp(lhs, rhs, n) == 0);
        EXPECT_EQ(::strncmp(lhs, rhs, n) < 0,
                  liuyunbin::strncmp(lhs, rhs, n) < 0);
    }
}

TEST(test_cstring, test_strncpy) {
    {
        const char *src = "";
        char to_1[100];
        char to_2[100];
        const int n = 10;
        EXPECT_STREQ(::strncpy(to_1, src, n), liuyunbin::strncpy(to_2, src, n));
    }
    {
        const char *src = "1234567890";
        char to_1[100];
        char to_2[100];
        const int n = 5;
        std::string str_to_1(::strncpy(to_1, src, n), n);
        std::string str_to_2(liuyunbin::strncpy(to_2, src, n), n);
        EXPECT_EQ(str_to_1, str_to_2);
    }
    {
        const char *src = "1234567890";
        char to_1[100];
        char to_2[100];
        const int n = 50;
        EXPECT_STREQ(::strncpy(to_1, src, n), liuyunbin::strncpy(to_2, src, n));
    }
}

TEST(test_cstring, test_strpbrk) {
    {
        const char *dest = "1234567890123";
        const char *breakset = "13";
        EXPECT_EQ(::strpbrk(dest, breakset),
                  liuyunbin::strpbrk(dest, breakset));
    }
    {
        const char *dest = "1234567890123";
        const char *breakset = "abc";
        EXPECT_EQ(::strpbrk(dest, breakset),
                  liuyunbin::strpbrk(dest, breakset));
    }
    {
        const char *dest = "1234567890123";
        const char *breakset = "123abc";
        EXPECT_EQ(::strpbrk(dest, breakset),
                  liuyunbin::strpbrk(dest, breakset));
    }
}

TEST(test_cstring, test_strrchr) {
    {
        const char *str = "1234567890123";
        const char ch = '1';
        EXPECT_EQ(::strrchr(str, ch), liuyunbin::strrchr(str, ch));
    }
    {
        const char *str = "1234567890123";
        const char ch = 'a';
        EXPECT_EQ(::strrchr(str, ch), liuyunbin::strrchr(str, ch));
    }
    {
        const char *str = "1234567890123";
        const char ch = '\0';
        EXPECT_EQ(::strrchr(str, ch), liuyunbin::strrchr(str, ch));
    }
}

TEST(test_cstring, test_strspn) {
    {
        const char *dest = "1234567890123";
        const char *src = "13";
        EXPECT_EQ(::strspn(dest, src), liuyunbin::strspn(dest, src));
    }
    {
        const char *dest = "1234567890123";
        const char *src = "abc";
        EXPECT_EQ(::strspn(dest, src), liuyunbin::strspn(dest, src));
    }
    {
        const char *dest = "1234567890123";
        const char *src = "123abc";
        EXPECT_EQ(::strspn(dest, src), liuyunbin::strspn(dest, src));
    }
}

TEST(test_cstring, test_strstr) {
    {
        const char *str = "1234567890123";
        const char *target = "13";
        EXPECT_EQ(::strstr(str, target), liuyunbin::strstr(str, target));
    }
    {
        const char *str = "1234567890123";
        const char *target = "abc";
        EXPECT_EQ(::strstr(str, target), liuyunbin::strstr(str, target));
    }
    {
        const char *str = "1234567890123";
        const char *target = "123abc";
        EXPECT_EQ(::strstr(str, target), liuyunbin::strstr(str, target));
    }
}

TEST(test_cstring, test_strtok) {
    char str_1[] = "1234567890123";
    char str_2[] = "1234567890123";
    const char *delim = "13";
    EXPECT_STREQ(::strtok(str_1, delim), liuyunbin::strtok(str_2, delim));
    for (;;) {
        const char *p1 = ::strtok(NULL, delim);
        const char *p2 = liuyunbin::strtok(NULL, delim);
        EXPECT_STREQ(p1, p2);
        if (p1 == NULL) break;
    }
}
