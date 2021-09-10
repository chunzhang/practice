/*
  Given an array of integers nums and an integer k, return the total number of continuous subarrays whose sum equals to k.

 

  Example 1:

  Input: nums = [1,1,1], k = 2
  Output: 2
  Example 2:

  Input: nums = [1,2,3], k = 3
  Output: 2
 

  Constraints:

  1 <= nums.length <= 2 * 104
  -1000 <= nums[i] <= 1000
  -10^7 <= k <= 10^7
*/

// O(N): prefix and count mapping
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int psum = 0;  // prefix sum
        unordered_map<int,int> count;  // psum --> count mapping
        int ans = 0;
        for(int num: nums) {
            psum += num;
            if(psum == k)  // full path, i.e., starting from nums[0]
                ++ans;
            ans += count[psum-k];  // partial path, i.e., starting from nums[0], nums[1], etc.
            ++count[psum];
        }
        
        return ans;
    }
};

// O(N): a different impl
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int count = 0;
        int csum = 0;
        map<int, int> csumCount; // # times this csum has been seen so far
        csumCount[0] = 1;  // in the case nums[0]==k
    
        for(int i=0; i<nums.size(); ++i){
            csum += nums[i];
            count += csumCount[csum-k];
            csumCount[csum]++;
        }

        return count;
    }
};

// O(N^2) brute-force
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int count = 0;
        vector<int> sums(nums.begin(), nums.end());
        for(int i=1; i<sums.size(); ++i)
            sums[i] += sums[i-1];

        for(int i=0; i<nums.size(); ++i)
            for(int j=i; j<nums.size(); ++j)
                if(sums[j]-sums[i]+nums[i] == k)
                    ++count;

        return count;
    }
};
