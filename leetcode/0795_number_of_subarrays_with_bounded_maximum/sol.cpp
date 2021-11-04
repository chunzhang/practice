/*
Given an integer array nums and two integers left and right, return the number of contiguous non-empty subarrays such that the value of the maximum array element in that subarray is in the range [left, right].

The test cases are generated so that the answer will fit in a 32-bit integer.

 

Example 1:

Input: nums = [2,1,4,3], left = 2, right = 3
Output: 3
Explanation: There are three subarrays that meet the requirements: [2], [2, 1], [3].
Example 2:

Input: nums = [2,9,2,5,6], left = 2, right = 8
Output: 7
 

Constraints:

1 <= nums.length <= 10^5
0 <= nums[i] <= 10^9
0 <= left <= right <= 10^9
*/


// #subarrays with maxVal<=right minus #subarrays with maxVal<left-1
// time complexity: O(N)
class Solution {
public:
    int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
        return count(nums,right) - count(nums,left-1); 
    }
    
private:
    // return number of sub-arrays that has max val <= threshold
    int count(const vector<int> &nums, int threshold) {
        int ans = 0;
        // dp(i): total number of subarrays that ends at i
        // dp(i)=dp(i)+1, if nums[i]<=threshold; otherwise 0
        int dp = 0;
        for(int num : nums) {
            if(num > threshold) {
                dp = 0;
            }
            else {
                ++dp;
                ans += c;  // DP: add all subarrays that ends at current number
            }
        }
        
        return ans;
    }
};
