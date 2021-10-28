/*
The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.

 

Example 1:


Input: n = 4
Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above
Example 2:

Input: n = 1
Output: [["Q"]]
 

Constraints:

1 <= n <= 9
*/

// DFS: try to assign one queen each row
// time complexity: O(N!)
// space complexity: O(N)
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        _col = vector<int>(n, 0);
        _diag1 = vector<int>(2*n-1, 0);
        _diag2 = vector<int>(2*n-1, 0);
        
        // DFS
        vector<string> board(n, string(n,'.'));
        vector<vector<string>> ans;
        dfs(n, board, 0, ans);
        return ans;
    }
    
private:
    vector<int> _col;
    vector<int> _diag1;  // 45 degree diagonal
    vector<int> _diag2;  // -45 degree diagonal
    
    // DFS: since we assign one quene eqch row, we don't need to track row conflicts
    void dfs(const int N, vector<string> &board, int r/*current row*/, vector<vector<string>> &ans) {
        if(r == N) {
            ans.push_back(board);
            return;
        }
        
        for(int c=0; c<N; ++c) {
            if(_col[c] || _diag1[r+c] || _diag2[N-1-c+r])
                continue;
            
            board[r][c] = 'Q';
            _col[c] = 1;
            _diag1[r+c] = 1;
            _diag2[N-1-c+r] = 1;
            dfs(N, board, r+1, ans);
            board[r][c] = '.';
            _col[c] = 0;
            _diag1[r+c] = 0;
            _diag2[N-1-c+r] = 0;
        }
    }
};
