
#include <iostream>

int main() {
    // scanf     # 除了 %c 外, 将忽略所有的空白字符
    // getchar() # 读取一个字符, 包含空白字符
    // fgets()   # 读取一行, 包含换行符

#if 0
    char ch;
    printf("请输入字符(包括空白字符)");
    scanf("%c", &ch);
    printf("111%c111", ch);
#endif

#if 0
    char ch;
    printf("请输入字符(空白字符将被忽略)");
    scanf(" %c", &ch);
    printf("111%c111", ch);
#endif

#if 0
    char buf[64];
    printf("请输入字符串(最多输入5位)");
    scanf("%5s", buf);
    printf("1111%s111", buf);
#endif

#if 0
    int v;
    printf("请输入整数(最多输入5位)");
    scanf("%5d", &v);
    printf("aaa%daaa", v);
#endif

    const char* s = "123";

    printf("字符串(原始            ): %s\n", s);
    printf("字符串(最小宽度, 右对齐): %10s\n", s);
    printf("字符串(最小宽度, 左对齐): %-10s\n", s);
    printf("字符串(最小宽度, 参数指定): %*s\n\n", 10, s);

    int i = 123;

    printf("整数(原始              ): %d\n", i);
    printf("整数(最小宽度,   右对齐): %10d\n", i);
    printf("整数(最小宽度,   左对齐): %-10d\n", i);
    printf("整数  (最小宽度, 参数指定): %*d\n\n", 10, i);
    printf("整数(最小宽度, 前缀为零): %010d\n", i);
    printf("整数(正数添加前缀加号  ): %+10d\n", i);
    printf("整数(  十进制    无符号): %u\n", i);
    printf("整数(  八进制    无符号): %o\n", i);
    printf("整数(十六进制    无符号): %x\n", i);
    // %lu %ld 同理
    printf("指针                    : %p\n", &i);

    double d = 3.1459265354;
    printf("浮点数(非科学计数)      : %f\n", d);
    printf("浮点数(  科学计数)      : %e\n", d);
    printf("浮点数(指明小数点位数)  : %.2f\n", d);  // 四舍六入五取偶
    printf("浮点数(指明最小宽度)    : %10.2f\n", d);

    return 0;
}
