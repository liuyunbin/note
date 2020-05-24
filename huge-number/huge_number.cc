
#include "huge_number.h"

#include <ctype.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

std::string check_digit_string_is_valid_and_format(const std::string &str) {

  std::size_t index = 0;
  while (index != str.size() && isspace(str[index]))
    ++index;

  std::string result = str.substr(index);

  if (result == "0" || result == "+0" || result == "-0")
    return "0";

  if (result[0] == '-') {
    if (result[1] == '0' || result[1] == '\0')
      goto err;

    for (index = 1; index != result.size(); ++index)
      if (!isdigit(result[index]))
        goto err;
  } else {
    if (result[0] == '+')
      result = result.substr(1);

    if (result[0] == '0' || result[0] == '\0')
      goto err;

    for (index = 0; index != result.size(); ++index)
      if (!isdigit(result[index]))
        goto err;
  }

  return result;

err:
  printf("数字字符串只支持三种形式：\n");
  printf("* 零：\"0\"，\"+0\"，\"-0\" \n");
  printf("* 正数：\"123\"，\"+123\"，其中数字不能以 0 打头 \n");
  printf("* 负数：\"-123\"，其中数字不能以 0 打头 \n");
  exit(EXIT_FAILURE);
}

int compare_huge_number(const std::string &lhs, const std::string &rhs) {
  std::string lhs_string = check_digit_string_is_valid_and_format(lhs);
  std::string rhs_string = check_digit_string_is_valid_and_format(rhs);

  if (lhs_string[0] == '-' && rhs_string[0] == '-')
    return compare_huge_number(rhs_string.substr(1), lhs_string.substr(1));

  if (lhs_string[0] == '-')
    return -1;
  if (rhs_string[0] == '-')
    return 1;

  if (lhs_string.size() < rhs_string.size())
    return -1;
  if (lhs_string.size() > rhs_string.size())
    return 1;

  if (lhs_string < rhs_string)
    return -1;
  if (lhs_string > rhs_string)
    return 1;

  return 0;
}

std::string add_huge_number(const std::string &lhs, const std::string &rhs) {
  std::string lhs_string = check_digit_string_is_valid_and_format(lhs);
  std::string rhs_string = check_digit_string_is_valid_and_format(rhs);

  if (lhs_string == "0")
    return rhs_string;
  if (rhs_string == "0")
    return lhs_string;

  if (lhs_string[0] == '-')
    return sub_huge_number(rhs_string, lhs_string.substr(1));
  if (rhs_string[0] == '-')
    return sub_huge_number(lhs_string, rhs_string.substr(1));

  auto lhs_string_it = lhs_string.crbegin();
  auto rhs_string_it = rhs_string.crbegin();

  int last = 0;
  std::string result;

  while (lhs_string_it != lhs_string.crend() ||
         rhs_string_it != rhs_string.crend()) {
    if (lhs_string_it != lhs_string.crend())
      last += *lhs_string_it++ - '0';
    if (rhs_string_it != rhs_string.crend())
      last += *rhs_string_it++ - '0';
    result.push_back('0' + last % 10);
    last /= 10;
  }
  if (last == 1)
    result.push_back('1');
  std::reverse(std::begin(result), std::end(result));
  return result;
}

std::string sub_huge_number(const std::string &lhs, const std::string &rhs) {
  std::string lhs_string = check_digit_string_is_valid_and_format(lhs);
  std::string rhs_string = check_digit_string_is_valid_and_format(rhs);

  if (lhs_string == rhs_string)
    return "0";

  if (rhs_string == "0")
    return lhs_string;

  if (lhs_string == "0") {
    if (rhs_string[0] == '-')
      return rhs_string.substr(1);
    else
      return "-" + rhs_string;
  }

  if (lhs_string[0] == '-') {
    std::string result = add_huge_number(lhs_string.substr(1), rhs_string);
    if (result[0] == '-')
      return result.substr(1);
    else
      return '-' + result;
  }

  if (rhs_string[0] == '-')
    return add_huge_number(lhs_string, rhs_string.substr(1));

  if (compare_huge_number(lhs_string, rhs_string) == -1)
    return "-" + sub_huge_number(rhs_string, lhs_string);

  std::string result;

  auto lhs_string_it = lhs_string.crbegin();
  auto rhs_string_it = rhs_string.crbegin();

  int prev = 0;

  while (lhs_string_it != lhs_string.crend() ||
         rhs_string_it != rhs_string.crend()) {
    if (lhs_string_it != lhs_string.crend())
      prev += *lhs_string_it++ - '0';
    if (rhs_string_it != rhs_string.crend())
      prev -= *rhs_string_it++ - '0';
    if (prev < 0) {
      result.push_back(prev + 10 + '0');
      prev = -1;
    } else {
      result.push_back(prev + '0');
      prev = 0;
    }
  }
  std::reverse(std::begin(result), std::end(result));
  auto index = result.find_first_not_of('0'); // 去除可能存在的前置 0
  return result.substr(index);
}

std::string mul_huge_number(const std::string &lhs, const std::string &rhs) {
  std::string lhs_string = check_digit_string_is_valid_and_format(lhs);
  std::string rhs_string = check_digit_string_is_valid_and_format(rhs);

  if (lhs_string == "0" || rhs_string == "0")
    return "0";

  if (lhs_string[0] == '-' && rhs_string[0] == '-')
    return mul_huge_number(lhs_string.substr(1), rhs_string.substr(1));

  if (lhs_string[0] == '-')
    return "-" + mul_huge_number(lhs_string.substr(1), rhs_string);

  if (rhs_string[0] == '-')
    return "-" + mul_huge_number(lhs_string, rhs_string.substr(1));

  // 对于 m 位无符号的数 乘以 n 位无符号的数，
  // 结果至少有 m + n - 1 位，最多有 m + n 位
  std::string result(lhs_string.size() + rhs_string.size(), '0');

  std::size_t begin_index = 0;
  std::size_t i = lhs_string.size();
  while (i > 0) {
    --i;
    int last = 0;
    int k = begin_index++;
    int j = rhs_string.size();
    while (j > 0) {
      --j;
      last += (lhs_string[i] - '0') * (rhs_string[j] - '0') + result[k] - '0';
      result[k++] = '0' + last % 10;
      last /= 10;
    }
    if (last != 0)
      result[k] = result[k] - '0' + last + '0';
  }
  std::reverse(std::begin(result), std::end(result));
  if (result[0] == '0') // 去掉多余的 0
    return result.substr(1);
  else
    return result;
}

std::string div_huge_number(const std::string &lhs, const std::string &rhs) {
  std::string lhs_string = check_digit_string_is_valid_and_format(lhs);
  std::string rhs_string = check_digit_string_is_valid_and_format(rhs);

  if (rhs_string == "0") {
    printf("除数不能为 0\n");
    exit(EXIT_FAILURE);
  }

  if (lhs_string == "0")
    return "0";

  if (lhs_string == rhs_string)
    return "1";

  if (lhs_string[0] == '-' && rhs_string[0] == '-')
    return div_huge_number(lhs_string.substr(1), rhs_string.substr(1));

  if (lhs_string[0] == '-') {
    std::string result = div_huge_number(lhs_string.substr(1), rhs_string);
    return result == "0" ? "0" : ("-" + result);
  }

  if (rhs_string[0] == '-') {
    std::string result = div_huge_number(lhs_string, rhs_string.substr(1));
    return result == "0" ? "0" : ("-" + result);
  }

  if (compare_huge_number(lhs_string, rhs_string) == -1)
    return "0";

  std::string result;

  std::string current_str = lhs_string.substr(0, rhs_string.size());
  std::string last_str = lhs_string.substr(rhs_string.size());

  if (compare_huge_number(current_str, rhs_string) == -1) {
    current_str += last_str[0];
    last_str = last_str.substr(1);
  }

  for (;;) {
    int count = 0;
    for (;;) {
      std::string temp = sub_huge_number(current_str, rhs_string);
      if (temp == "0") {
        ++count;
        current_str = "";
        break;
      }
      if (temp[0] == '-')
        break;
      ++count;
      current_str = temp;
    }
    result.push_back('0' + count);

    if (last_str.empty())
      break;

    current_str += last_str[0];
    last_str = last_str.substr(1);
  }

  return result;
}

