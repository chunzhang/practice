/*
Given two strings word1 and word2, return the minimum number of steps required to make word1 and word2 the same.

In one step, you can delete exactly one character in either string.

 

Example 1:

Input: word1 = "sea", word2 = "eat"
Output: 2
Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
Example 2:

Input: word1 = "leetcode", word2 = "etco"
Output: 4
 

Constraints:

1 <= word1.length, word2.length <= 500
word1 and word2 consist of only lowercase English letters.
*/

// DP O(m*n)
class Solution {
public:
    int minDistance(string word1, string word2) {
        // dp(m,n): #deletions between word1[0:m) and word2[0:n)
        const int M = word1.size();
        const int N = word2.size();
        vector<vector<int>> dp(M+1, vector<int>(N+1, INT_MAX));
        for(int m=0; m<=M; ++m) {
            for(int n=0; n<=N; ++n) {
                if(m == 0)
                    dp[m][n] = n;
                else if(n == 0)
                    dp[m][n] = m;
                else {
                    if(word1[m-1] == word2[n-1])
                        dp[m][n] = dp[m-1][n-1];
                    else {
                        int rm1 = dp[m-1][n] + 1;      // remove last character from word1
                        int rm2 = dp[m][n-1] + 1;      // remove last character from word2
                        dp[m][n] = min(rm1, rm2);
                        // Actually, deleted both is not needed as it is included in other solutions, i.e., delete from word1 and then delete from word2
                        /*
                        int rm12 = dp[m-1][n-1] + 2;   // remove last character from both word1 and word2
                        dp[m][n] = min({rm1,rm2,rm12});
                        */
                    }
                }
            }
        }
        
        return dp[M][N];
    }
};


// Another DP O(m*n): convert it to LCS problem (leetcode-1143)
class Solution {
public:
    int minDistance(string word1, string word2) {
        // convert it to LCS problem: after deletion, the remaining strings are LCS
        int len = longestCommonSubsequence(word1, word2);
        return word1.size()+word2.size()-2*len;
    }
    
private:
    int longestCommonSubsequence(const string &text1, const string &text2) {
        // dp(m,n): LCS of text1[0:m) and text2[0:n)
        const int M = text1.size();
        const int N = text2.size();
        vector<vector<int>> dp(M+1, vector<int>(N+1, 0));  // first row and column is 0, which is the base case
        for(int m=1; m<=M; ++m) {
            for(int n=1; n<=N; ++n) {
                if(text1[m-1] == text2[n-1])
                    dp[m][n] = dp[m-1][n-1] + 1;  // One may wonder what if the LCS is in dp[m-1][n]? But if that's the case, dp[m][n] is at least as good as it
                else
                    dp[m][n] = max(dp[m][n-1], dp[m-1][n]);
            }
        }
        
        return dp[M][N];
    }
};
