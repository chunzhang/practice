/*
Facebook/Nvidia/Google/Uber

Given an integer array nums, design an algorithm to randomly shuffle the array. All permutations of the array should be equally likely as a result of the shuffling.

Implement the Solution class:

Solution(int[] nums) Initializes the object with the integer array nums.
int[] reset() Resets the array to its original configuration and returns it.
int[] shuffle() Returns a random shuffling of the array.
 

Example 1:

Input
["Solution", "shuffle", "reset", "shuffle"]
[[[1, 2, 3]], [], [], []]
Output
[null, [3, 1, 2], [1, 2, 3], [1, 3, 2]]

Explanation
Solution solution = new Solution([1, 2, 3]);
solution.shuffle();    // Shuffle the array [1,2,3] and return its result.
                       // Any permutation of [1,2,3] must be equally likely to be returned.
                       // Example: return [3, 1, 2]
solution.reset();      // Resets the array back to its original configuration [1,2,3]. Return [1, 2, 3]
solution.shuffle();    // Returns the random shuffling of array [1,2,3]. Example: return [1, 3, 2]

 

Constraints:

1 <= nums.length <= 50
-10^6 <= nums[i] <= 10^6
All the elements of nums are unique.
At most 10^4 calls in total will be made to reset and shuffle.
*/

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */


// idea is to randomly pick an unslected number for each position -- Fisher-Yates Algorithm
// each call of shuffle() is of O(N) time complexity
class Solution {
public:
    Solution(vector<int>& nums) : m_origNums(nums) {
        
    }
    
    vector<int> reset() {
        return m_origNums;
    }
    
    vector<int> shuffle() {
        vector<int> nums = m_origNums;
        for(int len=nums.size(); len>0; --len) {  // populate from last number for easy of implementation
            int idx = rand()%len;  // randomly picked up number for len-1 location
            swap(nums[idx], nums[len-1]);
        }
        return nums;
    }

private:
    vector<int> m_origNums;
};


// due to the extensive use of reset, simply doing many times of swap does not work!!!
// this is becasue it has bias over previous shuffled result -- so not evenly randomized among all permutations!!!
class Solution {
public:
    Solution(vector<int>& nums) : m_origNums(nums), m_nums(nums){
        
    }
    
    vector<int> reset() {
        m_nums = m_origNums;
        return m_nums;
    }
    
    vector<int> shuffle() {
        for(int i=0; i<m_nums.size(); ++i) {
            swap(m_nums[0], m_nums[rand()%m_nums.size()]);
        }
        return m_nums;
    }

private:
    vector<int> m_origNums;
    vector<int> m_nums;
};
