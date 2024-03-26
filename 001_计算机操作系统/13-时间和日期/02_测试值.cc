
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include <functional>
#include <iostream>
#include <string>

std::string format(size_t val) {
    return std::to_string(val);
}

std::string format(struct timeval tv) {
    return std::to_string(tv.tv_sec);
}

std::string format(struct tm t) {
    char buf[1024];

    snprintf(buf,
             sizeof(buf),
             "%d-%02d-%02d %02d:%02d:%02d",
             t.tm_year + 1900,
             t.tm_mon + 1,
             t.tm_mday,
             t.tm_hour,
             t.tm_min,
             t.tm_sec);

    return std::string(buf);
}

void test_help(const std::string& str, std::function<std::string()> f) {
    std::cout << str << ", 结果为 " << f() << std::endl;
}

void test(const std::string& prompt, std::function<std::string()> f) {
    unsetenv("TZ");
    test_help(prompt + ", TZ 为 NULL  ", f);
    setenv("TZ", "", 1);
    test_help(prompt + ", TZ 为 空    ", f);
    setenv("TZ", "GMT+6", 1);
    test_help(prompt + ", TZ 为 GMT+6 ", f);
}

int main() {
    time_t         now;
    struct tm      t;
    struct timeval tv;
    char           buf[1024];

    time(&now);
    gmtime_r(&now, &t);

    test("时间戳, time()", []() -> std::string {
        return std::to_string(time(NULL));
    });

    test("时间戳 => 时间元组, localtime()", [now]() mutable -> std::string {
        return format(*localtime(&now));
    });

    test("时间戳 => 时间元组, localtime_r()",
         [now, t]() mutable -> std::string {
             localtime_r(&now, &t);
             return format(t);
         });

    test("时间戳 => 时间元组, gmtime()", [now]() mutable -> std::string {
        return format(*gmtime(&now));
    });

    test("时间戳 => 时间元组, gmtime_r()", [now, t]() mutable -> std::string {
        gmtime_r(&now, &t);
        return format(t);
    });

    test("时间元组 => 时间戳, mktime()", [t]() mutable -> std::string {
        return std::to_string(mktime(&t));
    });

    test("时间元组 => 字符串, asctime()", [t]() mutable -> std::string {
        asctime(&t);
        return format(t);
    });

    test("时间元组 => 字符串, asctime_r()", [t, buf]() mutable -> std::string {
        asctime_r(&t, buf);
        return format(t);
    });

    test("时间戳 => 字符串, ctime()", [now]() mutable -> std::string {
        return ctime(&now);
    });

    test("时间戳 => 字符串, ctime_r()", [now, buf]() mutable -> std::string {
        ctime_r(&now, buf);
        return buf;
    });

    test("字符串 => 时间元组, strptime()", [t]() mutable -> std::string {
        strptime("2023-12-01", "%Y-%m-%d", &t);
        return format(t);
    });

    test("时间元组 => 字符串, strftime()", [t, buf]() mutable -> std::string {
        strftime(buf, 1024, "%Y-%m-%d", &t);
        return buf;
    });

    // 获取毫秒 -- 应该是本地时间
    test("获取本地毫秒, gettimeofday()", [tv]() mutable -> std::string {
        gettimeofday(&tv, NULL);
        return format(tv);
    });

    return 0;
}
