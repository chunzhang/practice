#include "../common/common.h"

using namespace std;

class Solution {
public:
  Solution() : _count(20, vector<int>(2001, -1)) {

  }
  
  int findTargetSumWays(vector<int>& nums, int S) {
    if(nums.empty())
      return 0;

    // baseline
    _count[0] = vector<int>(2001, 0);
    _count[0][nums[0]+1000] += 1;
    _count[0][-nums[0]+1000] += 1;
    
    return findTargetSumWaysRec(nums, nums.size()-1, S);
  }

  int findTargetSumWaysRec(vector<int> &nums, int end, int S) {
    if(S>1000 || S<-1000)
      return 0;

    if(_count[end][S+1000] != -1)
      return _count[end][S+1000];

    int count = 0;
    count += findTargetSumWaysRec(nums, end-1, S-nums[end]);  // plus
    count += findTargetSumWaysRec(nums, end-1, S+nums[end]);  // minus

    _count[end][S+1000] = count;
    return count;
  }
  
private:
  vector<vector<int>> _count;
};

int main(int argc, char *argv[])
{
  vector<int> nums = readVector(argc, argv);
  int S = nums.back();
  nums.pop_back();
  Solution sol;
  int count = sol.findTargetSumWays(nums, S);
  cout << "count: " << count << endl;

  return 0;
}
