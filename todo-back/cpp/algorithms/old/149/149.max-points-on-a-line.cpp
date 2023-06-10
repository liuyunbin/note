/*
 * [149] Max Points on a Line
 *
 * https://leetcode.com/problems/max-points-on-a-line/description/
 *
 * algorithms
 * Hard (15.21%)
 * Total Accepted:    87.5K
 * Total Submissions: 574.9K
 * Testcase Example:  '[]'
 *
 * Given n points on a 2D plane, find the maximum number of points that lie on
 * the same straight line.
 */
/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
   public:
    int maxPoints(vector<Point>& points) {
        int result = 0;
        for (int i = 0; i < points.size(); ++i) {
            map<pair<int, int>, int> my_map;
            int same_count = 1;
            int same_x = 0;
            int same_y = 0;
            int current_max = 0;
            for (int j = i + 1; j < points.size(); ++j) {
                if (points[i].x == points[j].x && points[i].y == points[j].y) {
                    ++same_count;
                    continue;
                }
                if (points[i].x == points[j].x) {
                    ++same_x;
                    continue;
                }
                if (points[i].y == points[j].y) {
                    ++same_y;
                    continue;
                }
                int x = points[i].x - points[j].x;
                int y = points[i].y - points[j].y;
                int z = function(x, y);
                current_max =
                    max(current_max, ++my_map[make_pair(x / z, y / z)]);
            }
            result = max(result, same_x + same_count);
            result = max(result, same_y + same_count);
            result = max(result, current_max + same_count);
        }
        return result;
    }

    int function(int x, int y) {
        if (y == 0) return x;
        return function(y, x % y);
    }
};
