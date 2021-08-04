/*
You are given an integer array nums. You want to maximize the number of points you get by performing the following operation any number of times:

Pick any nums[i] and delete it to earn nums[i] points. Afterwards, you must delete every element equal to nums[i] - 1 and every element equal to nums[i] + 1.
Return the maximum number of points you can earn by applying the above operation some number of times.

 

Example 1:

Input: nums = [3,4,2]
Output: 6
Explanation: You can perform the following operations:
- Delete 4 to earn 4 points. Consequently, 3 is also deleted. nums = [2].
- Delete 2 to earn 2 points. nums = [].
You earn a total of 6 points.
Example 2:

Input: nums = [2,2,3,3,3,4]
Output: 9
Explanation: You can perform the following operations:
- Delete a 3 to earn 3 points. All 2's and 4's are also deleted. nums = [3,3].
- Delete a 3 again to earn 3 points. nums = [3].
- Delete a 3 once more to earn 3 points. nums = [].
You earn a total of 9 points.
 

Constraints:

1 <= nums.length <= 2 * 10^4
1 <= nums[i] <= 10^4
*/

class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        // Convert this to House Rob (leetcode 198) problem: when I choose nums[i], then I can't choose the two neighboring numbers;
        // since the number range is given, I can create a new array that is indexed by numbers
        vector<int> houses(1e4+1, 0);
        for(int n : nums)
            houses[n] += n;
        
        // Now start to solve the house rob problem by DP;
        // dp(n): max points one can get by robbing up to house n
        // -- dp(n) = max(dp(n-1), dp(n-2)+house[n]) if houe[n]!=0
        // -- dp(n) = dp(n-1) if house[n]==0  ==> this is actually NOT needed as I can prove dp(n-1)>=dp(n-2)
        // Optimize to O(1) space
        int dp1 = 0;
        int dp2 = houses[1];
        for(int n=2; n<1e4+1; ++n) {
            int dp = max(dp2, dp1+houses[n]);
            dp1 = dp2;
            dp2 = dp;
        }
        
        return dp2;
    }
};
