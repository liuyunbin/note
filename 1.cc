
#include "log.h"

int main() {
    // scanf     # 除了 %c 外, 将忽略所有的空白字符
    // getchar() # 读取一个字符, 包含空白字符
    // fgets()   # 读取一行, 包含换行符

#if 0
    char ch;
    scanf("%c", &ch);  // 输入包括空白字符
    printf("111%c111\n", ch);
#endif

#if 0
    char ch;
    scanf(" %c", &ch);  // 输入忽略所有的空白字符
    printf("111%c111\n", ch);
#endif

#if 0
    // 指定输入的最大位数
    char buf[64];
    scanf("%3s", buf);
    printf("1111%s111\n", buf);
#endif

#if 0
    // 指定输入的最大位数
    int v;
    scanf("%3d", &v);
    printf("aaa%daaa\n", v);
#endif

    const char* s = "123";

    log("字符串(原始              ): %s\n", s);
    log("字符串(最小宽度,   右对齐): %10s\n", s);
    log("字符串(最小宽度,   左对齐): %-10s\n", s);
    log("字符串(最小宽度, 参数指定): %*s\n", 10, s);

    int i = 123;

    log("整数(原始                ): %d\n", i);
    log("整数(最小宽度,   右对齐  ): %10d\n", i);
    log("整数(最小宽度,   左对齐  ): %-10d\n", i);
    log("整数(最小宽度, 参数指定  ): %*d\n", 10, i);
    log("整数(最小宽度, 前缀为零  ): %010d\n", i);
    log("整数(正数添加前缀加号    ): %+10d\n", i);
    //"%u"     # 无符号的  十进制整数
    //"%o"     # 无符号的  八进制整数
    //"%x"     # 无符号的十六进制整数
    // %lu %ld 同理
    log("                      指针: %p\n", &i);

    double d = 3.1459265354;
    log("浮点数(非科学计数)        : %f\n", d);
    log("浮点数(  科学计数)        : %e\n", d);
    log("浮点数(指明小数点位数)    : %.2f\n", d);  // 四舍六入五取偶
    log("浮点数(指明最小宽度)      : %10.2f\n", d);

    std::string str = "123";

    // 全缓存
    // * 程序结束
    // * 缓冲区满
    // * 手动刷新缓存
    // * 涉及磁盘文件一般是全缓存
    // 行缓冲
    // * 程序结束
    // * 缓冲区满
    // * 遇到文件结束符
    // * 手动刷新缓存
    // * 涉及终端一般是行缓存
    // 无缓冲
    // * 涉及终端输出错误是无缓存
    std::cout << std::endl << "测试  自动刷新缓冲" << std::endl;
    std::cout << std::unitbuf;  // 每次调用都自动刷新缓冲区
    std::cout << "暂停5s...";
    sleep(5);
    std::cout << "完成" << std::endl;

    std::cout << std::endl << "测试不自动刷新缓冲" << std::endl;
    std::cout << std::nounitbuf;  // 不自动刷新缓冲区
    std::cout << "暂停5s...";
    sleep(5);
    std::cout << "完成" << std::endl;

    return 0;
}
