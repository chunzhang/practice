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
// Key idea: satisfied subarray ==> psum(j)-psum(i)=k ==> psum(i)=psum(j)-k
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int psum = 0;  // prefix sum
        unordered_map<int,int> count;  // psum --> count
        int ans = 0;
        for(int num: nums) {
            psum += num;
            if(psum == k)
                ++ans;
            ans += count[psum-k];
            ++count[psum];
        }
        
        return ans;
    }
};

// O(N): a different impl
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int psum = 0;
        unordered_map<int,int> count;
        count[0] = 1;
        int ans = 0;

        for(int num : nums) {
            psum += num;
            ans += count[psum-k];  // since count[0]=1, this accounts for the case where psum==k
            ++count[psum];
        }

        return ans;
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
