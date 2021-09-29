/*
You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

The area of an island is the number of cells with a value 1 in the island.

Return the maximum area of an island in grid. If there is no island, return 0.

 

Example 1:


Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
Output: 6
Explanation: The answer is not 11, because the island must be connected 4-directionally.
Example 2:

Input: grid = [[0,0,0,0,0,0,0,0]]
Output: 0
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 50
grid[i][j] is either 0 or 1.
*/


// DFS
// time complexity: O(M*N)
// space complexity: O(M*N)
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int ans = 0;
        for(int i=0; i<grid.size(); ++i)
            for(int j=0; j<grid[0].size(); ++j)
                if(grid[i][j]==1)
                    ans = max(ans, dfs(grid,i,j));
        
        return ans;
    }
    
private:
    int dfs(vector<vector<int>> &grid, int i, int j) {
        int area = 1;
        grid[i][j] = 0;
        if(i+1<grid.size() && grid[i+1][j]==1)
            area += dfs(grid, i+1, j);
        if(i-1>=0 && grid[i-1][j]==1)
            area += dfs(grid, i-1, j);
        if(j+1<grid[0].size() && grid[i][j+1]==1)
            area += dfs(grid, i, j+1);
        if(j-1>=0 && grid[i][j-1]==1)
            area += dfs(grid, i, j-1);
        
        return area;
    }
};


// BFS
// time complexity: O(<*N)
// space complexity: O(min(M*N))
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int ans = 0;
        for(int i=0; i<grid.size(); ++i)
            for(int j=0; j<grid[0].size(); ++j)
                if(grid[i][j]==1)
                    ans = max(ans, bfs(grid,i,j));
        
        return ans;
    }
    
private:
    const vector<pair<int,int>> _dir = {{0,1},{0,-1},{1,0},{-1,0}};
    int bfs(vector<vector<int>> &grid, int i, int j) {
        queue<pair<int,int>> q;
        int area = 1;
        q.push({i,j});
        grid[i][j] = 0;
        while(q.size()) {
            auto node = q.front();
            q.pop();
            for(auto &d : _dir) {
                int ni = node.first + d.first;
                int nj = node.second + d.second;
                if(ni>=0 && ni<grid.size() && nj>=0 && nj<grid[0].size() && grid[ni][nj]==1) {
                    ++area;
                    grid[ni][nj] = 0;  // must mark visisted when node is added to the queue
                    q.push({ni,nj});
                }
            }
        }
        
        return area;
    }
};


// DFS ref impl -- simulte with a stack (in Java)
class Solution {
    public int maxAreaOfIsland(int[][] grid) {
        boolean[][] seen = new boolean[grid.length][grid[0].length];
        int[] dr = new int[]{1, -1, 0, 0};
        int[] dc = new int[]{0, 0, 1, -1};

        int ans = 0;
        for (int r0 = 0; r0 < grid.length; r0++) {
            for (int c0 = 0; c0 < grid[0].length; c0++) {
                if (grid[r0][c0] == 1 && !seen[r0][c0]) {
                    int shape = 0;
                    Stack<int[]> stack = new Stack();
                    stack.push(new int[]{r0, c0});
                    seen[r0][c0] = true;
                    while (!stack.empty()) {
                        int[] node = stack.pop();
                        int r = node[0], c = node[1];
                        shape++;
                        for (int k = 0; k < 4; k++) {
                            int nr = r + dr[k];
                            int nc = c + dc[k];
                            if (0 <= nr && nr < grid.length &&
                                    0 <= nc && nc < grid[0].length &&
                                    grid[nr][nc] == 1 && !seen[nr][nc]) {
                                stack.push(new int[]{nr, nc});
                                seen[nr][nc] = true;
                            }
                        }
                    }
                    ans = Math.max(ans, shape);
                }
            }
        }
        return ans;
    }
}
    ;
