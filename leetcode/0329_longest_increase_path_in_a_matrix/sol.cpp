/*
  Given an integer matrix, find the length of the longest increasing path.

  From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

  Example 1:

  nums = [
  [9,9,4],
  [6,6,8],
  [2,1,1]
  ]
  Return 4
  The longest increasing path is [1, 2, 6, 9].

  Example 2:

  nums = [
  [3,4,5],
  [3,2,6],
  [2,2,1]
  ]
  Return 4
  The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
*/

#include "../common/common.h"

using namespace std;

// DFS + memoization
class Solution {
public:
  Solution() : _m(0),
	       _n(0),
	       _dir({{-1,0}, {0,1}, {1,0}, {0,-1}})
  {
    // Dummy
  }
  
  int longestIncreasingPath(vector<vector<int>>& matrix) {
    if(matrix.empty())
      return 0;

    _m = matrix.size();
    _n = matrix[0].size();
    int maxLen = 0;

    vector<vector<int>> mem(_m, vector<int>(_n, 0));  // used as both memoization and visited flag
    for(int i=0; i<_m; ++i) {
      for(int j=0; j<_n; ++j) {
	maxLen = max(maxLen, search(matrix, mem, i, j));
      }
    }
    
    return maxLen;
  }

private:
  // Note there can't be loop as the path is monotonically increasing
  int search(vector<vector<int>> &matrix,
	     vector<vector<int>> &mem,
	     int i,
	     int j)
  {
    if(mem[i][j])
      return mem[i][j];
    
    for(auto d : _dir) {
      int ii = i + d.first;
      int jj = j + d.second;
      if(ii>=0 && ii<_m && jj>=0 && jj<_n  && matrix[i][j]<matrix[ii][jj]) {
	mem[i][j] = max(mem[i][j], search(matrix, mem, ii, jj));
      }
    }

    return ++mem[i][j];
  }

private:
  int _m;
  int _n;
  vector<pair<int,int>> _dir;
};

int main()
{
  //xxx vector<vector<int>> matrix = {{9,9,4},{6,6,8},{2,1,1}};
  vector<vector<int>> matrix = {{1,2,3}, {6,5,4}, {7, 8, 9}};
  //xxx vector<vector<int>> matrix= {{1,2,3,2,1,0}};
  Solution sol;
  int res = sol.longestIncreasingPath(matrix);
  cout << "res: " << res << endl;

  return 0;
}
