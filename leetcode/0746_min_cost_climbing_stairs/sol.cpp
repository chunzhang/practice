/*
You are given an integer array cost where cost[i] is the cost of ith step on a staircase. Once you pay the cost, you can either climb one or two steps.

You can either start from the step with index 0, or the step with index 1.

Return the minimum cost to reach the top of the floor.

 

Example 1:

Input: cost = [10,15,20]
Output: 15
Explanation: Cheapest is: start on cost[1], pay that cost, and go to the top.
Example 2:

Input: cost = [1,100,1,1,1,100,1,1,100,1]
Output: 6
Explanation: Cheapest is: start on cost[0], and only step on 1s, skipping cost[3].
 

Constraints:

2 <= cost.length <= 1000
0 <= cost[i] <= 999
*/

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int d0 = 0;
        int d1 = 0;
        for(int n=2; n<=cost.size(); ++n) {  // destination is one beyond the last step
            int d = min(d0+cost[n-2], d1+cost[n-1]);
            d0 = d1;
            d1 = d;
        }
        return d1;
    }
};
