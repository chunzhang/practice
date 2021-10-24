/*
Given two integers n and k, return all possible combinations of k numbers out of the range [1, n].

You may return the answer in any order.

 

Example 1:

Input: n = 4, k = 2
Output:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
Example 2:

Input: n = 1, k = 1
Output: [[1]]
 

Constraints:

1 <= n <= 20
1 <= k <= n
*/

// DFS with pruning
// time complexity: O(C(n,k))
// space complexity: O(k)
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<int> cur;
        vector<vector<int>> ans;
        dfs(n, k, 1, cur, ans);
        return ans;
    }

private:
    void dfs(const int N, const int K, int curNum, vector<int> &cur, vector<vector<int>> &ans) {
        if(cur.size() == K) {
            ans.push_back(cur);
            return;
        }
        
        for(int num=curNum; num<=N; ++num) {
            if(N-num+1<K-cur.size())  // pruning: not enough numbers left
                break;
            cur.push_back(num);
            dfs(N, K, num+1, cur, ans);
            cur.pop_back();
        }
    }
};
