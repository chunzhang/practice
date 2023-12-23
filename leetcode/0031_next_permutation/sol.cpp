/*
Facebook/JPMorgan/Amazon

A permutation of an array of integers is an arrangement of its members into a sequence or linear order.

For example, for arr = [1,2,3], the following are all the permutations of arr: [1,2,3], [1,3,2], [2, 1, 3], [2, 3, 1], [3,1,2], [3,2,1].
The next permutation of an array of integers is the next lexicographically greater permutation of its integer. More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, then the next permutation of that array is the permutation that follows it in the sorted container. If such arrangement is not possible, the array must be rearranged as the lowest possible order (i.e., sorted in ascending order).

For example, the next permutation of arr = [1,2,3] is [1,3,2].
Similarly, the next permutation of arr = [2,3,1] is [3,1,2].
While the next permutation of arr = [3,2,1] is [1,2,3] because [3,2,1] does not have a lexicographical larger rearrangement.
Given an array of integers nums, find the next permutation of nums.

The replacement must be in place and use only constant extra memory.

 

Example 1:

Input: nums = [1,2,3]
Output: [1,3,2]
Example 2:

Input: nums = [3,2,1]
Output: [1,2,3]
Example 3:

Input: nums = [1,1,5]
Output: [1,5,1]
 

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 100
*/


// idea is to first identify LSB to be swapped, then sort all numbers after it
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        for(int i=nums.size()-2; i>=0; --i) {
            int candIdx = -1;
            for(int j=i+1; j<nums.size(); ++j) {
                if(nums[j]>nums[i] && (candIdx==-1 || nums[j]<nums[candIdx]))
                    candIdx = j;
            }
            if(candIdx != -1) {  // found number to swap
                swap(nums[i], nums[candIdx]);
                sort(nums.begin()+i+1, nums.end());
                return;
            }
        }

        reverse(nums.begin(), nums.end());  // array is in reverse sorted manner, so return it's reverse as the next permutation
        return;
    }
};


// a very smart solution
// First, find right most pair that satisfies a[i]<a[i+1] ==> i is the LSB to be swapped
//   -- Note it guarantees that a[i+1], a[i+2], ... are in reverse sorted order (i.e., large to small)
// Second, find smallest number in a[i+1], a[i+2], ..., that is greater than a[i] ==> let the index be j of such number
//   -- Now we swap a[i] and a[j]
//   -- Note after the swap, a[i+1], a[i+2], ... are still in reverse sorted order
// Lastly, we reverse a[i+1], a[i+2], ...
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int i = nums.size() - 2;
        // find LSB to be swapped, i.e., first pair (searching from right): nums[i]<nums[i+1]
        while(i>=0 && nums[i]>=nums[i+1])
            --i;
        if(i >= 0) {  // find such pair
            int j = nums.size() - 1;
            while(nums[j] <= nums[i])
                --j;
            swap(nums[i],nums[j]);
        }

        reverse(nums.begin()+i+1, nums.end());  // rest of the array is already in reverse-sorted order
    }
};
