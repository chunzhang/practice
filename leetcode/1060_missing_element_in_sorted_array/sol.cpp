/*
Given an integer array nums which is sorted in ascending order and all of its elements are unique and given also an integer k, return the kth missing number starting from the leftmost number of the array.

 

Example 1:

Input: nums = [4,7,9,10], k = 1
Output: 5
Explanation: The first missing number is 5.
Example 2:

Input: nums = [4,7,9,10], k = 3
Output: 8
Explanation: The missing numbers are [5,6,8,...], hence the third missing number is 8.
Example 3:

Input: nums = [1,2,4], k = 3
Output: 6
Explanation: The missing numbers are [3,5,6,7,...], hence the third missing number is 6.
 

Constraints:

1 <= nums.length <= 5 * 10^4
1 <= nums[i] <= 10^7
nums is sorted in ascending order, and all the elements are unique.
1 <= k <= 10^8
 

Follow up: Can you find a logarithmic time complexity (i.e., O(log(n))) solution?
*/


// binary search: find first (i.e., smallest) number where there're enough missing elements to its left
class Solution {
public:
    int missingElement(vector<int>& nums, int k) {
        int lo = 0;
        int hi = nums.size();
        while(lo < hi) {
            int mid = lo + (hi-lo)/2;
            int total = nums[mid] - nums[0] + 1;  // total number in range [0, mid]
            int missing = total - (mid+1);  //  missing number in range [0, mid]
            if(missing >= k) {  // g(m): enough missing number to its left
                hi = mid;
            }
            else {
                lo = mid + 1;
            }
        }
        
        int missing = nums[lo-1] - nums[0] + 1 - lo;  // missing numbers in [lo, lo-1]
        return nums[lo-1] + k - missing;
    }
};



// binary search: a different but still working impl
class Solution {
public:
    int missingElement(vector<int>& nums, int k) {
        int lo = 0;
        int hi = nums.size();
        while(lo < hi) {
            int total = nums[hi-1] - nums[lo] + 1;
            int missing = total - (hi-lo);
            if(k > missing)
                return nums[hi-1] + (k-missing);
            
            int mid = lo + (hi-lo)/2;
            total = nums[mid] - nums[lo] + 1;
            missing = total - (mid-lo+1);
            if(missing >= k) {
                hi = mid;
            }
            else {
                lo = mid;  // will not cause infinit loop as we have another exit condition
                k -= missing;
            }
        }
        
        return -1;  // should never reach here
    }
};
