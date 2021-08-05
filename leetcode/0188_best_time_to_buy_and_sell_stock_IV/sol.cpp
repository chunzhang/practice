/*
You are given an integer array prices where prices[i] is the price of a given stock on the ith day, and an integer k.

Find the maximum profit you can achieve. You may complete at most k transactions.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

Example 1:

Input: k = 2, prices = [2,4,1]
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
Example 2:

Input: k = 2, prices = [3,2,6,5,0,3]
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
 

Constraints:

0 <= k <= 100
0 <= prices.length <= 1000
0 <= prices[i] <= 1000
*/

// DP: O(N*K) time complexity, O(K) space complexity
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if(k==0 || prices.size()<2)
            return 0;
        
        // Extend the one pass simulation method from leetcode-123 to K transactions
        vector<int> cost(k, INT_MAX);  // min cost at transcation i
        vector<int> profit(k, 0);      // max profit at transaction i
        for(int p:prices) {
            cost[0] = min(cost[0], p);
            profit[0] = max(profit[0], p-cost[0]);
            for(int i=1; i<k; ++i) {
                cost[i] = min(cost[i], p-profit[i-1]);
                profit[i] = max(profit[i], p-cost[i]);
            }
        }
        
        return profit[k-1];
    }
};


// Another O(N*K) DP solution is can be considered as extension to kadane's algorithm
class Solution {
public:
  // General solution
  // Define f(k, i) being the maxprofit with at most k transactions up to i
  // Then f(k, i) can be computed the max of the following
  // -- f(k, i-1), if not selling at i
  // -- prices[i] + max(f(k-1, j)-prices[j]) for all 0<=j<i, if selling at i and buy at j
  // In addition, we have
  // -- f(k, 0) = 0
  // -- f(0, i) = 0
    int maxProfit(int k, vector<int> &prices) {
        if(prices.empty())
            return 0;
        
        vector<vector<int> > f(k+1, vector<int>(prices.size(), 0));
        
        for(int k=1; k<=k; ++k){
            int maxk = f[k-1][0] - prices[0];
            for(int i=1; i<prices.size(); ++i){
                f[k][i] = max(f[k][i-1], prices[i]+maxk);
                maxk = max(maxk, f[k-1][i]-prices[i]);
            }
        }
        
        return f[k][prices.size()-1];
    }

};


// Yet another O(N*K DP solution with more explicit definition (in Java)
public class Solution {
    public int maxProfit(int k, int[] prices) {
        int n = prices.length;

        // solve special cases
        if (n <= 0 || k <= 0) {
            return 0;
        }

        if (2 * k > n) {
            int res = 0;
            for (int i = 1; i < n; i++) {
                res += Math.max(0, prices[i] - prices[i - 1]);
            }
            return res;
        }

        // dp[i][used_k][ishold] = balance
        // ishold: 0 nothold, 1 hold
        int[][][] dp = new int[n][k + 1][2];

        // initialize the array with -inf
        // we use -1e9 here to prevent overflow
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= k; j++) {
                dp[i][j][0] = -1000000000;
                dp[i][j][1] = -1000000000;
            }
        }

        // set starting value
        dp[0][0][0] = 0;
        dp[0][1][1] = -prices[0];

        // fill the array
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= k; j++) {
                dp[i][j][0] = Math.max(dp[i - 1][j][0]/*previously not hold*/, dp[i - 1][j][1] + prices[i]/*sell on day-i*/);
                // you can't hold stock without any transaction
                if (j > 0) {
                    dp[i][j][1] = Math.max(dp[i - 1][j][1]/*previously hold*/, dp[i - 1][j - 1][0] - prices[i]/*buy on day-i*/);
                }
            }
        }

        int res = 0;
        for (int j = 0; j <= k; j++) {
            res = Math.max(res, dp[n - 1][j][0]);
        }

        return res;
    }
};
