/*
Given two strings str1 and str2, return the shortest string that has both str1 and str2 as subsequences. If there are multiple valid strings, return any of them.

A string s is a subsequence of string t if deleting some number of characters from t (possibly 0) results in the string s.

 

Example 1:

Input: str1 = "abac", str2 = "cab"
Output: "cabac"
Explanation: 
str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
The answer provided is the shortest such string that satisfies these properties.
Example 2:

Input: str1 = "aaaaaaaa", str2 = "aaaaaaaa"
Output: "aaaaaaaa"
 

Constraints:

1 <= str1.length, str2.length <= 1000
str1 and str2 consist of lowercase English letters.
*/

// DP O(m*n) time complexity
// But if I directly store the result string as dp solution, it will exceed either memory or time limit
class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        // dp(m,n): shortest common super-sequence (SCS) of str1[0:m) and str2[0:)
        const int M = str1.size();
        const int N = str2.size();
        vector<vector<string>> dp(M+1, vector<string>(N+1, ""));
        for(int m=1; m<=M; ++m)
            dp[m][0] = dp[m-1][0] + str1[m-1];  // first col, str1[0:m)
        for(int n=1; n<=N; ++n)
            dp[0][n] = dp[0][n-1] + str2[n-1];  // first row, str2[0:n)
        
        // bottom-up for remaining dp elements
        for(int m=1; m<=M; ++m) {
            for(int n=1; n<=N; ++n) {
                if(str1[m-1] == str2[n-1]) {
                    dp[m][n] = dp[m-1][n-1] + str1[m-1];
                }
                else {
                    if(dp[m-1][n].size() <= dp[m][n-1].size())
                        dp[m][n] = dp[m-1][n] + str1[m-1];  // use last character from str1
                    else
                        dp[m][n] = dp[m][n-1] + str2[n-1];  // use last character from str2
                }
            }
        }
        
        return dp[M][N];
    }
};


// DP O(m*n), but with space optimized, i.e., not store string result directly
class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        // dp(m,n): shortest common super-sequence (SCS) of str1[0:m) and str2[0:n)
        // To avoid reaching runtime and memory limit, I do not store the string result directly in dp(m,n)
        // Instead, I break it into two: dpl(m,n) for min length, and dpc(m,n) for character to be used at current location
        // After populating dpl and dpc, I can recover the result string at the end
        const int M = str1.size();
        const int N = str2.size();
        vector<vector<int>> dpl(M+1, vector<int>(N+1, 0));        // length
        vector<vector<char>> dpc(M+1, vector<char>(N+1, '\0'));   // character
        for(int m=1; m<=M; ++m) {
            dpl[m][0] = m;
            dpc[m][0] = str1[m-1];
        }
        for(int n=1; n<=N; ++n) {
            dpl[0][n] = n;
            dpc[0][n] = str2[n-1];
        }
        
        // bottom-up for remaining dp elements
        for(int m=1; m<=M; ++m) {
            for(int n=1; n<=N; ++n) {
                if(str1[m-1] == str2[n-1]) {
                    dpl[m][n] = dpl[m-1][n-1] + 1;
                    dpc[m][n] = str1[m-1];
                }
                else {
                    if(dpl[m-1][n] <= dpl[m][n-1]) {
                        dpl[m][n] = dpl[m-1][n] + 1;  // use last character from str1
                        dpc[m][n] = str1[m-1];
                    }
                    else {
                        dpl[m][n] = dpl[m][n-1] + 1;  // use last character from str2
                        dpc[m][n] = str2[n-1];
                    }
                }
            }
        }
                
        // build result string
        string res;
        for(int m=M,n=N; m!=0||n!=0; ) {
            res.push_back(dpc[m][n]);
            if(m == 0) {
                --n;
            }
            else if(n == 0) {
                --m;
            }
            else if(str1[m-1] == str2[n-1]) {
                --m;
                --n;
            }
            else if(str1[m-1] == dpc[m][n]) {  // result use char from str1
                --m;
            }
            else {  // result use char from str2
                --n;
            }
        }
        
        reverse(res.begin(), res.end());
        return res;
    }
};

// DP O(m*n) time complexity
// With further space optimization, i.e., no need to book-keep char being used
class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        // dp(m,n): length of shortest common super-sequence (SCS) of str1[0:m) and str2[0:n)
        const int M = str1.size();
        const int N = str2.size();
        vector<vector<int>> dp(M+1, vector<int>(N+1, 0));        // length
        for(int m=1; m<=M; ++m) {
            dp[m][0] = m;
        }
        for(int n=1; n<=N; ++n) {
            dp[0][n] = n;
        }
        
        // bottom-up for remaining dp elements
        for(int m=1; m<=M; ++m) {
            for(int n=1; n<=N; ++n) {
                if(str1[m-1] == str2[n-1]) {
                    dp[m][n] = dp[m-1][n-1] + 1;
                }
                else {
                    dp[m][n] = min(dp[m-1][n]/*use last character from str1*/,dp[m][n-1]/*use last character from str2*/) + 1;
                }
            }
        }
                
        // build result string
        string res;
        for(int m=M,n=N; m!=0||n!=0; ) {
            char c;
            if(m == 0) {
                c = str2[n-1];
                --n;
            }
            else if(n == 0) {
                c = str1[m-1];
                --m;
            }
            else if(str1[m-1] == str2[n-1]) {
                c = str1[m-1];
                --m;
                --n;
            }
            else if(dp[m][n] == dp[m-1][n]+1) {  // result use char from str1
                c = str1[m-1];
                --m;
            }
            else {  // result use char from str2
                c = str2[n-1];
                --n;
            }
            res.push_back(c);
        }
        
        reverse(res.begin(), res.end());
        return res;
    }
};
