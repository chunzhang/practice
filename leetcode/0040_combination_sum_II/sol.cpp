/*
  Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target.

  Each number in candidates may only be used once in the combination.

  Note: The solution set must not contain duplicate combinations.

 

  Example 1:

  Input: candidates = [10,1,2,7,6,1,5], target = 8
  Output: 
  [
  [1,1,6],
  [1,2,5],
  [1,7],
  [2,6]
  ]
  Example 2:

  Input: candidates = [2,5,2,1,2], target = 5
  Output: 
  [
  [1,2,2],
  [5]
  ]
 

  Constraints:

  1 <= candidates.length <= 100
  1 <= candidates[i] <= 50
  1 <= target <= 30
*/

// DFS with pruning
// time complexity: O(2^N), i.e., each element can either be selected or not
// space complexity: O(N)
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());  // for pruning
        vector<int> cur;
        vector<vector<int>> ans;
        dfs(candidates, target, 0, cur, ans);
        return ans;
    }
    
private:
    void dfs(const vector<int> &candidates, int target, int start, vector<int> &cur, vector<vector<int>> &ans) {
        if(target == 0) {
            ans.push_back(cur);
            return;
        }
        
        for(int i=start; i<candidates.size(); ++i) {
            if(candidates[i] > target)  // strong pruning
                break;
            if(i==start || candidates[i]!=candidates[i-1]) {  // avoid duplicates: alwasy use the first one of duplicated numbers
                cur.push_back(candidates[i]);
                dfs(candidates, target-candidates[i], i+1, cur, ans);
                cur.pop_back();
            }
        }
    }
};


// A slightly less elegant impl
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());  // for pruning
        vector<int> cur;
        vector<int> used(candidates.size(), 0);
        vector<vector<int>> ans;
        dfs(candidates, target, 0, 0, cur, used, ans);
        return ans;
    }
    
private:
    void dfs(const vector<int> &candidates, const int target, int idx, int sum, vector<int> &cur, vector<int> &used, vector<vector<int>> &ans) {
        if(sum == target) {
            ans.push_back(cur);
            return;
        }
        
        for(int i=idx; i<candidates.size(); ++i) {
            if(i>0 && candidates[i]==candidates[i-1] && !used[i-1])  // avoid duplicates: always use the first element of duplicated numbers
                continue;
            if(sum+candidates[i] > target)  // fast pruning
                break;
            cur.push_back(candidates[i]);
            used[i] = 1;
            dfs(candidates, target, i+1, sum+candidates[i], cur, used, ans);
            cur.pop_back();
            used[i] = 0;
        }
    }
};


// use std::set to avoid duplicates
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        set<vector<int>> ans;
        std::sort(candidates.begin(), candidates.end());
        vector<int> curr;
        dfs(candidates, target, 0, ans, curr);
        return vector<vector<int>>(ans.begin(), ans.end());
    }
private:
    void dfs(const vector<int>& candidates, 
             int target, int s, 
             set<vector<int>>& ans,              
             vector<int>& curr) {
        if (target == 0) {
            ans.insert(curr);
            return;
        }
        
        for (int i = s; i < candidates.size(); ++i) {
            int num = candidates[i];
            if (num > target) return;
            curr.push_back(num);
            dfs(candidates, target - num, i + 1, ans, curr);
            curr.pop_back();
        }
    }
};
