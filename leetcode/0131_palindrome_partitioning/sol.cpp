/*
Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.

A palindrome string is a string that reads the same backward as forward.

 

Example 1:

Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]
Example 2:

Input: s = "a"
Output: [["a"]]
 

Constraints:

1 <= s.length <= 16
s contains only lowercase English letters.

*/

// DFS solution
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> part;
        dfs(s, 0, res, part);
        return res;
    }
    
private:
    void dfs(const string &s, int cur, vector<vector<string>> &res, vector<string> &part) {
        if(cur == s.size()) {    // find solution
            res.push_back(part);
            return;
        }
        
        for(int len=1; cur+len<=s.size(); ++len) {
            string sub = s.substr(cur, len);
            if(isPalindrome(sub)) {
                part.push_back(sub);
                dfs(s, cur+len, res, part);
                part.pop_back();
            }
        }
    }
    
    bool isPalindrome(const string &s) {
        int i = 0;
        int j = s.size() - 1;
        while(i<=j) {
            if(s[i++]!=s[j--])
                return false;
        }
        return true;
    }
};


// DP with memoization
class Solution {
public:
    vector<vector<string>> partition(string s) {
        // DP with memoization
        // dp(i): all palindrome partitioning of s[0:i), so final result is dp(N)
        const int N = s.size();
        vector<vector<vector<string>>> dp(N+1);
        vector<int> mem(N+1, 0);  // whether this has been computed already
        dp[0].push_back(vector<string>());  // padding element
        mem[0] = 1;
        dpByMem(dp, mem, s, N);
        return dp[N];
    }
    
private:
    void dpByMem(vector<vector<vector<string>>> &dp, vector<int> &mem, const string &s, int cur) {
        if(mem[cur])  // computed already
            return;
        
        for(int i=0; i<cur; ++i) {
            string sub = s.substr(i, cur-i);  // s[i,cur)
            if(!isPalindrome(s, i, cur))
                continue;
            dpByMem(dp, mem, s, i);
            const vector<vector<string>> &parts = dp[i];
            for(vector<string> p : parts) {
                p.push_back(sub);
                dp[cur].push_back(p);
            }
        }
        
        mem[cur] = 1;
    }
    
    // [start, end) range
    bool isPalindrome(const string &s, int start, int end) {
        int i=start;
        int j = end-1;
        while(i<=j) {
            if(s[i++]!=s[j--])
                return false;
        }
        return true;
    }
};


// DP bottom up
class Solution {
public:
    vector<vector<string>> partition(string s) {
        // DP with memoization
        // dp(i): all palindrome partitioning of s[0:i), so final result is dp(N)
        const int N = s.size();
        vector<vector<vector<string>>> dp(N+1);
        vector<int> mem(N+1, 0);  // whether this has been computed already
        dp[0].push_back(vector<string>());  // padding element
        mem[0] = 1;
        
        for(int j=0; j<=N; ++j) {  // for computing dp(j)
            for(int i=0; i<j; ++i) {
                string sub = s.substr(i, j-i);  // s[i,j)
                if(!isPalindrome(s,i,j))
                    continue;
                for(vector<string> p : dp[i]) {
                    p.push_back(sub);
                    dp[j].push_back(p);
                }
            }
        }
                
        return dp[N];
    }
    
private:
    // [start, end) range
    bool isPalindrome(const string &s, int start, int end) {
        int i=start;
        int j = end-1;
        while(i<=j) {
            if(s[i++]!=s[j--])
                return false;
        }
        return true;
    }
};
