/*
You have some coins.  The i-th coin has a probability prob[i] of facing heads when tossed.

Return the probability that the number of coins facing heads equals target if you toss every coin exactly once.

 

Example 1:

Input: prob = [0.4], target = 1
Output: 0.40000
Example 2:

Input: prob = [0.5,0.5,0.5,0.5,0.5], target = 0
Output: 0.03125
 

Constraints:

1 <= prob.length <= 1000
0 <= prob[i] <= 1
0 <= target <= prob.length
Answers will be accepted as correct if they are within 10^-5 of the correct answer.
*/

// DP O(N*target), where N is number of coins
class Solution {
public:
    double probabilityOfHeads(vector<double>& prob, int target) {
        // dp(i,n): probability of having n coins facing up in coins[0:i)
        const int N = prob.size();   // number of coins
        vector<double> dp(target+1, 0.0);  // reduce the i dimension
        dp[0] = 1.0;  // dp(0, 0) = 1;
        
        for(int i=0; i<N; ++i) {
            vector<double> dpn(target+1, 0.0);
            for(int n=0; n<=target; ++n) {
                if(dp[n]) {  // PUSH style
                    dpn[n] += dp[n]*(1-prob[i]);  // next coin facing down
                    if(n<target)
                        dpn[n+1] += dp[n]*prob[i];  // next-th coin facing up
                }
            }
            dp.swap(dpn);
        }
        
        return dp[target];
    }
};
