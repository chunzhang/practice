/*
Given an integer array nums that may contain duplicates, return all possible subsets (the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.

 

Example 1:

Input: nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
Example 2:

Input: nums = [0]
Output: [[],[0]]
 

Constraints:

1 <= nums.length <= 10
-10 <= nums[i] <= 10
*/


// DFS with pruning
// time complexity: O(2^N)
// space complexity: O(N)
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());  // for avoid duplicaates
        vector<vector<int>> ans;
        vector<int> cur;
        dfs(nums, 0, cur, ans);
        
        return ans;
    }
    
private:
    // find all subsets of size K
    void dfs(const vector<int> &nums, int start, vector<int> &cur, vector<vector<int>> &ans) {
        ans.push_back(cur);
        
        for(int i=start; i<nums.size(); ++i) {
            if(i==start || nums[i]!=nums[i-1]) {  // avoid duplicates: always use the first one of duplicated numbers
                cur.push_back(nums[i]);
                dfs(nums, i+1, cur, ans);
                cur.pop_back();
            }
        }
    }
};


// a less elegant DFS impl
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());  // for avoid duplicaates
        vector<vector<int>> ans;
        for(int k=0; k<=nums.size(); ++k) {
            vector<int> cur;
            dfs(nums, k, 0, 0, cur, ans);
        }
        
        return ans;
    }
    
private:
    // find all subsets of size K
    void dfs(const vector<int> &nums, const int K, int len, int idx, vector<int> &cur, vector<vector<int>> &ans) {
        if(len == K) {
            ans.push_back(cur);
            return;
        }
        
        for(int i=idx; i<nums.size(); ++i) {
            if(nums.size()-idx < K-len)  // pruning: not enough numbers left
                break;

            if(i==idx || nums[i]!=nums[i-1]) {  // avoid duplicates: always use the first one of duplicated numbers
                cur.push_back(nums[i]);
                dfs(nums, K, len+1, i+1, cur, ans);
                cur.pop_back();
            }
        }
    }
};


// cascading: for duplicated numbers, only need to expand the second half
// time complexity: O(2^N)
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans(1);  // start with one empty subset
        int oldSize = 1;
        for(int i=0; i<nums.size(); ++i) {
            int start = (i==0||nums[i]!=nums[i-1])?0:oldSize;  // for duplicated numbers, only need to expand the second half
            oldSize = ans.size();
            for(int j=start; j<oldSize; ++j) {
                vector<int> cur = ans[j];
                cur.push_back(nums[i]);
                ans.push_back(cur);
            }
        }
        
        return ans;
    }
};


// binary bitmask
// use hash table to avoid duplicates
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        int n = nums.size();

        // Sort the generated subset. This will help to identify duplicates.
        sort(nums.begin(), nums.end());
        vector<vector<int>> subsets;

        int maxNumberOfSubsets = pow(2, n);
        // To store the previously seen sets.
        unordered_set<string> seen;

        for (int subsetIndex = 0; subsetIndex < maxNumberOfSubsets; subsetIndex++) {
            // Append subset corresponding to that bitmask.
            vector<int> currentSubset;
            string hashcode = "";
            for (int j = 0; j < n; j++) {
                // Generate the bitmask
                int mask = 1 << j;
                int isSet = mask & subsetIndex;
                if (isSet != 0) {
                    currentSubset.push_back(nums[j]);
                    // Generate the hashcode by creating a comma separated string of numbers in the currentSubset.
                    hashcode.append(to_string(nums[j]) + ",");
                }
            }

            if (seen.find(hashcode) == seen.end()) {
                subsets.push_back(currentSubset);
                seen.insert(hashcode);
            }
        }

        return subsets;
    }
};
