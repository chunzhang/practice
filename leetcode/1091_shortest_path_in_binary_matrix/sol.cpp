/*
Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.

A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:

All the visited cells of the path are 0.
All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they share an edge or a corner).
The length of a clear path is the number of visited cells of this path.

 

Example 1:


Input: grid = [[0,1],[1,0]]
Output: 2
Example 2:


Input: grid = [[0,0,0],[1,1,0],[1,1,0]]
Output: 4
Example 3:

Input: grid = [[1,0,0],[1,1,0],[1,1,0]]
Output: -1
 

Constraints:

n == grid.length
n == grid[i].length
1 <= n <= 100
grid[i][j] is 0 or 1
*/


// BFS O(N*N)
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        vector<pair<int,int>> dir = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
        const int N = grid.size();

        // quickly filter edge case
        if(grid[0][0] || grid[N-1][N-1])
            return -1;
        if(N == 1)
            return 1;

        // BFS (reuse grid as visited flag)
        int len = 1;
        queue<pair<int,int>> q;
        q.emplace(0,0);
        grid[0][0] = 1;  // mark visited

        while(!q.empty()) {
            int sz = q.size();
            while(sz--) {
                auto p = q.front();
                q.pop();
                for(auto &d : dir) {
                    int ni = p.first + d.first;
                    int nj = p.second + d.second;
                    if(ni>=0 && nj>=0 && ni<N && nj<N && !grid[ni][nj]) {
                        if(ni==N-1 && nj==N-1)  // found solution
                            return len+1;
                        q.emplace(ni,nj);
                        grid[ni][nj] = 1;  // mark visited
                    }
                }
            }
            ++len;
        }
        
        return -1;  // no path found
    }

private:
};
