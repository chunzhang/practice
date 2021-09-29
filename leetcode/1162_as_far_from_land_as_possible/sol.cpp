/*
Given an n x n grid containing only values 0 and 1, where 0 represents water and 1 represents land, find a water cell such that its distance to the nearest land cell is maximized, and return the distance. If no land or water exists in the grid, return -1.

The distance used in this problem is the Manhattan distance: the distance between two cells (x0, y0) and (x1, y1) is |x0 - x1| + |y0 - y1|.

 

Example 1:


Input: grid = [[1,0,1],[0,0,0],[1,0,1]]
Output: 2
Explanation: The cell (1, 1) is as far as possible from all the land with distance 2.
Example 2:


Input: grid = [[1,0,0],[0,0,0],[0,0,0]]
Output: 4
Explanation: The cell (2, 2) is as far as possible from all the land with distance 4.
 

Constraints:

n == grid.length
n == grid[i].length
1 <= n <= 100
grid[i][j] is 0 or 1
*/

// BFS
// time complexity: O(M*N)
// space complexity: O(M*N) (i.e., all grids are ones)
class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        vector<pair<int,int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};
        const int M = grid.size();
        const int N = grid[0].size();

        // BFS
        queue<pair<int,int>> q;
        for(int i=0; i<M; ++i)
            for(int j=0; j<N; ++j)
                if(grid[i][j] == 1)
                    q.push({i,j});
        int level = 0;
        while(q.size()) {
            int sz = q.size();
            while(sz--) {
                auto node = q.front();
                q.pop();
                for(auto &d : dir) {
                    int ni = node.first + d.first;
                    int nj = node.second + d.second;
                    if(ni>=0 && ni<M && nj>=0 && nj<N && grid[ni][nj]==0) {
                        grid[ni][nj] = 1;  // need to mark as visited
                        q.push({ni,nj});
                    }
                }
            }
                
            if(q.size())  // this check is important
                ++level;
        }
        
        return level?level:-1;
    }
};
