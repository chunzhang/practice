/*
  154. Find Minimum in Rotated Sorted Array II
  Hard

  1940

  297

  Add to List

  Share
  Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For example, the array nums = [0,1,4,4,5,6,7] might become:

  [4,5,6,7,0,1,4] if it was rotated 4 times.
  [0,1,4,4,5,6,7] if it was rotated 7 times.
  Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

  Given the sorted rotated array nums that may contain duplicates, return the minimum element of this array.

  You must decrease the overall operation steps as much as possible.

 

  Example 1:

  Input: nums = [1,3,5]
  Output: 1
  Example 2:

  Input: nums = [2,2,2,0,1]
  Output: 0
 

  Constraints:

  n == nums.length
  1 <= n <= 5000
  -5000 <= nums[i] <= 5000
  nums is sorted and rotated between 1 and n times.
 

  Follow up: This problem is similar to Find Minimum in Rotated Sorted Array, but nums may contain duplicates. Would this affect the runtime complexity? How and why?
*/

// divide and conquer
// time complexity: average O(N), worst case O(N)
// space complexity: O(lgN), which is recursion depth
class Solution {
public:
    int findMin(vector<int>& nums) {
        return findMin(nums,0,nums.size()-1);
    }
    
private:
    int findMin(const vector<int> &nums, int l, int r) {
        if(nums[l] < nums[r])
            return nums[l];
        
        if(l == r)
            return nums[l];
        
        int mid = l + (r-l)/2;
        return min(findMin(nums,l,mid), findMin(nums,mid+1,r));
    }
};


// binary search -- iterative
// time complexity: average O(N), worst case O(N)
// space complexity: O(1)
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0;
        int h= nums.size() - 1;
        while(l < h) {
            int mid = l + (h-l)/2;
            if(nums[mid] < nums[h])
                h = mid;
            else if(nums[mid] > nums[h])
                l = mid + 1;
            else
                --h;  // this is key to handle duplicates!!!
        }
        
        return nums[l];
    }
};


// binary search -- iterative, a different impl
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0;
        int h = nums.size() - 1;

        while(l<h){
            int mid = (l+h)/2;
            if(nums[l]==nums[mid] && nums[h]==nums[l]){
                ++l;
                --h;
            }
            else if(nums[mid] <= nums[h])  // second half is in order
                h = mid;
            else
                l = mid + 1;
        }

        return nums[l];
    }
};
