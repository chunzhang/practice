/*
Facebook/Amazon/Google

Given an integer array nums and an integer k, find three non-overlapping subarrays of length k with maximum sum and return them.

Return the result as a list of indices representing the starting position of each interval (0-indexed). If there are multiple answers, return the lexicographically smallest one.

 

Example 1:

Input: nums = [1,2,1,2,6,7,5,1], k = 2
Output: [0,3,5]
Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.
Example 2:

Input: nums = [1,2,1,2,1,2,1,2,1], k = 2
Output: [0,2,4]
 

Constraints:

1 <= nums.length <= 2 * 10^4
1 <= nums[i] < 2^16
1 <= k <= floor(nums.length / 3)
*/

// 0. build the sum of each length-k subarray using psum
// 1. build max length-k subarray sum towards left and right of (by storing index)
// 2. iterating the start index of the middle array, then use information from 1) to get the max
// time: O(N), space: O(N)
// NOTE: the first three loops to build psum,subsum and maxsumLeft can be combined into one loop
class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        const int N = nums.size();

        vector<int> psum(N, nums[0]);  // prefix sum
        for(int i=1; i<psum.size(); ++i)
            psum[i] = psum[i-1] + nums[i];

        vector<int> subsum(N-k+1, psum[k-1]);  // length-k subarray sum starting at each index
        for(int i=1; i<subsum.size(); ++i)
            subsum[i] = psum[i+k-1] - psum[i-1];

        vector<int> maxsumLeft(N-k+1, 0);  // max length-k subarray looking left (store index)
        for(int i=1; i<maxsumLeft.size(); ++i) {
            maxsumLeft[i] = subsum[i]>subsum[maxsumLeft[i-1]] ? i : maxsumLeft[i-1];
        }

        vector<int> maxsumRight(N-k+1, subsum.size()-1);  // max length-k subarray looking right (store index)
        for(int i=maxsumRight.size()-2; i>=0; --i) {
            maxsumRight[i] = subsum[i]>=subsum[maxsumRight[i+1]] ? i : maxsumRight[i+1];
        }

        // now, iterate through the starting index of the middle sub-array, we can query maxsumLeft and maxsumRight
        // to get the solution
        vector<int> ans(3,-1);
        int msum = INT_MIN;
        for(int j=k; j<=N-2*k; ++j) {
            int sum = subsum[maxsumLeft[j-k]] + subsum[j] + subsum[maxsumRight[j+k]];
            if(sum > msum) {
                msum = sum;
                ans[0] = maxsumLeft[j-k];
                ans[1] = j;
                ans[2] = maxsumRight[j+k];
            }
        }

        return ans;
    }
};


// brute-force: fix the start index of first and second subarray
// time: O(N^2) -- TLE
class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        const int N = nums.size();

        vector<int> psum(N, nums[0]);  // prefix sum
        for(int i=1; i<psum.size(); ++i)
            psum[i] = psum[i-1] + nums[i];

        vector<int> subsum(N-k+1, psum[k-1]);  // length-k subarray sum starting at each index
        for(int i=1; i<subsum.size(); ++i)
            subsum[i] = psum[i+k-1] - psum[i-1];

        vector<pair<int,int>> maxsumLeft(N-k+1, {subsum[0],0});  // max length-k subarray looking left
        for(int i=1; i<maxsumLeft.size(); ++i) {
            if(subsum[i] > maxsumLeft[i-1].first)
                maxsumLeft[i] = {subsum[i],i};
            else
                maxsumLeft[i] = maxsumLeft[i-1];
        }

        vector<pair<int,int>> maxsumRight(N-k+1, {subsum.back(),subsum.size()-1});  // max length-k subarray looking right
        for(int i=maxsumRight.size()-2; i>=0; --i) {
            if(subsum[i] >= maxsumRight[i+1].first)
                maxsumRight[i] = {subsum[i],i};
            else
                maxsumRight[i] = maxsumRight[i+1];
        }

        // now, iterate through the starting index of the middle sub-array, we can query maxsumLeft and maxsumRight
        // to get the solution
        vector<int> ans(3,-1);
        int msum = INT_MIN;
        for(int j=k; j<=N-2*k; ++j) {
            int sum = maxsumLeft[j-k].first + subsum[j] + maxsumRight[j+k].first;
            if(sum > msum) {
                msum = sum;
                ans[0] = maxsumLeft[j-k].second;
                ans[1] = j;
                ans[2] = maxsumRight[j+k].second;
            }
        }

        return ans;
    }
};


// ref solution
class Solution {
    public int[] maxSumOfThreeSubarrays(int[] nums, int k) {
        // W is an array of sums of windows
        int[] W = new int[nums.length - k + 1];
        int currSum = 0;
        for (int i = 0; i < nums.length; i++) {
            currSum += nums[i];
            if (i >= k) {
                currSum -= nums[i - k];
            }
            if (i >= k - 1) {
                W[i - k + 1] = currSum;
            }
        }

        int[] left = new int[W.length];
        int best = 0;
        for (int i = 0; i < W.length; i++) {
            if (W[i] > W[best]) best = i;
            left[i] = best;
        }

        int[] right = new int[W.length];
        best = W.length - 1;
        for (int i = W.length - 1; i >= 0; i--) {
            if (W[i] >= W[best]) {
                best = i;
            }
            right[i] = best;
        }
        
        int[] ans = new int[]{-1, -1, -1};
        for (int j = k; j < W.length - k; j++) {
            int i = left[j - k], l = right[j + k];
            if (ans[0] == -1 || W[i] + W[j] + W[l] > W[ans[0]] + W[ans[1]] + W[ans[2]]) {
                ans[0] = i;
                ans[1] = j;
                ans[2] = l;
            }
        }
        return ans;
    }
}
