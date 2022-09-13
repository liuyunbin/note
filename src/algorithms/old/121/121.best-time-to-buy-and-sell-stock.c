/*
 * [121] Best Time to Buy and Sell Stock
 *
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/
 *
 * algorithms
 * Easy (42.25%)
 * Total Accepted:    250.3K
 * Total Submissions: 592.2K
 * Testcase Example:  '[7,1,5,3,6,4]'
 *
 * Say you have an array for which the ith element is the price of a given
 * stock on day i.
 * 
 * If you were only permitted to complete at most one transaction (ie, buy one
 * and sell one share of the stock), design an algorithm to find the maximum
 * profit.
 * 
 * Example 1:
 * 
 * Input: [7, 1, 5, 3, 6, 4]
 * Output: 5
 * 
 * max. difference = 6-1 = 5 (not 7-1 = 6, as selling price needs to be larger
 * than buying price)
 * 
 * 
 * 
 * Example 2:
 * 
 * Input: [7, 6, 4, 3, 1]
 * Output: 0
 * 
 * In this case, no transaction is done, i.e. max profit = 0.
 * 
 * 
 */

int max(int x, int y) {
    return x > y ? x : y;
}

int min(int x, int y) {
    return x > y ? y : x;
}

int maxProfit(int* prices, int pricesSize) {
    if (pricesSize <= 0)
        return 0;
    int current_max = 0;
    int current_min = prices[0];
    for (int i = 1; i < pricesSize; ++i) {
        current_min = min(current_min, prices[i]);
        current_max = max(current_max, prices[i] - current_min);
    }
    return current_max;
}
