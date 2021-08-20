/*
You are given an integer array nums and an integer k. You can partition the array into at most k non-empty adjacent subarrays. The score of a partition is the sum of the averages of each subarray.

Note that the partition must use every integer in nums, and that the score is not necessarily an integer.

Return the maximum score you can achieve of all the possible partitions. Answers within 10-6 of the actual answer will be accepted.

 

Example 1:

Input: nums = [9,1,2,3,9], k = 3
Output: 20.00000
Explanation: 
The best choice is to partition nums into [9], [1, 2, 3], [9]. The answer is 9 + (1 + 2 + 3) / 3 + 9 = 20.
We could have also partitioned nums into [9, 1], [2], [3, 9], for example.
That partition would lead to a score of 5 + 2 + 6 = 13, which is worse.
Example 2:

Input: nums = [1,2,3,4,5,6,7], k = 4
Output: 20.50000
 

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 10^4
1 <= k <= nums.length
*/

// DP O(k*N*N) time, O(k*N) space
class Solution {
public:
    double largestSumOfAverages(vector<int>& nums, int k) {
        // dp(i,p): LSA (largest sum of averages) in nums[0:i) with at most p partitions
        // dp(i,p) = max{dp(i-len, p-1)+rollingAverage} for all len<=i
        const int N = nums.size();
        vector<vector<double>> dp(N+1, vector<double>(k+1, 0.0));
        // dp(0,p) = dp(i,0) = 0
        // dp(i,1) can be computed as base case
        double sum = 0;
        for(int i=1; i<=N; ++i) {
            sum += nums[i-1];
            dp[i][1] = sum/i;
        }
        
        // bottom-up computing rest of dp, O(k*N*N) time complexity
        for(int i=1; i<=N; ++i) {
            for(int p=2; p<=k; ++p) {
                double sum = 0.0;
                for(int len=1; len<=i; ++len) {
                    // one possible enhancement: we can compute prefix sum in advance for computing average of any sub-array
                    sum += nums[i-len];
                    dp[i][p] = max(dp[i][p], dp[i-len][p-1]+sum/len);
                }
            }
        }
        
        return dp[N][k];
    }
};
