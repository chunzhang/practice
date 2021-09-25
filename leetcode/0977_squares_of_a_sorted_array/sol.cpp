/*
Given an integer array nums sorted in non-decreasing order, return an array of the squares of each number sorted in non-decreasing order.

 

Example 1:

Input: nums = [-4,-1,0,3,10]
Output: [0,1,9,16,100]
Explanation: After squaring, the array becomes [16,1,0,9,100].
After sorting, it becomes [0,1,9,16,100].
Example 2:

Input: nums = [-7,-3,2,3,11]
Output: [4,9,9,49,121]
 

Constraints:

1 <= nums.length <= 10^4
-10^4 <= nums[i] <= 10^4
nums is sorted in non-decreasing order.
 

Follow up: Squaring each element and sorting the new array is very trivial, could you find an O(n) solution using a different approach?
*/


// use two pointers: from cetner to left/right
// time complexity: O(N)
// space complexity: O(1) if not count for result memory
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int i = -1;  // to point to last negative number
        int j = -1;  // to point to first non-negative number
        for(int k=0; k<nums.size(); ++k) {
            if(nums[k] < 0)
                i = k;
            nums[k] = nums[k]*nums[k];
        }
        j = i + 1;
        
        vector<int> ans;
        while(i>=0 || j<nums.size()) {
            if(j>=nums.size() || i>=0&&nums[i]<nums[j])
                ans.push_back(nums[i--]);
            else
                ans.push_back(nums[j++]);
        }
        
        return ans;
    }
};


// use two pointers: from left/right to center, i.e., populate result vector from largest to smallest
// time complexity: O(N)
// space complexity: O(1) if not count for result memory
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int> ans(nums.size());
        const int N = nums.size();
        for(int i=0,j=N-1,k=N-1; i<=j; --k) {
            if(abs(nums[i]) > abs(nums[j])) {
                ans[k] = nums[i]*nums[i];
                ++i;
            }
            else {
                ans[k] = nums[j]*nums[j];
                --j;
            }
        }
        
        return ans;
    }
};
