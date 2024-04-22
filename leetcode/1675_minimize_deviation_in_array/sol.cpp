/*
Apple

You are given an array nums of n positive integers.

You can perform two types of operations on any element of the array any number of times:

If the element is even, divide it by 2.
For example, if the array is [1,2,3,4], then you can do this operation on the last element, and the array will be [1,2,3,2].
If the element is odd, multiply it by 2.
For example, if the array is [1,2,3,4], then you can do this operation on the first element, and the array will be [2,2,3,4].
The deviation of the array is the maximum difference between any two elements in the array.

Return the minimum deviation the array can have after performing some number of operations.

Example 1:

Input: nums = [1,2,3,4]
Output: 1
Explanation: You can transform the array to [1,2,3,2], then to [2,2,3,2], then the deviation will be 3 - 2 = 1.

Example 2:

Input: nums = [4,1,5,20,3]
Output: 3
Explanation: You can transform the array after two operations to [4,2,5,5,3], then the deviation will be 5 - 2 = 3.

Example 3:

Input: nums = [2,10,8]
Output: 3
 

Constraints:

n == nums.length
2 <= n <= 5 * 10^4
1 <= nums[i] <= 10^9
*/

// greedy: grow each number to it's max (i.e., multiple two for all odd number) -- this does not change solution space;
// then, the min deviation can only be achieved by shrinking max num (since min num cannot be doubled as it's already even)
// time: O(KlgN), where K is the the times where max num can be shrinked
// space: O(N)
class Solution {
public:
    int minimumDeviation(vector<int>& nums) {
        // greedy: first grow each number to it's max possible, then start to reduce the max number until we cannot
        priority_queue<int> pq;  // top is the max number
        int curMin = INT_MAX;  // keep track of smallest number in the pq
        for(int n : nums) {
            if(n%2)  // only odd number can grow once, while even number can only shrink
                n *= 2;
            pq.push(n);
            curMin = min(curMin, n);
        }

        int ans = pq.top() - curMin;
        // greedily shrink largest number
        while(pq.top()%2 == 0) {  // only even number can shrink
            int val = pq.top() / 2;
            pq.pop();
            curMin = min(curMin, val);
            pq.push(val);
            ans = min(ans, pq.top()-curMin);
        } 

        return ans;
    }
};


// other solutions: conver it to the problem of "0632 -- Smallest Range Covering Elements from K Lists"
// -- all possible values of a given number forms an array of candidents for that particular number

// solution 2: sliding window to get the window where at least one candidate of each number is in the window

// solution 3: merge-sort like, i.e., increase min until any candidate array reaches the end
