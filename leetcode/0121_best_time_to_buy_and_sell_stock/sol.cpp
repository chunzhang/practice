/*
You are given an array prices where prices[i] is the price of a given stock on the ith day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

 

Example 1:

Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.
Example 2:

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transactions are done and the max profit = 0.
 

Constraints:

1 <= prices.length <= 10^5
0 <= prices[i] <= 10^4
*/

// DP: dp[i] being the max profit until day-i
// -- dp[i] = max(dp[i-1], prices[i]-minPrice), where minPrice is the minimal price before day-i
// -- can be reduced to O(1) space
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // DP with O(1) space
        int dp = 0;
        int minPrice = INT_MAX;  // min price before day-i
        for(int p : prices) {
            dp = max(dp, p-minPrice/*sell at current day*/);
            minPrice = min(minPrice, p);
        }
        
        return dp;
    }
};



class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int ans = 0;  // no transaction no profit        
        
        // dp[i]: lowest stock value on day-i and before
        vector<int> dp(prices);  // dp[0] = prices[0]
        for(int i=1; i<prices.size(); ++i) {  // can only sell at day-1 or after
            ans = max(ans, prices[i]-dp[i-1]);
            dp[i] = min(dp[i-1], prices[i]);
        }
        
        return ans;
    }
};
