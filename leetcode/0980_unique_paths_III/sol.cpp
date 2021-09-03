/*
You are given an m x n integer array grid where grid[i][j] could be:

1 representing the starting square. There is exactly one starting square.
2 representing the ending square. There is exactly one ending square.
0 representing empty squares we can walk over.
-1 representing obstacles that we cannot walk over.
Return the number of 4-directional walks from the starting square to the ending square, that walk over every non-obstacle square exactly once.

 

Example 1:


Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
Output: 2
Explanation: We have the following two paths: 
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)
Example 2:


Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,0,2]]
Output: 4
Explanation: We have the following four paths: 
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)
Example 3:


Input: grid = [[0,1],[2,0]]
Output: 0
Explanation: There is no path that walks over every empty square exactly once.
Note that the starting and ending square can be anywhere in the grid.
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 20
1 <= m * n <= 20
-1 <= grid[i][j] <= 2
There is exactly one starting cell and one ending cell.
*/


// My solution of DFS + memoization
// -- time and space complexity: O(M*N*2^(M*N)), i.e., total number of sub-problems
class Solution {
public:
    // my idea is to try DFS + memoization
    // dp(i,j,state): number of paths starting from (i,j) and state of visited nodes (state is represented as a bitmap of nodes that have been visited)
    int uniquePathsIII(vector<vector<int>>& grid) {
        _dir = {{0,1},{1,0},{0,-1},{-1,0}};
        _g = grid;
        M = grid.size();
        N = grid[0].size();
        _mem.resize(M*N);
        _visited = 0;
        _target = 0;
        int si;  // starting point
        int sj;
        for(int i=0; i<M; ++i) {
            for(int j=0; j<N; ++j) {
                int idx = i*N + j;
                _target |= (0x1<<idx);
                if(grid[i][j]==1 || grid[i][j]==-1) {
                    _visited |= (0x1<<idx);
                    if(grid[i][j] == 1) {
                        si = i;
                        sj = j;
                    }
                }
            }
        }
        
        return dfs(si,sj);
    }
    
private:
    vector<vector<int>> _dir;
    vector<vector<int>> _g;
    vector<unordered_map<int,int>> _mem;
    int _visited;  // bit-representation of whether each grid is visited
    int _target;   // means find an answer
    int M;
    int N;
    
    int dfs(int i, int j) {
        if(_g[i][j] == 2)
            return _visited==_target;  // reach destination, either we find a solution or not
        
        int idx = i*N + j;
        auto it = _mem[idx].find(_visited);
        if(it != _mem[idx].end())
            return it->second;
        
        int ans = 0;
        for(auto &dir : _dir) {
            int ni = i + dir[0];
            int nj = j + dir[1];
            if(ni<0 || nj<0 || ni>=M || nj>=N)
                continue;
            int nidx = ni*N + nj;
            int mask = 0x1<<nidx;
            if(_visited&mask)  // already visited
                continue;
            _visited ^= mask;  // set visited for next node
            ans += dfs(ni,nj);
            _visited ^= mask;  // unset visited for next node
        }
        
        _mem[idx][_visited] = ans;
        return ans;
    }
};


// HuaHua: brute-force
// O(4^(M*N)) time complexity
// O(M*N) space complexity
class Solution {
public:
  int uniquePathsIII(vector<vector<int>>& grid) {    
    int sx = -1;
    int sy = -1;
    int n = 1;
    for (int i = 0; i < grid.size(); ++i)
      for (int j = 0; j < grid[0].size(); ++j)
        if (grid[i][j] == 0) ++n;
        else if (grid[i][j] == 1) { sx = j; sy = i; }    
    return dfs(grid, sx, sy, n);
  }
private:
  int dfs(vector<vector<int>>& grid, int x, int y, int n) {
    if (x < 0 || x == grid[0].size() || 
        y < 0 || y == grid.size() || 
        grid[y][x] == -1) return 0;
    if (grid[y][x] == 2) return n == 0;    
    grid[y][x] = -1;
    int paths = dfs(grid, x + 1, y, n - 1) + 
                dfs(grid, x - 1, y, n - 1) +
                dfs(grid, x, y + 1, n - 1) + 
                dfs(grid, x, y - 1, n - 1);
    grid[y][x] = 0;
    return paths;
  };
};


// HuaHua: DP with memoization
class Solution {
public:
  int uniquePathsIII(vector<vector<int>>& grid) {
    const int n = grid.size();
    const int m = grid[0].size();
    const vector<int> dirs{-1, 0, 1, 0, -1};
    
    vector<vector<vector<short>>> cache(n, vector<vector<short>>(m, vector<short>(1 << n * m, -1)));
    int sx = -1;
    int sy = -1;
    int state = 0;
    
    auto key = [m](int x, int y) { return 1 << (y * m + x); };
    
    function<short(int, int, int)> dfs = [&](int x, int y, int state) {    
      if (cache[y][x][state] != -1) return cache[y][x][state];
      if (grid[y][x] == 2) return static_cast<short>(state == 0); 
      int paths = 0;      
      for (int i = 0; i < 4; ++i) {
        const int tx = x + dirs[i];
        const int ty = y + dirs[i + 1];
        if (tx < 0 || tx == m || ty < 0 || ty == n || grid[ty][tx] == -1) continue;
        if (!(state & key(tx, ty))) continue;
        paths += dfs(tx, ty, state ^ key(tx, ty));
      }
      return cache[y][x][state] = paths;
    };
    
    for (int y = 0; y < n; ++y)
      for (int x = 0; x < m; ++x)
        if (grid[y][x] == 0 || grid[y][x] == 2) state |= key(x, y);
        else if (grid[y][x] == 1) { sx = x; sy = y; }
    return dfs(sx, sy, state);
  }
};
