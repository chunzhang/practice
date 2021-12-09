/*
You are given an array colors, in which there are three colors: 1, 2 and 3.

You are also given some queries. Each query consists of two integers i and c, return the shortest distance between the given index i and the target color c. If there is no solution return -1.

 

Example 1:

Input: colors = [1,1,2,1,3,2,2,3,3], queries = [[1,3],[2,2],[6,1]]
Output: [3,0,3]
Explanation: 
The nearest 3 from index 1 is at index 4 (3 steps away).
The nearest 2 from index 2 is at index 2 itself (0 steps away).
The nearest 1 from index 6 is at index 3 (3 steps away).
Example 2:

Input: colors = [1,2], queries = [[0,3]]
Output: [-1]
Explanation: There is no 3 in the array.
 

Constraints:

1 <= colors.length <= 5*10^4
1 <= colors[i] <= 3
1 <= queries.length <= 5*10^4
queries[i].length == 2
0 <= queries[i][0] < colors.length
1 <= queries[i][1] <= 3
*/


// pre-compute the indexes of each color
// then for each query, we need to find the first target color with index>=i, i.e., binary search ==> lower_bound
// time complexity: O(QlgN + N), each query takes lgN time, but pre-compute indexes takes O(N) total
// space complexity: O(N), i.e., for book-keeping color indexes
class Solution {
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
        vector<vector<int>> locs(4);  // for each color 1,2,3, remember its indexes from "colors" input array
        for(int i=0; i<colors.size(); ++i) {
            locs[colors[i]].push_back(i);
        }
        
        vector<int> ans(queries.size(), -1);
        for(int i=0; i<queries.size(); ++i) {
            int idx = queries[i][0];
            int target = queries[i][1];
            vector<int> &loc = locs[target];
            if(loc.empty()) {
                continue;
            }
            
            int lo = 0;
            int hi = loc.size();
            while(lo < hi) {
                int mid = lo + (hi-lo)/2;
                if(loc[mid] >= idx)
                    hi = mid;
                else
                    lo = mid + 1;
            }
            
            int dist = INT_MAX;
            if(lo < loc.size())
                dist = loc[lo] - idx;
            if(lo > 0)
                dist = min(dist, idx-loc[lo-1]);
            ans[i] = dist;
        }
        
        return ans;
    }
};


// binary search using std::lower_bound
// time complexity: O(QlgN + N)
// space complexity: O(N)
class Solution {
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
        vector<vector<int>> locs(4);  // for each color 1,2,3, remember its indexes from "colors" input array
        for(int i=0; i<colors.size(); ++i) {
            locs[colors[i]].push_back(i);
        }
        
        vector<int> ans(queries.size(), -1);
        for(int i=0; i<queries.size(); ++i) {
            int idx = queries[i][0];
            int target = queries[i][1];
            vector<int> &loc = locs[target];
            if(loc.empty()) {
                continue;
            }
            int dist = INT_MAX;
            auto right = lower_bound(loc.begin(), loc.end(), idx);
            if(right != loc.end())
                dist = *right - idx;
            if(right != loc.begin())
                dist = min(dist, idx-*(--right));
            ans[i] = dist;
        }
        
        return ans;
    }
};


// DP: pre-compute shortest distance to target color
// time complexity: O(N+Q)
// space complexity: O(N)
class Solution {
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
        // dp(i,c): shortest distance of i-th to target color c
        // for each color
        // -- scan from left to right, we can propagate the shortest distance to target color on the left
        // -- scan from right to left, we can propagate the shortest distance to target color on the right
        
        const int N = colors.size();
        vector<vector<int>> dp(N, vector<int>(4, -1));
        // shortest distance to the target color on the left
        for(int c=1; c<=3; ++c) {
            int pos = -1;  // right-most target color index in current scan
            for(int i=0; i<N; ++i) {
                if(colors[i] == c)
                    pos = i;
                if(pos != -1)
                    dp[i][c] = i-pos;
            }
        }
        // shortest distance to the target color on the right
        for(int c=1; c<=3; ++c) {
            int pos = -1;  // left-most target color index in current scan
            for(int i=N-1; i>=0; --i) {
                if(colors[i] == c)
                    pos = i;
                if(pos != -1)
                    dp[i][c] = dp[i][c]==-1?(pos-i):min(dp[i][c], pos-i);
            }
        }
        
        // now each query is just simple table lookup
        vector<int> ans;
        for(auto &q : queries) {
            ans.push_back(dp[q[0]][q[1]]);
        }
        
        return ans;
    }
};
