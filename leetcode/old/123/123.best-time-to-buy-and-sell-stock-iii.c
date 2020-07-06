/*
 * [123] Best Time to Buy and Sell Stock III
 *
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/description/
 *
 * algorithms
 * Hard (29.98%)
 * Total Accepted:    99.3K
 * Total Submissions: 331.1K
 * Testcase Example:  '[]'
 *
 * Say you have an array for which the ith element is the price of a given
 * stock on day i.
 * 
 * Design an algorithm to find the maximum profit. You may complete at most two
 * transactions.
 * 
 * Note:
 * You may not engage in multiple transactions at the same time (ie, you must
 * sell the stock before you buy again).
 */

int max(int x, int y) {
    return x > y ? x : y;
}

int maxProfit(int* prices, int pricesSize) {
    for (int i = 0; i + 1 < pricesSize; ++i)
        prices[i] = prices[i+1] - prices[i];
    int     must[2] = {0, 0};
    int not_must[2] = {0, 0};
    for (int i = 0; i + 1 < pricesSize; ++i) {
            must[1] = max(must[1], not_must[0]) + prices[i]; 
        not_must[1] = max(not_must[1], must[1]);
            must[0] = max(must[0], 0) + prices[i];
        not_must[0] = max(not_must[0], must[0]);
    }
    return max(not_must[0], not_must[1]);
}
