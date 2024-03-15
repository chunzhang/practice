/*
Facebook/Amazon/JPMorgan/Google/Apple
  
Given an array of intervals intervals where intervals[i] = [start_i, end_i], return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

Example 1:

Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.

Example 2:

Input: intervals = [[1,2],[1,2],[1,2]]
Output: 2
Explanation: You need to remove two [1,2] to make the rest of the intervals non-overlapping.

Example 3:

Input: intervals = [[1,2],[2,3]]
Output: 0
Explanation: You don't need to remove any of the intervals since they're already non-overlapping.
 

Constraints:

1 <= intervals.length <= 10^5
intervals[i].length == 2
-5 * 10^4 <= start_i < end_i <= 5 * 10^4
*/

// greedy
// time: O(NlgN)
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        // greedy: when there's an overlap, always remove the one that ends latest
        int ans = 0;
        // sort intervals by starting time
        sort(intervals.begin(), intervals.end(), [&](const vector<int> &i1, const vector<int> &i2) {
            return i1[0]!=i2[0] ? i1[0]<i2[0] : i1[1]<i2[1];
        });

        int cur = 0;  // last interval that is kept
        for(int i=1; i<intervals.size(); ++i) {
            if(intervals[i][0] < intervals[cur][1]) {  // overlap exists
                ++ans;
                cur = intervals[cur][1]>=intervals[i][1] ? i/*remove interval cur*/ : cur/*remove interval i*/;
            }
            else {
                cur = i;
            }
        }
        return ans;
    }
};
