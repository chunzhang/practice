#include "../common/common.h"

using namespace std;

// O(M+N) space
// O(1) amortized time using path compression + ranking
// Ref: https://www.geeksforgeeks.org/union-find-algorithm-set-2-union-by-rank/
class UnionFind
{
public:
  UnionFind(const vector<vector<char>> &grid) {
    int m = grid.size();
    int n = m ? grid[0].size() : 0;
    _parent.resize(m*n);
    _rank.resize(m*n);
    _numSets = 0;
    for(int i=0; i<m; ++i) {
      for(int j=0; j<n; ++j) {
	int idx = i*n + j;  // 2D --> 1D index
	if(grid[i][j] == '1') {
	  _parent[idx] = idx;
	  _rank[idx] = 0;
	  ++_numSets;
	}
	else {
	  _parent[idx] = -1;
	  _rank[idx] = -1;
	}
      }
    }
  }

  int findRoot(int idx) {
    if(_parent[idx] == -1)
      return -1;
    if(_parent[idx] != idx)  // not root of the set, keep searching upward
      _parent[idx] = findRoot(_parent[idx]);  // path compression: shorten path to root when called
    return _parent[idx];
  }

  // Rank based set union
  void merge(int idx1, int idx2) {
    int root1 = findRoot(idx1);
    int root2 = findRoot(idx2);
    if(root1 == root2)  // already belongs to the same set, no-op
      return;
    if(_rank[root1] > _rank[root2]) {
      _parent[root2] = root1;
    }
    else if(_rank[root1] < _rank[root2]) {
      _parent[root1] = root2;
    }
    else {
      _parent[root2] = root1;
      ++_rank[root1];
    }
    --_numSets;
  }

  int numSets() const {
    return _numSets;
  }
  
private:
  vector<int> _parent;  // grid index --> root, parent[i]==-1 if the grid is '0', parent[i]==i if the grid is root
  vector<int> _rank;    // grid index --> rank
  int _numSets;          // number of disjoint sets
};


class Solution {
public:
  int numIslands(vector<vector<char>>& grid) {
    UnionFind uf(grid);
    int m = grid.size();
    int n = m ? grid[0].size() : 0;
    for(int i=0; i<m; ++i) {
      for(int j=0; j<n; ++j) {
	if(grid[i][j] == '1') {
	  int idx1 = i*n + j;
	  if(i>0 && grid[i-1][j]=='1')
	    uf.merge(idx1, (i-1)*n+j);
	  if(j+1<n && grid[i][j+1]=='1')
	    uf.merge(idx1, i*n+j+1);
	  if(i+1<m && grid[i+1][j]=='1')
	    uf.merge(idx1, (i+1)*n+j);
	  if(j>0 && grid[i][j-1]=='1')
	    uf.merge(idx1, i*n+j-1);
	}
      }
    }

    return uf.numSets();
  }
};

int main()
{
  //vector<vector<char>> grid = {{'1','1','1','1','0'}, {'1','1','0','1','0'}, {'1','1','0','0','0'}, {'0','0','0','0','0'}};
  vector<vector<char>> grid = {{'1','1','0','0','0'}, {'1','1','0','0','0'}, {'0','0','1','0','0'}, {'0','0','0','1','1'}};
  Solution sol;
  int num = sol.numIslands(grid);
  cout << "num: " << num << endl;

  return 0;
}
