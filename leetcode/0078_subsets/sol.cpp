/*
Given an integer array nums of unique elements, return all possible subsets (the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.

 

Example 1:

Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
Example 2:

Input: nums = [0]
Output: [[],[0]]
 

Constraints:

1 <= nums.length <= 10
-10 <= nums[i] <= 10
All the numbers of nums are unique.
*/


// DFS with pruning
// time complexity: O(2^N)
// space complexity: O(N)
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> cur;
        dfs(nums, 0, cur, ans);
        return ans;
    }
    
private:
    // find all subsets of size K
    void dfs(const vector<int> &nums, int start, vector<int> &cur, vector<vector<int>> &ans) {
        ans.push_back(cur);  // NOTE: we found a valid sub-set
        
        for(int i=start; i<nums.size(); ++i) {
            cur.push_back(nums[i]);
            dfs(nums, i+1, cur, ans);
            cur.pop_back();
        }
    }
};

// A less elegant DFS impl
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        for(int k=0; k<=nums.size(); ++k) {
            vector<int> cur;
            dfs(nums, k, 0, cur, ans);
        }
        
        return ans;
    }
    
private:
    // find all subsets of size K
    void dfs(const vector<int> &nums, const int K, int start, vector<int> &cur, vector<vector<int>> &ans) {
        if(cur.size() == K) {
            ans.push_back(cur);
            return;
        }
        
        for(int i=start; i<nums.size(); ++i) {
            if(nums.size()-start < K-cur.size())  // pruning: not enough numbers left
                break;
            cur.push_back(nums[i]);
            dfs(nums, K, i+1, cur, ans);
            cur.pop_back();
        }
    }
};


// cascading: for each number, add it to all exists sub-sets, i.e., double current sub-sets count
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans(1, vector<int>());
        
        // cascading
        for(int num : nums) {  // at each iteration, add all sub-sets that ends with num
            int sz = ans.size();
            for(int i=0; i<sz; ++i) {
                vector<int> subset = ans[i];
                subset.push_back(num);
                ans.push_back(subset);
            }
        }
        
        return ans;
    }
};


// binary bitmasek: represent whether the number is selected as one bit of the binary number;
// if the bit is one, add the number to the subset
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        const int N = nums.size();
        vector<vector<int>> ans;
        
        // add the number when its binary bit is 1
        for(int bin=0; bin<(1<<N); ++bin) {
            vector<int> cur;
            for(int i=0; i<N; ++i)
                if(bin&(1<<i))
                    cur.push_back(nums[i]);
            ans.push_back(cur);
        }
        
        return ans;
    }
};
