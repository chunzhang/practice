/*
Given an array nums which consists of non-negative integers and an integer m, you can split the array into m non-empty continuous subarrays.

Write an algorithm to minimize the largest sum among these m subarrays.

 

Example 1:

Input: nums = [7,2,5,10,8], m = 2
Output: 18
Explanation:
There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8],
where the largest sum among the two subarrays is only 18.
Example 2:

Input: nums = [1,2,3,4,5], m = 2
Output: 9
Example 3:

Input: nums = [1,4,4], m = 3
Output: 4
 

Constraints:

1 <= nums.length <= 1000
0 <= nums[i] <= 10^6
1 <= m <= min(50, nums.length)
*/

// DP O(m*N*N) time, O(m*N) space
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        // dp(i,p): minimal largest sum in nums[0:i) with p partitions
        // dp(i,p) = min{max(dp(i-len, p-1), rollingSum} for all len<=i
        const int N = nums.size();
        vector<vector<int>> dp(N+1, vector<int>(m+1, INT_MAX));
        dp[0][0] = 0;  // important boundary condition
        
        for(int i=1; i<=N; ++i) {
            for(int p=1; p<=m; ++p) {
                int sum = 0;
                //dp[i][p] = INT_MAX;
                for(int len=1; i-len>=p-1/*must have enough elements for remaining p-1 partitions*/; ++len) {
                    sum += nums[i-len];
                    dp[i][p] = min(dp[i][p], max(dp[i-len][p-1], sum));
                }
            }
        }
        
        return dp[N][m];
    }
};


// A even smarter binary search solution O(N*lgS), where N is the size of nums, S is the sum of nums
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        // binary search in [l,r) range
        int l = *max_element(nums.begin(), nums.end());
        int r = accumulate(nums.begin(), nums.end(), 0) + 1;
        while(l<r) {
            int mid = l+(r-l)/2;
            if(g(nums, m, mid))
                r = mid;
            else
                l = mid+1;
        }
        return l;  // this is first number that satisfies g() function, i.e., read HuaHua's template
    }
    
private:
    bool g(const vector<int> &nums, const int m, const int cap) {
        int sum = 0;
        int p = 1;  // number of partitions needed s.t. each partition has sum<=cap
        for(int num : nums) {
            sum += num;
            if(sum > cap) {
                sum = num;
                ++p;
            }
            if(p > m)
                return false;
        }
        return true;
    }
};
