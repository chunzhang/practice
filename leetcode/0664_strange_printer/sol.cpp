/*
There is a strange printer with the following two special properties:

The printer can only print a sequence of the same character each time.
At each turn, the printer can print new characters starting from and ending at any place and will cover the original existing characters.
Given a string s, return the minimum number of turns the printer needed to print it.

 

Example 1:

Input: s = "aaabbb"
Output: 2
Explanation: Print "aaa" first and then print "bbb".
Example 2:

Input: s = "aba"
Output: 2
Explanation: Print "aaa" first and then print "b" from the second place of the string, which will cover the existing character 'a'.
 

Constraints:

1 <= s.length <= 100
s consists of lowercase English letters.
*/

// DP with memoization
class Solution {
public:
    int strangePrinter(string s) {
        // compress string, i.e., "aabbaa" is same as "aba" in terms of results, as the printer should always greedily print all continuous characters
        int len = 1;
        for(int i=1; i<s.size(); ++i)
            if(s[i]!=s[i-1])
                s[len++] = s[i];
        s.resize(len);
        const int N = s.size();
        
        _mem = vector<vector<int>>(N, vector<int>(N, 0));
        return dp(s,0,N-1);
    }
    
private:
    vector<vector<int>> _mem;  // dp with memoization, i.e., min truns of s[i:j]
    
    int dp(const string &s, int i, int j) {
        if(i > j)
            return 0;
        if(i == j)
            return 1;
        if(_mem[i][j] != 0)
            return _mem[i][j];


        // think about how s[j] can be printed?
        // it can be printed either standone, or along with all previous k where s[k]==s[j]
        int ans = dp(s,i,j-1) + 1;
        for(int k=i; k<j; ++k) {
            if(s[k] == s[j]) {
                // here dp(i,k-1)+dp(k+1,j-1)+1 is incorrect as it over counts: 
                // let's say s[i:k]="aba", then break it to "ab" and "a" over counts
                ans = min(ans, dp(s,i,k)+dp(s,k+1,j-1));  // print s[j] can be printed along with s[i:k] since s[j]==s[k]
            }
        }
        
        _mem[i][j] = ans;
        return ans;
    }
    
};
