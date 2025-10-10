/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif
// 1
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    // 情况 1
    int a = (~x) & (~y);
    // 情况 2 3 4
    int b = ~a;
    // 情况 4
    int c = x & y;
    // 情况 1 2 3
    int d = ~c;
    return b & d;
}

/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) { return 0x1 << 31; }
// 2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    // if x = 0x7FFFFFFF, x + 1 = 0x80000000, //可能是未定义的行为
    // x + 1 + x + 1 == 0
    // 排除 0 + 0 = 0 的情况
    //  return (!(x + 1 + x + 1)) & (!!(x + 1));
    int y = x + 1;
    return (!((~y + 1) ^ y)) & (!!y);
}
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    // a == 0xAAAA
    int a = (0xAA << 8) + 0xAA;
    // a == 0xAAAA AAAA
    a = (a << 16) + a;
    return !((a & x) ^ a);
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) { return ~x + 1; }
// 3
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0'
 * to '9') Example: isAsciiDigit(0x35) = 1. isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    int sign;
    int a;
    int b;

    // 符号位置为 1，其它位为 0
    sign = 0x1 << 31;

    // a == -0x30 即：0x30 + a == 0
    a = ~0x30 + 1;

    // 获取 x + a 的符号位，其它位置为 0
    a = sign & (a + x);

    // 对 a 的符号位取反，其它位依然是 0
    a = sign & (~a);

    // b == ~0x39 == ~0x39 + 1 - 1 == -0x39 - 1 == -0x3a
    // 即：0x39 + b == -1
    // 即：0x3a + b ==  0
    b = ~0x39;

    // 获取 x + b 的符号位，其它位置为 0
    b = sign & (b + x);

    // 如果 x 属于 [0x30, 0x39]
    // a == 0x8000 0000
    // b == 0x8000 0000
    return !!(a & b);
}

/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    // x == 0 或 1
    x = !!x;
    // x == 0x0000 0000 或 0xFFFF FFFF
    x = ~x + 1;
    return (x & y) | (~x & z);
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    int sign;
    int a;
    int b;
    int c;
    int d;

    // 符号位置为 1，其它位为 0
    sign = 0x1 << 31;

    // 如果 a，b 异号，a == 0x8000 0000，否则，a == 0x0000 0000
    a = (sign & x) ^ (sign & y);

    // 如果 a，b 异号，a == 1，否则，a == 0
    a = !!a;

    // 如果 a，b 异号，a == 0xFFFF FFFF，否则，a == 0x0000 0000
    a = ~a + 1;

    // b = x - y
    b = x + ~y + 1;

    // 如果 x，y 异号 且 x <  0，c == 1，否则，c == 0
    c = !!(a & (x & sign));

    // 如果 x，y 同号 且 x <= y，c == 1，否则，c == 0
    d = !!((~a) & ((b & sign) | (!b)));

    return c | d;
}
// 4
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x) {
    int a;
    int b;

    // 如果 x 与 -x 的符号位不同，a 的最低位为 1, 否则 a 的最低位为 0
    a = (x ^ (~x + 1)) >> 31;

    // 如果 x 的最高位为 1，b 的最低位为 1，否则，b 的最低位为 0
    b = x >> 31;

    return ~(a | b) & 0x1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    int a;
    int b;
    int ret;

    // 如果，x < 0，a == 1，否则，a == 0
    a = (x >> 31) & 0x1;

    // 如果，a == 1，a == 0xFFFF FFFF，否则，a == 0x0000 0000
    a = ~a + 1;

    // 如果 x >= 0, 则不变，
    // 如果 x <  0，按位取反，前面连续的 1 都变为 0
    x = (a & ~x) | (~a & x);

    // 位从右往左数，从 0 开始

    // 如果 x 的 [16, 32) 位存在 1，b == 16，否则，b == 0
    b = !!(x >> 16) << 4;
    // 如果 x 的 [16, 32) 位存在 1
    //    则 [0, 16) 位是必须的，只要判断 [16, 32) 位即可，
    //    将 x 右移 16 位
    ret = b;
    x = x >> b;

    // 接下来判断 [8, 16) 位
    // 如果 x 的 [8, 16) 位存在 1，b == 8，否则，b == 0
    b = !!(x >> 8) << 3;
    // 如果 x 的 [8, 16) 位存在 1
    //    则 [0, 8) 位是必须的，只要判断 [8, 16) 位即可，
    //    将 x 右移 8 位
    ret += b;
    x = x >> b;

    // 接下来判断 [4, 8) 位
    // 如果 x 的 [4, 8) 位存在 1，b == 4，否则，b == 0
    b = !!(x >> 4) << 2;
    // 如果 x 的 [4, 8) 位存在 1
    //    则 [0, 4) 位是必须的，只要判断 [4, 8) 位即可，
    //    将 x 右移 4 位
    ret += b;
    x = x >> b;

    // 接下来判断 [2, 4) 位
    // 如果 x 的 [2, 4) 位存在 1，b == 2，否则，b == 0
    b = !!(x >> 2) << 1;
    // 如果 x 的 [4, 8) 位存在 1
    //    则 [0, 2) 位是必须的，只要判断 [2, 4) 位即可，
    //    将 x 右移 2 位
    ret += b;
    x = x >> b;

    // 接下来判断 [1, 2) 位
    // 如果 x 的 [1, 2) 位存在 1，b == 1，否则，b == 0
    b = !!(x >> 1) << 0;
    // 如果 x 的 [1, 2) 位存在 1
    //    则 [0, 1) 位是必须的，只要判断 [1, 2) 位即可，
    //    将 x 右移 1 位
    ret += b;
    x = x >> b;

    // 接下来判断 [0, 1) 位
    ret += x;

    return ret + 1;  // 加上符号位
}
// float
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
    int sign;
    int exp;

    // 获取符号位
    sign = uf & (1 << 31);

    // 阶码部分
    exp = (uf & 0x7f800000) >> 23;

    // 阶码为 0，表示非规格化的值，即，尾码不包含前置的 1
    // 尾码直接左移一位表示乘以 2，然后，加上 符号位即可
    if (exp == 0) return uf << 1 | sign;

    // 阶码为 255，表示 无穷小 或 无群大  或 NaN
    if (exp == 255) return uf;

    exp++;
    if (exp == 255) return 0x7f800000 | sign;  // 无穷小 或 无穷大
    return (exp << 23) | (uf & 0x807fffff);
}
/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
    int exp;
    int frac;

    // 获取 阶码
    exp = ((uf & 0x7f800000) >> 23) - 127;

    // int 的最大值为 0x7FFFF FFFF
    // 即：2 的 31 次 - 1
    // int 的最小值为 0x80000 0000
    // 即：- 2 的 31 次
    // 如果 阶数 大于 31 肯定溢出
    if (exp > 31) return 0x80000000;

    // 如果 阶数 小于 0 ，结果是小数
    if (exp < 0) return 0;

    // 活得尾数，并加上省略前置的 1
    frac = (uf & 0x007fffff) | 0x00800000;

    // 阶数大于 23，需要将尾数左移
    if (exp > 23) frac <<= (exp - 23);
    // 阶数小于 23，需要将尾数右移
    else
        frac >>= (23 - exp);

    // frac uf 的最到位都为 0
    if (frac >= 0 && uf < 0x80000000) return frac;
    // frac 的最到位为 0，uf 最高位为 1
    else if (frac >= 0 && uf >= 0x80000000)
        return -frac;
    else
        // frac 的最高位为 1，frac 不足以存储 uf，溢出
        return 0x80000000;
}
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    int exp = x + 127;

    // 阶码必须大于等于 0
    // 如果 exp == 0，尾码没有前置的 1，所以结果也为 0
    if (exp <= 0) return 0;

    // 阶码必须小于等于 255
    // 如果 exp == 255，表示 无穷大 无穷小 或 NaN，所以结果也为 0xff << 23
    // 即：符号位为 0，阶码的位都为 1，尾码的位都为 0
    if (exp >= 255) return 0xff << 23;

    // 符号位为 0，尾码为 0
    return exp << 23;
}
