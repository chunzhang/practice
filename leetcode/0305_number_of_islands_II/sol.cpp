/*
  A 2d grid map of m rows and n columns is initially filled with water. We may perform an addLand operation which turns the water at position (row, col) into a land. Given a list of positions to operate, count the number of islands after each addLand operation. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

  Example:

  Given m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]].
  Initially, the 2d grid grid is filled with water. (Assume 0 represents water and 1 represents land).

  0 0 0
  0 0 0
  0 0 0
  Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.

  1 0 0
  0 0 0   Number of islands = 1
  0 0 0
  Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.

  1 1 0
  0 0 0   Number of islands = 1
  0 0 0
  Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.

  1 1 0
  0 0 1   Number of islands = 2
  0 0 0
  Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land.

  1 1 0
  0 0 1   Number of islands = 3
  0 1 0
  We return the result as an array: [1, 1, 2, 3]

  Challenge:

  Can you do it in time complexity O(k log mn), where k is the length of the positions?
*/

#include "../common/common.h"

using namespace std;

class Solution {
public:
  vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
    _sets.resize(m*n, -1);
    _ranks.resize(m*n, -1);
    _numIslands = 0;

    vector<pair<int,int>> directions = {{-1,0}, {0,1}, {1,0}, {0,-1}};
    vector<int> res;
    for(auto pos : positions) {
      int idx = pos.first*n + pos.second;
      addIsland(idx);
      for(auto dir : directions) {
	int ii = pos.first + dir.first;
	int jj = pos.second + dir.second;
	int idxNeig = ii*n + jj;
	if(ii>=0 && ii<m && jj>=0 && jj<n && _sets[idxNeig]!=-1) {
	  unionIslands(idx, idxNeig);
	}
      }

      res.push_back(_numIslands);
    }

    return res;
  }

private:
  void addIsland(int idx) {
    _sets[idx] = idx;
    _ranks[idx] = 1;
    ++_numIslands;
  }
  
  int findRoot(int idx) {
    if(_sets[idx] == -1)  // this is not a valid set
      return -1;
    
    if(_sets[idx] != idx)
      _sets[idx] = findRoot(_sets[idx]);  // path compression
    return _sets[idx];
  }

  void unionIslands(int idx1, int idx2) {
    int p1 = findRoot(idx1);
    int p2 = findRoot(idx2);
    if(p1!=-1 && p2!=-1 && p1!=p2) {
      if(_ranks[p1] > _ranks[p2]) {  // use ranks
	_sets[p2] = p1;
      }
      else if(_ranks[p1] < _ranks[p2]) {
	_sets[p1] = p2;
      }
      else {
	_sets[p2] = p1;
	_ranks[p1]++;
      }

      --_numIslands;
    }
  }

private:
  vector<int> _sets;    // _sets[i] keeps parent of i; _sets[i]==i --> root, _sets[i]==-1 --> invalid
  vector<int> _ranks;   // higher rank means the set has more nodes; _ranks[i]==-1 --> invalid
  int _numIslands;
};

int main()
{
  int m = 3;
  int n = 3;
  vector<pair<int,int>> positions = {{0,0}, {0,1}, {1,2}, {2,1}, {1,1}};
  //xxx vector<pair<int,int>> positions = {{0,0}, {0,1}, {1,2}, {1,1}};
  Solution sol;
  auto res = sol.numIslands2(m, n, positions);
  printVector(res);

  return 0;
}
