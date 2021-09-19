/*
Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For example, the array nums = [0,1,2,4,5,6,7] might become:

[4,5,6,7,0,1,2] if it was rotated 4 times.
[0,1,2,4,5,6,7] if it was rotated 7 times.
Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

Given the sorted rotated array nums of unique elements, return the minimum element of this array.

You must write an algorithm that runs in O(log n) time.

 

Example 1:

Input: nums = [3,4,5,1,2]
Output: 1
Explanation: The original array was [1,2,3,4,5] rotated 3 times.
Example 2:

Input: nums = [4,5,6,7,0,1,2]
Output: 0
Explanation: The original array was [0,1,2,4,5,6,7] and it was rotated 4 times.
Example 3:

Input: nums = [11,13,15,17]
Output: 11
Explanation: The original array was [11,13,15,17] and it was rotated 4 times. 
 

Constraints:

n == nums.length
1 <= n <= 5000
-5000 <= nums[i] <= 5000
All the integers of nums are unique.
nums is sorted and rotated between 1 and n times.
*/

// binary search -- iterative
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0;
        int h = nums.size() - 1;
        while(l < h) {  // when l==h, answer is found
            int mid = l + (h-l)/2;

            // NOTE: if we compare mid vs. l, we cann't reduce the range!!!
            // -- when nums[l]<nums[mid], min can exist either in [l,mid], or [mid+1,h]
            if(nums[mid] < nums[h])
                h = mid;
            else
                l = mid + 1;
        }
        
        return nums[l];
    }
};


// divide and conquer
// since one of the subarray is sorted, T(N) = O(1) + T(N/2) ==> time complexity is O(lgN)
class Solution {
public:
    int findMin(vector<int>& nums) {
        return findMin(nums, 0, nums.size()-1);
    }
    
private:
    // find min in [l,r] range
    int findMin(const vector<int> &nums, int l, int r) {
        if(nums[l] < nums[r])  // already sorted
            return nums[l];
        
        if(r-l <= 1)  // one or two elements
            return min(nums[l],nums[r]);
        
        int mid = l + (r-l)/2;
        return min(findMin(nums,l,mid), findMin(nums,mid+1,r));
    }
};


// binary search -- recursive
class Solution {
public:
    int findMin(vector<int>& nums) {
        return helper(nums, 0, nums.size());
    }
    
private:
    int helper(const vector<int> &nums, int l, int r) {
        if(nums[l] < nums[r-1])
            return nums[l];
        
        if(r-l <= 2)  // since nums[l]>nums[r-1]
            return nums[r-1];
        
        int mid = l + (r-l)/2;
        if(nums[l] <= nums[mid-1])
            return helper(nums, mid, r);
        else
            return helper(nums, l, mid);
    }
};
