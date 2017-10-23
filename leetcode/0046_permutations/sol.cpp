#include "../common/common.h"

using namespace std;

class Solution {
public:
  vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> results;
    vector<int> used(nums.size(), 0);  // whether a number has already been used
    vector<int> perm;  // one permutation
    search(nums, results, used, perm, nums.size());
    return results;
  }

  void search(const vector<int> &nums, vector<vector<int>> &results, vector<int> &used, vector<int> &perm, /* elements left*/int n) {
    if(n == 0) {
      results.push_back(perm);
      return;
    }

    for(int i=0; i<nums.size(); ++i) {
      if(used[i])
	continue;
      used[i] = 1;
      perm.push_back(nums[i]);
      search(nums, results, used, perm, n-1);
      used[i] = 0;
      perm.pop_back();
    }
  }
};

int main(int argc, char *argv[])
{
  vector<int> nums = readVector(argc, argv);
  Solution sol;
  auto results = sol.permute(nums);
  printMatrix(results);

  return 0;
}
