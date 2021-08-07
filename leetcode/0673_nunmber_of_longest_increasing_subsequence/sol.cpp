/*
Given an integer array nums, return the number of longest increasing subsequences.

Notice that the sequence has to be strictly increasing.

 

Example 1:

Input: nums = [1,3,5,4,7]
Output: 2
Explanation: The two longest increasing subsequences are [1, 3, 4, 7] and [1, 3, 5, 7].
Example 2:

Input: nums = [2,2,2,2,2]
Output: 5
Explanation: The length of longest continuous increasing subsequence is 1, and there are 5 subsequences' length is 1, so output 5.

 

Constraints:

1 <= nums.length <= 2000
-10^6 <= nums[i] <= 10^6
*/

// DP O(N^2)
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        vector<int> maxLen(nums.size(), 1);  // max length of strictly increase sub-sequence that ends at i
        vector<int> count(nums.size(), 1);   // count of sub-sequences
        
        int longest = 1;
        for(int i=1; i<nums.size(); ++i) {
            for(int j=0; j<i; ++j) {
                if(nums[i] > nums[j]) {  // a new increase sub-sequence can be formed
                    int curLen = maxLen[j] + 1;
                    if(curLen > maxLen[i]) {  // reset count
                        maxLen[i] = curLen;
                        count[i] = count[j];
                    }
                    else if(curLen == maxLen[i]) {  // accumulate count
                        count[i] += count[j];
                    }
                }
            }
            longest = max(longest, maxLen[i]);
        }
        
        // collect results
        int ans = 0;
        for(int i=0; i<nums.size(); ++i)
            if(maxLen[i] == longest)
                ans += count[i];
        
        return ans;
    }
};
