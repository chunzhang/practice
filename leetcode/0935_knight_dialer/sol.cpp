/*
The chess knight has a unique movement, it may move two squares vertically and one square horizontally, or two squares horizontally and one square vertically (with both forming the shape of an L). The possible movements of chess knight are shown in this diagaram:

A chess knight can move as indicated in the chess diagram below:


We have a chess knight and a phone pad as shown below, the knight can only stand on a numeric cell (i.e. blue cell).


Given an integer n, return how many distinct phone numbers of length n we can dial.

You are allowed to place the knight on any numeric cell initially and then you should perform n - 1 jumps to dial a number of length n. All jumps should be valid knight jumps.

As the answer may be very large, return the answer modulo 109 + 7.

 

Example 1:

Input: n = 1
Output: 10
Explanation: We need to dial a number of length 1, so placing the knight over any numeric cell of the 10 cells is sufficient.
Example 2:

Input: n = 2
Output: 20
Explanation: All the valid number we can dial are [04, 06, 16, 18, 27, 29, 34, 38, 40, 43, 49, 60, 61, 67, 72, 76, 81, 83, 92, 94]
Example 3:

Input: n = 3
Output: 46
Example 4:

Input: n = 4
Output: 104
Example 5:

Input: n = 3131
Output: 136006598
Explanation: Please take care of the mod.
 

Constraints:

1 <= n <= 5000
*/

// DP using vector, O(m*n*k) time, O(m*n) space
class Solution {
public:
    int knightDialer(int n) {
        const vector<vector<int>> moves = {{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1},{2,1},{1,2}};
        
        // dp(i,j,k): number of unique ways that the knight is at (i,j) in the k-th iteration
        // dp(i,j,k) can be calculated from dp(x,y,k-1) if we can move the knight from (x,y) to (i,j)
        const int M = 4;
        const int N = 3;
        vector<vector<int>> dp{{1,1,1},{1,1,1},{1,1,1},{0,1,0}};
        const int MOD = 1e9+7;
        for(int k=2; k<=n; ++k) {
            vector<vector<int>> dpn(M, vector<int>(N,0));  // init to 0
            for(int i=0; i<M; ++i) {
                for(int j=0; j<N; ++j) {
                    for(auto &move : moves) {
                        int ni = i + move[0];
                        int nj = j + move[1];
                        if(ni>=0 && ni<M && nj>=0 && nj<N && !(ni==3&&nj==0 || ni==3&&nj==2)) {
                            dpn[ni][nj] = (dpn[ni][nj]+dp[i][j]) % MOD;
                        }
                    }
                }
            }
            dp.swap(dpn);
        }
        
        int ans = 0;
        for(int i=0; i<M; ++i)
            for(int j=0; j<N; ++j)
                ans = (ans+dp[i][j]) % MOD;
        
        return ans;
    }
};


// DP using array, O(m*n*k) time, O(m*n) space
lass Solution {
public:
    int knightDialer(int n) {
        const vector<vector<int>> moves = {{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1},{2,1},{1,2}};
        
        // dp(i,j,k): number of unique ways that the knight is at (i,j) in the k-th iteration
        // dp(i,j,k) can be calculated from dp(x,y,k-1) if we can move the knight from (x,y) to (i,j)
        const int M = 4;
        const int N = 3;
        int dp[M][N] = {{1,1,1},{1,1,1},{1,1,1},{0,1,0}};
        const int MOD = 1e9+7;
        for(int k=2; k<=n; ++k) {
            int dpn[M][N] = {{0,0,0},{0,0,0},{0,0,0}};  // init to 0
            for(int i=0; i<M; ++i) {
                for(int j=0; j<N; ++j) {
                    for(auto &move : moves) {
                        int ni = i + move[0];
                        int nj = j + move[1];
                        if(ni>=0 && ni<M && nj>=0 && nj<N && !(ni==3&&nj==0 || ni==3&&nj==2)) {
                            dpn[ni][nj] = (dpn[ni][nj]+dp[i][j]) % MOD;
                        }
                    }
                }
            }
            swap(dp, dpn);  // note this works for array as well
        }
        
        int ans = 0;
        for(int i=0; i<M; ++i)
            for(int j=0; j<N; ++j)
                ans = (ans+dp[i][j]) % MOD;
        
        return ans;
    }
};
