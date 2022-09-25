/*
 * [40] Combination Sum II
 *
 * https://leetcode.com/problems/combination-sum-ii/description/
 *
 * algorithms
 * Medium (35.04%)
 * Total Accepted:    136.8K
 * Total Submissions: 390.3K
 * Testcase Example:  '[10,1,2,7,6,1,5]\n8'
 *
 *
 * Given a collection of candidate numbers (C) and a target number (T), find
 * all unique combinations in C where the candidate numbers sums to T.
 *
 *
 * Each number in C may only be used once in the combination.
 *
 * Note:
 *
 * All numbers (including target) will be positive integers.
 * The solution set must not contain duplicate combinations.
 *
 *
 *
 *
 * For example, given candidate set [10, 1, 2, 7, 6, 1, 5] and target 8,
 * A solution set is:
 *
 * [
 * ⁠ [1, 7],
 * ⁠ [1, 2, 5],
 * ⁠ [2, 6],
 * ⁠ [1, 1, 6]
 * ]
 *
 *
 */
class Solution {
   public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
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
        for (int i = k; i < candidates.size() && target >= candidates[i]; ++i)
            if (i == k || candidates[i] != candidates[i - 1]) {
                temp.push_back(candidates[i]);
                backtrack(candidates, i + 1, target - candidates[i], temp,
                          result);
                temp.pop_back();
            }
    }
};
