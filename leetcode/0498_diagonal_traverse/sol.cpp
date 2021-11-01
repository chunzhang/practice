/*
Given an m x n matrix mat, return an array of all the elements of the array in a diagonal order.

 

Example 1:


Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,4,7,5,3,6,8,9]
Example 2:

Input: mat = [[1,2],[3,4]]
Output: [1,2,3,4]
 

Constraints:

m == mat.length
n == mat[i].length
1 <= m, n <= 104
1 <= m * n <= 104
-10^5 <= mat[i][j] <= 10^5
*/

// simulate traversal process -- keep track of diagonal direction
// time complexity: O(M*N)
// space complexity: O(1) (not including answer space)
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        const int M = mat.size();
        const int N = mat[0].size();
        int i = 0;
        int j = 0;
        int d = 1;  // 1: +45 degree, -1: -45 degree
        vector<int> ans(M*N,0);
        for(int k=0; k<ans.size(); ++k) {
            ans[k] = mat[i][j];
            if(d == 1) {  // +45 degree
                if(j == N-1) {
                    ++i;
                    d = -1;
                }
                else if(i == 0) {
                    ++j;
                    d = -1;
                }
                else {
                    --i;
                    ++j;
                }
            }
            else {  // -45 degree
                if(i == M-1) {
                    ++j;
                    d = 1;
                }
                else if(j == 0) {
                    ++i;
                    d = 1;
                }
                else {
                    ++i;
                    --j;
                }
            }
        }

        return ans;
    }
};

