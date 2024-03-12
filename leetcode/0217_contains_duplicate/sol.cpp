/*
Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.

Example 1:

Input: nums = [1,2,3,1]
Output: true

Example 2:

Input: nums = [1,2,3,4]
Output: false

Example 3:

Input: nums = [1,1,1,3,3,4,3,2,4,2]
Output: true
 

Constraints:

1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
*/


// based on hash table
// time: O(N)
// space: O(N)
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> ns;
        for(int num : nums) {
            if(ns.count(num))
                return true;
            ns.insert(num);
        }
        return false;
    }
};


// based on sorting
// time: O(NlgN)
// space: O(1)
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for(int i=1; i<nums.size(); ++i)
            if(nums[i] == nums[i-1])
                return true;

        return false;
    }
};
