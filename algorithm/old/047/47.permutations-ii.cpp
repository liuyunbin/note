/*
 * [47] Permutations II
 *
 * https://leetcode.com/problems/permutations-ii/description/
 *
 * algorithms
 * Medium (34.06%)
 * Total Accepted:    145.2K
 * Total Submissions: 426K
 * Testcase Example:  '[1,1,2]'
 *
 *
 * Given a collection of numbers that might contain duplicates, return all
 * possible unique permutations.
 *
 *
 *
 * For example,
 * [1,1,2] have the following unique permutations:
 *
 * [
 * ⁠ [1,1,2],
 * ⁠ [1,2,1],
 * ⁠ [2,1,1]
 * ]
 *
 *
 */
class Solution {
   public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> result;
        if (nums.size() == 0) return result;
        vector<bool> used(nums.size(), false);
        vector<int> temp;
        sort(nums.begin(), nums.end());
        backtrack(nums, used, temp, result);
        return result;
    }

   private:
    void backtrack(vector<int>& nums, vector<bool>& used, vector<int>& temp,
                   vector<vector<int>>& result) {
        if (temp.size() == nums.size()) {
            result.push_back(temp);
            return;
        }
        for (int i = 0; i < nums.size(); ++i)
            if (used[i] == false &&
                (i == 0 || nums[i] != nums[i - 1] || used[i - 1] == true)) {
                used[i] = true;
                temp.push_back(nums[i]);
                backtrack(nums, used, temp, result);
                temp.pop_back();
                used[i] = false;
            }
    }
};
