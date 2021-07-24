/*
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.
 

Example 1:


Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Output: true
Example 2:


Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
Output: false
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 100
-10^4 <= matrix[i][j], target <= 10^4
*/


class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // straightforward binary search: convert 1-D index to 2-D index
        const int M = matrix.size();
        const int N = matrix[0].size();
        
        int l = 0;
        int r = M*N;
        while(l < r) {
            int m = l + (r-l)/2;
            int row = m/N;
            int col = m%N;
            if(matrix[row][col] == target)
                return true;
            if(matrix[row][col] > target)
                r = m;
            else
                l = m + 1;
        }
        
        return false;
    }
};
