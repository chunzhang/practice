/*
The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.

Given an integer n, return the number of distinct solutions to the n-queens puzzle.

 

Example 1:


Input: n = 4
Output: 2
Explanation: There are two distinct solutions to the 4-queens puzzle as shown.
Example 2:

Input: n = 1
Output: 1
 

Constraints:

1 <= n <= 9
*/

// DFS: try assign one queen each row
// time complexity: O(N!)
// space complexity: O(N)
class Solution {
public:
    int totalNQueens(int n) {
        _col = vector<int>(n, 0);
        _diag1 = vector<int>(2*n-1, 0);
        _diag2 = vector<int>(2*n-1, 0);
        
        // DFS
        int ans = 0;
        dfs(n, 0, ans);
        return ans;
    }
    
private:
    vector<int> _col;
    vector<int> _diag1;  // 45 degree diagonal
    vector<int> _diag2;  // -45 degree diagonal
    
    // DFS: since we assign one quene eqch row, we don't need to track row conflicts
    void dfs(const int N, int r/*current row*/, int &ans) {
        if(r == N) {
            ++ans;
            return;
        }
        
        for(int c=0; c<N; ++c) {
            if(_col[c] || _diag1[r+c] || _diag2[N-1-c+r])
                continue;
            
            _col[c] = 1;
            _diag1[r+c] = 1;
            _diag2[N-1-c+r] = 1;
            dfs(N, r+1, ans);
            _col[c] = 0;
            _diag1[r+c] = 0;
            _diag2[N-1-c+r] = 0;
        }
    }
};
