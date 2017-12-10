/*
  Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

  For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums should be [1, 3, 12, 0, 0].

  Note:
  You must do this in-place without making a copy of the array.
  Minimize the total number of operations.
*/

/* TAGs: facebook, bloomberg */

#include "../common/common.h"

using namespace std;

class Solution {
public:
  void moveZeroes(vector<int>& nums) {
    int last = 0;
    for(int i=0; i<nums.size(); ++i) {
      if(nums[i]!=0) {
	if(i != last)
	  nums[last] = nums[i];
	++last;
      }
    }
    for( ; last<nums.size(); ++last)
      nums[last] = 0;
  }
};

int main(int argc, char *argv[])
{
  vector<int> nums = readVector(argc, argv);
  Solution sol;
  sol.moveZeroes(nums);
  printVector(nums);

  return 0;
}
