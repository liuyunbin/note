/*
 * [56] Merge Intervals
 *
 * https://leetcode.com/problems/merge-intervals/description/
 *
 * algorithms
 * Medium (31.24%)
 * Total Accepted:    168.5K
 * Total Submissions: 539K
 * Testcase Example:  '[[1,3],[2,6],[8,10],[15,18]]'
 *
 * Given a collection of intervals, merge all overlapping intervals.
 *
 *
 * For example,
 * Given [1,3],[2,6],[8,10],[15,18],
 * return [1,6],[8,10],[15,18].
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

int compare(const void* x, const void* y) {
    return ((const struct Interval*)x)->start -
           ((const struct Interval*)y)->start;
}

struct Interval* merge(struct Interval* intervals, int intervalsSize,
                       int* returnSize) {
    if (intervalsSize <= 0) {
        *returnSize = 0;
        return NULL;
    }
    qsort(intervals, intervalsSize, sizeof(struct Interval), compare);
    struct Interval* result =
        (struct Interval*)malloc(sizeof(struct Interval) * intervalsSize);
    *returnSize = 0;
    for (int i = 0; i < intervalsSize;) {
        result[*returnSize].start = intervals[i].start;
        result[*returnSize].end = intervals[i].end;
        ++i;
        while (i < intervalsSize &&
               intervals[i].start <= result[*returnSize].end) {
            if (intervals[i].end > result[*returnSize].end)
                result[*returnSize].end = intervals[i].end;
            ++i;
        }
        ++*returnSize;
    }
    return result;
}
