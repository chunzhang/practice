/*
You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number on it represented by an array nums. You are asked to burst all the balloons.

If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins. If i - 1 or i + 1 goes out of bounds of the array, then treat it as if there is a balloon with a 1 painted on it.

Return the maximum coins you can collect by bursting the balloons wisely.

 

Example 1:

Input: nums = [3,1,5,8]
Output: 167
Explanation:
nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
Example 2:

Input: nums = [1,5]
Output: 10
 

Constraints:

n == nums.length
1 <= n <= 500
0 <= nums[i] <= 100
*/

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        // dp(i,j): max coins by bursting balloons in mums[i:j]
        // dp(i,j) = max{dp(i,k-1) + dp(k+1,j) + nums[i-1]*nums[k]+nums[j+1]} for i<=k<=j, where k is the last ballon to burst in [i:j]
        const int N = nums.size();
        vector<int> balloons;
        balloons.push_back(1);  // padding left most and right most with 1 to simplify code
        for(int n : nums)
            balloons.push_back(n);
        balloons.push_back(1);
        
        vector<vector<int>> dp(N+2, vector<int>(N+2, 0));  // padding simplies code
        // base case: length=1
        for(int i=1; i<=N; ++i)
            dp[i][i] = balloons[i-1]*balloons[i]*balloons[i+1];
        
        // bottom-up by sub-array length
        for(int len=2; len<=N; ++len) {
            for(int i=1,j=len; j<=N; ++i,++j) {
                for(int k=i; k<=j; ++k) {  // k is the last ballon to burst in [i:j]
                    dp[i][j] = max(dp[i][j], dp[i][k-1]+dp[k+1][j]+balloons[i-1]*balloons[k]*balloons[j+1]);  // no need to check index boundary due to enough padding
                }
            }
        }
        
        return dp[1][N];
    }
};
