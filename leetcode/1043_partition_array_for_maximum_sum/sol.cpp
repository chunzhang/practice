/*
Given an integer array arr, partition the array into (contiguous) subarrays of length at most k. After partitioning, each subarray has their values changed to become the maximum value of that subarray.

Return the largest sum of the given array after partitioning. Test cases are generated so that the answer fits in a 32-bit integer.

 

Example 1:

Input: arr = [1,15,7,9,2,5,10], k = 3
Output: 84
Explanation: arr becomes [15,15,15,9,10,10,10]
Example 2:

Input: arr = [1,4,1,5,7,3,6,1,9,9,3], k = 4
Output: 83
Example 3:

Input: arr = [1], k = 1
Output: 1
 

Constraints:

1 <= arr.length <= 500
0 <= arr[i] <= 109
1 <= k <= arr.length
*/

// DP O(N*k) time complexity, O(N) space complexity
class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        // dp(i): max sum of valid partition of array[0:i)
        // dp(i) = max{dp(i-len)+maxVal*len} for len<=k, and maxVal is the max of arr[i-len:i)
        const int N = arr.size();
        vector<int> dp(N+1, INT_MIN);
        dp[0] = 0;
        for(int i=1; i<=N; ++i) {
            int maxVal = INT_MIN;  // rolling maximum
            for(int len=1; len<=k&&i-len>=0; ++len) {
                maxVal = max(maxVal, arr[i-len]);
                dp[i] = max(dp[i], dp[i-len]+maxVal*len);
            }
        }
        
        return dp[N];
    }
};
