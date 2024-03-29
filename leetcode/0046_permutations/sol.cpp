/*
Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.

 

Example 1:

Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
Example 2:

Input: nums = [0,1]
Output: [[0,1],[1,0]]
Example 3:

Input: nums = [1]
Output: [[1]]
 

Constraints:

1 <= nums.length <= 6
-10 <= nums[i] <= 10
All the integers of nums are unique.
*/


// DFS
// time complexity: O(N*N!)
// space complexity: O(N)
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> cur;
        vector<int> used(nums.size(), 0);
        dfs(nums, cur, used, ans);
        return ans;
    }
    
private:
    void dfs(const vector<int> &nums, vector<int> &cur, vector<int> &used, vector<vector<int>> &ans) {
        if(cur.size() == nums.size()) {
            ans.emplace_back(cur);
            return;
        }
        
        for(int i=0; i<nums.size(); ++i) {
            if(used[i])
                continue;
            cur.push_back(nums[i]);
            used[i] = 1;
            dfs(nums, cur, used, ans);
            cur.pop_back();
            used[i] = 0;
        }
    }
};
