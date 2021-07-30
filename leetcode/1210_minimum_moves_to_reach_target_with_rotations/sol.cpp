/*
In an n*n grid, there is a snake that spans 2 cells and starts moving from the top left corner at (0, 0) and (0, 1). The grid has empty cells represented by zeros and blocked cells represented by ones. The snake wants to reach the lower right corner at (n-1, n-2) and (n-1, n-1).

In one move the snake can:

- Move one cell to the right if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
- Move down one cell if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
- Rotate clockwise if it's in a horizontal position and the two cells under it are both empty. In that case the snake moves from (r, c) and (r, c+1) to (r, c) and (r+1, c).
- Rotate counterclockwise if it's in a vertical position and the two cells to its right are both empty. In that case the snake moves from (r, c) and (r+1, c) to (r, c) and (r, c+1).

Return the minimum number of moves to reach the target.

If there is no way to reach the target, return -1.

 

Example 1:



Input: grid = [[0,0,0,0,0,1],
               [1,1,0,0,1,0],
               [0,0,0,0,1,1],
               [0,0,1,0,1,0],
               [0,1,1,0,0,0],
               [0,1,1,0,0,0]]
Output: 11
Explanation:
One possible solution is [right, right, rotate clockwise, right, down, down, down, down, rotate counterclockwise, right, down].
Example 2:

Input: grid = [[0,0,1,1,1,1],
               [0,0,0,0,1,1],
               [1,1,0,0,0,1],
               [1,1,1,0,0,1],
               [1,1,1,0,0,1],
               [1,1,1,0,0,0]]
Output: 9
 

Constraints:

2 <= n <= 100
0 <= grid[i][j] <= 1
It is guaranteed that the snake starts at empty cells.
*/

// BFS solution
class Solution {
public:
    int minimumMoves(vector<vector<int>>& grid) {
        // BFS, each node is an (head_x, head_y, direction) tuple;
        // direction=0 --> horizontal, direction=1 --> vertical
        int n = grid.size();
        vector<vector<vector<int>>> visited(n, vector<vector<int>>(n, vector<int>(2,0)));
        queue<vector<int>> q;
        q.push({0,1,0});  // initial head at (0,1) with horizontal direction
        visited[0][1][0] = 1;
        int level = 0;
        while(!q.empty()) {
            int size = q.size();
            while(size--) {
                auto cur = q.front();
                q.pop();
                int x = cur[0];
                int y = cur[1];
                int dir = cur[2];
                
                if(x==n-1 && y==n-1 && !dir)  // find destination
                    return level;
            
                // move right
                if(y<n-1 && !grid[x][y+1] && (!dir || !grid[x-1][y+1])) {
                    if(!visited[x][y+1][dir]) {
                        q.push({x,y+1,dir});
                        visited[x][y+1][dir] = 1;
                    }
                }
            
                // move down
                if(x<n-1 && !grid[x+1][y] && (dir || !grid[x+1][y-1])) {
                    if(!visited[x+1][y][dir]) {
                        q.push({x+1,y,dir});
                        visited[x+1][y][dir] = 1;
                    }
                }    
            
                // rotate clockwise
                if(!dir && x<n-1 && !grid[x+1][y-1] && !grid[x+1][y]) {
                    if(!visited[x+1][y-1][1]) {
                        q.push({x+1,y-1,1});
                        visited[x+1][y-1][1] = 1;
                    }
                }
            
                // rotate counter-clockwise
                if(dir && y<n-1 && !grid[x][y+1] && !grid[x-1][y+1]) {
                    if(!visited[x-1][y+1][0]) {
                        q.push({x-1,y+1,0});
                        visited[x-1][y+1][0] = 1;
                    }
                }
            }
            ++level;
        }
        
        return -1;
    }
};

// DP solution for reference -- 1
// Author: Huahua, 16 ms, 12.1MB
class Solution {
public:
  int minimumMoves(vector<vector<int>>& grid) {
    constexpr int kInf = 1e9;
    const int n = grid.size();
    vector<vector<pair<int, int>>> dp(n + 1, 
                                      vector<pair<int, int>>(n + 1, {kInf, kInf}));
    dp[0][1].first = dp[1][0].first = -1;
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j) {
        bool h = false;
        bool v = false;
        if (!grid[i - 1][j - 1] && j < n && !grid[i - 1][j]) {
          dp[i][j].first = min(dp[i - 1][j].first, dp[i][j - 1].first) + 1;
          h = true;          
        }
        if (!grid[i - 1][j - 1] && i < n && !grid[i][j - 1]) {
          dp[i][j].second = min(dp[i - 1][j].second, dp[i][j - 1].second) + 1;
          v = true;          
        }
        if (v && j < n && !grid[i][j])
            dp[i][j].second = min(dp[i][j].second, dp[i][j].first + 1);
        if (h && i < n && !grid[i][j])
            dp[i][j].first = min(dp[i][j].first, dp[i][j].second + 1);        
      }      
    return dp[n][n - 1].first >= kInf ? -1 : dp[n][n - 1].first;
  }
};

// DP solution for reference -- 2
/*
  The idea is to create two DP arrays representing two different snake states at each grid point (lying horizontally or vertically) and then update these two DP arrays diagonally from top-left (i+j=0) to bottom-right (i+j = 2n-2). Space and time complexity is O(n^2).
*/
class Solution {
public:
    int minimumMoves(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dph(n, vector<int>(n, INT_MAX/2)); //min moves to reach state with snake head at (i,j) and snake tail at (i,j-1) (ie, a snake lying horizontally)
        vector<vector<int>> dpv = dph; //min moves to reach state with snake head at (i,j) and snake tail at (i-1,j) (ie, a snake lying vertically)
        //0. init
        dph[0][1] = 0;
        if(!grid[1][0] && !grid[1][1]) dpv[1][0] = 1;
        for(int k = 2; k <= 2*n-2; k++){ //k is the wavefront, k = i+j
            int i_start = max(0, k - n + 1);
            int i_end = min(k, n-1);
            //1. first update dph[i][j] and dpv[i][j] (i+j == k) based on horizonal or vertical shifts, using dp[i'][j'] where i'+j'==k-1
            for(int i = i_start; i <= i_end; i++){
                int j = k - i;
                if(grid[i][j]) continue;
                //1.1. update dph
                if(j>0 && !grid[i][j-1]){
                    dph[i][j] = dph[i][j-1] + 1; //horizontal shift (right)
                    if(i>0) dph[i][j] = min(dph[i][j], dph[i-1][j] + 1); //vertical shift (down)
                }
                //1.2. update dpv
                if(i>0 && !grid[i-1][j]){
                    dpv[i][j] = dpv[i-1][j] + 1; //vertical shift (down)
                    if(j>0) dpv[i][j] = min(dpv[i][j], dpv[i][j-1] + 1); //horizontal shift (right)
                }
            }
            //2. Then update dph[i][j] and dpv[i][j] (i+j == k) based on rotations, using dp[i'][j'] where i'+j'==k (ie, same wavefronts)
            for(int i = i_start; i <= i_end; i++){
                int j = k - i;
                if(grid[i][j]) continue;
                if(j>0 && !grid[i][j-1] && i<n-1 && !grid[i+1][j]) dph[i][j] = min(dph[i][j], dpv[i+1][j-1] + 1);
                if(i>0 && !grid[i-1][j] && j<n-1 && !grid[i][j+1]) dpv[i][j] = min(dpv[i][j], dph[i-1][j+1] + 1);
            }
        }
        if(dph[n-1][n-1] >= INT_MAX/2) return -1;
        else return dph[n-1][n-1];
    }
};
