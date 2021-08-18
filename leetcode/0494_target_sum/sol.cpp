/*
You are given an integer array nums and an integer target.

You want to build an expression out of nums by adding one of the symbols '+' and '-' before each integer in nums and then concatenate all the integers.

For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and concatenate them to build the expression "+2-1".
Return the number of different expressions that you can build, which evaluates to target.

 

Example 1:

Input: nums = [1,1,1,1,1], target = 3
Output: 5
Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3
Example 2:

Input: nums = [1], target = 1
Output: 1
 

Constraints:

1 <= nums.length <= 20
0 <= nums[i] <= 1000
0 <= sum(nums[i]) <= 1000
-1000 <= target <= 1000
*/


#include "../common/common.h"

using namespace std;

// DP bottom-up (pull style)
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(target>sum || target<-sum)
            return 0;
        // dp(i, n): number of different ways to add up to n using nums[0,...,i]
        // dp(i,n) = dp(i-1, n-nums[i]) + dp(i-1, n+nums[i])
        vector<int> dp(2*sum+1, 0);  // reduce to one dimension, and also shift index to account for negative values
        dp[nums[0]+sum] += 1;  // use positive nums[0]
        dp[-nums[0]+sum] += 1;   // use negative nums[0], note +0 and -0 are considered as two different ways
        for(int i=1; i<nums.size(); ++i) {
            vector<int> dpn(2*sum+1, 0);
            for(int n=-sum; n<=sum; ++n) {
                if(n+nums[i]+sum<=2*sum)  
                    dpn[n+sum] += dp[n+nums[i]+sum];  // use nums[i] as negative
                if(n-nums[i]+sum>=0)
                    dpn[n+sum] += dp[n-nums[i]+sum];  // use nums[i] as positive
            }
            dp.swap(dpn);
        }
        return dp[target+sum];
    }
};

// DP bottom (push style)
class Solution {
public:
    // Push style
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(target>sum || target<-sum)
            return 0;
        // dp(i, n): number of different ways to add up to n using nums[0,...,i]
        // dp(i,n) = dp(i-1, n-nums[i]) + dp(i-1, n+nums[i])
        // Alternatively, we can push dp(i-1,n) to dp(i,n+nums[i]) and dp(i,n-nums[i])
        vector<int> dp(2*sum+1, 0);  // reduce to one dimension, and also shift index to account for negative values
        dp[nums[0]+sum] += 1;  // use positive nums[0]
        dp[-nums[0]+sum] += 1;   // use negative nums[0], note +0 and -0 are considered as two different expressions
        for(int i=1; i<nums.size(); ++i) {
            vector<int> dpn(2*sum+1, 0);
            for(int n=-sum; n<=sum; ++n) {
                if(dp[n+sum]>0) {  // in push sytle, it automatically guarantees boundary correctness
                    dpn[n+nums[i]+sum] += dp[n+sum];
                    dpn[n-nums[i]+sum] += dp[n+sum];
                }
            }
            dp.swap(dpn);
        }
        return dp[target+sum];
    }
};


// DP with memoization
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
