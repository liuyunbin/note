
// ## 项目流程：
// 1. 输出命令行前缀：“>”
// 2. 读取用户的输入，忽略所有的空格，
// 3. 如果用户输入为空，跳到第 1 步
// 4. 新建两个栈，一个存储数字，一个存储字符，然后开始判断每一个字符，
//     * 如果当前字符是 “+”
//     且是用户输入的第一个字符，跳过该字符，然后判断下一个字符
//     * 如果当前字符是 “-” 且是用户输入的第一个字符，将其压入字符栈，将 0
//     压入数字栈，然后判断下一字符
//     * 如果当前字符是数字字符，尽可能解析出整数，将其压入数字栈，然后判断下一字符
//     * 如果当前字符是 “(”，直接将其压入字符栈，然后，判断下一字符，
//         * 如果下一字符是 “+”，跳过该字符，然后判断下一字符
//         * 如果下一字符是 “-”，将其压入字符栈，将 0
//         压入数字栈，然后判断下一字符
//     * 如果当前字符是 “)”，
//         * 如果字符栈里的栈顶字符是 “+”，“-”，“*”，“/”，
//             * 从字符栈里弹出符号，
//             * 从数字栈里弹出两个数字，
//             * 利用上述的两个数字和运算符计算，将结果压入数字栈，然后继续判断字符栈栈顶字符
//         * 如果字符栈里的栈顶字符是 “(”，弹出栈顶字符，然后判断下一字符
//     * 如果当前字符是 “+”，“-”，“*”，“/”，然后判断，
//         * 如果字符栈为空 或 字符栈栈顶元素为
//         “(”，直接将当前字符压入字符栈，然后判断下一字符
//         * 如果字符栈栈顶元素是 “*” 或 “/” 或者 当前字符是 “+” 或 “-”，
//             * 从字符栈里弹出符号，
//             * 从数字栈里弹出两个数字，
//             * 利用上述的两个数字和运算符计算，将结果压入数字栈，然后继续判断栈顶字符
//         * 如果字符栈栈顶元素是 “+” 或 “-” 而且 当前字符是 “*” 或
//         “/”，将当前字符压入字符栈，然后判断下一字符
// 5. 判断字符栈，
//     * 如果字符栈不为空，
//         * 从字符栈里弹出符号，
//         * 从数字栈里弹出两个数字，
//         * 利用上述的两个数字和运算符计算，将结果压入数字栈，然后继续判断字符栈
//     * 如果字符栈为空，直接输出数字栈栈顶值，即是最后的计算结果
//
// **注意：**
// * 最后数字栈应该只有一个元素，字符栈为空，否则，输入格式错误
// * 对于用户开头输入的 + 或 左括号后的 + 直接忽略
// * 对于用户开头输入的 - 或 左括号后的 - ，在其前面添加 0 ，从而将其变成减法
//
// ## 支持的格式：
// * 1+2
// * 1+2=
// * 1+2*(3+4)
// * 1+2*(+3+4)
// * 1+2*(-3+4)
// * (-(-1))
// * (+(-1))
// * +1
// * -1
//
#include "lshell.h"

char             data[1024];  // 存储输入字符串
std::stack<char> stack_char;  // 存储运算符
std::stack<long> stack_long;  // 存储运算数

static void input() {
    fputs("> ", stdout);
    if (fgets(data, sizeof(data), stdin) == NULL)  // 读入 EOF
        exit(EXIT_SUCCESS);
    // 移除多余的空格
    int k = 0;
    for (size_t i = 0; data[i] != '\0'; ++i)
        if (data[i] != ' ' && data[i] != '\n')
            data[k++] = data[i];
    if (k > 0 && data[k - 1] == '=')
        data[k - 1] = '\0';
    else
        data[k] = '\0';
}

bool count_one_char(char ch) {
    if (stack_long.size() < 2)
        return false;

    long rhs = stack_long.top();
    stack_long.pop();
    long lhs = stack_long.top();
    stack_long.pop();
    long data;
    switch (ch) {
    case '+':
        data = lhs + rhs;
        break;
    case '-':
        data = lhs - rhs;
        break;
    case '*':
        data = lhs * rhs;
        break;
    case '/':
        if (rhs == 0)
            return false;
        data = lhs / rhs;
        break;
    default:
        return false;
    }
    stack_long.push(data);
    return true;
}

bool solve() {
    char *st = data;
    if (*st == '+') {  // 解决开头类似 +123 的情况
        ++st;
    } else if (*st == '-') {  // 解决开头类似 -123 的情况
        stack_long.push(0);
        stack_char.push(*st++);
    }

    while (*st != '\0') {
        if (isdigit(*st)) {  // 当前是数字
            long data = strtol(st, &st, 10);
            stack_long.push(data);
            continue;
        }

        if (*st == '(') {
            stack_char.push(*st++);
            if (*st == '+') {  // 解决 类似 (+123) 的问题
                ++st;
            } else if (*st == '-') {  // 解决 类似 (-123) 的问题
                stack_long.push(0);
                stack_char.push(*st++);
            }
            continue;
        }
        if (*st == ')') {
            for (;;) {
                if (stack_char.empty())
                    return false;
                char ch = stack_char.top();
                stack_char.pop();
                if (ch == '(')
                    break;
                if (count_one_char(ch) == false)
                    return false;
            }
            ++st;
            continue;
        }
        if (*st != '+' && *st != '-' && *st != '*' && *st != '/')
            return false;
        for (;;) {
            if (stack_char.empty() || stack_char.top() == '(') {
                stack_char.push(*st++);
                break;
            }
            char ch = stack_char.top();
            if ((ch == '+' || ch == '-') && (*st == '*' || *st == '/')) {
                stack_char.push(*st++);
                break;
            }
            if (count_one_char(ch) == false)
                return false;
            stack_char.pop();
        }
    }
    for (;;) {
        if (stack_char.empty())
            break;
        char ch = stack_char.top();
        if (count_one_char(ch) == false)
            return false;
        stack_char.pop();
    }
    if (stack_long.size() != 1)
        return false;
    std::cout << stack_long.top() << std::endl;
    return true;
}

void output() {
    if (data[0] == '\0')
        return;

    if (solve() == false)
        std::cout << "输入格式错误" << std::endl;

    // 清空栈，避免影响下次计算
    while (!stack_char.empty())
        stack_char.pop();
    while (!stack_long.empty())
        stack_long.pop();
}

int do_bc(int argc, char *argv[]) {
    for (;;) {
        input();
        output();
    }
    return 0;
}
