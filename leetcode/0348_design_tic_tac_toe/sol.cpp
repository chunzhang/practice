/*
Facebook/Databricks/Amazon

Assume the following rules are for the tic-tac-toe game on an n x n board between two players:

A move is guaranteed to be valid and is placed on an empty block.
Once a winning condition is reached, no more moves are allowed.
A player who succeeds in placing n of their marks in a horizontal, vertical, or diagonal row wins the game.
Implement the TicTacToe class:

TicTacToe(int n) Initializes the object the size of the board n.
int move(int row, int col, int player) Indicates that the player with id player plays at the cell (row, col) of the board. The move is guaranteed to be a valid move, and the two players alternate in making moves. Return
0 if there is no winner after the move,
1 if player 1 is the winner after the move, or
2 if player 2 is the winner after the move.
 

Example 1:

Input
["TicTacToe", "move", "move", "move", "move", "move", "move", "move"]
[[3], [0, 0, 1], [0, 2, 2], [2, 2, 1], [1, 1, 2], [2, 0, 1], [1, 0, 2], [2, 1, 1]]
Output
[null, 0, 0, 0, 0, 0, 0, 1]

Explanation
TicTacToe ticTacToe = new TicTacToe(3);
Assume that player 1 is "X" and player 2 is "O" in the board.
ticTacToe.move(0, 0, 1); // return 0 (no one wins)
|X| | |
| | | |    // Player 1 makes a move at (0, 0).
| | | |

ticTacToe.move(0, 2, 2); // return 0 (no one wins)
|X| |O|
| | | |    // Player 2 makes a move at (0, 2).
| | | |

ticTacToe.move(2, 2, 1); // return 0 (no one wins)
|X| |O|
| | | |    // Player 1 makes a move at (2, 2).
| | |X|

ticTacToe.move(1, 1, 2); // return 0 (no one wins)
|X| |O|
| |O| |    // Player 2 makes a move at (1, 1).
| | |X|

ticTacToe.move(2, 0, 1); // return 0 (no one wins)
|X| |O|
| |O| |    // Player 1 makes a move at (2, 0).
|X| |X|

ticTacToe.move(1, 0, 2); // return 0 (no one wins)
|X| |O|
|O|O| |    // Player 2 makes a move at (1, 0).
|X| |X|

ticTacToe.move(2, 1, 1); // return 1 (player 1 wins)
|X| |O|
|O|O| |    // Player 1 makes a move at (2, 1).
|X|X|X|
 

Constraints:

2 <= n <= 100
player is 1 or 2.
0 <= row, col < n
(row, col) are unique for each different call to move.
At most n2 calls will be made to move.
 

Follow-up: Could you do better than O(n2) per move() operation?
*/

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe* obj = new TicTacToe(n);
 * int param_1 = obj->move(row,col,player);
 */

// keep track of placed block from each player on each row/col/+45 and -45 diagonal
class TicTacToe {
public:
    TicTacToe(int n) : N(n), _counts(2*N+2, vector<int>(2,0)) {
        
    }
    
    int move(int row, int col, int player) {
        if(++_counts[row][player-1] == N)  // row
            return player;

        if(++_counts[N+col][player-1] == N)  // col
            return player;

        if(row==col && ++_counts[2*N][player-1] == N)  // -45 degree diagonal
            return player;

        if(row+col==N-1 && ++_counts[2*N+1][player-1] == N)  // +45 degree diagonal
            return player;

        return 0;
    }

private:
    const int N;  // board size
    vector<vector<int>> _counts;  // for each row/col/diagonal, how many block each player has put on it
};


// this solution can return -1 if no more player can win any more
class TicTacToe {
public:
    TicTacToe(int n) : N(n), _counts(2*N+2, vector<int>(2,0)), _blocked(0){
        
    }
    
    int move(int row, int col, int player) {
        if(mark(row,player))  // row
            return player;

        if(mark(N+col,player))  // col
            return player;

        if(i==j && mark(2*N,player))  // -45 degree diagonal
            return player;

        if(i+j==N-1 && mark(2*N+1,player))  // +45 degree diagonal
            return player;

        if(_blocked == _counts.size())
            return -1;

        return 0;
    }

private:
    const int N;  // board size
    vector<vector<int>> _counts;  // for each row/col/diagonal, how many block each player has put on it
    int _blocked;  // number of blocked row/col/diagonal

    bool mark(int idx, int player) {
        int curPlayer = player - 1;
        int otherPlayer = curPlayer^0x1;
        ++_counts[idx][curPlayer];
        if(counts[idx][otherPlayer])
            ++_blocked;
        return _counts[idx][curPlayer]==N;
    }
};

