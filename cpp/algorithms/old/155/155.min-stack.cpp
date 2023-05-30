/*
 * [155] Min Stack
 *
 * https://leetcode.com/problems/min-stack/description/
 *
 * algorithms
 * Easy (30.04%)
 * Total Accepted:    162.6K
 * Total Submissions: 540.4K
 * Testcase Example:
 * '["MinStack","push","push","push","getMin","pop","top","getMin"]\n[[],[-2],[0],[-3],[],[],[],[]]'
 *
 *
 * Design a stack that supports push, pop, top, and retrieving the minimum
 * element in constant time.
 *
 *
 * push(x) -- Push element x onto stack.
 *
 *
 * pop() -- Removes the element on top of the stack.
 *
 *
 * top() -- Get the top element.
 *
 *
 * getMin() -- Retrieve the minimum element in the stack.
 *
 *
 *
 *
 * Example:
 *
 * MinStack minStack = new MinStack();
 * minStack.push(-2);
 * minStack.push(0);
 * minStack.push(-3);
 * minStack.getMin();   --> Returns -3.
 * minStack.pop();
 * minStack.top();      --> Returns 0.
 * minStack.getMin();   --> Returns -2.
 *
 *
 */
class MinStack {
   public:
    /** initialize your data structure here. */
    stack<int> data;
    stack<int> min_data;

    MinStack() {}

    void push(int x) {
        data.push(x);
        if (min_data.empty() || min_data.top() >= x) min_data.push(x);
    }

    void pop() {
        if (data.top() == min_data.top()) min_data.pop();
        data.pop();
    }

    int top() { return data.top(); }

    int getMin() { return min_data.top(); }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */
