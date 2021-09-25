/*
Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order, find two numbers such that they add up to a specific target number. Let these two numbers be numbers[index1] and numbers[index2] where 1 <= first < second <= numbers.length.

Return the indices of the two numbers, index1 and index2, as an integer array [index1, index2] of length 2.

The tests are generated such that there is exactly one solution. You may not use the same element twice.

 

Example 1:

Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: The sum of 2 and 7 is 9. Therefore index1 = 1, index2 = 2.
Example 2:

Input: numbers = [2,3,4], target = 6
Output: [1,3]
Explanation: The sum of 2 and 4 is 6. Therefore index1 = 1, index2 = 3.
Example 3:

Input: numbers = [-1,0], target = -1
Output: [1,2]
Explanation: The sum of -1 and 0 is -1. Therefore index1 = 1, index2 = 2.
 

Constraints:

2 <= numbers.length <= 3 * 10^4
-1000 <= numbers[i] <= 1000
numbers is sorted in non-decreasing order.
-1000 <= target <= 1000
The tests are generated such that there is exactly one solution.
*/

// use two pointers
// time complexity: O(N), space complexity: O(1)
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        for(int i=0,j=numbers.size()-1; i<j; ) {
            int sum = numbers[i] + numbers[j];
            if(sum == target)
                return {i+1,j+1};
            else if(sum > target)
                --j;
            else
                ++i;
        }
        
        return {-1,-1};
    }
};


// binary search
// time complexity: O(NlgN), space complexity: O(1)
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        // binary search
        for(int i=0; i<numbers.size()-1; ++i) {
            int j = distance(numbers.begin(), lower_bound(numbers.begin()+i+1, numbers.end(), target-numbers[i]));
            if(j<numbers.size() && numbers[i]+numbers[j]==target)
                return {i+1,j+1};
        }
        
        return {-1,-1};
    }
};
