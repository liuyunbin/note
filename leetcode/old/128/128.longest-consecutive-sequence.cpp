/*
 * [128] Longest Consecutive Sequence
 *
 * https://leetcode.com/problems/longest-consecutive-sequence/description/
 *
 * algorithms
 * Hard (37.71%)
 * Total Accepted:    126.1K
 * Total Submissions: 334.1K
 * Testcase Example:  '[100,4,200,1,3,2]'
 *
 * 
 * Given an unsorted array of integers, find the length of the longest
 * consecutive elements sequence.
 * 
 * 
 * For example,
 * Given [100, 4, 200, 1, 3, 2],
 * The longest consecutive elements sequence is [1, 2, 3, 4]. Return its
 * length: 4.
 * 
 * 
 * Your algorithm should run in O(n) complexity.
 * 
 */
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int result = 0;
        unordered_map<int, int> my_map;
        for (auto number:nums) 
            if (my_map.find(number) == my_map.end()) {
                int left  = my_map.find(number-1) == my_map.end() ? 0 : my_map[number-1];
                int right = my_map.find(number+1) == my_map.end() ? 0 : my_map[number+1];
                my_map[number] = my_map[number-left] = my_map[number+right] = left + right + 1;
                result = max(result, left + right + 1);
        }
        return result;
    }
};
