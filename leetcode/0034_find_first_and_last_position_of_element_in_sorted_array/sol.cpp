/*
Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.

If target is not found in the array, return [-1, -1].

You must write an algorithm with O(log n) runtime complexity.

 

Example 1:

Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]
Example 2:

Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]
Example 3:

Input: nums = [], target = 0
Output: [-1,-1]
 

Constraints:

0 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
nums is a non-decreasing array.
-10^9 <= target <= 10^9
*/

// implement lower_bound and upper_bound
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size();
        
        // find lower bound
        while(l<r) {
            int mid = l + (r-l)/2;
            if(nums[mid]>=target)
                r = mid;
            else
                l = mid + 1;
        }
        if(l==nums.size() || nums[l]!=target)
            return {-1,-1};
        
        // find upper bound -- directly start from [lower, r)
        int lower = l;
        r = nums.size();
        while(l<r) {
            int mid = l + (r-l)/2;
            if(nums[mid]>target)
                r = mid;
            else
                l = mid + 1;
        }
        
        return {lower, l-1};
    }
};


// directly use std::lower_bound and std::upper_bound
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        auto lower = lower_bound(nums.begin(), nums.end(), target);
        if(lower==nums.end() || *lower!=target)
            return {-1,-1};
        auto upper = upper_bound(lower, nums.end(), target);
        return {(int)distance(nums.begin(),lower), (int)distance(nums.begin(),upper)-1};
    }
};
