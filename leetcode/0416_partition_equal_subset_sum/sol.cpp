/*
Given a non-empty array nums containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

 

Example 1:

Input: nums = [1,5,11,5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].
Example 2:

Input: nums = [1,2,3,5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.
 

Constraints:

1 <= nums.length <= 200
1 <= nums[i] <= 100
*/

// DP O(N*sum), push style
class Solution {
public:
    // push style of DP implementation; under the hood, this is very similar to the bit-manipulation based solution
    bool canPartition(vector<int>& nums) {
        // Can I find a sub-set of elements in nums that add up to sum(nums)/2?
        // dp(i,n): whether I can use elements from nums[0,...,i] to get amount n
        // dp(i,n) can be calculated from dp(i-1, n-nums[i]) and dp(i-1,n)
        // Alternatively, we can push dp(i-1,n) to dp(i,n) and dp(i, n+nums[i])
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(sum & 0x1)  // odd number, definitely no solution
            return false;
        int target = sum>>0x1;  // divide by 2
        vector<int> dp(sum+1, 0);  // The i dimension can be reduced
        dp[0] = 1;  // we can always select no number to add up to 0
        dp[nums[0]] = 1;
        for(int i=1; i<nums.size(); ++i) {
            vector<int> dpn = dp;  // implicitly, dp(i,n) is pushed to dp(i+1,n)
            for(int n=0; n<=sum; ++n) {
                if(dp[n] == 1)
                    dpn[n+nums[i]] = 1;  // push dp(i,n) to dp(i+1,n+nums[i])
            }
            if(dpn[target])  // early exit
                return true;
            dp.swap(dpn);
        }
        
        return dp[target];
    }
};


// DP O(N*target) time complexity
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        // Can I find a sub-set of elements in nums that add up to sum(nums)/2?
        // dp(i,n): whether I can use elements from nums[0,...,i] to get amount n
        // dp(i,n) can be calculated from dp(i-1, n-nums[i]) and dp(i-1,n)
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(sum & 0x1)  // odd number, definitely no solution
            return false;
        int target = sum/2;  // target amount
        vector<int> dp(target+1, 0);  // we can reduce the i dimension
        dp[0] = 1;  // by selecting no numbers, we can add it to amount 0
        if(nums[0] <= target)
            dp[nums[0]] = 1;  // first num
        for(int i=1; i<nums.size(); ++i) {
            vector<int> dpn(target+1, 0);
            dpn[0] = 1;
            for(int n=1; n<=target; ++n) {
                int use = (n-nums[i]>=0?dp[n-nums[i]]:0);  // select nums[i]
                int notUse = dp[n];                        // not select nums[i]
                dpn[n] = use|notUse;
            }
            if(dpn[target])   // early exit
                return true;
            dp.swap(dpn);
        }
        
        return dp[target];
    }
};

// A very smart bit-manipulation solution, O(N) time complexity
class Solution {
public:
    // This is based on smart bit manipulation
  bool canPartition(vector<int>& nums) {
    // bits[i]==1 means we can pick up elements from nums that sums up to i
    // -- since max sum is 100*200/2, we need size 10,000 + 1 (to account sum==0)
    // -- bits[0]==1 (i.e., from 0x1) means sum==0 is true as the boundary condition
    bitset<10001> bits(0x1);
    int sum = accumulate(nums.begin(), nums.end(), 0);
    // add new combination of sum into 'bits' when a new number 'n' is encountered
    // -- let's say previous we have bits[10]=1 (meaning there's a previous sum=10 for all elements
    //    before n)
    // -- let's say n=5, now we have n[15]=1 (n is picked up) due to the << operation and n[10]=1 (n
    //    is not picked up) due to the |= operation
    for(int n : nums)
      bits |= bits<<n;

    return !(sum&0x1) && bits[sum>>0x1];
  }
  
};
