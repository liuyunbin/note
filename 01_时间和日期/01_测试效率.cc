
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include <functional>
#include <iostream>
#include <string>

void test_help(const std::string& str, std::function<void()> f) {
    struct timeval t1;
    gettimeofday(&t1, NULL);
    for (int i = 0; i < 2000000; ++i)
        f();
    struct timeval t2;
    gettimeofday(&t2, NULL);
    int res = (t2.tv_sec - t1.tv_sec) * 1000 + (t2.tv_usec - t1.tv_usec) / 1000;
    std::cout << str << ", 耗时 " << res << " 豪秒" << std::endl;
}

void test(const std::string& prompt, std::function<void()> f) {
    unsetenv("TZ");
    test_help(prompt + ", TZ 为 NULL", f);
    setenv("TZ", "", 1);
    test_help(prompt + ", TZ 为 空  ", f);
    setenv("TZ", "UTC", 1);
    test_help(prompt + ", TZ 为 UTC ", f);
}

int main() {
    time_t         now;
    struct tm      t;
    struct timeval tv;
    char           buf[1024];

    time(&now);
    gmtime_r(&now, &t);

    test("时间戳, time()", []() {
        time(NULL);
    });

    test("时间戳 => 时间元组, localtime()", [now]() mutable {
        localtime(&now);
    });

    test("时间戳 => 时间元组, localtime_r()", [now, t]() mutable {
        localtime_r(&now, &t);
    });

    test("时间戳 => 时间元组, gmtime()", [now]() mutable {
        gmtime(&now);
    });

    test("时间戳 => 时间元组, gmtime_r()", [now, t]() mutable {
        gmtime_r(&now, &t);
    });

    test("时间元组 => 时间戳, mktime()", [t]() mutable {
        mktime(&t);
    });

    test("时间元组 => 字符串, asctime()", [t]() mutable {
        asctime(&t);
    });

    test("时间元组 => 字符串, asctime_r()", [t, buf]() mutable {
        asctime_r(&t, buf);
    });

    test("时间戳 => 字符串, ctime()", [now]() mutable {
        ctime(&now);
    });

    test("时间戳 => 字符串, ctime_r()", [now, buf]() mutable {
        ctime_r(&now, buf);
    });

    test("字符串 => 时间元组, strptime()", [t]() mutable {
        strptime("2023-12-01", "%Y-%m-%d", &t);
    });

    test("时间元组 => 字符串, strftime()", [t, buf]() mutable {
        strftime(buf, 1024, "%Y-%m-%d", &t);
    });

    test("设置时区, tzset()", []() {
        tzset();
    });

    // 获取毫秒 -- 应该是本地时间
    test("获取本地毫秒, gettimeofday()", [tv]() mutable {
        gettimeofday(&tv, NULL);
    });

    return 0;
}
