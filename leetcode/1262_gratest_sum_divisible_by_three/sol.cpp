/*
Given an array nums of integers, we need to find the maximum possible sum of elements of the array such that it is divisible by three.

 

Example 1:

Input: nums = [3,6,5,1,8]
Output: 18
Explanation: Pick numbers 3, 6, 1 and 8 their sum is 18 (maximum sum divisible by 3).
Example 2:

Input: nums = [4]
Output: 0
Explanation: Since 4 is not divisible by 3, do not pick any number.
Example 3:

Input: nums = [1,2,3,4,4]
Output: 12
Explanation: Pick numbers 1, 3, 4 and 4 their sum is 12 (maximum sum divisible by 3).
 

Constraints:

1 <= nums.length <= 4 * 10^4
1 <= nums[i] <= 10^4
*/

// DP O(N) time, O(1) space
class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        // dp(i, n): max sum in nums[0:i] where sum%3=n
        vector<int> dp = {0,0,0};
        dp[nums[0]%3] = nums[0];  // base case
        for(int i=1; i<nums.size(); ++i) {
            vector<int> dpn = dp;  // copy, i.e., if we do not use current number, it is at least previous result
            int mod = nums[i] % 3;
            dpn[mod] = max(dpn[mod], nums[i]);  // current number can be used as is
            for(int n=0; n<3; ++n) {
                // compute dp(i, n)
                for(int k=0; k<3; ++k) {
                    if((k+mod)%3==n && dp[k]!=0) {  // current number can be used
                        dpn[n] = max(dpn[n], dp[k]+nums[i]);
                    }
                }
            }
            swap(dp, dpn);
        }
        
        return dp[0];
    }
};


// DP with PUSH style from HuaHua
class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        // dp(i, n): max sum in nums[0:i] where sum%3=n
        vector<int> dp(3);
        for(int num : nums) {
            vector<int> dpn(dp);
            for(int s : dp)
                dpn[(s+num)%3] = max(dpn[(s+num)%3]/*current num is not used*/, s+num/*current num is used*/);  // PUSH style
            dp.swap(dpn);
        }
        
        return dp[0];
    }
};
