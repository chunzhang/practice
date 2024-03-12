/*

Given an integer array nums and an integer k, return true if there are two distinct indices i and j in the array such that nums[i] == nums[j] and abs(i - j) <= k.

Example 1:

Input: nums = [1,2,3,1], k = 3
Output: true

Example 2:

Input: nums = [1,0,1,1], k = 1
Output: true

Example 3:

Input: nums = [1,2,3,1,2,3], k = 2
Output: false

Constraints:

1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
0 <= k <= 10^5
*/

// using two pointers
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {

        // the special handling only speeds up bit; but the two pointers still works correctly without it
        /*
        if(k == 0)
            return false;
        */
        
        unordered_set<int> ns;
        for(int i=0,j=0; j<nums.size(); ++j) {
            if(ns.count(nums[j]))
                return true;
            ns.insert(nums[j]);
            if(j-i == k)
                ns.erase(nums[i++]);
        }

        return false;
    }
};
