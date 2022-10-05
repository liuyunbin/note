
#ifndef HUGR_NUMBER_HUGE_NUMBER_H_
#define HUGR_NUMBER_HUGE_NUMBER_H_

/*
 * 本程序主要处理大数的加减乘除
 *
 * 对于本程序的所有数字字符串参数都将忽略掉前置的空白字符
 *
 * 参数数字字符串分为三类：
 * * 零（"0"，"+0"，"-0"）
 * * 正数（"+123"，"123"），数字不能以 0 打头
 * * 负数（"-123"），数字不能以 0 打头
 *
 * 如果字符串不合法，将直接退出
 *
 * 如果字符串除数为 0，将直接退出
 *
 * 返回的数字字符串只有三种类型：
 * * 零（"0"）
 * * 正数（"123"）
 * * 负数（"-123"）
 */

#include <string>

/*
 * 检查字符串是否合法，如果不合法，将直接退出
 * 然后，将其格式化，即：去掉前置空白字符和 +
 */
std::string check_digit_string_is_valid_and_format(const std::string &str);

/*
 * 比较两个数字字符串的大小
 *   * 如果左数字字符串 小于 右数字字符串，返回 -1
 *   * 如果左数字字符串 等于 右数字字符串，返回  0
 *   * 如果左数字字符串 大于 右数字字符串，返回  1
 */
int compare_huge_number(const std::string &lhs, const std::string &rhs);

/*
 * 两个数字字符串相加
 */
std::string add_huge_number(const std::string &lhs, const std::string &rhs);

/*
 * 两个数字字符串相减
 * 必须处理可能存在的前置 0，例如 111 - 110 应该等于 1，而不是 001
 */
std::string sub_huge_number(const std::string &lhs, const std::string &rhs);

/*
 * 两个数字字符串相乘
 */
std::string mul_huge_number(const std::string &lhs, const std::string &rhs);

/*
 * 两个数字字符串相除，本函数结果只包含整数部分
 * 如果除数为 0，将退出
 */
std::string div_huge_number(const std::string &lhs, const std::string &rhs);

#endif

//简介：
//  本程序主要处理大数的加减乘除
//
//函数参数说明：
//  对于本程序的所有数字字符串参数都将忽略掉前置的空白字符
//
//参数数字字符串分为三类：
//  * 零（"0"，"+0"，"-0"）
//  * 正数（"+123"，"123"），数字不能以 0 打头
//  * 负数（"-123"），数字不能以 0 打头
//
//如果字符串不合法，将直接退出
//
//函数返回值说明：
//  返回的数字字符串只有三种类型：
//    * 零（"0"）
//    * 正数（"123"），数字不会以 0 打头
//    * 负数（"-123"），数字不会以 0 打头
//
//函数详细说明：
//
//函数：std::string check_digit_string_is_valid_and_format(const std::string&
//str); 说明：检查数字字符串是否合法，并格式化数字字符串
//        * 如果不合法，将直接退出
//        * 如果合法，将其格式化，即：去掉前置空白字符和 `+`
//
//函数：int compare_huge_number(const std::string& lhs, const std::string& rhs);
//说明：比较两个数字字符串的大小
//        * 如果左数字字符串 小于 右数字字符串，返回 -1
//        * 如果左数字字符串 等于 右数字字符串，返回  0
//        * 如果左数字字符串 大于 右数字字符串，返回  1
//
//函数：std::string add_huge_number(const std::string& lhs, const std::string&
//rhs); 说明：两个数字字符串相加
//
//函数：std::string sub_huge_number(const std::string& lhs, const std::string&
//rhs); 说明：两个数字字符串相减
//        * 必须处理可能存在的前置 0，例如 "111" - "110" 应该等于 "1"，而不是
//        "001"
//
//函数：std::string mul_huge_number(const std::string& lhs, const std::string&
//rhs); 说明：两个数字字符串相乘
//        * 必须处理某一参数为 "0" 的情况，例如 "111" * "0" 应该等于 "0"，而不是
//        "000"
//
//函数：std::string div_huge_number(const std::string& lhs, const std::string&
//rhs); 说明：两个数字字符串相除，结果只包含整数部分
//        * 如果除数为 0，将直接退出
//        * 如果被除数的绝对值小于除数的绝对值，将返回 "0"
//
