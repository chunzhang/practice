/*
You have two types of tiles: a 2 x 1 domino shape and a tromino shape. You may rotate these shapes.


Given an integer n, return the number of ways to tile an 2 x n board. Since the answer may be very large, return it modulo 109 + 7.

In a tiling, every square must be covered by a tile. Two tilings are different if and only if there are two 4-directionally adjacent cells on the board such that exactly one of the tilings has both squares occupied by a tile.

 

Example 1:


Input: n = 3
Output: 5
Explanation: The five different ways are show above.
Example 2:

Input: n = 1
Output: 1
 

Constraints:

1 <= n <= 1000
*/

class Solution {
public:
    int numTilings(int n) {
        // The right most piece can only be one of the fout: -, |, _|, |¯
        // As such, we define dp[n] as the number of ways for 2xn board, but it needs to have different states due to the existence of trominos
        // -- dp[n][0]: 2xn is fully covered
        // -- dp[n][1]: 2xn is fully covered except the bottom-right corner grid, e.g., ||¯
        // -- dp[n][2]: 2xn is fully covered except the top-right corner grid, e.g., ||_
        // As such, the transition function becomes
        // -- dp[n][0] = dp[n-1][0] + dp[n-2][0] + dp[n-1][1] + dp[n-1][2]
        // -- dp[n][1] = dp[n-2][0] + dp[n-1][2]
        // -- dp[n][2] = dp[n-2][0] + dp[n-1][1]
        // Since dp[n][1] is always equal to dp[n][2], we can further simplify it to
        // -- dp[n][0] = dp[n-1][0] + dp[n-2][0] + 2*dp[n-1][1]
        // -- dp[n][1] = dp[n-2][0] + dp[n-1][1]
        
        const unsigned M = 1e9+7;
        
        vector<vector<unsigned>> dp(n+1, vector<unsigned>(2, 0));  // use unsigned to avoid overflow
        dp[0][0] = 1;
        dp[1][0] = 1;
        for(int i=2; i<=n; ++i) {
            dp[i][0] = (dp[i-1][0]      // last piece is |
                + dp[i-2][0]            // last piece is -
                + 2*dp[i-1][1]) % M;    // last piece is _| or ¯|
            
            dp[i][1] = (dp[i-2][0]      // ||¯
                + dp[i-1][1]) % M;      // |_¯
        }
        
        return dp[n][0];
    }
};

// Another reference solution from HuaHua, which I don't fully understand yet
/*
dp[0] = 1 # {}
dp[1] = 1 # {|}
dp[2] = 2 # {||, =}
dp[3] = 5 # {|||, |=, =|, ⌊⌉, ⌈⌋} = dp[2] ⊗ {|} + dp[1] ⊗ {=} + dp[0] ⊗ {⌊⌉, ⌈⌋}
dp[4] = 11 # dp[3] ⊗ {|} + dp[2] ⊗ {=} + dp[1] ⊗ {⌊⌉, ⌈⌋} + dp[0] ⊗ {⌊¯⌋,⌈_⌉}
dp[5] = 24 # dp[4] ⊗ {|} + dp[3] ⊗ {=} + 2*(dp[2] + dp[1] + dp[0])
...
dp[n] = dp[n-1] + dp[n-2] + 2*(dp[n-3] + ... + dp[0])
      = dp[n-1] + dp[n-3] + [dp[n-2] + dp[n-3] + 2*(dp[n-4] + ... + dp[0])]
      = dp[n-1] + dp[n-3] + dp[n-1]
      = 2*dp[n-1] + dp[n-3]
*/
class Solution {
public:
  int numTilings(int N) {
    constexpr int kMod = 1000000007;
    vector<long> dp(N + 1, 1);
    dp[2] = 2;
    for (int i = 3; i <= N; ++i)
      dp[i] = (dp[i - 3] + dp[i - 1] * 2) % kMod;
    return dp[N];
  }
};
