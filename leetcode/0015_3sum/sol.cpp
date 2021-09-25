/*
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

 

Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Example 2:

Input: nums = []
Output: []
Example 3:

Input: nums = [0]
Output: []
 

Constraints:

0 <= nums.length <= 3000
-10^5 <= nums[i] <= 10^5
*/


// sort array and use two pointers
// need to avoid duplicates
// time complexity: O(N^2)
// space complexity: bounded by sorting
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        for(int i=0; i<(int)nums.size()-2; ++i) {
            if(i!=0 && nums[i]==nums[i-1])  // remove duplicates
                continue;
            
            // now use two pointers to find 2sum from sorted array
            int target = -nums[i];
            for(int j=i+1,k=(int)nums.size()-1; j<k; ) {
                int sum = nums[j]+nums[k];
                if(sum < target)
                    ++j;
                else if(sum > target)
                    --k;
                else {
                    ans.push_back({nums[i],nums[j],nums[k]});
                    ++j;
                    while(j<k && nums[j]==nums[j-1])  // remove duplicates
                        ++j;
                }
            }
        }
        return ans;
    }
};


// sort array and use hashtable
// time complexity: O(N^2)
// space complexity: O(N)
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        unordered_map<int,int> counts;
        for(int n:nums)
            counts[n]++;
        
        for(int i=0; i<(int)nums.size()-2; ++i) {
            if(i>0 && nums[i]==nums[i-1])
                continue;
            for(int j=i+1; j<(int)nums.size()-1; ++j) {
                if(j>i+1 && nums[j]==nums[j-1])
                    continue;
                int target = -nums[i]-nums[j];
                if(target < nums[j])
                    continue;
                int needed = 1 + (target==nums[i]) + (target==nums[j]);
                auto it = counts.find(target);
                if(it!=counts.end() && it->second >= needed)
                    ans.push_back({nums[i],nums[j],target});
            }
        }
        return ans;
    }
};


// ref impl w/o sorting
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        set<vector<int>> res;
        unordered_set<int> dups;
        unordered_map<int, int> seen;
        for (int i = 0; i < nums.size(); ++i)
            if (dups.insert(nums[i]).second) {
                for (int j = i + 1; j < nums.size(); ++j) {
                    int complement = -nums[i] - nums[j];
                    auto it = seen.find(complement);
                    if (it != end(seen) && it->second == i) {
                        vector<int> triplet = {nums[i], nums[j], complement};
                        sort(begin(triplet), end(triplet));
                        res.insert(triplet);
                    }
                    seen[nums[j]] = i;
                }
            }
        return vector<vector<int>>(begin(res), end(res));
    }
};
