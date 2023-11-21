/*
Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.

 

Example 1:

Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]
Example 2:

Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation: 
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]
 

Constraints:

1 <= nums.length <= 105
-231 <= nums[i] <= 231 - 1
0 <= k <= 105
 

Follow up:

Try to come up with as many solutions as you can. There are at least three different ways to solve this problem.
Could you do it in-place with O(1) extra space?
*/


// Solution 1: use additional array
// O(N) time, O(K) space
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        // use an additional array to store the first k elements to be moved
        const int sz = nums.size();
        k %= sz;
        if(k == 0)
            return;
        vector<int> vec(nums.end()-k, nums.end());
        for(int i=sz-1; i>=k; --i)
            nums[i] = nums[i-k];
        copy(vec.begin(), vec.end(), nums.begin());
    }
};

// Solution 2: use three array reverse
// O(N) time, O(1) space
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        const int N = nums.size();
        k %= N;
        if(k == 0)
            return;

        // for [1,2,3,4,5,6,7], k=3
        // First reverse entire array: [7,6,5,4,3,2,1]
        // Then, reverse k first element: [5,6,7,4,3,2,1]
        // Lastly reverse last N-k elements: [5,6,7,1,2,3,4]
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin()+k);
        reverse(nums.begin()+k, nums.end());
    }

};

// Solution 3: use in-place movement/substitution
// O(N) time, O(1) space
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        // In-place movement: nums[i] ==> nums[(i+k)%N]
        // Always remember the index and number that is substituted out
        // note the need to jump out of cyclic looping: e.g., index 2 ==> index 4 ==> index 2 ==> ...
        const int N = nums.size();
        k %= N;
        if(k == 0)
            return;
        
        // total N count of movements
        for(int startIdx=0,count=0; count<N; ++startIdx) {
            int curIdx = startIdx;
            int curNum = nums[curIdx];
            do {
                int nextIdx = (curIdx+k) % N;
                int temp = nums[nextIdx];
                nums[nextIdx] = curNum;
                curIdx = nextIdx;
                curNum = temp;
                ++count;
            } while(curIdx!=startIdx);  // detects loop, then increment startIdx (note there's no need to check count<N here)
        }
    }
};
