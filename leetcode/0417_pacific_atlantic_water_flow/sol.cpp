/*
  Given an m x n matrix of non-negative integers representing the height of each unit cell in a continent, the "Pacific ocean" touches the left and top edges of the matrix and the "Atlantic ocean" touches the right and bottom edges.

  Water can only flow in four directions (up, down, left, or right) from a cell to another one with height equal or lower.

  Find the list of grid coordinates where water can flow to both the Pacific and Atlantic ocean.

  Note:
  The order of returned grid coordinates does not matter.
  Both m and n are less than 150.
  Example:

  Given the following 5x5 matrix:

  Pacific ~   ~   ~   ~   ~ 
  ~  1   2   2   3  (5) *
  ~  3   2   3  (4) (4) *
  ~  2   4  (5)  3   1  *
  ~ (6) (7)  1   4   5  *
  ~ (5)  1   1   2   4  *
  *   *   *   *   * Atlantic

  Return:

  [[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]] (positions with parentheses in above matrix).
*/

#include "../common/common.h"

using namespace std;

// BFS from oceans
class Solution {
public:
  vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
    vector<pair<int,int>> res;
    if(matrix.empty())
      return res;
        
    _m = matrix.size();
    _n = matrix[0].size();
    _dir.push_back({-1,0});
    _dir.push_back({0,1});
    _dir.push_back({1,0});
    _dir.push_back({0,-1});
    _tbl.resize(_m, vector<int>(_n,0));
        
    // BFS from Pacific
    for(int i=0; i<_m; ++i) {
      _q.push(make_pair(i,0));
      _tbl[i][0] |= 0x1;
    }
    for(int j=1; j<_n; ++j) {
      _q.push(make_pair(0,j));
      _tbl[0][j] |= 0x1;
    }
    search(matrix, 0x1);
        
    // BFS from Atlantic
    for(int i=0; i<_m; ++i) {
      _q.push(make_pair(i,_n-1));
      _tbl[i][_n-1] |= 0x2;
    }
    for(int j=0; j<_n-1; ++j) {
      _q.push(make_pair(_m-1,j));
      _tbl[_m-1][j] |= 0x2;
    }
    search(matrix, 0x2);
        
    for(int i=0; i<_m; ++i)
      for(int j=0; j<_n; ++j)
	if(_tbl[i][j] == 0x3)
	  res.push_back(make_pair(i,j));
        
    return res;
  }
    
private:
  // BFS routine
  void search(vector<vector<int>>& matrix, int flag) {
    while(!_q.empty()) {
      int i = _q.front().first;
      int j = _q.front().second;
      _q.pop();
      for(auto d : _dir) {
	int ii = i + d.first;
	int jj = j + d.second;
	if(ii>=0 && ii<_m && jj>=0 && jj<_n && (_tbl[ii][jj]&flag)==0 && matrix[i][j]<=matrix[ii][jj]) {
	  _q.push(make_pair(ii,jj));
	  _tbl[ii][jj] |= flag;
	}
      }
    }
  }
    
private:
  int _m;
  int _n;
  vector<pair<int,int>> _dir;
  vector<vector<int>> _tbl;  // 0x1--visit flag; 0x2--reach pacific; 0x4--reach atlantic
  queue<pair<int,int>> _q;  // BFS frontier queue
    
};
