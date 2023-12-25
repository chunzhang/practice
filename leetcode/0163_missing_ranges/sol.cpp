/*
  Facebook/TikTok/ByteDance

  You are given an inclusive range [lower, upper] and a sorted unique integer array nums, where all elements are within the inclusive range.

  A number x is considered missing if x is in the range [lower, upper] and x is not in nums.

  Return the shortest sorted list of ranges that exactly covers all the missing numbers. That is, no element of nums is included in any of the ranges, and each missing number is covered by one of the ranges.

  
  Example 1:

  Input: nums = [0,1,3,50,75], lower = 0, upper = 99
  Output: [[2,2],[4,49],[51,74],[76,99]]
  Explanation: The ranges are:
  [2,2]
  [4,49]
  [51,74]
  [76,99]
  Example 2:

  Input: nums = [-1], lower = -1, upper = -1
  Output: []
  Explanation: There are no missing ranges since there are no missing numbers.
 

  Constraints:

  -109 <= lower <= upper <= 109
  0 <= nums.length <= 100
  lower <= nums[i] <= upper
  All the values of nums are unique.
*/


// concise implementation -- but less readable
// check range [lower-1, upper+1] to avoid missing lower/higher on the edge
class Solution {
public:
    vector<vector<int>> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<vector<int>> ans;
        int prev = lower - 1;
        nums.push_back(upper+1);
        for(int cur : nums) {
            if(cur > prev+1)
                ans.push_back({prev+1,cur-1});
            prev = cur;
        }

        return ans;
    }
};


// A simpler version (old version that returns string as results)
class Solution {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<string> res;
        long long pre = (long long)lower -1;  // invariant: this number is not missing
        for(int i=0; i<=nums.size(); ++i) {
            long long cur = i<nums.size() ? nums[i] : (long long)upper+1;
            if(cur-pre > 1)
                res.push_back(genRange(pre+1, cur-1));
            pre = cur;
        }

        return res;
    }

    string genRange(int lo, int hi) {
        ostringstream oss;
        if(lo == hi)
            oss << lo;
        else
            oss << lo << "->" << hi;
        return oss.str();
    }

};


// explicitly handle boundary conditions (old version that returns string as results)
class Solution2 {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<string> res;
        if(nums.empty()) {
            res.push_back(genRange(lower, upper));
            return res;
        }

        int first = nums.front();
        if(first > lower)
            res.push_back(genRange(lower, first-1));
        for(int i=1; i<nums.size(); ++i) {
            if((long long)nums[i]-nums[i-1] > 1)  // need the cast in case of integer overflow!
                res.push_back(genRange(nums[i-1]+1, nums[i]-1));
        }
        int last = nums.back();
        if(last < upper)
            res.push_back(genRange(last+1, upper));

        return res;
    }

    string genRange(int lo, int hi) {
        ostringstream oss;
        if(lo == hi)
            oss << lo;
        else
            oss << lo << "->" << hi;
        return oss.str();
    }
};

