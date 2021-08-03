/*
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed. All houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, adjacent houses have a security system connected, and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.

 

Example 1:

Input: nums = [2,3,2]
Output: 3
Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.
Example 2:

Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.
Example 3:

Input: nums = [0]
Output: 0
 

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 1000
*/

class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size() == 1)  // special boundary case
            return nums[0];
        // Key is to break the circle and then reduce the problem to the simple House Robber problem (leetcode 0198)
        // -- If house 0 is robbed, then the last house, i.e., n-1 cannot be robbed ==> simpleRob on houses [0, n-1)
        // -- If house 1 is NOT robbed, then the last house can be robbed ==> simpleRob on houes [1, n)
        int ans1 = simpleRob(nums, 0, nums.size()-1);
        int ans2 = simpleRob(nums, 1, nums.size());
        return max(ans1, ans2);
    }
    
private:
    // House robber on [s,e) w/o circle
    int simpleRob(const vector<int> &nums, int s, int e) {
        if(s >= e)
            return 0;
        int dp1 = 0;
        int dp2 = nums[s];
        for(int i=s+1; i<e; ++i) {
            int dp = max(dp2/*not rob current house*/, dp1+nums[i]/*rob current house*/);
            dp1 = dp2;
            dp2 = dp;
        }
        return dp2;
    }
};
