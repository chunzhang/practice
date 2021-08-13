/*
Given two integer arrays nums1 and nums2, return the maximum length of a subarray that appears in both arrays.

 

Example 1:

Input: nums1 = [1,2,3,2,1], nums2 = [3,2,1,4,7]
Output: 3
Explanation: The repeated subarray with maximum length is [3,2,1].
Example 2:

Input: nums1 = [0,0,0,0,0], nums2 = [0,0,0,0,0]
Output: 5
 

Constraints:

1 <= nums1.length, nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 100
*/

// DP O(m*n) solution
class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        // dp(m,n): max-len of sub-array that ends at nums1[m-1] and nums2[n-1]
        const int M = nums1.size();
        const int N = nums2.size();
        vector<vector<int>> dp(M+1, vector<int>(N+1, 0));  // first row and col is 0
        int ans = INT_MIN;
        for(int m=1; m<=M; ++m) {
            for(int n=1; n<=N; ++n) {
                dp[m][n] = (nums1[m-1]==nums2[n-1]?dp[m-1][n-1]+1:0);
                ans = max(ans, dp[m][n]);
            }
        }
        
        return ans;
    }
};
