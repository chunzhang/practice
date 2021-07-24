/*
Write an efficient algorithm that searches for a target value in an m x n integer matrix. The matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.
 

Example 1:


Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
Output: true
Example 2:


Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
Output: false
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= n, m <= 300
-10^9 <= matix[i][j] <= 10^9
All the integers in each row are sorted in ascending order.
All the integers in each column are sorted in ascending order.
-10^9 <= target <= 10^9
*/


class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // O(N) search that starts from bottom-left to up-right corner;
        // every step we either move up or right;
        // at (i,j), search space is the matrix where (i,j) is the bottom-left corner;
        // based on value of(i,j) compared with target, we can either eliminate i-th row, or j-th column, or target is found
        
        // m by n matrix
        int m = matrix.size();
        int n = matrix[0].size();
 
        // start from bottom-left corner
        int i = m - 1; 
        int j = 0;
        while(i>=0 && j<=n-1) {
            if(matrix[i][j] == target)
                return true;
            else if(matrix[i][j] < target)  // everything above in the same column is smaller than target
                ++j;
            else  // everything right in the same row is bigger than target
                --i;
        }
        
        return false;
    }
};
