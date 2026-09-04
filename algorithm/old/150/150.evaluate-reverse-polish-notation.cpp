/*
 * [150] Evaluate Reverse Polish Notation
 *
 * https://leetcode.com/problems/evaluate-reverse-polish-notation/description/
 *
 * algorithms
 * Medium (27.86%)
 * Total Accepted:    105.6K
 * Total Submissions: 379K
 * Testcase Example:  '["18"]'
 *
 *
 * Evaluate the value of an arithmetic expression in Reverse Polish
 * Notation.
 *
 *
 *
 * Valid operators are +, -, *, /. Each operand may be an integer or another
 * expression.
 *
 *
 *
 * Some examples:
 *
 * ⁠ ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
 * ⁠ ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
 *
 *
 */
class Solution {
   public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for (auto str : tokens)
            if (isdigit(str[0]) || str.size() > 1)
                st.push(stoi(str));
            else {
                int y = st.top();
                st.pop();
                int x = st.top();
                st.pop();
                switch (str[0]) {
                    case '+':
                        st.push(x + y);
                        break;
                    case '-':
                        st.push(x - y);
                        break;
                    case '*':
                        st.push(x * y);
                        break;
                    case '/':
                        st.push(x / y);
                        break;
                }
            }
        return st.top();
    }
};
