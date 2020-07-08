
#include "tiny-huge-number-calculator.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

int compare(const std::string& left, const std::string& right) {
  if (left.size() < right.size()) return -1;
  if (left.size() > right.size()) return 1;
  if (left < right) return -1;
  if (left > right) return 1;
  return 0;
}

std::string add(const std::string& left, const std::string& right) {
  std::string result;

  auto left_it = left.crbegin();
  auto right_it = right.crbegin();

  int next = 0;

  while (left_it != left.crend() || right_it != right.crend()) {
    if (left_it != left.crend()) next += *left_it++ - '0';
    if (right_it != right.crend()) next += *right_it++ - '0';
    result.push_back('0' + next % 10);
    next /= 10;
  }
  if (next == 1) result.push_back('1');
  std::reverse(std::begin(result), std::end(result));
  return result;
}

std::string sub(const std::string& left, const std::string& right) {
  if (left == right) return "0";
  if (compare(left, right) == -1) return "-" + sub(right, left);

  std::string result;

  auto left_it = left.crbegin();
  auto right_it = right.crbegin();

  int prev = 0;

  while (left_it != left.crend() || right_it != right.crend()) {
    if (left_it != left.crend()) prev += *left_it++ - '0';
    if (right_it != right.crend()) prev -= *right_it++ - '0';
    if (prev < 0) {
      result.push_back(prev + 10 + '0');
      prev = -1;
    } else {
      result.push_back(prev + '0');
      prev = 0;
    }
  }
  std::reverse(std::begin(result), std::end(result));
  auto index = result.find_first_not_of('0');
  if (index == std::string::npos) return "0";
  return result.substr(index);
}

std::string add_huge_numbers(const std::string& left,
                             const std::string& right) {
  if (left[0] == '-' && right[0] == '-')
    return '-' + add(left.substr(1), right.substr(1));
  if (left[0] == '-' && right[0] == '+')
    return sub(right.substr(1), left.substr(1));
  if (left[0] == '+' && right[0] == '-')
    return sub(left.substr(1), right.substr(1));
  if (left[0] == '+' && right[0] == '+')
    return add(left.substr(1), right.substr(1));

  if (left[0] == '+') return add(left.substr(1), right);
  if (left[0] == '-') return sub(right, left.substr(1));
  if (right[0] == '+') return add(left, right.substr(1));
  if (right[0] == '-') return sub(left, right.substr(1));

  return add(left, right);
}

std::string sub_huge_numbers(const std::string& left,
                             const std::string& right) {
  if (right[0] == '-') return add_huge_numbers(left, right.substr(1));
  if (right[0] == '+') return add_huge_numbers(left, "-" + right.substr(1));
  return add_huge_numbers(left, "-" + right);
}

std::string mul_huge_numbers(const std::string& left,
                             const std::string& right) {
  if (left == "0" || right == "0") return "0";
  if ((left[0] == '-' && right[0] == '-') ||
      (left[0] == '+' && right[0] == '+'))
    return mul_huge_numbers(left.substr(1), right.substr(1));
  if ((left[0] == '-' && right[0] == '+') ||
      (left[0] == '+' && right[0] == '-'))
    return "-" + mul_huge_numbers(left.substr(1), right.substr(1));
  if (left[0] == '-') return "-" + mul_huge_numbers(left.substr(1), right);
  if (left[0] == '+') return mul_huge_numbers(left.substr(1), right);
  if (right[0] == '-') return "-" + mul_huge_numbers(left, right.substr(1));
  if (right[0] == '+') return mul_huge_numbers(left, right.substr(1));

  std::string result(left.size() + right.size(), '0');

  int k = 0;
  for (auto it = left.crbegin(); it != left.crend(); ++it) {
    int temp = 0;
    int i = k++;
    for (int j = right.size() - 1; j >= 0; --j, ++i) {
      temp += (*it - '0') * (right[j] - '0') + result[i] - '0';
      result[i] = '0' + temp % 10;
      temp /= 10;
    }
    if (temp != 0) result[i] = result[i] - '0' + temp + '0';
  }
  std::reverse(std::begin(result), std::end(result));
  auto index = result.find_first_not_of('0');
  if (index == std::string::npos) return "0";
  return result.substr(index);
}

std::string div_huge_numbers(const std::string& left,
                             const std::string& right) {
  if (left == "0" || right == "0") return "0";
  if ((left[0] == '-' && right[0] == '-') ||
      (left[0] == '+' && right[0] == '+'))
    return div_huge_numbers(left.substr(1), right.substr(1));
  if ((left[0] == '-' && right[0] == '+') ||
      (left[0] == '+' && right[0] == '-')) {
    auto result = div_huge_numbers(left.substr(1), right.substr(1));
    return result == "0" ? "0" : ("-" + result);
  }
  if (left[0] == '-') {
    auto result = div_huge_numbers(left.substr(1), right);
    return result == "0" ? "0" : ("-" + result);
  }
  if (left[0] == '+') return div_huge_numbers(left.substr(1), right);
  if (right[0] == '-') {
    auto result = div_huge_numbers(left, right.substr(1));
    return result == "0" ? "0" : ("-" + result);
  }
  if (right[0] == '+') return div_huge_numbers(left, right.substr(1));

  if (left == right) return "1";
  if (compare(left, right) == -1) return "0";

  std::string result;

  std::string current_str = left.substr(0, right.size());
  std::string next_str = left.substr(right.size());

  if (compare(current_str, right) == -1) {
    current_str += next_str[0];
    next_str = next_str.substr(1);
  }

  for (;;) {
    int count = 0;
    for (;;) {
      auto temp = sub(current_str, right);
      if (temp == "0") {
        ++count;
        current_str = "";
        break;
      }
      if (temp[0] == '-') break;
      ++count;
      current_str = temp;
    }
    result.push_back('0' + count % 10);
    if (next_str.empty()) break;
    current_str += next_str[0];
    next_str = next_str.substr(1);
  }

  return result;
}
