/*
You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.

Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

You may assume that you have an infinite number of each kind of coin.

 

Example 1:

Input: coins = [1,2,5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1
Example 2:

Input: coins = [2], amount = 3
Output: -1
Example 3:

Input: coins = [1], amount = 0
Output: 0
Example 4:

Input: coins = [1], amount = 1
Output: 1
Example 5:

Input: coins = [1], amount = 2
Output: 2
 

Constraints:

1 <= coins.length <= 12
1 <= coins[i] <= 2^31 - 1
0 <= amount <= 104
*/

// DP bottom-up, O(k*n) time complexity, O(n) space complexity
// where k is the number of coins, and n is amount
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // dp(n): min number of coins needed to make amount of n
        // dp(n) can be computed from min{dp(n-c)}, where c is the coin value
        vector<int> dp(amount+1, 0);  // dp[0] = 0 as base case
        for(int n=1; n<=amount; ++n) {
            int nCoins = INT_MAX;
            for(int c : coins) {
                int remaining = n - c;  // remaing amount to be coined
                if(remaining>=0 && dp[remaining]!=-1)
                    nCoins = min(nCoins, dp[remaining]);
            }
            dp[n] = (nCoins==INT_MAX?-1:nCoins+1);
        }
        
        return dp[amount];
    }
};


// A slightly different bottom-up DP: we can store INT_MAX as no solution in the dp array
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // dp(n): min number of coins needed to make amount of n
        // dp(n) can be computed from min{dp(n-c)}, where c is the coin value
        vector<int> dp(amount+1, 0);  // dp[0] = 0 as base case
        for(int n=1; n<=amount; ++n) {
            int nCoins = INT_MAX;
            for(int c : coins) {
                int remaining = n - c;  // remaing amount to be coined
                if(remaining>=0 && dp[remaining]!=INT_MAX)
                    nCoins = min(nCoins, dp[remaining]+1);
            }
            dp[n] = nCoins;  // could be INT_MAX
        }
        
        return dp[amount]==INT_MAX?-1:dp[amount];
    }
};

// DP with memoization
class Solution {
public:
    // DP with memoization
    int coinChange(vector<int>& coins, int amount) {
        _dp = vector<int>(amount+1, 0);
        return dp(coins, amount);
    }
    
private:
    int dp(const vector<int> &coins, int amount) {
        if(amount == 0)
            return 0;
        else if(amount < 0)
            return -1;
        
        if(_dp[amount] != 0)
            return _dp[amount];
        
        int ans = INT_MAX;
        for(int c : coins) {
            int num = dp(coins, amount-c);
            if(num != -1)
                ans = min(ans, num);
        }
        
        ans = (ans==INT_MAX?-1:ans+1);
        _dp[amount] = ans;
        return ans;
        
    }
    vector<int> _dp;  // memoization: min number of coins of a given amount
};


// DFS+greedy pruning approach from HuaHua
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // Sort coins in desending order
        std::sort(coins.rbegin(), coins.rend());
        int ans = INT_MAX;
        coinChange(coins, 0, amount, 0, ans);
        return ans == INT_MAX ? -1 : ans;
    }
private:
    void coinChange(const vector<int>& coins, 
                    int s, int amount, int count, int& ans) {
        if (amount == 0) {
            ans = min(ans, count);
            return;
        }
        
        if (s == coins.size()) return;
        
        const int coin = coins[s];                
        for (int k = amount / coin; k >= 0 && count + k < ans; k--)
            coinChange(coins, s + 1, amount - k * coin, count + k, ans);
    }    
};
