/*
Facebook/Yandex/Amazon

Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.

Note that you must do this in-place without making a copy of the array.

 

Example 1:

Input: nums = [0,1,0,3,12]
Output: [1,3,12,0,0]
Example 2:

Input: nums = [0]
Output: [0]
 

Constraints:

1 <= nums.length <= 104
-231 <= nums[i] <= 231 - 1
 

Follow up: Could you minimize the total number of operations done?
*/

#include "../common/common.h"

using namespace std;

// idea: two pointers to move all non-zero numbers, and fill zeros at the end of the array
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int cur = 0;
        for(int i=0; i<nums.size(); ++i)
            if(nums[i])
                nums[cur++] = nums[i];
        while(cur<nums.size())  // filling zeros
            nums[cur++] = 0;
    }
};

// use swap to avoid filling zeros in the end
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int cur = 0;
        for(int i=0; i<nums.size(); ++i)
            if(nums[i])
                swap(nums[cur++],nums[i]);
    }
};

// further avoid unnecessary memory writes
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int cur = 0;
        for(int i=0; i<nums.size(); ++i)
            if(nums[i]) {
                if(i != cur)  // otherwise avoid memory writes
                    swap(nums[cur],nums[i]);
                ++cur;
            }
    }
};
