/*
 * [122] Best Time to Buy and Sell Stock II
 *
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/description/
 *
 * algorithms
 * Easy (47.77%)
 * Total Accepted:    175.6K
 * Total Submissions: 367.4K
 * Testcase Example:  '[]'
 *
 * Say you have an array for which the ith element is the price of a given
 * stock on day i.
 *
 * Design an algorithm to find the maximum profit. You may complete as many
 * transactions as you like (ie, buy one and sell one share of the stock
 * multiple times). However, you may not engage in multiple transactions at the
 * same time (ie, you must sell the stock before you buy again).
 */

int max(int x, int y) { return x > y ? x : y; }

int maxProfit(int* prices, int pricesSize) {
    int result = 0;
    for (int i = 1; i < pricesSize; ++i)
        result += max(0, prices[i] - prices[i - 1]);
    return result;
}
