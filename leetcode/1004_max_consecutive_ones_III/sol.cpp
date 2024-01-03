/*
Facebook/Amazon/Google

Given a binary array nums and an integer k, return the maximum number of consecutive 1's in the array if you can flip at most k 0's.
 
Example 1:

Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
Output: 6
Explanation: [1,1,1,0,0,1,1,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.
Example 2:

Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
Output: 10
Explanation: [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.
 

Constraints:

1 <= nums.length <= 10^5
nums[i] is either 0 or 1.
0 <= k <= nums.length
*/


// use sliding window with two pointers, i.e., [i,j) defines a valid all-ones window
// time complexity: O(N)
// space complexity: O(1)
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        // two pointers with sliding window
        int ans = 0;
        
        // [i,j) sliding window
        int i = 0;
        int j = 0;
        for(; j<nums.size(); ) {
            if(k >= 0) {  // valid window, increment j
                ans = max(ans, j-i);
                if(nums[j++] == 0)  // expand window to right
                    --k;
            }
            else {  // invalid window, incremental i
                if(nums[i++] == 0)  // shrink window from left
                    ++k;
            }
        }
        
        if(k>=0)  // do not forget the last window
            ans = max(ans, j-i);
        return ans;
    }
};


// most optimal: use sliding window but no need to shrink it
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int i = 0;
        int j = 0;
        for (; j<nums.size(); ++j) {
            if (nums[j] == 0) {
                k--;
            }
            if (k < 0) {
                if(nums[i++] == 0)
                    ++k;
            }
        }
        return j-i;
    }
};
