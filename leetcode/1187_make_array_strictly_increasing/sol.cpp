/*
Given two integer arrays arr1 and arr2, return the minimum number of operations (possibly zero) needed to make arr1 strictly increasing.

In one operation, you can choose two indices 0 <= i < arr1.length and 0 <= j < arr2.length and do the assignment arr1[i] = arr2[j].

If there is no way to make arr1 strictly increasing, return -1.

 

Example 1:

Input: arr1 = [1,5,3,6,7], arr2 = [1,3,2,4]
Output: 1
Explanation: Replace 5 with 2, then arr1 = [1, 2, 3, 6, 7].
Example 2:

Input: arr1 = [1,5,3,6,7], arr2 = [4,3,1]
Output: 2
Explanation: Replace 5 with 3 and then replace 3 with 4. arr1 = [1, 3, 4, 6, 7].
Example 3:

Input: arr1 = [1,5,3,6,7], arr2 = [1,6,3,3]
Output: -1
Explanation: You can't make arr1 strictly increasing.
 

Constraints:

1 <= arr1.length, arr2.length <= 2000
0 <= arr1[i], arr2[i] <= 10^9
*/

// DP solution, similar to leetcode 0801 -- Minimum Swaps to Nake Sequences Increasing
// Time complexity: O(NlgN+M*(N+lgN))=O(M*N+(M+N)lgN)
// Space complexity: O(M*N)
class Solution {
public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        // keep[i]: min steps to make arr1[0...i] strictly increasing by keeping arr1[i]
        // swap[i][j]: min steps to make arr1[0...i] strictly increasing by swapping arr1[i] with arr2[j]
        // keep[i] is the min of blow:
        // -- keep[i-1], if arr1[i]>arr1[i-1]
        // -- min{swap[i-1][k], for all arr2[k]<arr1[i]}
        // swap[i][j] is the min of below:
        // -- keep[i-1]+1, if arr1[i-1] < arr2[j]
        // -- min{swap[i-1][k], for all arr2[k]<arr2[j]}
        
        // first, we sort and remove redundant elements from arr2;
        // this is because duplicate values can't make arr1 strictly increasing
        sort(arr2.begin(), arr2.end());
        auto last = unique(arr2.begin(), arr2.end());
        arr2.erase(last, arr2.end());
        
        const int M = arr1.size();
        const int N = arr2.size();
        
        // DP base values
        vector<int> keep(M, 1e5);
        keep[0] = 0;  // no op needed to keep the first element
        vector<vector<int>> swap(M, vector<int>(N, 1e5));
        for(int j=0; j<N; ++j)
            swap[0][j] = 1;  // one op to swap the first element
        
        for(int i=1; i<M; ++i) {  // O(M*(N+lgN))
            // running min of swap[i-1][j]
            vector<int> running_min(N, INT_MAX);
            running_min[0] = swap[i-1][0];
            for(int j=1; j<N; ++j)
                running_min[j] = min(running_min[j-1], swap[i-1][j]);
            
            // compute keep[i]
            if(arr1[i] > arr1[i-1])
                keep[i] = keep[i-1];
            auto it = lower_bound(arr2.begin(), arr2.end(), arr1[i]);
            int dist = distance(arr2.begin(), it);
            if(dist != 0)  // there exist k such that arr2[k] < arr1[i]
                keep[i] = min(keep[i], running_min[dist-1]);
            
            // compute swap[i][j]
            for(int j=0; j<N; ++j) {
                if(arr2[j] > arr1[i-1])
                    swap[i][j] = keep[i-1] + 1;
                if(j != 0)
                    swap[i][j] = min(swap[i][j], running_min[j-1]+1);
            }
        }
        
        // result
        int res = min(keep[M-1], *min_element(swap[M-1].begin(), swap[M-1].end()));
        return res<1e5?res:-1;
    }
};

// A reference C++ solution from HuaHua
// Author: Huahua
class Solution {
public:
  int makeArrayIncreasing(vector<int>& a, vector<int>& c) {
    constexpr int kInf = 1e9;
    int m = a.size();    
    // Sort b and make it only containing unique numbers.
    sort(begin(c), end(c));
    vector<int> b;
    for (int i = 0; i < c.size(); ++i) {
      if (!b.empty() && c[i] == b.back()) continue;
      b.push_back(c[i]);
    }    
    int n = b.size();
    
    // min steps to make a[0~i] valid by keeping a[i]
    vector<int> keep(m, kInf);
    keep[0] = 0;
    // swap[i][j] := min steps to make a[0~i] valid by a[i] = b[j]
    vector<int> swap(n, 1);
    
    for (int i = 1; i < m; ++i) {
      int min_keep = kInf;
      int min_swap = kInf;
      vector<int> temp(n, kInf);
      for (int j = 0; j < n; ++j) {
        if (j > 0) min_swap = min(min_swap, swap[j - 1] + 1);
        if (a[i] > b[j]) min_keep = min(min_keep, swap[j]);        
        if (a[i] > a[i - 1]) keep[i] = keep[i - 1];
        if (b[j] > a[i - 1]) temp[j] = keep[i - 1] + 1;        
        temp[j] = min(temp[j], min_swap);
        keep[i] = min(keep[i], min_keep);
      }
      temp.swap(swap);
    }
    
    int s = *min_element(begin(swap), end(swap));
    int k = keep.back();
    int ans = min(s, k);
    return ans >= kInf ? -1 : ans;
  }
};
