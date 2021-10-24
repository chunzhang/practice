/*
Given a collection of numbers, nums, that might contain duplicates, return all possible unique permutations in any order.

 

Example 1:

Input: nums = [1,1,2]
Output:
[[1,1,2],
 [1,2,1],
 [2,1,1]]
Example 2:

Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 

Constraints:

1 <= nums.length <= 8
-10 <= nums[i] <= 10
*/


// DFS
// time complexity: O(N*N!)
// space complexity: O(N)
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());  // for avoiding duplicates
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
            if(i>0 && nums[i]==nums[i-1] && !used[i-1])  // avoid duplicates
                continue;
            cur.push_back(nums[i]);
            used[i] = 1;
            dfs(nums, cur, used, ans);
            cur.pop_back();
            used[i] = 0;
        }
    }
};
