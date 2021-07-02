/*
 * [135] Candy
 *
 * https://leetcode.com/problems/candy/description/
 *
 * algorithms
 * Hard (25.04%)
 * Total Accepted:    74.8K
 * Total Submissions: 298.5K
 * Testcase Example:  '[0]'
 *
 * 
 * There are N children standing in a line. Each child is assigned a rating
 * value. 
 * 
 * 
 * You are giving candies to these children subjected to the following
 * requirements:
 * 
 * 
 * Each child must have at least one candy.
 * Children with a higher rating get more candies than their neighbors.
 * 
 * 
 * What is the minimum candies you must give?
 * 
 */
int candy(int* ratings, int ratingsSize) {
    if (ratingsSize <= 0)
        return 0;
    int* f = (int*)malloc(sizeof(int)*ratingsSize);
    f[0] = 1;
    for (int i = 1; i < ratingsSize; ++i)
        if (ratings[i] > ratings[i-1])
            f[i] = f[i-1] + 1;
        else
            f[i] = 1;
    for (int i = ratingsSize - 2; i >= 0; --i)
        if (ratings[i] > ratings[i+1] && f[i] <= f[i+1])
            f[i] = f[i+1] + 1;
    int result = 0;
    for (int i = 0; i < ratingsSize; ++i)
        result += f[i];
    return result;
}
