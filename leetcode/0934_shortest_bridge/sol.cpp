/*
In a given 2D binary array grid, there are two islands.  (An island is a 4-directionally connected group of 1s not connected to any other 1s.)

Now, we may change 0s to 1s so as to connect the two islands together to form 1 island.

Return the smallest number of 0s that must be flipped.  (It is guaranteed that the answer is at least 1.)

 

Example 1:

Input: grid = [[0,1],[1,0]]
Output: 1
Example 2:

Input: grid = [[0,1,0],[0,0,0],[0,0,1]]
Output: 2
Example 3:

Input: grid = [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
Output: 1
 

Constraints:

2 <= grid.length == grid[0].length <= 100
grid[i][j] == 0 or grid[i][j] == 1
*/

// BFS to find shortest path
// time complexity: O(M*N)
class Solution {
public:
    int shortestBridge(vector<vector<int>>& grid) {
        const int M = grid.size();
        const int N = grid[0].size();
        const int DIR[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
   
        queue<pair<int,int>> q;  // for BFS
        
        // DFS to color one island
        std::function<void(int,int,int)> dfs = [&](int i, int j, const int color) {
            grid[i][j] = color;
            q.push({i,j});  // for BFS
            for(int k=0; k<4; ++k) {
                int ni = i + DIR[k][0];
                int nj = j + DIR[k][1];
                if(ni<0 || ni>=M || nj<0 || nj>=N || grid[ni][nj]!=1)
                    continue;
                dfs(ni,nj,color);
            }
        };
        bool found = false;
        for(int i=0; i<M&&!found; ++i) {
            for(int j=0; j<N; ++j) {
                if(grid[i][j] == 1) {
                    dfs(i,j,2);
                    found = true;  // for breaking outer loop...
                    break;  // only need to color one island
                }
            }
        }
        
        // BFS to compute shortest distance between two islands
        int steps = 0;
        while(!q.empty()) {
            int sz = q.size();
            while(sz--) {
                int i = q.front().first;
                int j = q.front().second;
                q.pop();
                for(int k=0; k<4; ++k) {
                    int ni = i + DIR[k][0];
                    int nj = j + DIR[k][1];
                    if(ni<0 || ni>=M || nj<0 || nj>=N || grid[ni][nj]==2/*already visited*/)
                        continue;
                    if(grid[ni][nj] == 1)
                        return steps;
                    q.push({ni,nj});
                    grid[ni][nj] = 2;
                }
            }
            ++steps;
        }
        
        return -1;  // should not reach here
    }
};
