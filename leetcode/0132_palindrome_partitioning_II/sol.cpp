/*
Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

 

Example 1:

Input: s = "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
Example 2:

Input: s = "a"
Output: 0
Example 3:

Input: s = "ab"
Output: 1
 

Constraints:

1 <= s.length <= 2000
s consists of lower-case English letters only.
*/

// DP O(N^2) time, O(N^2) space complexity
class Solution {
public:
    int minCut(string s) {
        const int N = s.size();

        // DP 1: define pal(i,j) as s[i:j] is a palindrome
        // pal(i,j) = pal(i+1,j-1)&&(s[i]==sj[j])
        vector<vector<int>> pal(N, vector<int>(N,1));  // pal[i][i]==1, since length-1 string is always palindrome
        for(int len=2; len<=N; ++len)  // O(N^2) time
            for(int i=0,j=len-1; j<N; ++i,++j)
                pal[i][j] = pal[i+1][j-1] & (s[i]==s[j]);
        
        // DP 2: define dp(i) as the min cut needed for string s[0:i)
        // dp(i) = min{dp(k)+1}, for k<i and s[k:i) is palindrome
        vector<int> dp(N+1,INT_MAX);
        dp[0] = 0;
        for(int i=1; i<=N; ++i) {  // O(N^2) time
            for(int k=0; k<i; ++k) {
                if(pal[k][i-1])
                    dp[i] =  min(dp[i], dp[k]+(k==0?0:1));
            }
        }
        
        return dp[N];
    }
};


// A very smart O(N) space solution from HuaHua
// The idea is to scan mid point of palindrome and expand the palindrome, and PUSH the results
class Solution {
public:
  int minCut(string s) {
    const int n = s.length();        
    // dp[i] = min cuts of s[0~i] 
    vector<int> dp(n, n);    
    for (int m = 0; m < n; ++m)      
        for (int d = 0; d <= 1; ++d)  // odd or even mid point
            for (int i = m, j = m + d; i >= 0 && j < n && s[i] == s[j]; --i, ++j)
                dp[j] = min(dp[j], (i ? (dp[i - 1] + 1) : 0));  // PUSH
    return dp[n - 1];
  }
};
