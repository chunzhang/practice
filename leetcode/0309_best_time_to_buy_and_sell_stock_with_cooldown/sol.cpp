/*
You are given an array prices where prices[i] is the price of a given stock on the ith day.

Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times) with the following restrictions:

After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).
Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

Example 1:

Input: prices = [1,2,3,0,2]
Output: 3
Explanation: transactions = [buy, sell, cooldown, buy, sell]
Example 2:

Input: prices = [1]
Output: 0
 

Constraints:

1 <= prices.length <= 5000
0 <= prices[i] <= 1000
*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // DP with state machine transitions
        // At each day, one can only stay in one of the three status
        // -- hold, i.e., hold stock
        // -- sold, i.e., just sold stock
        // -- rest, i.e., no stock but also not just sold stock; this is the starting and cooldown status
        // With three possible actions: buy, sell and no-op, we can come up with the transition graph
        
        // Now let's define hold[i], sold[i] and rest[i] be the max money one can have at hand at day-i for each of the status
        // -- Assume we start with 0 money at hand, but we can borrow money to buy stock
        // -- hold[i] = max(hold[i-1], rest[i-1]-prices[i]), i.e., I can pay prices[i] to buy stock
        // -- sold[i] = hold[i-1] + prices[i], i.e., I sell stock with prices[i]
        // -- rest[i] = max(rest[i-1], sold[i-1]))
        
        // I can optimize the space to O(1)
        int hold = INT_MIN;  // impossible to be initial status
        int sold = INT_MIN;  // impossible to be initial status
        int rest = 0;        // Only possible initial status, 0 money at hand
        
        for(int p : prices) {
            int preSold = sold;
            sold = hold + p;           // can get p dollars by selling stock
            hold = max(hold, rest-p);  // can pay p dollars to buy stock
            rest = max(rest, preSold);
        }
        
        return max(rest, sold);  // doesn't make sense to hold any stock at last
    }
};
