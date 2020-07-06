/*
 * [18] 4Sum
 *
 * https://leetcode.com/problems/4sum/description/
 *
 * algorithms
 * Medium (27.25%)
 * Total Accepted:    140.1K
 * Total Submissions: 514K
 * Testcase Example:  '[1,0,-1,0,-2,2]\n0'
 *
 * Given an array S of n integers, are there elements a, b, c, and d in S such
 * that a + b + c + d = target? Find all unique quadruplets in the array which
 * gives the sum of target.
 * 
 * Note: The solution set must not contain duplicate quadruplets.
 * 
 * 
 * 
 * For example, given array S = [1, 0, -1, 0, -2, 2], and target = 0.
 * 
 * A solution set is:
 * [
 * ⁠ [-1,  0, 0, 1],
 * ⁠ [-2, -1, 1, 2],
 * ⁠ [-2,  0, 0, 2]
 * ]
 * 
 */
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        for (int i = 0; i < nums.size(); ++i) {
            if (i > 0 && nums[i] == nums[i-1])
                continue;
            for (int j = i + 1; j < nums.size(); ++j) {
                if (j > i + 1 && nums[j] == nums[j-1])
                    continue;
                int left  = j + 1;
                int right = nums.size() - 1;
                while (left < right) {
                    int temp = nums[i] + nums[j] + nums[left] + nums[right];
                    if (temp < target)
                        ++left;
                    else if (temp > target)
                        --right;
                    else {
                        vector<int> tmp;
                        tmp.push_back(nums[i]);
                        tmp.push_back(nums[j]);
                        tmp.push_back(nums[left]);
                        tmp.push_back(nums[right]);
                        result.push_back(tmp);
                        ++left;
                        --right;
                        while (left < right && nums[left]  == nums[left-1])
                            ++left;
                        while (left < right && nums[right] == nums[right+1])
                            --right;
                    }
                }
            }
        }
        return result;
    }
};
