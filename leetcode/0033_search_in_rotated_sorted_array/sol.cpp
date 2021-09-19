/*
There is an integer array nums sorted in ascending order (with distinct values).

Prior to being passed to your function, nums is rotated at an unknown pivot index k (0 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].

Given the array nums after the rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.

You must write an algorithm with O(log n) runtime complexity.

 

Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
Example 3:

Input: nums = [1], target = 0
Output: -1
 

Constraints:

1 <= nums.length <= 5000
-10^4 <= nums[i] <= 10^4
All values of nums are unique.
nums is guaranteed to be rotated at some pivot.
-10^4 <= target <= 10^4
*/

// binary search -- iterative
// time complexity: O(lgN)
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0;
        int h = nums.size() - 1;
        while(l < h) {  // size is at least 2
            //cout << l << "," << h << endl;
            int mid = l + (h-l)/2;
            if(nums[mid] == target)
                return mid;
            
            if(nums[mid] < nums[h]) {  // right half is sorted
                if(nums[mid]<=target && target<=nums[h])
                    l = mid + 1;
                else
                    h = mid - 1;
            }
            else {  // left half is sorted
                if(nums[l]<=target && target<=nums[mid])
                    h = mid - 1;
                else
                    l = mid + 1;
            }
        }
        
        return nums[l]==target?l:-1;
    }
};


// divide and conquer
class Solution {
public:
    int search(vector<int>& nums, int target) {
        return search(nums, target, 0, nums.size()-1);
    }
    
private:
    int search(const vector<int> &nums, int target, int l, int h) {
        if(l > h)
            return -1;
        if(l == h)
            return nums[l]==target?l:-1;
        
        // array is sorted, but target is out of range
        if(nums[l]<nums[h] && (target<nums[l] || target>nums[h]))
            return -1;
        
        int mid = l + (h-l)/2;
        if(nums[mid] == target)
            return mid;
        
        int left = search(nums, target, l, mid-1);
        int right = search(nums, target, mid+1, h);
        if(left!=-1 || right!=-1)
            return left!=-1?left:right;
        else
            return -1;
    }
};
