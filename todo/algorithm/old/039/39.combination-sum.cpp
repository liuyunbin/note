/*
 * [39] Combination Sum
 *
 * https://leetcode.com/problems/combination-sum/description/
 *
 * algorithms
 * Medium (40.23%)
 * Total Accepted:    193.5K
 * Total Submissions: 480.9K
 * Testcase Example:  '[2,3,6,7]\n7'
 *
 *
 * Given a set of candidate numbers (C) (without duplicates) and a target
 * number (T), find all unique combinations in C where the candidate numbers
 * sums to T.
 *
 *
 * The same repeated number may be chosen from C unlimited number of times.
 *
 *
 * Note:
 *
 * All numbers (including target) will be positive integers.
 * The solution set must not contain duplicate combinations.
 *
 *
 *
 *
 * For example, given candidate set [2, 3, 6, 7] and target 7,
 * A solution set is:
 *
 * [
 * ⁠ [7],
 * ⁠ [2, 2, 3]
 * ]
 *
 *
 */
class Solution {
   public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> temp;
        backtrack(candidates, 0, target, temp, result);
        return result;
    }

   private:
    void backtrack(vector<int>& candidates, int k, int target,
                   vector<int>& temp, vector<vector<int>>& result) {
        if (target == 0) {
            result.push_back(temp);
            return;
        }
        for (int i = k; i < candidates.size(); ++i)
            if (target >= candidates[i]) {
                temp.push_back(candidates[i]);
                backtrack(candidates, i, target - candidates[i], temp, result);
                temp.pop_back();
            }
    }
};
