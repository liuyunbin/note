/*
 * [78] Subsets
 *
 * https://leetcode.com/problems/subsets/description/
 *
 * algorithms
 * Medium (43.00%)
 * Total Accepted:    204.5K
 * Total Submissions: 475.3K
 * Testcase Example:  '[1,2,3]'
 *
 *
 * Given a set of distinct integers, nums, return all possible subsets (the
 * power set).
 *
 * Note: The solution set must not contain duplicate subsets.
 *
 *
 * For example,
 * If nums = [1,2,3], a solution is:
 *
 *
 *
 * [
 * ⁠ [3],
 * ⁠ [1],
 * ⁠ [2],
 * ⁠ [1,2,3],
 * ⁠ [1,3],
 * ⁠ [2,3],
 * ⁠ [1,2],
 * ⁠ []
 * ]
 *
 */
class Solution {
   public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        if (nums.size() == 0) return result;
        vector<int> temp;
        backtrack(nums, 0, temp, result);
        return result;
    }

    void backtrack(vector<int>& nums, int k, vector<int>& temp,
                   vector<vector<int>>& result) {
        result.push_back(temp);
        for (int i = k; i < nums.size(); ++i) {
            temp.push_back(nums[i]);
            backtrack(nums, i + 1, temp, result);
            temp.pop_back();
        }
    }
};
