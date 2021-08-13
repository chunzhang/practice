/*
Given two strings s and t, return the number of distinct subsequences of s which equals t.

A string's subsequence is a new string formed from the original string by deleting some (can be none) of the characters without disturbing the remaining characters' relative positions. (i.e., "ACE" is a subsequence of "ABCDE" while "AEC" is not).

It is guaranteed the answer fits on a 32-bit signed integer.

 

Example 1:

Input: s = "rabbbit", t = "rabbit"
Output: 3
Explanation:
As shown below, there are 3 ways you can generate "rabbit" from S.
rabbbit
rabbbit
rabbbit
Example 2:

Input: s = "babgbag", t = "bag"
Output: 5
Explanation:
As shown below, there are 5 ways you can generate "bag" from S.
babgbag
babgbag
babgbag
babgbag
babgbag
 

Constraints:

1 <= s.length, t.length <= 1000
s and t consist of English letters.
*/

// DP O(m*n) time and space complexity
class Solution {
public:
    int numDistinct(string s, string t) {
        // dp(m,n): number of distinct sub-sequence between s[0:m) and t[0:n)
        const int M = s.size();
        const int N = t.size();
        vector<vector<unsigned>> dp(M+1, vector<unsigned>(N+1, 0));  // use unsigned to avoid overflow
        // first row, i.e., dp(0,n)=0 where n!=0, since empty s does not have any sub-seq to match non-empty t
        // first col, i.e., dp(m,0)=1, since the "" is a sub-seq that matches t which is empty
        for(int m=0; m<=M; ++m)
            dp[m][0] = 1;
        
        for(int m=1; m<=M; ++m) {
            for(int n=1; n<=N; ++n) {
                if(s[m-1] == t[n-1]) {
                    dp[m][n] = dp[m-1][n-1]/*take s[m-1]*/ + dp[m-1][n]/*not take s[m-1]*/;
                }
                else {
                    dp[m][n] = dp[m-1][n];
                }
            }
        }
        
        return dp[M][N];
    }
};


// DFS solution  -- TLE
class Solution {
public:
    int numDistinct(string s, string t) {
        unsigned count = 0;
        dfs(s,t,0,0,count);
        return count;
    }
    
private:
    void dfs(const string &s, const string &t, int si, int ti, unsigned int &count) {
        if(ti==t.size()) {  // find solution
            ++count;
            return;
        }
        else if(si==s.size()) { // find no solution
            return;
        }
        
        if(s[si] == t[ti]) {
            dfs(s,t,si+1,ti+1,count);  // take s[si]
            dfs(s,t,si+1,ti,count);    // not take s[si]
        }
        else {
            dfs(s,t,si+1,ti,count);
        }
    }
};
