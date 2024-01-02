/*
Facebook/DoorDash/Apple

Given an m x n integers matrix, return the length of the longest increasing path in matrix.

From each cell, you can either move in four directions: left, right, up, or down. You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed).

 

Example 1:


Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
Output: 4
Explanation: The longest increasing path is [1, 2, 6, 9].
Example 2:


Input: matrix = [[3,4,5],[3,2,6],[2,2,1]]
Output: 4
Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
Example 3:

Input: matrix = [[1]]
Output: 1
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
0 <= matrix[i][j] <= 2^31 - 1
*/


// top-down DP with memoization
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        // top-down DP with memoization (this works as the path is directed to be strictly increasing)
        // dp(i,j): longest path that ends at (i,j)
        M = matrix.size();
        N = matrix[0].size();
        vector<vector<int>> dp(M, vector<int>(N,-1));

        int ans = INT_MIN;
        for(int i=0; i<M; ++i) {
            for(int j=0; j<N; ++j) {
                dp[i][j] = dfs(matrix, dp, i, j);
                ans = max(ans, dp[i][j]);
            }
        }

        return ans;
    }

private:
    int dfs(const vector<vector<int>> &matrix, vector<vector<int>> &dp, int i, int j) {
        if(dp[i][j] != -1)
            return dp[i][j];

        dp[i][j] = 1;
        for(auto &d : m_dir) {
            int ni = i + d.first;
            int nj = j + d.second;
            if(ni>=0 && ni<M && nj>=0 && nj<N && matrix[i][j]>matrix[ni][nj])
                dp[i][j] = max(dp[i][j], dfs(matrix,dp,ni,nj)+1);
        }
        return dp[i][j];
    }

private:
    const vector<pair<int,int>> m_dir = {{0,1},{0,-1},{1,0},{-1,0}};
    int M;
    int N;
};


// bottom-up DP: order is the topo-sort the for DAG with strictly increasing path
// ref solution (Java)
// Topological Sort Based Solution
// An Alternative Solution
public class Solution {
    private static final int[][] dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    private int m, n;
    public int longestIncreasingPath(int[][] grid) {
        int m = grid.length;
        if (m == 0) return 0;
        int n = grid[0].length;
        // padding the matrix with zero as boundaries
        // assuming all positive integer, otherwise use INT_MIN as boundaries
        int[][] matrix = new int[m + 2][n + 2];
        for (int i = 0; i < m; ++i)
            System.arraycopy(grid[i], 0, matrix[i + 1], 1, n);

        // calculate outdegrees
        int[][] outdegree = new int[m + 2][n + 2];
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= n; ++j)
                for (int[] d: dir)
                    if (matrix[i][j] < matrix[i + d[0]][j + d[1]])
                        outdegree[i][j]++;

        // find leaves who have zero out degree as the initial level
        n += 2;
        m += 2;
        List<int[]> leaves = new ArrayList<>();
        for (int i = 1; i < m - 1; ++i)
            for (int j = 1; j < n - 1; ++j)
                if (outdegree[i][j] == 0) leaves.add(new int[]{i, j});

        // remove leaves level by level in topological order
        int height = 0;
        while (!leaves.isEmpty()) {
            height++;
            List<int[]> newLeaves = new ArrayList<>();
            for (int[] node : leaves) {
                for (int[] d:dir) {
                    int x = node[0] + d[0], y = node[1] + d[1];
                    if (matrix[node[0]][node[1]] > matrix[x][y])
                        if (--outdegree[x][y] == 0)
                            newLeaves.add(new int[]{x, y});
                }
            }
            leaves = newLeaves;
        }
        return height;
    }
}
