/*
You are given an m x n integer matrix grid where each cell is either 0 (empty) or 1 (obstacle). You can move up, down, left, or right from and to an empty cell in one step.

Return the minimum number of steps to walk from the upper left corner (0, 0) to the lower right corner (m - 1, n - 1) given that you can eliminate at most k obstacles. If it is not possible to find such walk return -1.

 

Example 1:

Input: 
grid = 
[[0,0,0],
 [1,1,0],
 [0,0,0],
 [0,1,1],
 [0,0,0]], 
k = 1
Output: 6
Explanation: 
The shortest path without eliminating any obstacle is 10. 
The shortest path with one obstacle elimination at position (3,2) is 6. Such path is (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3,2) -> (4,2).
Example 2:

Input: 
grid = 
[[0,1,1],
 [1,1,1],
 [1,0,0]], 
k = 1
Output: -1
Explanation: 
We need to eliminate at least two obstacles to find such a walk.
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 40
1 <= k <= m * n
grid[i][j] == 0 or 1
grid[0][0] == grid[m - 1][n - 1] == 0
*/

// BFS solution
class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        vector<vector<int>> dirs = {{1,0},{0,1},{-1,0},{0,-1}};        
        const int rows = grid.size();
        const int cols = grid[0].size();
        vector<vector<int>> visited(rows, vector<int>(cols, INT_MAX));
        
        // BFS on node(i,j,r) where r is the number of  obstacles that has been removed        
        // Use vector<int> to represent (i,j,r)
        int level = 0;
        queue<vector<int>> q;
        q.push({0,0,0});
        visited[0][0] = 0;
        while(!q.empty()) {
            int size = q.size();
            while(size--) {
                auto node = q.front();
                q.pop();
                int i = node[0];
                int j = node[1];
                int r = node[2];
                if(i==rows-1 && j==cols-1)  // reach destination
                    return level;
                for(auto d : dirs) {
                    int ni = i+d[0];
                    int nj = j+d[1];
                    if(ni<0 || ni>=rows || nj<0 || nj>=cols)
                        continue;
                    int nr = r + grid[ni][nj];
                    // If not a better path, i.e., reach (ni,nj) with more obstacles that have been removed, we can skip
                    if(nr>=visited[ni][nj] || nr>k)  
                        continue;
                    
                    // add node
                    visited[ni][nj] = nr;
                    q.push({ni,nj,nr});
                }
            }
            ++level;
        }
        
        return -1;  // upon here, BFS does not find any solution
    }

};
