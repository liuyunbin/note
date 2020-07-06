/*
 * [20] Valid Parentheses
 *
 * https://leetcode.com/problems/valid-parentheses/description/
 *
 * algorithms
 * Easy (33.72%)
 * Total Accepted:    276.5K
 * Total Submissions: 819.8K
 * Testcase Example:  '"["'
 *
 * Given a string containing just the characters '(', ')', '{', '}', '[' and
 * ']', determine if the input string is valid.
 * 
 * The brackets must close in the correct order, "()" and "()[]{}" are all
 * valid but "(]" and "([)]" are not.
 * 
 */
class Solution {
public:
    bool isValid(string s) {
        stack<char> my_stack;
        for (int i = 0; i < s.size(); ++i)
            switch (s[i]) {
                case '(':
                case '[':
                case '{': my_stack.push(s[i]); break;
                case ')':
                          if (my_stack.empty() || my_stack.top() != '(')
                              return false;
                          my_stack.pop();
                          break;

                case ']':
                          if (my_stack.empty() || my_stack.top() != '[')
                              return false;
                          my_stack.pop();
                          break;
                case '}':
                          if (my_stack.empty() || my_stack.top() != '{')
                              return false;
                          my_stack.pop();
                          break;
            }
        return my_stack.empty();
    }
};
