/*
There is an integer array nums sorted in non-decreasing order (not necessarily with distinct values).

Before being passed to your function, nums is rotated at an unknown pivot index k (0 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,4,4,5,6,6,7] might be rotated at pivot index 5 and become [4,5,6,6,7,0,1,2,4,4].

Given the array nums after the rotation and an integer target, return true if target is in nums, or false if it is not in nums.

You must decrease the overall operation steps as much as possible.

 

Example 1:

Input: nums = [2,5,6,0,0,1,2], target = 0
Output: true
Example 2:

Input: nums = [2,5,6,0,0,1,2], target = 3
Output: false
 

Constraints:

1 <= nums.length <= 5000
-10^4 <= nums[i] <= 10^4
nums is guaranteed to be rotated at some pivot.
-10^4 <= target <= 10^4
 

Follow up: This problem is similar to Search in Rotated Sorted Array, but nums may contain duplicates. Would this affect the runtime complexity? How and why?
*/


// binary search -- iterative
// time complexity: worst case O(N)
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0;
        int h = nums.size() - 1;
        while(l < h) {  // size is at least 2
            //cout << l << "," << h << endl;
            int mid = l + (h-l)/2;
            if(nums[mid] == target)
                return true;
            
            if(nums[mid] < nums[h]) {  // right half is sorted
                if(nums[mid]<=target && target<=nums[h])
                    l = mid + 1;
                else
                    h = mid - 1;
            }
            else if(nums[mid] > nums[h]) {  // left half is sorted
                if(nums[l]<=target && target<=nums[mid])
                    h = mid - 1;
                else
                    l = mid + 1;
            }
            else {  // cannot determine which half is sorted
                --h;
            }
        }
        
        return nums[l]==target?true:false;
    }
};


// divide and conquer
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        return search(nums, target, 0, nums.size()-1);
    }
    
private:
    bool search(const vector<int> &nums, int target, int l, int h) {
        if(l > h)
            return false;
        if(l == h)
            return nums[l]==target?true:false;
        
        // array is sorted, but target is out of range
        if(nums[l]<nums[h] && (target<nums[l] || target>nums[h]))
            return false;
        
        int mid = l + (h-l)/2;
        if(nums[mid] == target)
            return true;
        
        return search(nums, target, l, mid-1) || search(nums, target, mid+1, h);
    }
};
