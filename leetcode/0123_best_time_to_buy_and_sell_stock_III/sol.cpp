/*
You are given an array prices where prices[i] is the price of a given stock on the ith day.

Find the maximum profit you can achieve. You may complete at most two transactions.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

Example 1:

Input: prices = [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.
Example 2:

Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are engaging multiple transactions at the same time. You must sell before buying again.
Example 3:

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
Example 4:

Input: prices = [1]
Output: 0
 

Constraints:

1 <= prices.length <= 10^5
0 <= prices[i] <= 10^5
*/

// DP solution 1: O(N) time complexity, O(N) space complexity
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // If we break the prices into left and right half, then the problem reduces to find best profit for each half with at most one transaction
        // -- left[i] as the max profit one can get on prices[0, ..., i] by at most one transaction
        // -- right[i] as the max profit one can get on prices[i, ..., N-1] by at most one transaction
        // Then, we can compute the max profit as max(left[i]+right[i+1]) for 0<=i<=N-1
       
        const int N = prices.size();
        
        // Left half
        vector<int> left(N, 0);
        int minLeft = prices[0];
        for(int i=1; i<N; ++i) {
            left[i] = max(left[i-1], prices[i]-minLeft/*sell at day-i*/);
            minLeft = min(minLeft, prices[i]);
        }
        
        // Right half
        vector<int> right(N,0);
        int maxRight = prices[N-1];
        for(int i=N-2; i>=0; --i) {
            right[i] = max(right[i+1], maxRight-prices[i]/*buy at day-i*/);
            maxRight = max(maxRight, prices[i]);
        }
        
        int ans = 0;
        for(int i=0; i<N-1; ++i)
            ans = max(ans, left[i]+right[i+1]);
        return max(ans, left[N-1]);
    }
};

// DP solution 2: O(N) time complexity, O(1) space complexity
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // Another way of looking at it is to do one pass iteration by keeping track of the cost and profits of the two transactions      
        int cost1 = INT_MAX;  // min cost for transaction #1
        int cost2 = INT_MAX;  // min cost for transaction #2
        int profit1 = 0;      // max profit for transaction #1
        int profit2 = 0;      // max profit for transaction #2
        
        for(int p:prices) {
            cost1 = min(cost1, p);
            profit1 = max(profit1, p-cost1);
            cost2 = min(cost2, p-profit1);  // profit from transcation is accounted!!!
            profit2 = max(profit2, p-cost2);
        }
        
        return profit2;
    }
};
