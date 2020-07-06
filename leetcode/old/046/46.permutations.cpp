/*
 * [46] Permutations
 *
 * https://leetcode.com/problems/permutations/description/
 *
 * algorithms
 * Medium (45.72%)
 * Total Accepted:    205.4K
 * Total Submissions: 449.2K
 * Testcase Example:  '[1,2,3]'
 *
 * 
 * Given a collection of distinct numbers, return all possible permutations.
 * 
 * 
 * 
 * For example,
 * [1,2,3] have the following permutations:
 * 
 * [
 * ⁠ [1,2,3],
 * ⁠ [1,3,2],
 * ⁠ [2,1,3],
 * ⁠ [2,3,1],
 * ⁠ [3,1,2],
 * ⁠ [3,2,1]
 * ]
 * 
 * 
 */
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        if (nums.size() == 0)
            return result;
        backtrack(nums, 0, result);
        return result;
    }

private:
    void backtrack(vector<int>& nums, int k, vector<vector<int>>& result) {
        if (k == nums.size()) {
            result.push_back(nums);
            return ;
        }
        backtrack(nums, k + 1, result);
        for (int i = k + 1; i < nums.size(); ++i) {
            swap(nums[i], nums[k]);
            backtrack(nums, k + 1, result);
            swap(nums[i], nums[k]);
        }
    }
};
