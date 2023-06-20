
#include "log.h"

int main() {
    log();
    // scanf     # 除了 %c 外, 将忽略所有的空白字符
    // getchar() # 读取一个字符, 包含空白字符
    // fgets()   # 读取一行, 包含换行符

#if 0
    char ch;
    log("请输入字符(包括空白字符)");
    scanf("%c", &ch);
    log("111%c111", ch);
#endif

#if 0
    char ch;
    log("请输入字符(空白字符将被忽略)");
    scanf(" %c", &ch);
    log("111%c111", ch);
#endif

#if 0
    char buf[64];
    log("请输入字符串(最多输入5位)");
    scanf("%5s", buf);
    log("1111%s111", buf);
#endif

#if 0
    int v;
    log("请输入整数(最多输入5位)");
    scanf("%5d", &v);
    log("aaa%daaa", v);
#endif

    const char* s = "123";

    log("字符串(原始            ): %s", s);
    log("字符串(最小宽度, 右对齐): %10s", s);
    log("字符串(最小宽度, 左对齐): %-10s", s);
    printf("字符串(最小宽度, 参数指定): %*s\n", 10, s);

    int i = 123;

    log("整数(原始              ): %d", i);
    log("整数(最小宽度,   右对齐): %10d", i);
    log("整数(最小宽度,   左对齐): %-10d", i);
    printf("整数  (最小宽度, 参数指定): %*d\n", 10, i);
    log("整数(最小宽度, 前缀为零): %010d", i);
    log("整数(正数添加前缀加号  ): %+10d", i);
    log("整数(  十进制    无符号): %u", i);
    log("整数(  八进制    无符号): %o", i);
    log("整数(十六进制    无符号): %x", i);
    // %lu %ld 同理
    log("指针                    : %p", &i);

    double d = 3.1459265354;
    log("浮点数(非科学计数)      : %f", d);
    log("浮点数(  科学计数)      : %e", d);
    log("浮点数(指明小数点位数)  : %.2f", d);  // 四舍六入五取偶
    log("浮点数(指明最小宽度)    : %10.2f", d);

    log();

    return 0;
}
