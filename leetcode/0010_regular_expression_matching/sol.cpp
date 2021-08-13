/*
Given an input string s and a pattern p, implement regular expression matching with support for '.' and '*' where:

'.' Matches any single character.​​​​
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).

 

Example 1:

Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input: s = "aa", p = "a*"
Output: true
Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
Example 3:

Input: s = "ab", p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".
Example 4:

Input: s = "aab", p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore, it matches "aab".
Example 5:

Input: s = "mississippi", p = "mis*is*p*."
Output: false
 

Constraints:

1 <= s.length <= 20
1 <= p.length <= 30
s contains only lowercase English letters.
p contains only lowercase English letters, '.', and '*'.
It is guaranteed for each appearance of the character '*', there will be a previous valid character to match.
*/

class Solution {
public:
    bool isMatch(string s, string p) {
        // dp(m,n): whether s[0:m) matches p[0:n)
        const int M = s.size();
        const int N = p.size();
        vector<vector<int>> dp(M+1, vector<int>(N+1, 0));
        dp[0][0] = 1;  // empty string matches empty pattern
        // first column, i.e., dp(m,0)=0 since empty pattern does not match any non-empty string
        // first row, i.e., dp(0, n) only matches when pattern is ".*.*.*"
        for(int n=1; n<N; n+=2) {
            if(p[n]=='*') {
                dp[0][n] = 1;
                dp[0][n+1] = 1;
            }
            else
                break;
        }
        
        // now bottom-up populate remaining dp(m,n)
        for(int m=1; m<=M; ++m) {
            for(int n=1; n<=N; ++n) {
                char sc = s[m-1];
                char pc = p[n-1];
                bool match = (sc==pc||pc=='.');  // pattern of last character matches
                if(pc == '*') {
                    dp[m][n] = dp[m][n-1];
                }
                else if(n<N && p[n]=='*') {
                    int zero = dp[m][n-1];                 // zero instantion
                    int oneOrMore = (match?dp[m-1][n]:0);  // one ore more instantion
                    dp[m][n] = (zero|oneOrMore);
                }
                else {
                    dp[m][n] = (match?dp[m-1][n-1]:0);
                }
            }
        }
        
        return dp[M][N];
    }
};


// DFS solution for reference (in Java)
// Can be extended to DP with memoization in a straightforward manner
class Solution {
    public boolean isMatch(String text, String pattern) {
        if (pattern.isEmpty()) return text.isEmpty();
        boolean first_match = (!text.isEmpty() &&
                               (pattern.charAt(0) == text.charAt(0) || pattern.charAt(0) == '.'));

        if (pattern.length() >= 2 && pattern.charAt(1) == '*'){
            return (isMatch(text, pattern.substring(2)) ||
                    (first_match && isMatch(text.substring(1), pattern)));
        } else {
            return first_match && isMatch(text.substring(1), pattern.substring(1));
        }
    }
};
