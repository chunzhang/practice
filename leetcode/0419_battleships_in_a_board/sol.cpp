/*
Facebook/Tinkoff/Microsoft/Google
  
Given an m x n matrix board where each cell is a battleship 'X' or empty '.', return the number of the battleships on board.

Battleships can only be placed horizontally or vertically on board. In other words, they can only be made of the shape 1 x k (1 row, k columns) or k x 1 (k rows, 1 column), where k can be of any size. At least one horizontal or vertical cell separates between two battleships (i.e., there are no adjacent battleships).

Example 1:


Input: board = [["X",".",".","X"],[".",".",".","X"],[".",".",".","X"]]
Output: 2

Example 2:

Input: board = [["."]]
Output: 0
 

Constraints:

m == board.length
n == board[i].length
1 <= m, n <= 200
board[i][j] is either '.' or 'X'.
*/

// simplified BFS
// time: O(M*N)
// space: O(1) but needs to modify original board
class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        int ans = 0;
        const int M = board.size();
        const int N = board[0].size();
        for(int i=0; i<M; ++i) {
            for(int j=0; j<N; ++j) {
                if(board[i][j] == '.')
                    continue;
                // find battleship start
                ++ans;
                for(int jj=j+1; jj<N&&board[i][jj]=='X'; ++jj)
                    board[i][jj] = '.';
                for(int ii=i+1; ii<M&&board[ii][j]=='X'; ++ii)
                    board[ii][j] = '.';
            }
        }

        return ans;
    }
};


// better solution: only count battleship head (i.e., either top->down or left->right)
// time: O(M*N)
// space: O(1) and no need to modify original board
class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        int ans = 0;
        const int M = board.size();
        const int N = board[0].size();
        for(int i=0; i<M; ++i) {
            for(int j=0; j<N; ++j) {
                if(board[i][j] == '.')
                    continue;
                if(i>0 && board[i-1][j]=='X')  // already counted top->down
                    continue;
                if(j>0 && board[i][j-1]=='X')  // already counted left->right
                    continue;
                ++ans;
            }
        }

        return ans;
    }
};
