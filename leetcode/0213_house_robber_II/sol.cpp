#include "../common/common.h"

class Solution {
public:
  int rob(vector<int>& nums) {
    if(nums.empty())
      return 0;
    if(nums.size() == 1)
      return nums[0];

    // Two pass to break the loop based on whether the last house is robbed
    int profit1 = robRange(nums, 0, nums.size()-2);  // not rob last house
    int profit2 = robRange(nums, 1, nums.size()-1);  // rob last house
    return max(profit1, profit2);
  }

  // max profit robbing house in [s, t]
  int robRange(const vector<int> &nums, int s, int t) {
    int pre = 0;
    int prepre = 0;
    for(int i=s; i<=t; ++i) {
      int cur = max(pre, prepre+nums[i]);
      prepre = pre;
      pre = cur;
    }
    return pre;
  }
};
