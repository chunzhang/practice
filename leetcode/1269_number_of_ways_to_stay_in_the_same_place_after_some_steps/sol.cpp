/*
You have a pointer at index 0 in an array of size arrLen. At each step, you can move 1 position to the left, 1 position to the right in the array, or stay in the same place (The pointer should not be placed outside the array at any time).

Given two integers steps and arrLen, return the number of ways such that your pointer still at index 0 after exactly steps steps. Since the answer may be too large, return it modulo 109 + 7.

 

Example 1:

Input: steps = 3, arrLen = 2
Output: 4
Explanation: There are 4 differents ways to stay at index 0 after 3 steps.
Right, Left, Stay
Stay, Right, Left
Right, Stay, Left
Stay, Stay, Stay
Example 2:

Input: steps = 2, arrLen = 4
Output: 2
Explanation: There are 2 differents ways to stay at index 0 after 2 steps
Right, Left
Stay, Stay
Example 3:

Input: steps = 4, arrLen = 2
Output: 8
 

Constraints:

1 <= steps <= 500
1 <= arrLen <= 10^6
*/


// DP O(S*min(S,L)) time complexity, where S is steps, L is array length
class Solution {
public:
    int numWays(int steps, int arrLen) {
        // dp(i,n): number of ways that the pointer is at i after exact n steps
        // dp(i,n) = dp(i-1,n-1)+dp(i,n-1)+dp(i+1,n-1)
        const int MOD = 1e9+7;
        const int effLen = min(1+steps/2, arrLen);  // if pointer goes beyond 1+steps/2, it can never go back to 0; so we effectively don't need to compute it
        vector<unsigned> dp(effLen);
        dp[0] = 1;  // starting point
        for(int n=1; n<=steps; ++n) {
            vector<unsigned> dpn(dp);  // copy because the pointer can always stay at current location
            if(effLen>1) {
                dpn[0] = (dpn[0]+dp[1])%MOD;
                dpn[effLen-1] = (dpn[effLen-1]+dp[effLen-2])%MOD;
            }
            for(int i=1; i<effLen-1; ++i) {
                dpn[i] = (dpn[i]+dp[i-1]+dp[i+1])%MOD;
            }
            dp.swap(dpn);
        }
        
        return dp[0];
    }
};
