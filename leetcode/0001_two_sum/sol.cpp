#include "../common/common.h"
#include <unordered_map>

class Solution {
public:
  vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> num2Idx;
    vector<int> result;
    for(int i=0; i<nums.size(); ++i){
      auto it = num2Idx.find(target-nums[i]);
      if(it != num2Idx.end()) {
	result.push_back(it->second);
	result.push_back(i);
	break;
      }
      num2Idx[nums[i]] = i;
    }
    return result;
  }
};

int main(int argc, char *argv[])
{
  vector<int> nums = readVector(argc, argv);
  int target = nums.back();
  nums.pop_back();

  Solution sol;
  vector<int> result = sol.twoSum(nums, target);
  printVector(result);
  
  return 0;
}
