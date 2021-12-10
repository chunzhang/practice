/*
Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.

There is only one repeated number in nums, return this repeated number.

You must solve the problem without modifying the array nums and uses only constant extra space.

 

Example 1:

Input: nums = [1,3,4,2,2]
Output: 2
Example 2:

Input: nums = [3,1,3,4,2]
Output: 3
Example 3:

Input: nums = [1,1]
Output: 1
Example 4:

Input: nums = [1,1,2]
Output: 1
 

Constraints:

1 <= n <= 10^5
nums.length == n + 1
1 <= nums[i] <= n
All the integers in nums appear only once except for precisely one integer which appears two or more times.
 

Follow up:

How can we prove that at least one duplicate number must exist in nums?
Can you solve the problem in linear runtime complexity?
*/



// hack by modifying input nums vector
// time complexity: O(N)
// space complexity: O(1), need to modify original input array
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums[0];
        for(int i=0; i<nums.size(); ++i) {
            if(nums[n] == -1)  // find the duplciate
                return n;
            int nx = nums[n];
            nums[n] = -1;  // record that the number has appeared
            n = nx;
        }
        
        return -1;  // should not reach here
    }
};


// reuse original inputs, but can recover it back after used
// time complexity: O(N)
// space complexity: O(1), need to modify original input array
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums[0];
        for(int i=0; i<nums.size(); ++i) {
            if(nums[n] < 0)
                return n;
            nums[n] = -nums[n];
            n = -nums[n];
        }
        
        // recover original inputs
        for(int i=0; i<nums.size(); ++i)
            nums[i] = abs(nums[i]);
        
        return -1;  // should not reach here
    }
};


// another interesting: put number to the same index, e.g., number 3 should be put to index-3
// once we find that the index is re-visited, we find the duplicate
// time complexity: O(N)
// space complexity: O(1), but needs to modify original input array
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        while (nums[0] != nums[nums[0]])
            swap(nums[0], nums[nums[0]]);
        return nums[0];
    }
};


// one can imagine that the inputs forms a linked-list with cycle
// as such, one can use same technique as "Linked List Cycle II" to find the cycle entrance
// time complexity: O(N)
// space complexity: O(1), no need to change input array
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        // use same technique as finding cycle entrance in linked list
        int slow = nums[0];
        int fast = nums[0];
        while(1) {  // since cycle is guaranteed to exist, we will always break from the while loop
            slow = nums[slow];
            fast = nums[nums[fast]];
            if(slow == fast)
                break;
        }
        
        int slow2 = nums[0];
        while(slow != slow2) {  // next meeting point is the loop entrance
            slow = nums[slow];
            slow2 = nums[slow2];
        }
        
        return slow;
    }
};


// the duplicate number will have a count of numbers less than or equal to itself, that is greater than itself
// hence, the smallest number that satisfies this property is the duplicate number
// we can use binary search here to find first/smallest such number
// time complexity: O(NlgN)
// space complexity: O(1)
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int lo = 1;
        int hi = nums.size();
        while(lo < hi) {
            int mid = lo + (hi-lo)/2;
            if(count(nums,mid) > mid)  // find first/smallest number that there're more than mid count of numbers in the input array which is smaller or equal to mid
                hi = mid;
            else
                lo = mid + 1;
        }
        
        return lo;
    }
    
private:
    // count numbers that is smaller or equal to m
    int count(const vector<int> &nums, int m) {
        int c = 0;
        for(int n : nums)
            if(n <= m)
                ++c;
        return c;
    }
};

