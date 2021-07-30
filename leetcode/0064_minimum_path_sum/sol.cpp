/*
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

 

Example 1:


Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
Output: 7
Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.
Example 2:

Input: grid = [[1,2,3],[4,5,6]]
Output: 12
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 200
0 <= grid[i][j] <= 100
*/

// DP with O(mn) space
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        // dp[i][j]: min sum path at (i,j)
        int m = grid.size();
        int n = grid[0].size();
        
        vector<vector<int>> dp(m, vector<int>(n,0));
        dp[0][0] = grid[0][0];
        
        // first column and row
        for(int i=1; i<m; ++i)
            dp[i][0] = dp[i-1][0] + grid[i][0];
        for(int j=1; j<n; ++j)
            dp[0][j] = dp[0][j-1] + grid[0][j];
        
        for(int i=1; i<m; ++i) {
            for(int j=1; j<n; ++j) {
                dp[i][j] = min(dp[i][j-1], dp[i-1][j]) + grid[i][j];
            }
        }
        
        return dp[m-1][n-1];
    }
};


// DP with O(n) space
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        // dp[i][j]: min sum path at (i,j)
        int m = grid.size();
        int n = grid[0].size();
        
        vector<int> dp(n, 0);
        dp[0] = grid[0][0];
        for(int i=0; i<m; ++i) {
            for(int j=0; j<n; ++j) {
                if(i==0 && j==0)
                    continue;
                else if(i==0)
                    dp[j] = dp[j-1] + grid[i][j];
                else if(j==0)
                    dp[j] = dp[j] + grid[i][j];
                else
                    dp[j] = min(dp[j-1], dp[j]) + grid[i][j];
            }
        }
        
        return dp[n-1];
    }
};
