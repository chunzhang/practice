/*
You are given an m x n grid where each cell can have one of three values:

0 representing an empty cell,
1 representing a fresh orange, or
2 representing a rotten orange.
Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.

 

Example 1:


Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
Output: 4
Example 2:

Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.
Example 3:

Input: grid = [[0,2]]
Output: 0
Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0.
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 10
grid[i][j] is 0, 1, or 2.
*/

// BFS
// O(M*N) time complexity
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        vector<vector<int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};
        // BFS
        const int M = grid.size();
        const int N = grid[0].size();
        queue<pair<int,int>> q;
        int level = 0;
        for(int i=0; i<M; ++i)
            for(int j=0; j<N; ++j)
                if(grid[i][j] == 2)
                    q.push({i,j});
        while(!q.empty()) {
            int sz = q.size();
            while(sz--) {
                pair<int,int> node = q.front();
                q.pop();
                for(vector<int> &d : dir) {
                    int ni = node.first + d[0];
                    int nj = node.second + d[1];
                    if(ni<0 || ni>=M || nj<0 || nj>=N)
                        continue;
                    if(grid[ni][nj] == 1) {  // next orange to rotten
                        grid[ni][nj] = 2;
                        q.push({ni,nj});
                    }
                }
            }
            if(!q.empty())  // important, only increment when next level exists
                ++level;
        }
        
        // check if all oranges are rotten
        for(int i=0; i<M; ++i)
            for(int j=0; j<N; ++j)
                if(grid[i][j] == 1)
                    return -1;
        
        
        return level;
    }
};
