/*
Facebook/Amazon/Uber/Nvidia/Adobe/Apple/Google/Bloomberg/Microsoft/Yahoo/Oracle/Infosys/ServiceNow

You are given a sorted array consisting of only integers where every element appears exactly twice, except for one element which appears exactly once.

Return the single element that appears only once.

Your solution must run in O(log n) time and O(1) space.

 

Example 1:

Input: nums = [1,1,2,3,3,4,4,8,8]
Output: 2
Example 2:

Input: nums = [3,3,7,7,10,11,11]
Output: 10
 

Constraints:

1 <= nums.length <= 10^5
0 <= nums[i] <= 10^5
*/


// binary search
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        // binary search: the number must exists in the array with odd size
        int l = 0;
        int r = nums.size() - 1;
        // [l, r] range
        while(l < r) {  // size must be odd and also greater than 1
            int mid = l + (r-l)/2;
            if(nums[mid] == nums[mid-1]) {
                if((mid-l)%2)  // this further check is important as to determine which half has odd size
                    l = mid + 1;
                else
                    r = mid;
            }
            else if(nums[mid] == nums[mid+1]) {
                if((r-mid)%2)
                    r = mid - 1;
                else
                    l = mid;
            }
            else
                return nums[mid];
        }

        return nums[l];
    }
};


// ref sol 1: same idea as above
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int lo = 0;
        int hi = nums.size() - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            bool halvesAreEven = (hi - mid) % 2 == 0;
            if (nums[mid + 1] == nums[mid]) {
                if (halvesAreEven) {
                    lo = mid + 2;
                } else {
                    hi = mid - 1;
                }
            } else if (nums[mid - 1] == nums[mid]) {
                if (halvesAreEven) {
                    hi = mid - 2;
                } else {
                    lo = mid + 1;
                }
            } else {
                return nums[mid];
            }
        }
        return nums[lo];
    }
};


// ref sol 2: only on even index
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int lo = 0;
        int hi = nums.size() - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (mid % 2 == 1) mid--;
            if (nums[mid] == nums[mid + 1]) {
                lo = mid + 2;
            } else {
                hi = mid;
            }
        }
        return nums[lo];
    }
};
