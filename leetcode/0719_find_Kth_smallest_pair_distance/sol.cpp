/*
  The distance of a pair of integers a and b is defined as the absolute difference between a and b.

  Given an integer array nums and an integer k, return the kth smallest distance among all the pairs nums[i] and nums[j] where 0 <= i < j < nums.length.

 

  Example 1:

  Input: nums = [1,3,1], k = 1
  Output: 0
  Explanation: Here are all the pairs:
  (1,3) -> 2
  (1,1) -> 0
  (3,1) -> 2
  Then the 1st smallest distance pair is (1,1), and its distance is 0.
  Example 2:

  Input: nums = [1,1,1], k = 2
  Output: 0
  Example 3:

  Input: nums = [1,6,1], k = 3
  Output: 5
 

  Constraints:

  n == nums.length
  2 <= n <= 10^4
  0 <= nums[i] <= 10^6
  1 <= k <= n * (n - 1) / 2
*/

// binary search
// time complexity: O(NlgN + NlgW), where W is the difference of max-distance and min-distance
class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        const int N = nums.size();
        sort(nums.begin(), nums.end());
        int l = INT_MAX;
        for(int i=0; i<N-1; ++i)
            l = min(l, nums[i+1]-nums[i]);  // min possible distance
        int r = nums[N-1]-nums[0] + 1;  // max possible distance
        
        // binary search
        while(l < r) {
            int m = l + (r-l)/2;
            if(countSmallerOrEqual(nums,m)>=k)
                r = m;
            else
                l = m + 1;
        }
        
        return l;
    }
    
private:
    // time complexity: O(N), using two pointers
    int countSmallerOrEqual(const vector<int> &nums, int val) {
        int count = 0;
        int j = 0;
        for(int i=0; i<nums.size()-1; ++i) {
            while(j<nums.size() && nums[j]-nums[i]<=val)
                ++j;
            count += j-i-1;
        }

        return count;
    }
};

// binary search
// time complexity: O(NlgN+NlgN*lgW), where W is the difference of max-distance and min-distance
class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        const int N = nums.size();
        sort(nums.begin(), nums.end());
        int l = INT_MAX;
        for(int i=0; i<N-1; ++i)
            l = min(l, nums[i+1]-nums[i]);  // min possible distance
        int r = nums[N-1]-nums[0] + 1;  // max possible distance
        
        // binary search
        while(l < r) {
            int m = l + (r-l)/2;
            if(countSmallerOrEqual(nums,m)>=k)
                r = m;
            else
                l = m + 1;
        }
        
        return l;
    }
    
private:
    // O(NlgN) time complexity
    int countSmallerOrEqual(const vector<int> &nums, int val) {
        int count = 0;
        for(int i=0; i<nums.size()-1;  ++i)
            count += distance(nums.begin()+i, upper_bound(nums.begin()+i, nums.end(), nums[i]+val)) - 1;
        return count;
    }
};


// brute-force: counting sort (from HuaHua)
// time complexity: O(N^2)
class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        std::sort(nums.begin(), nums.end());
        const int N = nums.back();
        vector<int> count(N + 1, 0);        
        const int n = nums.size();
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                ++count[nums[j] - nums[i]];
        for (int i = 0; i <= N; ++i) {
            k -= count[i];
            if (k <= 0) return i;
        }
        return 0;
    }
};
