/*
Given an m x n grid of characters board and a string word, return true if word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.

 

Example 1:


Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true
Example 2:


Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true
Example 3:


Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false
 

Constraints:

m == board.length
n = board[i].length
1 <= m, n <= 6
1 <= word.length <= 15
board and word consists of only lowercase and uppercase English letters.
 

Follow up: Could you use search pruning to make your solution faster with a larger board?
*/


// DFS
// time complexity: O(N*(4*3^(L-1))), where N is the number of grids and L is the length of words
// -- Starting grid has four searching direction, and rest have three
// space complexity: O(L), i.e., reuse input board as visited mark
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        _M = board.size();
        _N = board[0].size();
        for(int i=0; i<_M; ++i)
            for(int j=0; j<_N; ++j)
                if(dfs(board, word, 0, i, j))
                    return true;
        return false;
    }
    
private:
    const vector<pair<int,int>> DIR = {{0,1},{0,-1},{1,0},{-1,0}};
    int _M;
    int _N;

    // reuse input board as visited mark
    bool dfs(vector<vector<char>> &board, const string &word, int cur, int i, int j) {
        if(board[i][j] != word[cur])
            return false;
        if(cur == word.size()-1)
            return true;
        
        char c = board[i][j];
        board[i][j] = 1;  // mark as visited
        for(auto &d : DIR) {
            int ni = i + d.first;
            int nj = j + d.second;
            if(ni<0 || ni>=_M || nj<0 || nj>=_N || board[ni][nj]==1/*0 means it is already used*/)
                continue;
            if(dfs(board, word, cur+1, ni, nj))
                return true;
        }
        board[i][j] = c;  // unset visited mark
        return false;
    }
};


// Brute-force: search each word one by one using solution from 0079 -- Word Search, TLE
class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        _M = board.size();
        _N = board[0].size();
        
        vector<string> ans;
        for(string &word : words)
            if(exist(board, word))
                ans.emplace_back(word);
        
        return ans;
    }
    
private:
    const vector<pair<int,int>> DIR = {{0,1},{0,-1},{1,0},{-1,0}};
    int _M;
    int _N;
    
    bool exist(vector<vector<char>>& board, string &word) {
        for(int i=0; i<_M; ++i)
            for(int j=0; j<_N; ++j)
                if(dfs(board, word, 0, i, j))
                    return true;
        return false;
    }
    
    bool dfs(vector<vector<char>> &board, const string &word, int cur, int i, int j) {
        if(board[i][j] != word[cur])
            return false;
        if(cur == word.size()-1)
            return true;
        
        char c = board[i][j];
        board[i][j] = 1;  // set visited mark
        bool found = false;
        for(auto &d : DIR) {
            int ni = i + d.first;
            int nj = j + d.second;
            if(ni<0 || ni>=_M || nj<0 || nj>=_N || board[ni][nj]==1/*0 means it is already used*/)
                continue;
            found = dfs(board, word, cur+1, ni, nj);
            if(found)  // do not early return here -- we need to reset the board[i][j] for next word search
                break;
        }
        board[i][j] = c;
        return found;
    }
};
