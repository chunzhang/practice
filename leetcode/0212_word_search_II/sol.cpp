/*
Given an m x n board of characters and a list of strings words, return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

 

Example 1:


Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]
Example 2:


Input: board = [["a","b"],["c","d"]], words = ["abcb"]
Output: []
 

Constraints:

m == board.length
n == board[i].length
1 <= m, n <= 12
board[i][j] is a lowercase English letter.
1 <= words.length <= 3 * 104
1 <= words[i].length <= 10
words[i] consists of lowercase English letters.
All the strings of words are unique.
*/


// DFS with trie -- a more concise impl
// time complexity: O(N*(4*3^(L-1))), where N is the number of grids and L is the max length of all words
// -- starting grid has four searching direction, and rest have three
// space complexity: O(M), where M is totoal number of letters of all words, i.e., number of TrieNode
struct TrieNode {
    vector<TrieNode*> children;
    const char *word;  // sentinal of end of a word, also points to that word

    TrieNode() : children(26), word(nullptr) {}  // for lower case letters only
    ~TrieNode() {
        for(TrieNode *child : children)
            delete child;
    }
};

struct Trie {
    TrieNode *root;  // dummy root
    
    Trie() : root(new TrieNode()) {}
    ~Trie() {
        delete root;
    }
    
    void add(const string &s) {
        TrieNode *cur = root;
        for(char c : s) {
            auto &next = cur->children[c-'a'];
            if(!next)
                next = new TrieNode();
            cur = next;
        }
        cur->word = s.c_str();  // mark as a word
    }
    
    bool find(const string &s) {
        TrieNode *cur = root;
        for(char c : s) {
            cur = cur->children[c-'a'];
            if(!cur)
                return false;
        }
        return cur->word!=nullptr;
    }
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        _M = board.size();
        _N = board[0].size();
        
        Trie trie;
        for(const string &s : words)
            trie.add(s);
        
        vector<string> ans;
        for(int i=0; i<_M; ++i)
            for(int j=0; j<_N; ++j)
                dfs(board, trie.root, i, j, ans);
        return ans;
    }
    
private:
    const vector<pair<int,int>> DIR = {{0,1},{0,-1},{1,0},{-1,0}};
    int _M;
    int _N;
    
    void dfs(vector<vector<char>> &board, TrieNode *node, int i, int j, vector<string> & ans) {
        char c = board[i][j];
        TrieNode *next = node->children[c-'a'];
        if(!next)
            return;
       
        board[i][j] = 1;  // mark visited
        if(next->word) {
            ans.emplace_back(next->word);
            next->word = nullptr;  // avoid duplicates
        }
        
        for(auto &d : DIR) {
            int ni = i + d.first;
            int nj = j + d.second;
            if(ni<0 || ni>=_M || nj<0 || nj>=_N || board[ni][nj]==1)
                continue;
            dfs(board, next, ni, nj, ans);
        }
        board[i][j] = c;
    }
};


// DFS with trie -- my initial impl
struct TrieNode {
    char c;
    unordered_map<char,TrieNode*> children;
    bool isEnd;

    TrieNode(char ch) : c(ch), isEnd(false) {}
};

struct Trie {
    TrieNode *root;  // dummy root
    
    Trie() : root(new TrieNode(0)) {}
    
    void add(const string &s) {
        TrieNode *cur = root;
        for(char c : s) {
            auto it = cur->children.find(c);
            if(it != cur->children.end()) {
                cur = it->second;
            }
            else {
                TrieNode *next = new TrieNode(c);
                cur->children[c] = next;
                cur = next;
            }
        }
        cur->isEnd = true;
    }
    
    bool find(const string &s) {
        TrieNode *cur = root;
        for(char c : s) {
            auto it = cur->children.find(c);
            if(it == cur->children.end())
                return false;
            cur = it->second;
        }
        return cur->isEnd;
    }
    

};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        _M = board.size();
        _N = board[0].size();
        
        Trie trie;
        for(const string &s : words)
            trie.add(s);
        
        unordered_set<string> ans;
        string cur;
        for(int i=0; i<_M; ++i)
            for(int j=0; j<_N; ++j)
                dfs(board, cur, trie.root, i, j, ans);
        return vector<string>(ans.begin(), ans.end());
    }
    
private:
    const vector<pair<int,int>> DIR = {{0,1},{0,-1},{1,0},{-1,0}};
    int _M;
    int _N;
    
    void dfs(vector<vector<char>> &board, string &cur, TrieNode *node, int i, int j, unordered_set<string> & ans) {
        char c = board[i][j];
        auto it = node->children.find(c);
        if(it == node->children.end())  // no such word exist
            return;
        
        cur.push_back(c);
        board[i][j] = 1;  // mark visited
        TrieNode *next = it->second;
        if(next->isEnd)
            ans.insert(cur);
        for(auto &d : DIR) {
            int ni = i + d.first;
            int nj = j + d.second;
            if(ni<0 || ni>=_M || nj<0 || nj>=_N || board[ni][nj]==1)
                continue;
            dfs(board, cur, next, ni, nj, ans);
        }
        cur.pop_back();
        board[i][j] = c;
    }
};
