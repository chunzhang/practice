/*
  Given a 2D grid of 0s and 1s, return the number of elements in the largest square subgrid that has all 1s on its border, or 0 if such a subgrid doesn't exist in the grid.

 

  Example 1:

  Input: grid = [[1,1,1],[1,0,1],[1,1,1]]
  Output: 9
  Example 2:

  Input: grid = [[1,1,0,0]]
  Output: 1
 

  Constraints:

  1 <= grid.length <= 100
  1 <= grid[0].length <= 100
  grid[i][j] is 0 or 1
*/


// DP O(M*N*min(M,N)) time complexity, O(M*N) space complexity
class Solution {
public:
    int largest1BorderedSquare(vector<vector<int>>& grid) {
        // dph(m,n): how many continuous ones to the left of (m,n), including (m,n)
        // dpv(m,n): how many continuous ones to the up of (m,n), including (m,n)
        // For grid(m,n) as the bottom-right corner of square, try all possible squares that can be made from it;
        // By comparing whether we have continuous ones on the border from dph and dpv, we can get the answer
        const int M = grid.size();
        const int N = grid[0].size();
        vector<vector<int>> dph(M, vector<int>(N, 0));
        vector<vector<int>> dpv(M, vector<int>(N, 0));
        for(int m=0; m<M; ++m) {
            for(int n=0; n<N; ++n) {
                if(grid[m][n] == 1) {
                    dph[m][n] = (n==0?1:dph[m][n-1]+1);
                    dpv[m][n] = (m==0?1:dpv[m-1][n]+1);
                }
            }
        }
                
        int ans = 0;
        for(int m=0; m<M; ++m) {
            for(int n=0; n<N; ++n) {
                // grid(m,n) being the bottom-right corner of the potential square
                if(grid[m][n] == 0)
                    continue;
                int maxLen = min(dph[m][n]/*bottom horizontal boundary*/,dpv[m][n]/*right vertical boundary*/);  // 1-bordered is decided by the min of left and upper border
                // Starting from max possible len so we can break early, since we need to compute max area
                for(int k=maxLen-1; k>=0; --k) {  // O(min(M,N))
                    if(dph[m-k][n]>=k+1/*up horizontal boundary*/ && dpv[m][n-k]>=k+1/*left vertical boundary*/) {
                        ans = max(ans, k+1);
                        break;
                    }
                }
            }
        }
        
        return ans*ans;
    }
};



// An interesting idea from HuaHua
/*
  Compute the sums of all rectangles that has left-top corner at (0, 0) in O(m*n) time.
  For each square and check whether its borders are all ones in O(1) time.

  Time complexity: O(m*n*min(m,n))
  Space complexity: O(m*n)
*/
class Solution {
public:
    int largest1BorderedSquare(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));  // number of ones (i.e., area) in the rectangle with (m,n) as bottom-right corner
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + grid[i - 1][j - 1];
    
        for (int len = min(n, m); len > 0; --len)
            for (int x1 = 1, x2 = x1 + len - 1; x2 <= m; ++x1, ++x2)
                for (int y1 = 1, y2 = y1 + len - 1; y2 <= n; ++y1, ++y2)
                    if (getArea(x1, y1, x2, y1, dp) == len    // whether the four borders are all ones
                        && getArea(x1, y1, x1, y2, dp) == len
                        && getArea(x1, y2, x2, y2, dp) == len
                        && getArea(x2, y1, x2, y2, dp) == len)            
                        return len * len;        
        return 0;
    }
private:
    int getArea(int x1, int y1, int x2, int y2, const vector<vector<int>>& dp) {
        return dp[y2][x2] - dp[y2][x1 - 1] - dp[y1 - 1][x2] + dp[y1 - 1][x1 - 1];
    }
};

