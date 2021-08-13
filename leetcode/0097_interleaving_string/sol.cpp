/*
Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of s1 and s2.

An interleaving of two strings s and t is a configuration where they are divided into non-empty substrings such that:

s = s1 + s2 + ... + sn
t = t1 + t2 + ... + tm
|n - m| <= 1
The interleaving is s1 + t1 + s2 + t2 + s3 + t3 + ... or t1 + s1 + t2 + s2 + t3 + s3 + ...
Note: a + b is the concatenation of strings a and b.

 

Example 1:


Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
Output: true
Example 2:

Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
Output: false
Example 3:

Input: s1 = "", s2 = "", s3 = ""
Output: true
 

Constraints:

0 <= s1.length, s2.length <= 100
0 <= s3.length <= 200
s1, s2, and s3 consist of lowercase English letters.
 

Follow up: Could you solve it using only O(s2.length) additional memory space?
*/

// DP O(m*n) time and space complexity 
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        // dp(m,n): whether s1[0:m) and s2[0:n) can interleave to form s3[0:m+n)
        const int M = s1.size();
        const int N = s2.size();
        if(s3.size() != M+N)
            return false;
        
        // below is not needed as we're padding the dp array
        /*
        if(M == 0)
            return s2==s3;
        else if(N==0)
            return s1==s3;
        */
        
        vector<vector<int>> dp(M+1, vector<int>(N+1, 0));
        dp[0][0] = 1;  // empty string is also an interleave
        // first col
        for(int m=1; m<=M&&s1[m-1]==s3[m-1]; ++m)
            dp[m][0] = 1;
        // first row
        for(int n=1; n<=N&&s2[n-1]==s3[n-1]; ++n)
            dp[0][n] = 1;
        
        // bottom-up to populate rest of dp elements
        for(int m=1; m<=M; ++m) {
            for(int n=1; n<=N; ++n) {
                char sc1 = s1[m-1];     // current char of s1
                char sc2 = s2[n-1];     // current char of s2
                char sc3 = s3[m+n-1];   // current char of s3
                int useS1 = (sc1==sc3?dp[m-1][n]:0);  // use current char of s1
                int useS2 = (sc2==sc3?dp[m][n-1]:0);  // use current char of s2
                dp[m][n] = useS1|useS2;
            }
        }
        
        return dp[M][N];
    }
};


// DP O(m*n) time complexity, O(n) space complexity
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        // dp(m,n): whether s1[0:m) and s2[0:n) can interleave to form s3[0:m+n)
        // Reduce to O(N) space complexity
        const int M = s1.size();
        const int N = s2.size();
        if(s3.size() != M+N)
            return false;

        // below is not needed as we're padding the dp array
        /*
        if(M == 0)
            return s2==s3;
        else if(N==0)
            return s1==s3;
        */
        
        vector<int> dp(N+1, 0);
        // first row, i.e., M=0
        dp[0] = 1;
        for(int n=1; n<=N&&s2[n-1]==s3[n-1]; ++n)
            dp[n] = 1;
        
        // rest dp elements
        for(int m=1; m<=M; ++m) {
            for(int n=0; n<=N; ++n) {
                if(n == 0) {
                    dp[n] = (s1[m-1]==s3[m-1]?dp[n]:0);
                }
                else {
                    int useS1 = (s1[m-1]==s3[m+n-1]?dp[n]:0);    // use char from s1
                    int useS2 = (s2[n-1]==s3[m+n-1]?dp[n-1]:0);  // use char from s2
                    dp[n] = useS1|useS2;
                }
            }
        }
        
        return dp[N];
    }
};


// A brute-force DFS solution for reference (in Java)
public class Solution {
    public boolean is_Interleave(String s1, int i, String s2, int j, String res, String s3)
    {
        if(res.equals(s3) && i == s1.length() && j == s2.length())
            return true;
        boolean ans = false;
        if(i < s1.length())
            ans |= is_Interleave(s1, i + 1, s2, j, res + s1.charAt(i), s3);
        if(j < s2.length())
            ans |= is_Interleave(s1, i, s2, j + 1, res + s2.charAt(j), s3);
        return ans;

    }
    public boolean isInterleave(String s1, String s2, String s3) {
        if (s1.length() + s2.length() != s3.length()) {
            return false;
        }
        return is_Interleave(s1, 0, s2, 0, "", s3);
    }
};
