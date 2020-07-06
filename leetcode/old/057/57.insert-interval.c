/*
 * [57] Insert Interval
 *
 * https://leetcode.com/problems/insert-interval/description/
 *
 * algorithms
 * Hard (28.49%)
 * Total Accepted:    113.8K
 * Total Submissions: 399.4K
 * Testcase Example:  '[[1,3],[6,9]]\n[2,5]'
 *
 * Given a set of non-overlapping intervals, insert a new interval into the
 * intervals (merge if necessary).
 * 
 * You may assume that the intervals were initially sorted according to their
 * start times.
 * 
 * 
 * Example 1:
 * Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].
 * 
 * 
 * 
 * Example 2:
 * Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as
 * [1,2],[3,10],[12,16].
 * 
 * 
 * 
 * This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
 * 
 */
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct Interval* insert(struct Interval* intervals, int intervalsSize, struct Interval newInterval, int* returnSize) {
    struct Interval* result = (struct Interval*)malloc(sizeof(struct Interval)*(intervalsSize+1));
    memcpy(result, intervals, sizeof(struct Interval)*intervalsSize);
    int i;
    for (i = intervalsSize; i > 0; --i) {
        if (result[i-1].start <= newInterval.start)
            break;
        result[i].start = result[i-1].start;
        result[i].end   = result[i-1].end;
    }
    result[i].start = newInterval.start;
    result[i].end   = newInterval.end;
    *returnSize = 0;
    for (i = 0; i <= intervalsSize; ) {
        result[*returnSize].start = result[i].start;
        result[*returnSize].end   = result[i].end;
        ++i;
        while (i <= intervalsSize && result[i].start <= result[*returnSize].end) {
            if (result[i].end > result[*returnSize].end)
                result[*returnSize].end = result[i].end;
            ++i;
        }
        ++*returnSize;
    }
    return result;
}
