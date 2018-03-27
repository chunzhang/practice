/*
  Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....

  For example, given nums = [3, 5, 2, 1, 6, 4], one possible answer is [1, 6, 2, 5, 3, 4].
*/

#include "../common/common.h"

using namespace std;

// Solution 1: sort + swap
class Solution {
public:
  void wiggleSort(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    for(int i=1; i+1<nums.size(); i+=2) {
      swap(nums[i], nums[i+1]);
    }
  }
};

// Solution 2: one-pass swap
class Solution {
public:
  void wiggleSort(vector<int>& nums) {
    for(int i=0; i+1<nums.size(); ++i) {
      if( (i%2==0 && nums[i]>nums[i+1]) ||
	  (i%2==1 && nums[i]<nums[i+1])) {
	swap(nums[i], nums[i+1]);
      }
    }
  }
};
