/*
Given an n x n array of integers matrix, return the minimum sum of any falling path through matrix.

A falling path starts at any element in the first row and chooses the element in the next row that is either directly below or diagonally left/right. Specifically, the next element from position (row, col) will be (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1).

 

Example 1:

Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
Output: 13
Explanation: There are two falling paths with a minimum sum underlined below:
[[2,1,3],      [[2,1,3],
 [6,5,4],       [6,5,4],
 [7,8,9]]       [7,8,9]]
Example 2:

Input: matrix = [[-19,57],[-40,-5]]
Output: -59
Explanation: The falling path with a minimum sum is underlined below:
[[-19,57],
 [-40,-5]]
Example 3:

Input: matrix = [[-48]]
Output: -48
 

Constraints:

n == matrix.length
n == matrix[i].length
1 <= n <= 100
-100 <= matrix[i][j] <= 100
*/

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        // dp[i][j] = min(dp[i-1][j-1], dp[i-1][j], dp[i-1][j+1]) + matrix[i][j]
        
        // Let's reuse the matrix itself
        int n = matrix.size();
        for(int i=1; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                int upLeft = (j==0?INT_MAX:matrix[i-1][j-1]);
                int up = matrix[i-1][j];
                int upRight = (j==n-1?INT_MAX:matrix[i-1][j+1]);
                matrix[i][j] = min({upLeft,up,upRight}) + matrix[i][j];
            }
        }
        
        return *min_element(matrix[n-1].begin(), matrix[n-1].end());
    }
};
