#include "../leetcode/common/common.h"

using namespace std;

class BinaryIndexTree2D
{
public:
  BinaryIndexTree2D(const vector<vector<int>> &matrix) {
    _nRows = matrix.size();
    _nCols = _nRows ? matrix[0].size() : 0;
    _matrix.resize(_nRows, vector<int>(_nCols, 0));
    _tree2D.resize(_nRows+1, vector<int>(_nCols+1, 0));

    for(int i=0; i<_nRows; ++i)
      for(int j=0; j<_nCols; ++j)
	update(i, j, matrix[i][j]);
  }

  // update element (row,col) to val
  void update(int row, int col, int val) {
    int delta = val - _matrix[row][col];
    _matrix[row][col] = val;
    for(int i=row+1; i<_nRows+1; i+=(i&-i))
      for(int j=col+1; j<_nCols+1; j+=(j&-j))
	_tree2D[i][j] += delta;
  }

  // range sum from (0,0) to (row,col)
  int querySum(int row, int col) {
    int sum = 0;
    for(int i=row+1; i>0; i-=(i&-i))
      for(int j=col+1; j>0; j-=(j&-j))
	sum += _tree2D[i][j];
    return sum;
  }

  // range sum from (row1,col1) to (row2,col2)
  int querySum(int row1, int col1, int row2, int col2) {
    return querySum(row2,col2) + querySum(row1-1,col1-1) - querySum(row1-1,col2) - querySum(row2,col1-1);
  }

private:
  int _nRows;
  int _nCols;
  vector<vector<int>> _matrix;
  vector<vector<int>> _tree2D;
};

int main()
{
  vector<vector<int>> matrix = {
    {3, 0, 1, 4, 2},
    {5, 6, 3, 2, 1},
    {1, 2, 0, 1, 5},
    {4, 1, 0, 1, 7},
    {1, 0, 3, 0, 5}
  };

  BinaryIndexTree2D bit2d(matrix);
  cout << "querySum(2, 1, 4, 3): " << bit2d.querySum(2, 1, 4, 3) << endl;
  cout << "update(3, 2, 2)" << endl;
  bit2d.update(3, 2, 2);
  cout << "querySum(2, 1, 4, 3): " << bit2d.querySum(2, 1, 4, 3) << endl;

  return 0;
}
