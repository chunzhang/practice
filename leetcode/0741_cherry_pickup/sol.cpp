/*
You are given an n x n grid representing a field of cherries, each cell is one of three possible integers.

0 means the cell is empty, so you can pass through,
1 means the cell contains a cherry that you can pick up and pass through, or
-1 means the cell contains a thorn that blocks your way.
Return the maximum number of cherries you can collect by following the rules below:

Starting at the position (0, 0) and reaching (n - 1, n - 1) by moving right or down through valid path cells (cells with value 0 or 1).
After reaching (n - 1, n - 1), returning to (0, 0) by moving left or up through valid path cells.
When passing through a path cell containing a cherry, you pick it up, and the cell becomes an empty cell 0.
If there is no valid path between (0, 0) and (n - 1, n - 1), then no cherries can be collected.
 

Example 1:


Input: grid = [[0,1,-1],[1,0,-1],[1,1,1]]
Output: 5
Explanation: The player started at (0, 0) and went down, down, right right to reach (2, 2).
4 cherries were picked up during this single trip, and the matrix becomes [[0,1,-1],[0,0,-1],[0,0,0]].
Then, the player went left, up, up, left to return home, picking up one more cherry.
The total number of cherries picked up is 5, and this is the maximum possible.
Example 2:

Input: grid = [[1,1,-1],[1,-1,1],[-1,1,1]]
Output: 0
 

Constraints:

n == grid.length
n == grid[i].length
1 <= n <= 50
grid[i][j] is -1, 0, or 1.
grid[0][0] != -1
grid[n - 1][n - 1] != -1
*/


/*
Directly do two pass does not give correct result, see below counter-example
11100
00101
10100
00100
00111
*/

// DP O(N^3) time and space complexity
class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        // convert this to the problem of two person starts at same time from (0,0) to (n-1,n-1) for cherry pickup
        // dp(r1,c1,r2,c2): max cherries that can be picked up by both person, where one is at (r1,c1) and another is at (r2,c2)
        // -- since r1+c1==r2+c2, we can reduce one dimension on state
        // dp(r1,c1,r2,c2) = max{dp(r1-1,c1,r2-1,c2), dp(r1-1,c1,r2,c2-1),dp(r1,c1-1,r2-1,c2),dp(r1,c1-1,r2,c2-1)} + cherry at (r1,c1) and (r2,c2)
        
        vector<vector<int>> directions = {{-1,0,-1,0}, {-1,0,0,-1}, {0,-1,-1,0}, {0,-1,0,-1}};
        const int N = grid.size();
        vector<vector<vector<int>>> dp(N, vector<vector<int>>(N, vector<int>(N,INT_MIN)));  // defined as dp(r1,c1,r2)
        dp[0][0][0] = grid[0][0];
        for(int t=1; t<2*N-1; ++t) {  // it takes (2*N-1)-steps to move from (0,0) to (N-1,N-1)
            for(int r1=0,c1=t-r1; r1<N&&r1<=t; ++r1,--c1) {
                if(c1>=N || grid[r1][c1]==-1)
                    continue;
                for(int r2=0,c2=t-r2; r2<N&&r2<=t; ++r2,--c2) {
                    if(c2>=N || grid[r2][c2]==-1)
                        continue;
                    
                    // cherries that can be picked up at current state
                    int curCherry = grid[r1][c1];
                    if(r2!=r1 || c2!=c1)  // if two person are at the same location, at most one cherry can be picked up
                        curCherry += grid[r2][c2];
                    
                    for(vector<int> &dir : directions) {  // all possible previous states
                        int r11 = r1 + dir[0];
                        int c11 = c1 + dir[1];
                        int r22 = r2 + dir[2];
                        int c22 = c2 + dir[3];
                        if(r11<0 || c11<0 || r22<0 || c22<0 || dp[r11][c11][r22]==INT_MIN/*unreachable*/)
                            continue;
                        dp[r1][c1][r2] = max(dp[r1][c1][r2], dp[r11][c11][r22]+curCherry);
                    }
                }
            }
        }
        
        
        return dp[N-1][N-1][N-1]==INT_MIN?0:dp[N-1][N-1][N-1];
    }
};


// A faster implementation, but same idea
class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        // convert this to the problem of two person starts at same time from (0,0) to (n-1,n-1) for cherry pickup
        // dp(r1,c1,r2,c2): max cherries that can be picked up by both person, where one is at (r1,c1) and another is at (r2,c2)
        // -- since r1+c1==r2+c2, we can reduce one dimension on state
        // dp(r1,c1,r2,c2) = max{dp(r1-1,c1,r2-1,c2), dp(r1-1,c1,r2,c2-1),dp(r1,c1-1,r2-1,c2),dp(r1,c1-1,r2,c2-1)} + cherry at (r1,c1) and (r2,c2)

        // A faster version with better implementation
        const int N = grid.size();
        int dp[N][N][N];
        memset(dp, -1, sizeof(dp));
        dp[0][0][0] = grid[0][0];
        for(int r1=0; r1<N; ++r1) {  // the fact that one can only move to the right or bottom guarantees correctness of below bottom-up calculation order
            for(int c1=0; c1<N; ++c1) {
                if(grid[r1][c1] == -1)
                    continue;
                for(int r2=0; r2<N; ++r2) {
                    if(r1==0 && c1==0 && r2==0)  // already computed
                        continue;
                    int c2 = r1+c1-r2;
                    if(c2<0 || c2>=N)  // invalid state
                        continue;
                    if(grid[r2][c2] == -1)
                        continue;

                    int maxCherry = -1;
                    if(r1>=1 && r2>=1)
                        maxCherry = max(maxCherry,dp[r1-1][c1][r2-1]);   // from (up,up)
                    if(r1>=1 && c2>=1)
                        maxCherry = max(maxCherry, dp[r1-1][c1][r2]);    // from (up,left)
                    if(c1>=1 && r2>=1)
                        maxCherry = max(maxCherry, dp[r1][c1-1][r2-1]);  // from (left,up)
                    if(c1>=1 && c2>=1)
                        maxCherry = max(maxCherry, dp[r1][c1-1][r2]);    // from (left,left)
                    
                    if(maxCherry != -1) {
                        maxCherry += grid[r1][c1];
                        if(r1!=r2 || c1!=c2 )
                            maxCherry += grid[r2][c2];
                    }
                    
                    dp[r1][c1][r2] = maxCherry;
                }
            }
        }
        
        return max(dp[N-1][N-1][N-1], 0);
    }
};


// DP with memoization (from HuaHua)
class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        const int n = grid.size();
        grid_ = &grid;
        m_ = vector<vector<vector<int>>>(
                n, vector<vector<int>>(n, vector<int>(n, INT_MIN)));
        return max(0, dp(n - 1, n - 1, n - 1));
    }
private:
    // max cherries from (x1, y1) to (0, 0) + (x2, y2) to (0, 0)
    int dp(int x1, int y1, int x2) {
        const int y2 = x1 + y1 - x2;
        if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) return -1;
        if ((*grid_)[y1][x1] < 0 || (*grid_)[y2][x2] < 0) return -1;
        if (x1 == 0 && y1 == 0) return (*grid_)[y1][x1];
        if (m_[x1][y1][x2] != INT_MIN) return m_[x1][y1][x2];        
        int ans =  max(max(dp(x1 - 1, y1, x2 - 1), dp(x1, y1 - 1, x2)),
                       max(dp(x1, y1 - 1, x2 - 1), dp(x1 - 1, y1, x2)));
        if (ans < 0) return m_[x1][y1][x2] = -1;
        ans += (*grid_)[y1][x1];
        if (x1 != x2) ans += (*grid_)[y2][x2];
        
        return m_[x1][y1][x2] = ans;
    }
    
    vector<vector<vector<int>>> m_;
    vector<vector<int>>* grid_; // does not own the object
};
