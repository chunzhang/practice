/*
  You are given two lists of closed intervals, firstList and secondList, where firstList[i] = [start_i, end_i] and secondList[j] = [start_j, end_j]. Each list of intervals is pairwise disjoint and in sorted order.

  Return the intersection of these two interval lists.

  A closed interval [a, b] (with a <= b) denotes the set of real numbers x with a <= x <= b.

  The intersection of two closed intervals is a set of real numbers that are either empty or represented as a closed interval. For example, the intersection of [1, 3] and [2, 4] is [2, 3].

 

  Example 1:


  Input: firstList = [[0,2],[5,10],[13,23],[24,25]], secondList = [[1,5],[8,12],[15,24],[25,26]]
  Output: [[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
  Example 2:

  Input: firstList = [[1,3],[5,9]], secondList = []
  Output: []
  Example 3:

  Input: firstList = [], secondList = [[4,8],[10,12]]
  Output: []
  Example 4:

  Input: firstList = [[1,7]], secondList = [[3,10]]
  Output: [[3,7]]
 

  Constraints:

  0 <= firstList.length, secondList.length <= 1000
  firstList.length + secondList.length >= 1
  0 <= start_i < end_i <= 10^9
  end_i < start_i+1
  0 <= start_j < end_j <= 10^9
  end_j < start_j+1
*/


// two pointers
// time complexity: O(M+N), where M,N are the length of input intervals
class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        vector<vector<int>> ans;
        int i = 0;
        int j = 0;
        while(i<firstList.size() && j<secondList.size()) {
            if(firstList[i][1]>=secondList[j][0] && firstList[i][0]<=secondList[j][1]) {  // has overlap
                int start = max(firstList[i][0], secondList[j][0]);
                int end = min(firstList[i][1], secondList[j][1]);
                ans.push_back({start,end});  // based on the input interval conditions, it's impossible that two overlaps are consecutive
            }
            
            if(firstList[i][1] < secondList[j][1])
                ++i;
            else
                ++j;
        }
        
        return ans;
    }

};


// two pointers -- a slightly different impl from HuaHua
class Solution {
public:
    vector<Interval> intervalIntersection(vector<Interval>& A, vector<Interval>& B) {
        size_t i = 0;
        size_t j = 0;
        vector<Interval> ans;
        while (i < A.size() && j < B.size()) {
            const int s = max(A[i].start, B[j].start);
            const int e = min(A[i].end, B[j].end);
            if (s <= e) ans.emplace_back(s, e);
            if (A[i].end < B[j].end)
                ++i;
            else
                ++j;
        }
        return ans;
    }
};
