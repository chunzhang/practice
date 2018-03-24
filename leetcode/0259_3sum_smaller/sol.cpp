/*
  Given an array of n integers nums and a target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.

  For example, given nums = [-2, 0, 1, 3], and target = 2.

  Return 2. Because there are two triplets which sums are less than 2:

  [-2, 0, 1]
  [-2, 0, 3]
  Follow up:
  Could you solve it in O(n2) runtime?
*/

#include "../common/common.h"

using namespace std;

class Solution {
public:
  // Note since the problem asks about "total number of such index triplets", we don't
  // need to check number uniqueness as indexes are always unique!
  int threeSumSmaller(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int res = 0;
    for(int i=0; i+2<nums.size(); ++i) {
      // Quick pruning!
      if(nums[i] + nums[i+1] + nums[i+2] >= target)
	break;
            
      int target2 = target - nums[i];
      int lo = i + 1;
      int hi = nums.size() - 1;
      while(lo < hi) {
	if(nums[lo] + nums[hi] < target2) {
	  res += hi - lo;
	  ++lo;
	}
	else {
	  --hi;
	}
      }
    }
        
        
    return res;
  }
};
