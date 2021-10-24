/*
  Find all valid combinations of k numbers that sum up to n such that the following conditions are true:

  Only numbers 1 through 9 are used.
  Each number is used at most once.
  Return a list of all possible valid combinations. The list must not contain the same combination twice, and the combinations may be returned in any order.

 

  Example 1:

  Input: k = 3, n = 7
  Output: [[1,2,4]]
  Explanation:
  1 + 2 + 4 = 7
  There are no other valid combinations.
  Example 2:

  Input: k = 3, n = 9
  Output: [[1,2,6],[1,3,5],[2,3,4]]
  Explanation:
  1 + 2 + 6 = 9
  1 + 3 + 5 = 9
  2 + 3 + 4 = 9
  There are no other valid combinations.
  Example 3:

  Input: k = 4, n = 1
  Output: []
  Explanation: There are no valid combinations.
  Using 4 different numbers in the range [1,9], the smallest sum we can get is 1+2+3+4 = 10 and since 10 > 1, there are no valid combination.
  Example 4:

  Input: k = 3, n = 2
  Output: []
  Explanation: There are no valid combinations.
  Example 5:

  Input: k = 9, n = 45
  Output: [[1,2,3,4,5,6,7,8,9]]
  Explanation:
  1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 = 45
  There are no other valid combinations.
 

  Constraints:

  2 <= k <= 9
  1 <= n <= 60
*/


// DFS with pruning
// time complexity: O(C(9,k))
// space complexity: O(k)
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> cur;
        vector<vector<int>> ans;
        dfs(k, n, 1, cur, ans);
        return ans;
    }
    
private:
    void dfs(const int K, const int target, int curNum, vector<int> &cur, vector<vector<int>> &ans) {
        if(cur.size() == K) {
            if(target == 0)
                ans.push_back(cur);
            return;
        }
        
        for(int num=curNum; num<=9; ++num) {
            if(target-num < 0)  // cannot reach target
                break;
            if(10-num < K-cur.size())  // not enough number
                break;
            cur.push_back(num);
            dfs(K, target-num, num+1, cur, ans);
            cur.pop_back();
        }
    }
};


// binary bitmask
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> ans;
        
        // 2^9, generate all combinations of [1 .. 9]
        for (int i = 0; i < (1 << 9); ++i) {
            vector<int> cur;
            int sum = 0;
            // Use j if (j - 1)-th bit is 1
            for (int j = 1; j <= 9; ++j)
                if (i & (1 << (j - 1))) {
                    sum += j;
                    cur.push_back(j);
                }
            if (sum == n && cur.size() == k) 
                ans.push_back(cur);
        }
        
        return ans;
    }
};
