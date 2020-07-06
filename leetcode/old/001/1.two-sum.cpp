/*
 * [1] Two Sum
 *
 * https://leetcode.com/problems/two-sum/description/
 *
 * algorithms
 * Easy (36.53%)
 * Total Accepted:    736.4K
 * Total Submissions: 2M
 * Testcase Example:  '[3,2,4]\n6'
 *
 * Given an array of integers, return indices of the two numbers such that they
 * add up to a specific target.
 * 
 * You may assume that each input would have exactly one solution, and you may
 * not use the same element twice.
 * 
 * 
 * Example:
 * 
 * Given nums = [2, 7, 11, 15], target = 9,
 * 
 * Because nums[0] + nums[1] = 2 + 7 = 9,
 * return [0, 1].
 * 
 * 
 */
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        unordered_map<int, int> my_map;
        for (int i = 0; i < nums.size(); ++i) {
            int number_to_find = target - nums[i];
            if (my_map.find(number_to_find) != my_map.end()) {
                result.push_back(my_map[number_to_find]);
                result.push_back(i);
                break;
            }
            my_map[nums[i]] = i;
        }
        return result; 
    }
};
