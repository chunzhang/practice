/*
You are playing a variation of the game Zuma.

In this variation of Zuma, there is a single row of colored balls on a board, where each ball can be colored red 'R', yellow 'Y', blue 'B', green 'G', or white 'W'. You also have several colored balls in your hand.

Your goal is to clear all of the balls from the board. On each turn:

Pick any ball from your hand and insert it in between two balls in the row or on either end of the row.
If there is a group of three or more consecutive balls of the same color, remove the group of balls from the board.
If this removal causes more groups of three or more of the same color to form, then continue removing each group until there are none left.
If there are no more balls on the board, then you win the game.
Repeat this process until you either win or do not have any more balls in your hand.
Given a string board, representing the row of balls on the board, and a string hand, representing the balls in your hand, return the minimum number of balls you have to insert to clear all the balls from the board. If you cannot clear all the balls from the board using the balls in your hand, return -1.

 

Example 1:

Input: board = "WRRBBW", hand = "RB"
Output: -1
Explanation: It is impossible to clear all the balls. The best you can do is:
- Insert 'R' so the board becomes WRRRBBW. WRRRBBW -> WBBW.
- Insert 'B' so the board becomes WBBBW. WBBBW -> WW.
There are still balls remaining on the board, and you are out of balls to insert.
Example 2:

Input: board = "WWRRBBWW", hand = "WRBRW"
Output: 2
Explanation: To make the board empty:
- Insert 'R' so the board becomes WWRRRBBWW. WWRRRBBWW -> WWBBWW.
- Insert 'B' so the board becomes WWBBBWW. WWBBBWW -> WWWW -> empty.
2 balls from your hand were needed to clear the board.
Example 3:

Input: board = "G", hand = "GGGGG"
Output: 2
Explanation: To make the board empty:
- Insert 'G' so the board becomes GG.
- Insert 'G' so the board becomes GGG. GGG -> empty.
2 balls from your hand were needed to clear the board.
Example 4:

Input: board = "RBYYBBRRB", hand = "YRBGB"
Output: 3
Explanation: To make the board empty:
- Insert 'Y' so the board becomes RBYYYBBRRB. RBYYYBBRRB -> RBBBRRB -> RRRB -> B.
- Insert 'B' so the board becomes BB.
- Insert 'B' so the board becomes BBB. BBB -> empty.
3 balls from your hand were needed to clear the board.
 

Constraints:

1 <= board.length <= 16
1 <= hand.length <= 5
board and hand consist of the characters 'R', 'Y', 'B', 'G', and 'W'.
The initial row of balls on the board will not have any groups of three or more consecutive balls of the same color.
*/


// DFS -- have to use pruning and memoization to avoid TLE
lass Solution {
public:
    int findMinStep(string board, string hand) {
        return dfs(board, hand);
    }
    
private:
    unordered_map<string, int> _mem;

    // O((m+n)^n) time complexity, m is size of board, n is size of hand
    // think about all possible ways to insert balls, which is C(m+n, n)
    int dfs(const string &board, const string &hand) {
        if(board.empty())
            return 0;
        if(hand.empty())
            return -1;
        
        string key = board + "_" + hand;
        auto it = _mem.find(key);  // Without memoization, it will TLE
        if(it != _mem.end())
            return it->second;
        
        int tried[128];  // whether a color has been tried
        memset(tried, 0, sizeof(tried));
        
        int ans = INT_MAX;
        for(int i=0; i<hand.size(); ++i) {
            char ball = hand[i];
            if(tried[ball])  // no need to try ball of same color again
                continue;
            tried[ball] = 1;
            string nextHand = hand.substr(0,i) + hand.substr(i+1);
            for(int k=0; k<=board.size(); ++k) {
                // important pruning: we don't want to insert 'R' in the middle of 'RR'
                // -- however, we do need to insert the ball 'R' into 'WW' ==> 'WRW'
                // -- think about this example: board="RRWWRRBBRR", hand="WB", we need to do following:
                // ---- RRWWRRBBRR -> RRWWRRBBR[W]R -> RRWWRRBB[B]R[W]R 
                if(k<board.size() && board[k]==ball)
                    continue;
               
                string nextBoard = newBoard(board, ball, k);
                int subAns = dfs(nextBoard, nextHand);
                if(subAns != -1)
                    ans = min(ans, subAns+1);
            }
        }
        
        if(ans == INT_MAX)
            ans = -1;
        _mem[key] = ans;
        
        return ans;
    }
    
    // new board after insert ball at k
    // idea is to expand the to-be-deleted string from k to the left and to the right
    // O(m) time complexity, where m is the size of board
    string newBoard(const string &board, char ball, int k) {
        string bd = board.substr(0,k) + ball + board.substr(k);
        int i = k-1;
        int j = k;
        while(i>=0 && j<bd.size()) {
            if(bd[i] != bd[j])
                break;
            char curBall = bd[i];
            int left = 0;
            while(i>0 && bd[i-1]==curBall) {  // expand to the left
                --i;
                ++left;
            }
            int right = 0;
            while(j<bd.size()-1 && bd[j+1]==curBall) {  // expand to the right
                ++j;
                ++right;
            }
            
            if(left+right >= 1) {  // collapse only when there're three balls, including i and j
                --i;
                ++j;
            }
            else {
                // left==right==0
                break;
            }
        }
        
        bd = bd.substr(0,i+1) + bd.substr(j);  // everything between (i,j) are collapsed
        return bd;
    }
};


// HuaHua's solution
// -- it is incorrect for board="RRWWRRBBRR", hand="WB" case, but is still a good reference in terms of code implementation
class Solution {
public:
    int findMinStep(string board, string hand) {
        vector<int> h(128, 0);
        for (char color : hand) ++h[color];
        return dfs(board, h);
    }
private:
    // Return the min # of balls needed in hand to clear the board.
    // Returns -1 if not possible.
    int dfs(const string& board, vector<int>& hand) {        
        if (board.empty()) return 0;
        
        int ans = INT_MAX;
        int i = 0;
        int j = 0;
        while (i < board.size()) {
            while (j < board.size() && board[i] == board[j]) ++j;            
            // board[i] ~ board[j - 1] have the same color
            const char color = board[i];
            // Number of balls needed to clear board[i] ~ board[j - 1]
            const int b = 3 - (j - i);
            // Have sufficient balls in hand
            if (hand[color] >= b) {
                // Remove board[i] ~ board[j - 1] and update the board
                string nb = update(board.substr(0, i) + board.substr(j));
                // Find the solution on new board with updated hand
                hand[color] -= b;
                int r = dfs(nb, hand);
                if (r >= 0) ans = min(ans, r + b);
                // Recover the balls in hand
                hand[color] += b;
            }
            i = j;
        }
        return ans == INT_MAX ? -1 : ans;
    }
    
    // Update the board by removing all consecutive 3+ balls.
    // "YWWRRRWWYY" -> "YWWWWYY" -> "YYY" -> ""
    string update(string board) {        
        int i = 0;            
        while (i < board.size()) {
            int j = i;
            while (j < board.size() && board[i] == board[j]) ++j;
            if (j - i >= 3) {
                board = board.substr(0, i) + board.substr(j);
                i = 0;
            } else {
                ++i;
            }
        }
        return board;
    }
};
