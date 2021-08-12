/*
Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

You have the following three operations permitted on a word:

Insert a character
Delete a character
Replace a character
 

Example 1:

Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')
Example 2:

Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation: 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')
 

Constraints:

0 <= word1.length, word2.length <= 500
word1 and word2 consist of lowercase English letters.
*/

// DP solution O(mn)
class Solution {
public:
    int minDistance(string word1, string word2) {
        // speical corner case
        if(word1.empty())
            return word2.size();
        else if(word2.empty())
            return word1.size();
        
        // dp(m,n): edistance of word1[0:m) and word2[0:n)        
        const int M = word1.size();
        const int N = word2.size();
        vector<vector<int>> dp(M+1, vector<int>(N+1, INT_MAX));  // padding, index zero means the string is empty
        for(int m=0; m<=M; ++m) {
            for(int n=0; n<=N; ++n) {
                if(m == 0)      // word1[0:0) is empty
                    dp[m][n] = n;
                else if(n ==0)  // word2[0:0) is empty
                    dp[m][n] = m;
                else {
                    if(word1[m-1] == word2[n-1])
                        dp[m][n] = dp[m-1][n-1];
                    else {
                        int replace = dp[m-1][n-1] + 1;  // replace last character
                        int rm1 = dp[m-1][n] + 1;        // remove last character from word1
                        int rm2 = dp[m][n-1] + 1;        // remove last character from word2
                        dp[m][n] = min({replace,rm1,rm2});
                    }
                }
            }
        }

        return dp[M][N];
    }
};


// A simplified implementation from HuaHua
class Solution {
public:
    int minDistance(string word1, string word2) {
        int l1 = word1.length();
        int l2 = word2.length();
        // d[i][j] := minDistance(word1[0:i - 1], word2[0:j - 1]);
        vector<vector<int>> d(l1 + 1, vector<int>(l2 + 1, 0));
        
        for (int i = 0; i <= l1; ++i)
            d[i][0] = i;
        for (int j = 0; j <= l2; ++j)
            d[0][j] = j;
        
        for (int i = 1; i <= l1; ++i)
            for (int j = 1; j <= l2; ++j) {
                int c = (word1[i - 1] == word2[j - 1]) ? 0 : 1;
                d[i][j] = min(d[i - 1][j - 1] + c, 
                              min(d[i][j - 1], d[i - 1][j]) + 1);
            }
        
        return d[l1][l2];
    }
};
