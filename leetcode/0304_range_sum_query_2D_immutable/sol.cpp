/*
  Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

  Range Sum Query 2D
  The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

  Example:
  Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
  ]

  sumRegion(2, 1, 4, 3) -> 8
  sumRegion(1, 1, 2, 2) -> 11
  sumRegion(1, 2, 2, 4) -> 12
  
  Note:
  You may assume that the matrix does not change.
  There are many calls to sumRegion function.
  You may assume that row1 ≤ row2 and col1 ≤ col2.
*/

#include "../common/common.h"

using namespace std;

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * int param_1 = obj.sumRegion(row1,col1,row2,col2);
 */

class NumMatrix {
public:
  NumMatrix(vector<vector<int>> matrix) {
    _nRows = matrix.size();
    _nCols = _nRows ? matrix[0].size() : 0;

    // build prefix sum -- sum[i][j] is 2D sum from (0,0) to (i,j)
    _sum = matrix;
    for(int i=0; i<_nRows; ++i) {
      int sum = 0;  // prefix sum of current row
      for(int j=0; j<_nCols; ++j) {
	sum += matrix[i][j];
	_sum[i][j] = sum;
	if(i > 0)
	  _sum[i][j] += _sum[i-1][j];  // add prefix sum of previous rows
      }
    }
  }
    
  int sumRegion(int row1, int col1, int row2, int col2) {
    return sum(row2,col2) + sum(row1-1,col1-1) - sum(row1-1,col2) - sum(row2,col1-1);
  }

private:
  int sum(int i, int j) {
    if(i<0 || i>=_nRows || j<0 || j>=_nCols)
      return 0;
    return _sum[i][j];
  }

private:
  vector<vector<int>> _sum;
  int _nRows;
  int _nCols;
};

int main(int argc, char *argv[])
{
  vector<vector<int>> matrix = {
    {3, 0, 1, 4, 2},
    {5, 6, 3, 2, 1},
    {1, 2, 0, 1, 5},
    {4, 1, 0, 1, 7},
    {1, 0, 3, 0, 5}
  };

  NumMatrix sol(matrix);
  cout << sol.sumRegion(2, 1, 4, 3) << endl;
  cout << sol.sumRegion(1, 1, 2, 2) << endl;
  cout << sol.sumRegion(1, 2, 2, 4) << endl;

  return 0;
}
