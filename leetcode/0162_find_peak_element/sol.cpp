/*
  A peak element is an element that is strictly greater than its neighbors.

  Given an integer array nums, find a peak element, and return its index. If the array contains multiple peaks, return the index to any of the peaks.

  You may imagine that nums[-1] = nums[n] = -∞.

  You must write an algorithm that runs in O(log n) time.

 

  Example 1:

  Input: nums = [1,2,3,1]
  Output: 2
  Explanation: 3 is a peak element and your function should return the index number 2.
  Example 2:

  Input: nums = [1,2,1,3,5,6,4]
  Output: 5
  Explanation: Your function can return either index number 1 where the peak element is 2, or index number 5 where the peak element is 6.
 

  Constraints:

  1 <= nums.length <= 1000
  -2^31 <= nums[i] <= 2^31 - 1
  nums[i] != nums[i + 1] for all valid i.
*/

// binary search
// find first element with nums[i]>nums[i+1]
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int l = 0;
        int r = nums.size();
        while(l < r) {
            int mid = l + (r-l)/2;
            if(mid==nums.size()-1 || nums[mid]>nums[mid+1])  // note that last element automatically satisfy nums[mid]>nums[mid+1]
                r = mid;
            else
                l = mid + 1;
        }
        
        return l;
    }
};


// my different impl of binary search
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        // binary search in [lo, hi)
        int lo = 0;
        int hi = nums.size();

        while(lo<hi) {
            int mid = lo + (hi-lo)/2;
            if((mid==0||nums[mid]>nums[mid-1]) && (mid==nums.size()-1||nums[mid]>nums[mid+1]))  // find peak
                return mid;
            
            if(mid!=0 && nums[mid]<nums[mid-1])  // mid is on falling path ==> peak on its left
                hi = mid;
            else
                lo = mid+1;
        }

        return lo;
    }
};

// binary search -- a different impl
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        const int N = nums.size();
        int lo = 0;
        int hi = N - 1;
        while(lo <= hi) {
            int mid = lo + (hi-lo)/2;
            if(mid<N-1 && nums[mid]<nums[mid+1])     // on rising path
                lo = mid + 1;
            else if(mid>0 && nums[mid]<nums[mid-1])  // on falling path
                hi = mid - 1;
            else
                return mid;
        }
        
        return -1;  // should not reach here
    }
};

// O(N) time complexity, but intersting
// detect first element that drops -- based on the fact that nums[-1]=-inf
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        if(nums.size()<=1)
            return 0;

        for(int i=1; i<nums.size(); ++i){
            if(nums[i] < nums[i-1])
                return i-1;
        }

        return nums.size()-1;
    }
};
