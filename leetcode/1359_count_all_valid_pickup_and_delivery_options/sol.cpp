/*
Given n orders, each order consist in pickup and delivery services. 

Count all valid pickup/delivery possible sequences such that delivery(i) is always after of pickup(i). 

Since the answer may be too large, return it modulo 10^9 + 7.

 

Example 1:

Input: n = 1
Output: 1
Explanation: Unique order (P1, D1), Delivery 1 always is after of Pickup 1.
Example 2:

Input: n = 2
Output: 6
Explanation: All possible orders: 
(P1,P2,D1,D2), (P1,P2,D2,D1), (P1,D1,P2,D2), (P2,P1,D1,D2), (P2,P1,D2,D1) and (P2,D2,P1,D1).
This is an invalid order (P1,D2,P2,D1) because Pickup 2 is after of Delivery 2.
Example 3:

Input: n = 3
Output: 90
 

Constraints:

1 <= n <= 500
*/


// DP: one dimensional based on math formula
// time complexity: O(N)
// space complexity: O(1)
class Solution {
public:
    int countOrders(int n) {
        const int MOD = 1E9+7;
        // dp(i): total options with i items
        // -- for each option of dp(i-1), D_i can be inserted into any index k;
        // -- and there will be k+1 ways to insert P_i before D_i
        // -- as such, there will be totally sum(i)=1+2+3+....+2*i-1 new options for each old option
        // ==> dp(i) = dp(i-1)*sum(i)
        long dp = 1;
        for(int i=2; i<=n; ++i) {
            dp = dp*i*(2*i-1) % MOD;  // sum(i) = i*(2*i-1)
        }
        
        return dp;
    }
};
