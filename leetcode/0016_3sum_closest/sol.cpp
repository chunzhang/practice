/*
Given an integer array nums of length n and an integer target, find three integers in nums such that the sum is closest to target.

Return the sum of the three integers.

You may assume that each input would have exactly one solution.

 

Example 1:

Input: nums = [-1,2,1,-4], target = 1
Output: 2
Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
Example 2:

Input: nums = [0,0,0], target = 1
Output: 0
 

Constraints:

3 <= nums.length <= 1000
-1000 <= nums[i] <= 1000
-10^4 <= target <= 10^4
*/

// use two pointers
// time complexity: O(N^2)
// space complexity: depends on sorting
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int ans = INT_MAX/2;
        sort(nums.begin(), nums.end());
        for(int i=0; i<nums.size(); ++i) {
            if(i>0 && nums[i]==nums[i-1])  // avoid wasting on duplicates
                continue;
            for(int j=i+1,k=nums.size()-1; j<k; ) {
                if(j>i+1 && nums[j]==nums[j-1]) {  // further avoid wasting on duplicates
                    ++j;
                    continue;
                }
                int sum = nums[i]+nums[j]+nums[k];
                if(sum == target)
                    return sum;
                if(abs(sum-target) < abs(ans-target))
                    ans = sum;
                
                if(sum < target)
                    ++j;
                else
                    --k;
            }
        }
        
        return ans;
    }
};


// use binary search
// time complexity: O(N*N*lgN)
// space complexity: depends on sorting
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int ans = INT_MAX/2;
        sort(nums.begin(), nums.end());
        for(int i=0; i<nums.size(); ++i) {
            if(i>0 && nums[i]==nums[i-1])  // avoid wasting on duplicates
                continue;
            for(int j=i+1; j<nums.size(); ++j) {
                if(j>i+1 && nums[j]==nums[j-1])
                    continue;
                
                // binary search: find first k such that nums[i]+nums[j]+nums[k]>=target
                int k = distance(nums.begin(), lower_bound(nums.begin()+j+1, nums.end(), target-nums[i]-nums[j]));
                if(k < nums.size()) {
                    int sum = nums[i] + nums[j] + nums[k];
                    if(sum == target)
                        return sum;
                    if(abs(sum-target) < abs(ans-target))
                        ans = sum;
                }
                if(k>j+1) {
                    int sum = nums[i] + nums[j] + nums[k-1];
                    if(abs(sum-target) < abs(ans-target))
                        ans = sum;
                }
            }
        }
        
        return ans;
    }
};
