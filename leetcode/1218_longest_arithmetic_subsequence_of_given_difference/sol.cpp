/*
Given an integer array arr and an integer difference, return the length of the longest subsequence in arr which is an arithmetic sequence such that the difference between adjacent elements in the subsequence equals difference.

A subsequence is a sequence that can be derived from arr by deleting some or no elements without changing the order of the remaining elements.

 

Example 1:

Input: arr = [1,2,3,4], difference = 1
Output: 4
Explanation: The longest arithmetic subsequence is [1,2,3,4].
Example 2:

Input: arr = [1,3,5,7], difference = 1
Output: 1
Explanation: The longest arithmetic subsequence is any single element.
Example 3:

Input: arr = [1,5,7,8,5,3,4,2,1], difference = -2
Output: 4
Explanation: The longest arithmetic subsequence is [7,5,3,1].
 

Constraints:

1 <= arr.length <= 10^5
-10^4 <= arr[i], difference <= 10^4
*/

class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        int ans = INT_MIN;
        // dp[n]: max length of qualified sub-sequence that ends with number n
        unordered_map<int,int> dp;
        for(int n : arr) {
            int pn = n - difference;  // previous number, if exists
            auto it = dp.find(pn);
            int len = (it==dp.end()) ? 1 : 1+it->second;  // transition function
            dp[n] = len;  // here, we can prove that dp[n] never decreases
            ans = max(ans, len);
        }
        
        return ans;
    }
};


// Another concise implementation from HuaHua
class Solution {
public:
  int longestSubsequence(vector<int>& arr, int d) {
    unordered_map<int, int> dp;
    int ans = 0;
    for (int x : arr)      
        ans = max(ans, dp[x] = dp[x - d] + 1);  // If dp[x-d] does not exist, it will be initialzed to 0. But it has the disadvantage of increasing hash-table size
    return ans;
  }
};
