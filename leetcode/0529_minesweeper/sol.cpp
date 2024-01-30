/*
Facebook/Uber/Docusign/Amazon/Microsoft/LiveRamp/Bloomberg

Let's play the minesweeper game (Wikipedia, online game)!

You are given an m x n char matrix board representing the game board where:

'M' represents an unrevealed mine,
'E' represents an unrevealed empty square,
'B' represents a revealed blank square that has no adjacent mines (i.e., above, below, left, right, and all 4 diagonals),
digit ('1' to '8') represents how many mines are adjacent to this revealed square, and
'X' represents a revealed mine.
You are also given an integer array click where click = [clickr, clickc] represents the next click position among all the unrevealed squares ('M' or 'E').

Return the board after revealing this position according to the following rules:

If a mine 'M' is revealed, then the game is over. You should change it to 'X'.
If an empty square 'E' with no adjacent mines is revealed, then change it to a revealed blank 'B' and all of its adjacent unrevealed squares should be revealed recursively.
If an empty square 'E' with at least one adjacent mine is revealed, then change it to a digit ('1' to '8') representing the number of adjacent mines.
Return the board when no more squares will be revealed.
 

Example 1:


Input: board = [["E","E","E","E","E"],["E","E","M","E","E"],["E","E","E","E","E"],["E","E","E","E","E"]], click = [3,0]
Output: [["B","1","E","1","B"],["B","1","M","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]]
Example 2:


Input: board = [["B","1","E","1","B"],["B","1","M","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]], click = [1,2]
Output: [["B","1","E","1","B"],["B","1","X","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]]
 

Constraints:

m == board.length
n == board[i].length
1 <= m, n <= 50
board[i][j] is either 'M', 'E', 'B', or a digit from '1' to '8'.
click.length == 2
0 <= clickr < m
0 <= clickc < n
board[clickr][clickc] is either 'M' or 'E'.
*/

// BFS
// rule: recursively “click” adjacent grids IF AND ONLY IF current grid has no adjacent mines
class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        vector<pair<int,int>> dir = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
        const int M = board.size();
        const int N = board[0].size();
        // BFS
        queue<pair<int,int>> q;  // contains only unrevealed grid
        q.emplace(click[0],click[1]);
        while(!q.empty()) {
            int i = q.front().first;
            int j = q.front().second;
            q.pop();
            if(board[i][j] == 'M') {  // rule 1
                board[i][j] = 'X';
                break;
            }

            vector<pair<int,int>> next;
            int nMines = 0;
            for(auto &d : dir) {
                int ni = i + d.first;
                int nj = j + d.second;
                if(ni<0 || ni>=M || nj<0 || nj>=N)
                    continue;
                if(board[ni][nj]=='M')
                    ++nMines;
                if(board[ni][nj] == 'E') {
                    board[ni][nj] = 'e';  // mark as visited
                    next.emplace_back(ni,nj);
                }
            }
            board[i][j] = nMines ? (nMines+'0') : 'B';  // rule 2 and 3
            for(auto &n : next)
                if(!nMines)  // based on rule 2, recursion on all adjacent unrevealed grid
                    q.push(n);
                else
                    board[n.first][n.second] = 'E';  // based on rule 3, no recursion -- unset visited flag
        }

        return board;
    }
};

// ref DFS sol
class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        if (board[click[0]][click[1]] == 'M') {
            board[click[0]][click[1]] = 'X';
            return board;
        }

        dfs(board, click[0], click[1]);
        return board;
    }
    
    void dfs(vector<vector<char>>& board, int i, int j) {
        if (i < 0 || i == board.size() || j < 0 || j == board[0].size())
            return;
        if (board[i][j] != 'E')
            return;
        
        const int minesCount = getMinesCount(board, i, j);
        board[i][j] = minesCount == 0 ? 'B' : '0' + minesCount;
        
        if (minesCount == 0)
            for (int r=-1;r<=1;r++){
                for(int c=-1;c<=1;c++){
                    dfs(board, i +r , j + c);
                }
            }    
    }
    
    int getMinesCount(const vector<vector<char>>& board, int i, int j) {
        int minesCount = 0;
        for (int r=-1;r<=1;r++){
            for(int c=-1;c<=1;c++){
                const int x = i + r;
                const int y = j + c;
                if (x < 0 || x == board.size() || y < 0 || y == board[0].size())
                    continue;
                if (board[x][y] == 'M')
                    ++minesCount;
            }
        }
        return minesCount;
    }
};
