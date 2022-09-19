/*
 * [66] Plus One
 *
 * https://leetcode.com/problems/plus-one/description/
 *
 * algorithms
 * Easy (39.19%)
 * Total Accepted:    206.9K
 * Total Submissions: 527.7K
 * Testcase Example:  '[0]'
 *
 * Given a non-negative integer represented as a non-empty array of digits,
 * plus one to the integer.
 * 
 * You may assume the integer do not contain any leading zero, except the
 * number 0 itself.
 * 
 * The digits are stored such that the most significant digit is at the head of
 * the list.
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* plusOne(int* digits, int digitsSize, int* returnSize) {
    int* result = (int*)malloc(sizeof(int)*(digitsSize+1));
    *returnSize = 0;
    int count = 1;
    for (int i = digitsSize - 1; i >= 0; --i) {
        count += digits[i];
        result[(*returnSize)++] = count % 10;
        count /= 10;
    }
    if (count != 0)
        result[(*returnSize)++] = 1;
    int  left = 0;
    int right = *returnSize - 1;
    while (left < right) {
        int      temp = result[left];
        result[left]  = result[right];
        result[right] = temp;
        ++left;
        --right;
    }
    return result;
}
