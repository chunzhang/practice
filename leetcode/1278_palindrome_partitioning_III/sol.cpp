/*
You are given a string s containing lowercase letters and an integer k. You need to :

First, change some characters of s to other lowercase English letters.
Then divide s into k non-empty disjoint substrings such that each substring is a palindrome.
Return the minimal number of characters that you need to change to divide the string.

 

Example 1:

Input: s = "abc", k = 2
Output: 1
Explanation: You can split the string into "ab" and "c", and change 1 character in "ab" to make it palindrome.
Example 2:

Input: s = "aabbc", k = 3
Output: 0
Explanation: You can split the string into "aa", "bb" and "c", all of them are palindrome.
Example 3:

Input: s = "leetcode", k = 8
Output: 0
 

Constraints:

1 <= k <= s.length <= 100.
s only contains lowercase English letters.
*/

// DP O(k*N^3) time complexity
class Solution {
public:
    int palindromePartition(string s, int k) {
        // dp(i,p): min changes needed to divide s[0:i) into p palindrome partitions
        // dp(i,p) = min{dp(j,p-1)+num_changes_needed_in s[j+1,i)} for p-1<=j<i
        const int N = s.size();
        vector<vector<int>> dp(N+1, vector<int>(k+1, INT_MAX));
        // compute dp(i,1)
        for(int i=1; i<=N; ++i) {
            dp[i][1] = neededChanges(s,0,i-1);
        }
        
        // bottom-up compute remaining dp elements
        // O(k*N^2) of DP loop, while neededChanges() takes O(N), so totally O(k*N^3) time complexity
        for(int p=2; p<=k; ++p) {
            for(int i=p; i<=N; ++i) {  // i starts with p to make sure there's enough partitions available
                for(int j=p-1; j<i; ++j) {  // j breaks s into s[0:j) and s[j:i), and j starts with p-1 to make sure it's possible to make p-1 paritions in s[0:j)
                    dp[i][p] = min(dp[i][p], dp[j][p-1]+neededChanges(s,j,i-1));
                }
            }
        }
        
        return dp[N][k];
    }
    
private:
    int neededChanges(const string &s, int i, int j) {
        int ans = 0;
        while(i<=j) {
            if(s[i++] != s[j--])
                ++ans;
        }
        return ans;
    }
};


// DP O(k*N^2+N^3) time complexity, by pre-compute number of changes neeeded to make any s[i:j] substring palindrome
class Solution {
public:
    int palindromePartition(string s, int k) {
        // dp(i,p): min changes needed to divide s[0:i) into p palindrome partitions
        // dp(i,p) = min{dp(j,p-1)+num_changes_needed_in s[j+1,i)} for p-1<=j<i
        const int N = s.size();
        vector<vector<int>> dp(N+1, vector<int>(k+1, INT_MAX));
        
        // let's pre-compute number of changes needed for any sub-string s[i:j] to be used later
        // O(N^3)
        vector<vector<int>> cost(N, vector<int>(N, 0));
        for(int i=0; i<N; ++i)
            for(int j=0; j<N; ++j)
                cost[i][j] = neededChanges(s,i,j);
        
        // compute dp(i,1)
        for(int i=1; i<=N; ++i) {
            dp[i][1] = cost[0][i-1];
        }
        
        // bottom-up compute remaining dp elements
        // O(k*N^2)
        for(int p=2; p<=k; ++p) {
            for(int i=p; i<=N; ++i) {  // i starts with p to make sure there's enough partitions available
                for(int j=p-1; j<i; ++j) {  // j breaks s into s[0:j) and s[j:i), and j starts with p-1 to make sure it's possible to make p-1 paritions in s[0:j)
                    dp[i][p] = min(dp[i][p], dp[j][p-1]+cost[j][i-1]);
                }
            }
        }
        
        return dp[N][k];
    }
    
private:
    int neededChanges(const string &s, int i, int j) {
        int ans = 0;
        while(i<=j) {
            if(s[i++] != s[j--])
                ++ans;
        }
        return ans;
    }
};


// DP O(k*N^2), by pre-compute cost also using DP
class Solution {
public:
    int palindromePartition(string s, int k) {
        // dp(i,p): min changes needed to divide s[0:i) into p palindrome partitions
        // dp(i,p) = min{dp(j,p-1)+num_changes_needed_in s[j+1,i)} for p-1<=j<i
        const int N = s.size();
        vector<vector<int>> dp(N+1, vector<int>(k+1, INT_MAX));
        
        // let's pre-compute number of changes needed for any sub-string s[i:j] to be used later;
        // -- this can be solved using DP itself: cost(i,j) = (s[i]!=s[j]?1:0) + cost(i+1,j-1)
        // -- bottom-up compute by iterating through sub-array lenght, i.e., when compute cost of len, cost of len-1 is already available
        // -- O(N^2) time complexity
        vector<vector<int>> cost(N, vector<int>(N, 0));  // for length of 1 substrings, cost is 0; for i>j, cost(i,j) is also 0
        for(int len=2; len<=N; ++len) {
            for(int i=0,j=len-1; j<N; ++i,++j)
                cost[i][j] = (s[i]!=s[j]?1:0) + cost[i+1][j-1];
        }
        
        // compute dp(i,1)
        for(int i=1; i<=N; ++i) {
            dp[i][1] = cost[0][i-1];
        }
        
        // bottom-up compute remaining dp elements
        for(int p=2; p<=k; ++p) {
            for(int i=p; i<=N; ++i) {  // i starts with p to make sure there's enough partitions available
                for(int j=p-1; j<i; ++j) {  // j breaks s into s[0:j) and s[j:i), and j starts with p-1 to make sure it's possible to make p-1 paritions in s[0:j)
                    dp[i][p] = min(dp[i][p], dp[j][p-1]+cost[j][i-1]);
                }
            }
        }
        
        return dp[N][k];
    }
    
private:
    int neededChanges(const string &s, int i, int j) {
        int ans = 0;
        while(i<=j) {
            if(s[i++] != s[j--])
                ++ans;
        }
        return ans;
    }
};
