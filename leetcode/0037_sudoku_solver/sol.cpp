/*
Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:

Each of the digits 1-9 must occur exactly once in each row.
Each of the digits 1-9 must occur exactly once in each column.
Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
The '.' character indicates empty cells.

 

Example 1:


Input: board = [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]
Output: [["5","3","4","6","7","8","9","1","2"],["6","7","2","1","9","5","3","4","8"],["1","9","8","3","4","2","5","6","7"],["8","5","9","7","6","1","4","2","3"],["4","2","6","8","5","3","7","9","1"],["7","1","3","9","2","4","8","5","6"],["9","6","1","5","3","7","2","8","4"],["2","8","7","4","1","9","6","3","5"],["3","4","5","2","8","6","1","7","9"]]
Explanation: The input board is shown above and the only valid solution is shown below:


 

Constraints:

board.length == 9
board[i].length == 9
board[i][j] is a digit or '.'.
It is guaranteed that the input board has only one solution.
*/

// DFS: try to fill each empty grid one by one
// time complexity: O((9!)^9), loose bound O(9^81)
// space complexity: O(81), i.e., constant
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        memset(_row, 0, sizeof(_row));
        memset(_col, 0, sizeof(_col));
        memset(_sub, 0, sizeof(_sub));
        
        for(int i=0; i<9; ++i) {
            for(int j=0; j<9; ++j) {
                if(board[i][j] !='.') {
                    int num = board[i][j] - '0';
                    _row[i][num] = 1;
                    _col[j][num] = 1;
                    _sub[i/3][j/3][num] = 1;
                }
            }
        }
        
        // DFS
        dfs(board, 0);
    }
    
private:
    int _row[9][10];
    int _col[9][10];
    int _sub[3][3][10];
    
    bool dfs(vector<vector<char>> &board, int cur/*index of current grid to be filled, represented in 1-D*/) {
        if(cur == 81)  // all elements filled
            return true;
        
        int i = cur/9;
        int j = cur%9;
        if(board[i][j] != '.')
            return dfs(board, cur+1);
        
        int subi = i/3;
        int subj = j/3;
        for(int num=1; num<=9; ++num) {
            if(_row[i][num] || _col[j][num] || _sub[subi][subj][num])  // the number is already used
                continue;
                    
            board[i][j] = '0'+num;
            _row[i][num] = 1;
            _col[j][num] = 1;
            _sub[subi][subj][num] = 1;
            if(dfs(board, cur+1))
                return true;
            board[i][j] = '.';
            _row[i][num] = 0;
            _col[j][num] = 0;
            _sub[subi][subj][num] = 0;
        }
        
        return false;  // no solution found
    }
};
