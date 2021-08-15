/*
There is an m x n grid with a ball. The ball is initially at the position [startRow, startColumn]. You are allowed to move the ball to one of the four adjacent cells in the grid (possibly out of the grid crossing the grid boundary). You can apply at most maxMove moves to the ball.

Given the five integers m, n, maxMove, startRow, startColumn, return the number of paths to move the ball out of the grid boundary. Since the answer can be very large, return it modulo 109 + 7.

 

Example 1:


Input: m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
Output: 6
Example 2:


Input: m = 1, n = 3, maxMove = 3, startRow = 0, startColumn = 1
Output: 12
 

Constraints:

1 <= m, n <= 50
0 <= maxMove <= 50
0 <= startRow < m
0 <= startColumn < n
*/

// DP O(m*n*k) time complexity, O(m*n) space complexity
class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        const vector<vector<int>> moves = {{-1,0},{1,0},{0,-1},{0,1}};
        // dp(m,n,k): number of different ways that the ball is at (m,n) after k moves
        // dp(m,n,k) can be computed from dp(x,y,k-1) given the ball can be moved from (x,y) to (m,n)
        vector<vector<int>> dp(m, vector<int>(n,0));
        dp[startRow][startColumn] = 1;
        int ans = 0;
        const int M = 1e9+7;
        for(int k=0; k<maxMove; ++k) {
            vector<vector<int>> dpn(m, vector<int>(n,0));  // for next move
            for(int i=0; i<m; ++i) {
                for(int j=0; j<n; ++j) {
                    for(auto &move : moves) {
                        int ni = i + move[0];
                        int nj = j + move[1];
                        if(ni>=0 && ni<m && nj>=0 && nj<n) {
                            dpn[ni][nj] = (dpn[ni][nj]+dp[i][j])%M;
                        }
                        else {
                            ans = (ans+dp[i][j])%M;  // out of bound
                        }
                    }
                }
            }            
            dp.swap(dpn);
        }
        
        return ans;
    }
};


// A reference brute-force solution (in Java)
class Solution {
  public int findPaths(int m, int n, int N, int i, int j) {
    if (i == m || j == n || i < 0 || j < 0) return 1;
    if (N == 0) return 0;
    return findPaths(m, n, N - 1, i - 1, j)
        + findPaths(m, n, N - 1, i + 1, j)
        + findPaths(m, n, N - 1, i, j - 1)
        + findPaths(m, n, N - 1, i, j + 1);
  }
};
