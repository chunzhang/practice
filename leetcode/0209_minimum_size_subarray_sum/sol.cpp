/*
Given an array of positive integers nums and a positive integer target, return the minimal length of a contiguous subarray [numsl, numsl+1, ..., numsr-1, numsr] of which the sum is greater than or equal to target. If there is no such subarray, return 0 instead.

 

Example 1:

Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem constraint.
Example 2:

Input: target = 4, nums = [1,4,4]
Output: 1
Example 3:

Input: target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0
 

Constraints:

1 <= target <= 10^9
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^5
 

Follow up: If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log(n)).
*/

// use two pointers
// when we have window [i,j] whose sum>=target for the first time, we increment i
// however, we don't need to reset j back, since all subarrays of [i+1,j-1] does not meet target
// time complexity: O(N)
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        // use two pointers
        int ans = INT_MAX;
        int sum = nums[0];
        for(int i=0,j=0; i<=j&&j<nums.size(); ) {
            if(sum >= target) {  // any subarray between [i+1, j-1] does not meet target, as otherwise we should not reach j
                ans = min(ans,j-i+1);
                // a slight pruning here: if answer reaches 1, we can directly return
                sum -= nums[i++];
            }
            else {
                ++j;
                if(j<nums.size())
                    sum += nums[j];
            }
        }
        
        return ans==INT_MAX?0:ans;
    }
};


// use binary search: prefix sum monotonically increase!
// time complexity: O(NlgN)
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int ans = INT_MAX;
        
        // first, compute prefix sum
        vector<int> csum = nums;
        for(int i=1; i<nums.size(); ++i)
            csum[i] = csum[i-1] + nums[i];
        
        // now try for each possible sub-array starting point
        for(int i=0; i<nums.size(); ++i) {
            // use binary search to find the first element in [i:) such that sum>= target
            int l =i;
            int r = nums.size();
            while(l<r) {
                int mid = l + (r-l)/2;
                int sum = csum[mid]-csum[i]+nums[i];
                if(sum >= target)
                    r = mid;
                else
                    l = mid + 1;
            }
            
            if(l < nums.size()) {   // found valid subarray
                ans = min(ans, l-i+1);
            }
        }
        
        return ans==INT_MAX?0:ans;
    }
};


// binary search with lower_bound
// time complexity: O(NlgN)
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int ans = INT_MAX;
        
        // first, compute prefix sum
        vector<int> csum = nums;
        for(int i=1; i<nums.size(); ++i)
            csum[i] = csum[i-1] + nums[i];
        
        // now try for each possible sub-array starting point
        for(int i=0; i<nums.size(); ++i) {
            // use binary search to find the first element in [i:) such that sum>= target
            // subarray sum = csum[j]-csum[i]+nums[i] >= target ==> we want to search first j s.t. csum[j]>=target+csum[i]-nums[i]
            int j = distance(csum.begin(), lower_bound(csum.begin()+i, csum.end(), target+csum[i]-nums[i]));
            if(j < nums.size())  // find valid subarray
                ans = min(ans, j-i+1);
        }
        
        return ans==INT_MAX?0:ans;
    }
};
