/*
Given a triangle array, return the minimum path sum from top to bottom.

For each step, you may move to an adjacent number of the row below. More formally, if you are on index i on the current row, you may move to either index i or index i + 1 on the next row.

 

Example 1:

Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
Explanation: The triangle looks like:
   2
  3 4
 6 5 7
4 1 8 3
The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).
Example 2:

Input: triangle = [[-10]]
Output: -10
 

Constraints:

1 <= triangle.length <= 200
triangle[0].length == 1
triangle[i].length == triangle[i - 1].length + 1
-10^4 <= triangle[i][j] <= 10^4
*/

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        // dp[i][j]: min path sum at (i,j) from bottom to up
        // dp[i][j] = min(dp[i+1][j], dp[i+1][j+1]) + triangle[i][j]
        int m = triangle.size();  // m rows
        vector<int> dp(triangle[m-1]);
        for(int i=m-2; i>=0; --i) {
            vector<int> dp2(triangle[i]);
            for(int j=0; j<dp2.size(); ++j) {
                dp2[j] += min(dp[j], dp[j+1]);
            }
            dp.swap(dp2);
        }
        
        return dp[0];
    }
};
