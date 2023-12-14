/*
  A matrix is Toeplitz if every diagonal from top-left to bottom-right has the same element.

  Now given an M x N matrix, return True if and only if the matrix is Toeplitz.
 

  Example 1:

  Input: matrix = [[1,2,3,4],[5,1,2,3],[9,5,1,2]]
  Output: True
  Explanation:
  1234
  5123
  9512

  In the above grid, the diagonals are "[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]", and in each diagonal all elements are the same, so the answer is True.
  Example 2:

  Input: matrix = [[1,2],[2,2]]
  Output: False
  Explanation:
  The diagonal "[1, 2]" has different elements.
  Note:

  matrix will be a 2D array of integers.
  matrix will have a number of rows and columns in range [1, 20].
  matrix[i][j] will be integers in range [0, 99].
*/

#include "../common/common.h"

using namespace std;

// Scan from top-left to bottom-right
class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        for(int i=0; i<matrix.size(); ++i)
            for(int j=0; j<matrix[0].size(); ++j)
                if(i>0 && j>0 && matrix[i][j]!=matrix[i-1][j-1])
                    return false;
        return true;
    }
};

// Two coordinates (r1,c1) and (r2,c2) is on the same (top-left to bottom-right) diagonal if r1-c1==r2-c2
class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        unordered_map<int, int> vals;
        for(int i=0; i<matrix.size(); ++i) {
            for(int j=0; j<matrix[0].size(); ++j) {
                int val = i - j;  // this delta uniquely identifies the diagonal
                if(vals.find(val) == vals.end())
                    vals[val] = matrix[i][j];  // all elements on the same diagonal shall have same value as this
                else
                    if(matrix[i][j] != vals[val])
                        return false;
            }
        }
        
        return true;
        
    }
};

// Straightforward -- scan all diagonals
class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        // matrix won't be empty according the problem definition
        int m = matrix.size();
        int n = matrix[0].size();
        for(int i=0; i<m; ++i)
            if(!searchDiagonal(matrix, m, n, matrix[i][0], i, 0))  // first column
                return false;
        for(int j=1; j<n; ++j)
            if(!searchDiagonal(matrix, m, n, matrix[0][j], 0, j))  // first row (except beginning element which is already searched)
                return false;
        
        return true;
    }
    
    bool searchDiagonal(const vector<vector<int>>& matrix, int m, int n, int val, int i, int j) {
        while(i>=0 && i<m && j>=0 && j<n) {
            if(matrix[i][j] != val)
                return false;
            ++i;
            ++j;
        }
        return true;
    }
    
};
