#include "../common/common.h"

using namespace std;

class Solution {
public:
  bool PredictTheWinner(vector<int>& nums) {
    // Let P(i,j) be the max score the current player can win on nums[i, ..., j]
    // Then, P(i,j) = max(nums[i]-P(i+1,j), nums[j]-P(i,j-1))
    int sz = nums.size();
    vector<vector<int>> P(sz, vector<int>(sz, 0));
    for(int i=sz-1; i>=0; --i) {
      P[i][i] = nums[i];
      cout << "P[" << i << "][" << i << "] = " << P[i][i] << endl;
      for(int j=i+1; j<sz; ++j) {
	P[i][j] = max(nums[i]-P[i+1][j], nums[j]-P[i][j-1]);
	cout << "P[" << i << "][" << j << "] = " << P[i][j] << endl;
      }
    }
    
    return P[0][sz-1] >= 0;
  }
};

int main(int argc, char *argv[])
{
  vector<int> nums = readVector(argc, argv);
  Solution sol;
  bool win = sol.PredictTheWinner(nums);
  cout << "win: " << win << endl;

  return 0;
}
