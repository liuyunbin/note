/*
 * [90] Subsets II
 *
 * https://leetcode.com/problems/subsets-ii/description/
 *
 * algorithms
 * Medium (37.44%)
 * Total Accepted:    132.6K
 * Total Submissions: 353.9K
 * Testcase Example:  '[1,2,2]'
 *
 *
 * Given a collection of integers that might contain duplicates, nums, return
 * all possible subsets (the power set).
 *
 * Note: The solution set must not contain duplicate subsets.
 *
 *
 * For example,
 * If nums = [1,2,2], a solution is:
 *
 *
 *
 * [
 * ⁠ [2],
 * ⁠ [1],
 * ⁠ [1,2,2],
 * ⁠ [2,2],
 * ⁠ [1,2],
 * ⁠ []
 * ]
 *
 */
class Solution {
   public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> result;
        if (nums.size() == 0) return result;
        sort(nums.begin(), nums.end());
        vector<int> temp;
        backtrack(nums, 0, temp, result);
        return result;
    }

    void backtrack(vector<int>& nums, int k, vector<int>& temp,
                   vector<vector<int>>& result) {
        result.push_back(temp);
        for (int i = k; i < nums.size(); ++i)
            if (i == k || nums[i] != nums[i - 1]) {
                temp.push_back(nums[i]);
                backtrack(nums, i + 1, temp, result);
                temp.pop_back();
            }
    }
};
