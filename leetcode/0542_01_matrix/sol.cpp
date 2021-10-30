/*
Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.

The distance between two adjacent cells is 1.

 

Example 1:


Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
Output: [[0,0,0],[0,1,0],[0,0,0]]
Example 2:


Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
Output: [[0,0,0],[0,1,0],[1,2,1]]
 

Constraints:

m == mat.length
n == mat[i].length
1 <= m, n <= 104
1 <= m * n <= 104
mat[i][j] is either 0 or 1.
There is at least one 0 in mat.
*/

// BFS from all zeros
// time complexity: O(M*N)
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        const int M = mat.size();
        const int N = mat[0].size();
        const vector<pair<int,int>> DIR = {{0,1},{0,-1},{1,0},{-1,0}};
        
        // BFS starting from all zeros
        vector<vector<int>> ans = mat;
        queue<pair<int,int>> q;
        for(int i=0; i<M; ++i)
            for(int j=0; j<N; ++j)
                if(mat[i][j] == 0)
                    q.push({i,j});
        int steps = 0;
        while(!q.empty()) {
            ++steps;
            int sz = q.size();
            while(sz--) {
                int i = q.front().first;
                int j = q.front().second;
                q.pop();
                for(auto &d : DIR) {
                    int ni = i + d.first;
                    int nj = j + d.second;
                    if(ni<0 || ni>=M || nj<0 || nj>=N || mat[ni][nj]==0/*already visited yet*/)
                        continue;
                    q.push({ni,nj});
                    mat[ni][nj] = 0;  // mark as visited
                    ans[ni][nj] = steps;
                }
            }
        }
        
        return ans;
    }
};


// BFS impl 2: we actually do not need to keep track of current level, as it is already captured in ans
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        const int M = mat.size();
        const int N = mat[0].size();
        const vector<pair<int,int>> DIR = {{0,1},{0,-1},{1,0},{-1,0}};
        
        // BFS starting from all zeros
        vector<vector<int>> ans = mat;
        queue<pair<int,int>> q;
        for(int i=0; i<M; ++i)
            for(int j=0; j<N; ++j)
                if(mat[i][j] == 0)
                    q.push({i,j});
        while(!q.empty()) {
            int i = q.front().first;
            int j = q.front().second;
            q.pop();
            for(auto &d : DIR) {
                int ni = i + d.first;
                int nj = j + d.second;
                if(ni<0 || ni>=M || nj<0 || nj>=N || mat[ni][nj]==0/*already visited yet*/)
                    continue;
                q.push({ni,nj});
                mat[ni][nj] = 0;  // mark as visited
                ans[ni][nj] = ans[i][j] + 1;
            }
        }
        
        return ans;
    }
};


// DP
// time complexity: O(M*N)
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        const int M = mat.size();
        const int N = mat[0].size();
        
        // DP: dp(i,j) as the min distance from 0 of grid (i,j)
        // since the shortest path can come from all four directions, we need to iterations
        // -- in first iteration, we update path from top and left
        // -- in second iteration, we update path from bottom and right
        // -- since there is no obstacle, the shortest path is always matthan distance; in other words, the above
        //    two iterations can be proved to be correct
        vector<vector<int>> dp = mat;

        // iteration 1: from top and left path
        for(int i=0; i<M; ++i) {
            for(int j=0; j<N; ++j) {
                if(mat[i][j] == 1)
                    dp[i][j] = INT_MAX/2;  // init val
                
                if(i>0)
                    dp[i][j] = min(dp[i][j], dp[i-1][j]+1);
                if(j>0)
                    dp[i][j] = min(dp[i][j], dp[i][j-1]+1);
            }
        }
        
        // iteration 2: from bottom and right path
        for(int i=M-1; i>=0; --i) {
            for(int j=N-1; j>=0; --j) {
                if(i<M-1)
                    dp[i][j] = min(dp[i][j], dp[i+1][j]+1);
                if(j<N-1)
                    dp[i][j] = min(dp[i][j], dp[i][j+1]+1);
            }
        }
        
        return dp;
    }
};


// brute-force
// for each 1-grid, short path is the min matthan distance between it and all 0-grid
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        if (rows == 0)
            return matrix;
        int cols = matrix[0].size();
        vector<vector<int>> dist(rows, vector<int> (cols, INT_MAX));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == 0) {
                    dist[i][j] = 0;
                } else {
                    for (int k = 0; k < rows; k++) {
                        for (int l = 0; l < cols; l++) {
                            if (matrix[k][l] == 0) {
                                int dist_01 = abs(k - i) + abs(l - j);
                                dist[i][j] = min(dist[i][j], abs(k - i) + abs(l - j));
                            }
                        }
                    }
                }
            }
        }
        return dist;
    }
};
