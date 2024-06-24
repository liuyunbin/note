// 函数调用
// 1. 将所有参数入栈 -------- PSH
// 2. 栈中存储返回返回使用的地址
// 3. 执行函数调用
//    3.1 栈中保存 bp 地址, 开辟临时栈空间, 用于存储函数内局部变量 -- ENT XX
//    3.2 读取函数参数, 将索引存入符号表
//    3.3 读取函数内局部变量, 将索引存入符号表
//    3.4 处理函数内其他内容
//    3.5 恢复为函数内局部变量开辟的临时栈空间, bp, pc ---- LEV
// 4. 将函数参数出栈 -- ADJ XX

// 函数在栈中的表现
// 1. 函数参数
// 2. 函数返回地址
// 3. bp 备份
// 4. 函数内局部变量

// c4.c - C in four functions

// char, int, and pointer types
// if, while, return, and expression statements
// just enough features to allow self-compilation and a bit more

// Written by Robert Swierczek

#include <fcntl.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define int long long

char *p, *lp,  // current position in source code
    *data;     // data/bss pointer

int *e, *le,  // current position in emitted code
    *id,      // currently parsed identifier
    *sym,     // symbol table (simple list of identifiers)
    tk,       // current token
    ival,     // current token value
    ty,       // current expression type
    loc,      // local variable offset
    line,     // current line number
    src,      // print source and assembly flag
    debug;    // print executed instructions

// tokens and classes (operators last and in precedence order)
// Num------ 数字
// Fun------ 函数
// Sys------ 系统调用
// Glo------ 全局变量
// Loc------ 局部变量
// Id -- 变量
// Char Else Enum If Int Return Sizeof While -- 关键字
// Assign =
// Cond   ?
// Lor    ||
// Lan    &&
// Or     |
// Xor    ^
// And    &
// Eq    ==
// Ne    !=
// Lt     <
// Gt     >
// Le     <=
// Ge     >=
// Shl    <<
// Shr    >>
// Add    +
// Sub    -
// Mul    *
// Div    /
// Mod    %
// Inc    ++
// Dec    --
// Brak   [
enum {
    Num = 128,
    Fun,
    Sys,
    Glo,
    Loc,
    Id,
    Char,
    Else,
    Enum,
    If,
    Int,
    Return,
    Sizeof,
    While,
    Assign,
    Cond,
    Lor,
    Lan,
    Or,
    Xor,
    And,
    Eq,
    Ne,
    Lt,
    Gt,
    Le,
    Ge,
    Shl,
    Shr,
    Add,
    Sub,
    Mul,
    Div,
    Mod,
    Inc,
    Dec,
    Brak
};

// opcodes
enum {
    LEA,
    IMM,
    JMP,
    JSR,
    BZ,
    BNZ,
    ENT,
    ADJ,
    LEV,
    LI,
    LC,
    SI,
    SC,
    PSH,
    OR,
    XOR,
    AND,
    EQ,
    NE,
    LT,
    GT,
    LE,
    GE,
    SHL,
    SHR,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    OPEN,
    READ,
    CLOS,
    PRTF,
    MALC,
    FREE,
    MSET,
    MCMP,
    EXIT
};

// types
enum {
    CHAR,
    INT,
    PTR
};

// identifier offsets (since we can't create an ident struct)
// Tk ------ 标记, 用于区分是变量还是关键字
// Hash ---- 哈希值
// Name ---- 名称
// Class --- 数字 全局变量 局部变量
// Type ---- int char 指针
// Val ----- 变量值, 函数地址
// HClass -- 全局变量的信息
// HType --- 全局变量的信息
// HVal ---- 全局变量的信息
// Idsz ----
enum {
    Tk,
    Hash,
    Name,
    Class,
    Type,
    Val,
    HClass,
    HType,
    HVal,
    Idsz
};

void next() {
    char *pp;

    while (tk = *p) {
        ++p;
        if (tk == '\n') {
            if (src) {
                printf("%d: %.*s", line, p - lp, lp);
                lp = p;
                while (le < e) {
                    printf("%8.4s", &"LEA ,IMM ,JMP ,JSR ,BZ  ,BNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PSH ,"
                           "OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,"
                           "OPEN,READ,CLOS,PRTF,MALC,FREE,MSET,MCMP,EXIT,"[*++le * 5]);
                    if (*le <= ADJ)
                        printf(" %d\n", *++le);
                    else
                        printf("\n");
                }
            }
            ++line;
        } else if (tk == '#') {
            // 跳过预处理
            while (*p != 0 && *p != '\n')
                ++p;
        } else if ((tk >= 'a' && tk <= 'z') || (tk >= 'A' && tk <= 'Z') ||
                   tk == '_') {
            // id 存储对应的符号表
            pp = p - 1;
            while ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') ||
                   (*p >= '0' && *p <= '9') || *p == '_')
                tk = tk * 147 + *p++;
            tk = (tk << 6) + (p - pp);  // 获取对应的 hash 值
            id = sym;
            while (id[Tk]) {
                // 查看之前是否已存储
                if (tk == id[Hash] && !memcmp((char *)id[Name], pp, p - pp)) {
                    tk = id[Tk];
                    return;
                }
                id = id + Idsz;
            }
            id[Name] = (int)pp;
            id[Hash] = tk;
            tk = id[Tk] = Id;  // 变量或关键字
            return;
        } else if (tk >= '0' && tk <= '9') {
            // ival 存储对应的值
            // 十进制
            if (ival = tk - '0') {
                while (*p >= '0' && *p <= '9')
                    ival = ival * 10 + *p++ - '0';
            }
            // 十六进制
            else if (*p == 'x' || *p == 'X') {
                while ((tk = *++p) &&
                       ((tk >= '0' && tk <= '9') || (tk >= 'a' && tk <= 'f') ||
                        (tk >= 'A' && tk <= 'F')))
                    ival =
                        ival * 16 + (tk & 15) +
                        (tk >= 'A' ? 9 : 0);  // 'A' 和 '0' 最后三位 二进制相同
            }
            // 八进制
            else {
                while (*p >= '0' && *p <= '7')
                    ival = ival * 8 + *p++ - '0';
            }
            tk = Num;  // 数字
            return;
        } else if (tk == '/') {
            if (*p == '/') {
                // 跳过注释
                ++p;
                while (*p != 0 && *p != '\n')
                    ++p;
            } else {
                tk = Div;
                return;
            }
        } else if (tk == '\'' || tk == '"') {
            // 如果是字符的话, ival 存储对应的字符
            // 如果是字符串的话,  ival 存储对应的指针, 值存储在 data 中
            pp = data;
            while (*p != 0 && *p != tk) {
                if ((ival = *p++) == '\\') {
                    // 只支持 \n
                    if ((ival = *p++) == 'n')
                        ival = '\n';
                }
                if (tk == '"')
                    *data++ = ival;
            }
            ++p;
            // 字符当数字存储
            if (tk == '"')
                ival = (int)pp;
            else
                tk = Num;
            return;
        } else if (tk == '=') {
            if (*p == '=') {
                ++p;
                tk = Eq;
            } else
                tk = Assign;
            return;
        } else if (tk == '+') {
            if (*p == '+') {
                ++p;
                tk = Inc;
            } else
                tk = Add;
            return;
        } else if (tk == '-') {
            if (*p == '-') {
                ++p;
                tk = Dec;
            } else
                tk = Sub;
            return;
        } else if (tk == '!') {
            if (*p == '=') {
                ++p;
                tk = Ne;
            }
            return;
        } else if (tk == '<') {
            if (*p == '=') {
                ++p;
                tk = Le;
            } else if (*p == '<') {
                ++p;
                tk = Shl;
            } else
                tk = Lt;
            return;
        } else if (tk == '>') {
            if (*p == '=') {
                ++p;
                tk = Ge;
            } else if (*p == '>') {
                ++p;
                tk = Shr;
            } else
                tk = Gt;
            return;
        } else if (tk == '|') {
            if (*p == '|') {
                ++p;
                tk = Lor;
            } else
                tk = Or;
            return;
        } else if (tk == '&') {
            if (*p == '&') {
                ++p;
                tk = Lan;
            } else
                tk = And;
            return;
        } else if (tk == '^') {
            tk = Xor;
            return;
        } else if (tk == '%') {
            tk = Mod;
            return;
        } else if (tk == '*') {
            tk = Mul;
            return;
        } else if (tk == '[') {
            tk = Brak;
            return;
        } else if (tk == '?') {
            tk = Cond;
            return;
        } else if (tk == '~' || tk == ';' || tk == '{' || tk == '}' ||
                   tk == '(' || tk == ')' || tk == ']' || tk == ',' ||
                   tk == ':')
            return;
    }
}

// 优先级
// 1. [  后置++ --
// 2. 前置 ++ -- 一元 ~ !  - + & *
// 3. * / %
// 4. 二元 + -
// 5. << >>
// 6. < <= > >=
// 7. == !=
// 8. 位 &
// 9. 位 ^
// 10. 位 |
// 11. &&
// 12. ||
// 13. ?: =

// Assign =
// Cond   ?
// Lor    ||
// Lan    &&
// Or     |
// Xor    ^
// And    &
// Eq    ==
// Ne    !=
// Lt     <
// Gt     >
// Le     <=
// Ge     >=
// Shl    <<
// Shr    >>
// Add    +
// Sub    -
// Mul    *
// Div    /
// Mod    %
// Inc    ++
// Dec    --
// Brak   [
void expr(int lev) {
    // 执行的结果将存入寄存器
    int t, *d;

    if (!tk) {
        printf("%d: unexpected eof in expression\n", line);
        exit(-1);
    } else if (tk == Num) {
        *++e = IMM;
        *++e = ival;
        next();
        ty = INT;
    }  // 正文段直接存储数字
    else if (tk == '"') {
        // 正文段存储指针, 真正的数据存储在 data 中
        // ival 存储指针地址
        // 这里需要 char* 和 int 所占的位数相同
        *++e = IMM;
        *++e = ival;
        next();
        while (tk == '"')
            next();  // 处理多行的情况
        // 11111111111111111111111111111100 --  -4 的补码
        data = (char *)((int)data + sizeof(int) & -sizeof(int));
        ty   = PTR;  // 干嘛的? 添加 \0, 并字节对齐
    } else if (tk == Sizeof) {
        next();
        if (tk == '(')
            next();
        else {
            printf("%d: open paren expected in sizeof\n", line);
            exit(-1);
        }
        ty = INT;
        if (tk == Int)
            next();
        else if (tk == Char) {
            next();
            ty = CHAR;
        }
        while (tk == Mul) {
            next();
            ty = ty + PTR;
        }
        if (tk == ')')
            next();
        else {
            printf("%d: close paren expected in sizeof\n", line);
            exit(-1);
        }
        *++e = IMM;
        *++e = (ty == CHAR) ? sizeof(char) : sizeof(int);  // 指针按照 int 处理
        ty = INT;
    } else if (tk == Id) {
        d = id;
        next();
        if (tk == '(') {
            // 函数
            next();
            t = 0;
            // 处理参数
            while (tk != ')') {
                expr(Assign);
                *++e = PSH;
                ++t;
                if (tk == ',')
                    next();
            }  // 将寄存器中的值入栈
            next();
            if (d[Class] == Sys)
                *++e = d[Val];
            else if (d[Class] == Fun) {
                *++e = JSR;
                *++e = d[Val];
            }  // 自定义函数需要跳转, 栈中存储下一地址
            else {
                printf("%d: bad function call\n", line);
                exit(-1);
            }
            if (t) {
                *++e = ADJ;
                *++e = t;
            }  // 是否函数参数占用的栈空间, 恢复栈
            ty = d[Type];
        } else if (d[Class] == Num) {
            *++e = IMM;
            *++e = d[Val];
            ty   = INT;
        }  // 宏直接存储在正文段
        else {
            // 变量
            // 此时, 栈空间依次是: 函数参数, 返回地址, bp, 函数内局部变量
            if (d[Class] == Loc) {
                *++e = LEA;
                *++e = loc - d[Val];
            }  // 局部变量存储相对索引, 变量存入寄存器
            else if (d[Class] == Glo) {
                *++e = IMM;
                *++e = d[Val];
            }  // 全局变量存储值的索引, 结果存入寄存器
            else {
                printf("%d: undefined variable\n", line);
                exit(-1);
            }
            // 此时, 寄存器中存储的是变量的地址
            *++e = ((ty = d[Type]) == CHAR)
                       ? LC
                       : LI;  // 将寄存器中的地址对应的值拷入寄存器
                              // 此时, 寄存器中存储的是具体的值
        }
    } else if (tk == '(') {
        next();
        if (tk == Int || tk == Char) {
            // 强制类型转换 貌似直接忽略了
            t = (tk == Int) ? INT : CHAR;
            next();
            while (tk == Mul) {
                next();
                t = t + PTR;
            }
            if (tk == ')')
                next();
            else {
                printf("%d: bad cast\n", line);
                exit(-1);
            }
            expr(Inc);  // Inc 高优先级
            ty = t;
        } else {
            expr(Assign);
            if (tk == ')')
                next();
            else {
                printf("%d: close paren expected\n", line);
                exit(-1);
            }
        }
    } else if (tk == Mul) {
        // 指针取值
        next();
        expr(Inc);  // 高优先级
        if (ty > INT)
            ty = ty - PTR;
        else {
            printf("%d: bad dereference\n", line);
            exit(-1);
        }
        *++e = (ty == CHAR) ? LC : LI;  // 取指针对应的值
    } else if (tk == And) {
        // & 取地址
        next();
        expr(Inc);  // 高优先级
        // 后面一定得是变量或指针
        if (*e == LC || *e == LI)
            --e;
        else {
            printf("%d: bad address-of\n", line);
            exit(-1);
        }
        ty = ty + PTR;
    }
    // 将上一结果入栈, 将 0 写入寄存器, 比较
    else if (tk == '!') {
        next();
        expr(Inc);
        *++e = PSH;
        *++e = IMM;
        *++e = 0;
        *++e = EQ;
        ty   = INT;
    }  // 和 0 比较
    else if (tk == '~') {
        next();
        expr(Inc);
        *++e = PSH;
        *++e = IMM;
        *++e = -1;
        *++e = XOR;
        ty   = INT;
    } else if (tk == Add) {
        next();
        expr(Inc);
        ty = INT;
    }                      // +  一元 忽略
    else if (tk == Sub) {  // -
        next();
        *++e = IMM;
        // 区分常量和函数之类的
        if (tk == Num) {
            *++e = -ival;
            next();
        } else {
            *++e = -1;
            *++e = PSH;
            expr(Inc);
            *++e = MUL;
        }
        ty = INT;
    } else if (tk == Inc || tk == Dec) {
        // ++ -- 前置
        t = tk;
        next();
        expr(Inc);
        // 此时, 寄存器内存储的是变量的值
        // 将 变量的地址, 入栈, 然后 恢复 -- 用于保存结果
        if (*e == LC) {
            *e   = PSH;
            *++e = LC;
        } else if (*e == LI) {
            *e   = PSH;
            *++e = LI;
        } else {
            printf("%d: bad lvalue in pre-increment\n", line);
            exit(-1);
        }
        // 此时, 栈顶存储的是变量的地址
        // 寄存器中存储变量的值 -- 用于计算
        *++e = PSH;  // 将变量的值入栈
        *++e = IMM;
        *++e = (ty > PTR) ? sizeof(int) : sizeof(char);  // 寄存器
        *++e = (t == Inc) ? ADD : SUB;  // 结果在寄存器中
        *++e = (ty == CHAR) ? SC : SI;  // 将结果存回变量
    } else {
        printf("%d: bad expression\n", line);
        exit(-1);
    }

    // 求: = 1 * 2 + 3 * 4
    // 此时 lev 为 =, tk 为 *, 寄存器为 1
    // * 优先级比 = 高, 入栈, 求剩余表达式
    // 此时, 栈中存储 * 1
    //     求: 2 + 3 * 4
    //     此时, lev 为 *, tk 为 +, 寄存器为 2
    //     由于, + 优先级小于 *, 直接返回
    // 计算乘法, 并将结果存储在寄存器, 循环
    // 此时, 寄存器中存储的是 2, lev 为 =, tk 为 +
    // + 优先级比 = 高, 入栈, 求剩余表达式
    // 此时, 栈中存储 + 2
    //     求: 3*4
    //     此时, lev 为 *, tk 为 *, 寄存器为 2
    //     由于, * 的优先级 == *, 入栈, 求剩余表达式
    //     此时, 栈中存储 + 2 * 3
    //         求: 4
    //         此时, lev 为 *, tk 为 NUM, 寄存器为 4
    //         已无元素, 直接返回
    //    计算乘法, 结果入寄存器(12)
    //    此时, 栈中为 + 2
    // 计算加法, 结果入寄存器(14)
    // 此时, tk 为 NUM; , lev 为 =, 退出循环

    // 此时, 寄存器中存储 左操作数, tk 中存储下一字符
    while (tk >= lev) {  // "precedence climbing" or "Top Down Operator
                         // Precedence" method
        t = ty;
        if (tk == Assign) {
            next();
            // 此时, 应该是变量
            // 栈中存储结果
            if (*e == LC || *e == LI)
                *e = PSH;
            else {
                printf("%d: bad lvalue in assignment\n", line);
                exit(-1);
            }
            expr(Assign);
            *++e = ((ty = t) == CHAR) ? SC : SI;  // 存储变量
        } else if (tk == Cond) {
            // ?

            // BZ
            // 失败的跳转地址
            // 成功的部分
            // JMP
            // 跳转地址, 保证执行完成功的部分会跳转
            // 失败的部分 -- 失败将跳到这儿
            // 后续内容
            next();
            *++e = BZ;
            d    = ++e;
            expr(Assign);
            if (tk == ':')
                next();
            else {
                printf("%d: conditional missing colon\n", line);
                exit(-1);
            }
            *d   = (int)(e + 3);
            *++e = JMP;
            d    = ++e;
            expr(Cond);
            *d = (int)(e + 1);
        }
        // BNZ
        // 成功的跳转地址
        else if (tk == Lor) {
            next();
            *++e = BNZ;
            d    = ++e;
            expr(Lan);
            *d = (int)(e + 1);
            ty = INT;
        }  // ||
        else if (tk == Lan) {
            next();
            *++e = BZ;
            d    = ++e;
            expr(Or);
            *d = (int)(e + 1);
            ty = INT;
        }  // &&
        // 将上一结果入栈, 计算后续表达式, 然后, 计算
        else if (tk == Or) {
            next();
            *++e = PSH;
            expr(Xor);
            *++e = OR;
            ty   = INT;
        }  // |
        else if (tk == Xor) {
            next();
            *++e = PSH;
            expr(And);
            *++e = XOR;
            ty   = INT;
        }  // ^
        else if (tk == And) {
            next();
            *++e = PSH;
            expr(Eq);
            *++e = AND;
            ty   = INT;
        }  // &
        else if (tk == Eq) {
            next();
            *++e = PSH;
            expr(Lt);
            *++e = EQ;
            ty   = INT;
        }  // ==
        else if (tk == Ne) {
            next();
            *++e = PSH;
            expr(Lt);
            *++e = NE;
            ty   = INT;
        }  // !=
        else if (tk == Lt) {
            next();
            *++e = PSH;
            expr(Shl);
            *++e = LT;
            ty   = INT;
        }  // <
        else if (tk == Gt) {
            next();
            *++e = PSH;
            expr(Shl);
            *++e = GT;
            ty   = INT;
        }  // >
        else if (tk == Le) {
            next();
            *++e = PSH;
            expr(Shl);
            *++e = LE;
            ty   = INT;
        }  // <=
        else if (tk == Ge) {
            next();
            *++e = PSH;
            expr(Shl);
            *++e = GE;
            ty   = INT;
        }  // >=
        else if (tk == Shl) {
            next();
            *++e = PSH;
            expr(Add);
            *++e = SHL;
            ty   = INT;
        }  // <<
        else if (tk == Shr) {
            next();
            *++e = PSH;
            expr(Add);
            *++e = SHR;
            ty   = INT;
        }  // >>
        else if (tk == Add) {
            // +
            // 上一结果入栈
            // 执行表达式
            next();
            *++e = PSH;
            expr(Mul);
            // 此时, 栈中存储左操作数, 寄存器中存储右操作数
            // 数字 + 数字
            // 数字 + 指针
            // 指针 + 数字
            // 对于指针要加上偏移量
            if ((ty = t) > PTR) {
                *++e = PSH;
                *++e = IMM;
                *++e = sizeof(int);
                *++e = MUL;
            }
            *++e = ADD;
        } else if (tk == Sub) {
            // -
            next();
            *++e = PSH;
            expr(Mul);
            // 此时, 栈中存储左操作数, 寄存器中存储右操作数
            // 同类指针相减
            // 先按数字相减, 再将结果存入栈中, 然后除以元素大小,
            // 最终得到元素个数
            if (t > PTR && t == ty) {
                *++e = SUB;
                *++e = PSH;
                *++e = IMM;
                *++e = sizeof(int);
                *++e = DIV;
                ty   = INT;
            }
            // 指针 - 数字
            // 先把数字入栈, 然后乘以操作数的大小, 最后相减
            else if ((ty = t) > PTR) {
                *++e = PSH;
                *++e = IMM;
                *++e = sizeof(int);
                *++e = MUL;
                *++e = SUB;
            }
            // 数字 - 数字
            else
                *++e = SUB;
        } else if (tk == Mul) {
            next();
            *++e = PSH;
            expr(Inc);
            *++e = MUL;
            ty   = INT;
        } else if (tk == Div) {
            next();
            *++e = PSH;
            expr(Inc);
            *++e = DIV;
            ty   = INT;
        } else if (tk == Mod) {
            next();
            *++e = PSH;
            expr(Inc);
            *++e = MOD;
            ty   = INT;
        } else if (tk == Inc || tk == Dec) {
            // ++ -- a++ a--
            // 将变量地址入栈
            if (*e == LC) {
                *e   = PSH;
                *++e = LC;
            } else if (*e == LI) {
                *e   = PSH;
                *++e = LI;
            } else {
                printf("%d: bad lvalue in post-increment\n", line);
                exit(-1);
            }
            // 此时, 变量地址在栈中, 变量值在寄存器中
            // 将值推入栈中, 然后, 计算
            *++e = PSH;
            *++e = IMM;
            *++e = (ty > PTR) ? sizeof(int) : sizeof(char);
            *++e = (tk == Inc) ? ADD : SUB;
            // 将计算结果拷回变量
            *++e = (ty == CHAR) ? SC : SI;
            // 计算之前的值, 用于返回, 为啥不保存之前的变量
            *++e = PSH;
            *++e = IMM;
            *++e = (ty > PTR) ? sizeof(int) : sizeof(char);
            *++e = (tk == Inc) ? SUB : ADD;
            next();
        } else if (tk == Brak) {
            // [
            // 将索引入栈
            next();
            *++e = PSH;
            expr(Assign);
            if (tk == ']')
                next();
            else {
                printf("%d: close bracket expected\n", line);
                exit(-1);
            }
            // 对于指针, 计算偏移量
            if (t > PTR) {
                *++e = PSH;
                *++e = IMM;
                *++e = sizeof(int);
                *++e = MUL;
            } else if (t < PTR) {
                printf("%d: pointer type expected\n", line);
                exit(-1);
            }
            // 计算最终的地址
            *++e = ADD;
            // 将变量的值存入寄存器
            *++e = ((ty = t - PTR) == CHAR) ? LC : LI;
        } else {
            printf("%d: compiler error tk=%d\n", line, tk);
            exit(-1);
        }
    }
}

void stmt() {
    int *a, *b;

    if (tk == If) {
        next();
        if (tk == '(')
            next();
        else {
            printf("%d: open paren expected\n", line);
            exit(-1);
        }
        expr(Assign);
        if (tk == ')')
            next();
        else {
            printf("%d: close paren expected\n", line);
            exit(-1);
        }
        // 此时, 寄存器中存储条件的结果

        // BZ
        // 失败的跳转地址 -- else 里 或 if 后的地址
        // if 部分代码
        // JMP
        // 跳转地址 -- 保证 if 部分代码执行后会跳转
        // else 部分代码

        // 成功 -- 跳过下一位置继续
        // 失败 -- 跳转
        *++e = BZ;
        b    = ++e;
        stmt();
        if (tk == Else) {
            *b   = (int)(e + 3);
            *++e = JMP;
            b    = ++e;
            next();
            stmt();
        }
        *b = (int)(e + 1);
    } else if (tk == While) {
        next();
        a = e + 1;  // a 为 while 的起始地址
        if (tk == '(')
            next();
        else {
            printf("%d: open paren expected\n", line);
            exit(-1);
        }
        expr(Assign);
        if (tk == ')')
            next();
        else {
            printf("%d: close paren expected\n", line);
            exit(-1);
        }
        // 此时, 寄存器中存储 while 的判断条件

        // BZ
        // 失败的跳转地址, while 后的代码
        // 主体
        // JMP
        // 跳转地址 -- 跳到 while 条件判断
        *++e = BZ;
        b    = ++e;
        stmt();
        *++e = JMP;
        *++e = (int)a;
        *b   = (int)(e + 1);
    } else if (tk == Return) {  // 貌似不会处理这个
        next();
        if (tk != ';')
            expr(Assign);
        *++e = LEV;  // 会不会和之后的重复
        if (tk == ';')
            next();
        else {
            printf("%d: semicolon expected\n", line);
            exit(-1);
        }
    } else if (tk == '{') {
        next();
        while (tk != '}')
            stmt();
        next();
    } else if (tk == ';') {
        next();
    } else {
        expr(Assign);  // 一条处理表达式, 不包括 分号
        if (tk == ';')
            next();
        else {
            printf("%d: semicolon expected\n", line);
            exit(-1);
        }
    }
}

int main(int argc, char **argv) {
    int  fd, bt, ty, poolsz, *idmain;
    int *pc, *sp, *bp, a, cycle;  // vm registers
    int  i, *t;                   // temps

    --argc;
    ++argv;
    if (argc > 0 && **argv == '-' && (*argv)[1] == 's') {
        src = 1;
        --argc;
        ++argv;
    }
    if (argc > 0 && **argv == '-' && (*argv)[1] == 'd') {
        debug = 1;
        --argc;
        ++argv;
    }
    if (argc < 1) {
        printf("usage: c4 [-s] [-d] file ...\n");
        return -1;
    }

    if ((fd = open(*argv, 0)) < 0) {
        printf("could not open(%s)\n", *argv);
        return -1;
    }

    poolsz = 256 * 1024;  // arbitrary size
    // 存储符号表
    if (!(sym = malloc(poolsz))) {
        printf("could not malloc(%d) symbol area\n", poolsz);
        return -1;
    }
    // 存储正文段
    if (!(le = e = malloc(poolsz))) {
        printf("could not malloc(%d) text area\n", poolsz);
        return -1;
    }
    // 存储字符串
    if (!(data = malloc(poolsz))) {
        printf("could not malloc(%d) data area\n", poolsz);
        return -1;
    }
    // 栈空间
    if (!(sp = malloc(poolsz))) {
        printf("could not malloc(%d) stack area\n", poolsz);
        return -1;
    }

    memset(sym, 0, poolsz);
    memset(e, 0, poolsz);
    memset(data, 0, poolsz);

    p = "char else enum if int return sizeof while "
        "open read close printf malloc free memset memcmp exit void main";
    // 添加关键字到符号表
    i = Char;
    while (i <= While) {
        next();
        id[Tk] = i++;
    }  // add keywords to symbol table
    // 添加支持的系统调用, 类型是整型, 值为对应的宏名称
    i = OPEN;
    while (i <= EXIT) {
        next();
        id[Class] = Sys;
        id[Type]  = INT;
        id[Val]   = i++;
    }  // add library to symbol table
    next();
    id[Tk] = Char;  // handle void type -- void 类型当作 char 处理
    next();
    idmain = id;  // keep track of main -- 存储主函数的位置

    if (!(lp = p = malloc(poolsz))) {
        printf("could not malloc(%d) source area\n", poolsz);
        return -1;
    }
    if ((i = read(fd, p, poolsz - 1)) <= 0) {
        printf("read() returned %d\n", i);
        return -1;
    }
    p[i] = 0;  // 保存为字符串
    close(fd);

    // parse declarations
    line = 1;
    next();
    while (tk) {
        bt = INT;  // basetype
        if (tk == Int)
            next();
        else if (tk == Char) {
            next();
            bt = CHAR;
        } else if (tk == Enum) {
            next();
            // 此种情况下, tk 是枚举的名称
            if (tk != '{')
                next();
            // 枚举类型定义
            if (tk == '{') {
                next();
                i = 0;
                while (tk != '}') {
                    if (tk != Id) {
                        printf("%d: bad enum identifier %d\n", line, tk);
                        return -1;
                    }
                    next();  // 此处可能是 , 或 } 或 =
                    if (tk == Assign) {
                        next();
                        if (tk != Num) {
                            printf("%d: bad enum initializer\n", line);
                            return -1;
                        }
                        i = ival;
                        next();  // 此处可能是 , 或 }
                    }
                    id[Class] = Num;
                    id[Type]  = INT;
                    id[Val]   = i++;  // 相当于定义数字常量
                    if (tk == ',')
                        next();
                }
                next();
            }
        }
        // 对于枚举类型定义, 此处 tk 应该为 ;
        // 对于 int char enum 变量或函数的定义, 此时, tk 为下一标识
        while (tk != ';' && tk != '}') {
            ty = bt;
            while (tk == Mul) {
                next();
                ty = ty + PTR;
            }  // 指针类定义
            if (tk != Id) {
                printf("%d: bad global declaration\n", line);
                return -1;
            }  // 只能全局变量定义
            if (id[Class]) {
                printf("%d: duplicate global definition\n", line);
                return -1;
            }  // 重定义
            // 此时已读取 函数名或变量名
            next();
            id[Type] = ty;
            if (tk == '(') {  // function
                id[Class] = Fun;
                id[Val] = (int)(e + 1);  // 正文段的开头地址为啥是 0 了
                next();
                i = 0;  // 变量个数计数器
                while (tk != ')') {
                    ty = INT;
                    if (tk == Int)
                        next();
                    else if (tk == Char) {
                        next();
                        ty = CHAR;
                    }
                    while (tk == Mul) {
                        next();
                        ty = ty + PTR;
                    }  // 指针
                    if (tk != Id) {
                        printf("%d: bad parameter declaration\n", line);
                        return -1;
                    }
                    if (id[Class] == Loc) {
                        printf("%d: duplicate parameter definition\n", line);
                        return -1;
                    }
                    // 备份之前的全局变量, 并存储新变量, 避免变量覆盖
                    id[HClass] = id[Class];
                    id[Class]  = Loc;
                    id[HType]  = id[Type];
                    id[Type]   = ty;
                    id[HVal]   = id[Val];
                    id[Val]    = i++;  // 值为第几个参数 从 0 开始
                    next();
                    if (tk == ',')
                        next();
                }
                next();
                if (tk != '{') {
                    printf("%d: bad function definition\n", line);
                    return -1;
                }
                // 此时函数参数已经处理完成
                // 此时, 栈结构为
                // * 函数实参
                // * 函数返回地址
                // * 旧 bp 的内容 -- ENT
                // * 函数内局部变量
                loc = ++i;  // loc 存储函数参数个数
                next();
                while (tk == Int || tk == Char) {
                    bt = (tk == Int) ? INT : CHAR;
                    next();
                    while (tk != ';') {
                        ty = bt;
                        while (tk == Mul) {
                            next();
                            ty = ty + PTR;
                        }  // 指针
                        if (tk != Id) {
                            printf("%d: bad local declaration\n", line);
                            return -1;
                        }
                        if (id[Class] == Loc) {
                            printf("%d: duplicate local definition\n", line);
                            return -1;
                        }
                        id[HClass] = id[Class];
                        id[Class]  = Loc;
                        id[HType]  = id[Type];
                        id[Type]   = ty;
                        id[HVal]   = id[Val];
                        id[Val]    = ++i;  // 值为参数的索引
                        next();
                        if (tk == ',')
                            next();
                    }
                    next();
                }
                // 此时, 函数局部变量已处理完成, 局部变量不允许定义时初始化
                // 保存 bp 指针, 跳过用于存储局部变量的空间
                *++e = ENT;
                *++e = i - loc;
                while (tk != '}')
                    stmt();
                // 恢复 bp 指针, 恢复栈空间, 恢复 pc
                *++e = LEV;
                // 恢复全局变量
                id = sym;  // unwind symbol table locals
                while (id[Tk]) {
                    if (id[Class] == Loc) {
                        id[Class] = id[HClass];
                        id[Type]  = id[HType];
                        id[Val]   = id[HVal];
                    }
                    id = id + Idsz;
                }
            } else {
                // 定义全局变量 -- 不允许定义时初始化
                id[Class] = Glo;
                id[Val]   = (int)data;
                data      = data + sizeof(int);
            }
            if (tk == ',')
                next();
        }
        next();
    }

    if (!(pc = (int *)idmain[Val])) {
        printf("main() not defined\n");
        return -1;
    }
    if (src)
        return 0;

    // setup stack
    bp = sp = (int *)((int)sp + poolsz);  // 栈顶
    *--sp   = EXIT;                       // call exit if main returns
    *--sp   = PSH;
    t       = sp;  // 设置 EXIT 参数
    *--sp   = argc;
    *--sp   = (int)argv;
    *--sp   = (int)t;  // main 函数返回的跳转地址

    // run...
    cycle = 0;
    while (1) {
        i = *pc++;
        ++cycle;
        if (debug) {
            printf("%d> %.4s", cycle,
        &"LEA ,IMM ,JMP ,JSR ,BZ  ,BNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PSH ,"
         "OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,"
         "OPEN,READ,CLOS,PRTF,MALC,FREE,MSET,MCMP,EXIT,"[i * 5]);
            if (i <= ADJ)
                printf(" %d\n", *pc);
            else
                printf("\n");
        }
        // 从当前栈中读取函数局部变量和函数参数
        if (i == LEA)
            a = (int)(bp + *pc++);  // load local address
        // 读取正文段的值
        else if (i == IMM)
            a = *pc++;  // load global address or immediate
        // 无条件跳转
        else if (i == JMP)
            pc = (int *)*pc;  // jump
        // 函数调用时, 栈中依次存储:
        // * 实际参数
        // * 下一条命令的地址
        // * 旧 bp 的位置
        // 栈中存储下一命令的位置, 然后函数跳转
        else if (i == JSR) {
            *--sp = (int)(pc + 1);
            pc    = (int *)*pc;
        }  // jump to subroutine
        // false 就跳转
        else if (i == BZ)
            pc = a ? pc + 1 : (int *)*pc;  // branch if zero
        // true 就跳转
        else if (i == BNZ)
            pc = a ? (int *)*pc : pc + 1;  // branch if not zero
        // 保存之前的 bp 指针, 并开辟新的栈空间, 存储函数内局部变量
        else if (i == ENT) {
            *--sp = (int)bp;
            bp    = sp;
            sp    = sp - *pc++;
        }  // enter subroutine
        // 释放函数参数占用的栈空间
        else if (i == ADJ)
            sp = sp + *pc++;  // stack adjust
        // 恢复之前的栈顶指针
        // 依次获取 bp, 函数的返回地址
        // 结束函数调用
        else if (i == LEV) {
            sp = bp;
            bp = (int *)*sp++;
            pc = (int *)*sp++;
        }  // leave subroutine
        // 取元素到寄存器, 寄存器存放元素的地址 (int)
        else if (i == LI)
            a = *(int *)a;  // load int
        // 取元素到寄存器, 寄存器存放元素的地址 (char)
        else if (i == LC)
            a = *(char *)a;  // load char
        // 将寄存器中的元素当成整数存入指定地址
        // 地址存储在栈顶, 并出栈
        else if (i == SI)
            *(int *)*sp++ = a;  // store int
        // 将寄存器中的元素当成字符存入指定地址, 并将结果存回寄存器
        // 地址存储在栈顶, 并出栈
        else if (i == SC)
            a = *(char *)*sp++ = a;  // store char
        // 将寄存器中的元素存入栈顶
        // 可用于设置实参
        else if (i == PSH)
            *--sp = a;  // push

        else if (i == OR)
            a = *sp++ | a;  // 左操作数存储在栈顶, 右操作数存储在寄存器
        else if (i == XOR)
            a = *sp++ ^ a;
        else if (i == AND)
            a = *sp++ & a;
        else if (i == EQ)
            a = *sp++ == a;
        else if (i == NE)
            a = *sp++ != a;
        else if (i == LT)
            a = *sp++ < a;
        else if (i == GT)
            a = *sp++ > a;
        else if (i == LE)
            a = *sp++ <= a;
        else if (i == GE)
            a = *sp++ >= a;
        else if (i == SHL)
            a = *sp++ << a;
        else if (i == SHR)
            a = *sp++ >> a;
        else if (i == ADD)
            a = *sp++ + a;
        else if (i == SUB)
            a = *sp++ - a;
        else if (i == MUL)
            a = *sp++ * a;
        else if (i == DIV)
            a = *sp++ / a;
        else if (i == MOD)
            a = *sp++ % a;

        else if (i == OPEN)
            a = open((char *)sp[1], *sp);  // 函数参数的入栈顺序从右到左
        else if (i == READ)
            a = read(sp[2], (char *)sp[1], *sp);
        else if (i == CLOS)
            a = close(*sp);
        else if (i == PRTF) {
            t = sp + pc[1];
            a = printf((char *)t[-1], t[-2], t[-3], t[-4], t[-5], t[-6]);
        } else if (i == MALC)
            a = (int)malloc(*sp);
        else if (i == FREE)
            free((void *)*sp);
        else if (i == MSET)
            a = (int)memset((char *)sp[2], sp[1], *sp);
        else if (i == MCMP)
            a = memcmp((char *)sp[2], (char *)sp[1], *sp);
        else if (i == EXIT) {
            printf("exit(%d) cycle = %d\n", *sp, cycle);
            return *sp;
        } else {
            printf("unknown instruction = %d! cycle = %d\n", i, cycle);
            return -1;
        }
    }
}
