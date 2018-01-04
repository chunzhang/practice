/*
  Given a 2D grid, each cell is either a wall 'W', an enemy 'E' or empty '0' (the number zero), return the maximum enemies you can kill using one bomb.
  The bomb kills all the enemies in the same row and column from the planted point until it hits the wall since the wall is too strong to be destroyed.
  Note that you can only put the bomb at an empty cell.

  Example:
  For the given grid

  0 E 0 0
  E 0 W E
  0 E 0 0

  return 3. (Placing a bomb at (1,1) kills 3 enemies)
*/

#include "../common/common.h"

using namespace std;

// Here's a better solution based on https://leetcode.com/problems/bomb-enemy/discuss/83387/
// Actually, we can optimize the space complexity to O(m) or O(n) as we only need to keep track of enemies killed row-wise/col-wise between walls
// Time complexity is still O(mn)
class Solution {
public:
  int maxKilledEnemies(vector<vector<char>>& grid) {
    int m = grid.size();
    int n = m ? grid[0].size() : 0;
    if(!m || !n)
      return 0;

    int maxKilled = 0;
    int rowKill = 0;
    vector<int> colKill(n,0);  // Here I choose space complexity to be O(n)
    for(int i=0; i<m; ++i) {
      for(int j=0; j<n; ++j) {
	// we need to recompute rowKill for the current row as a wall has been encountered
	if(j==0 || grid[i][j-1]=='W') {
	  rowKill = 0;
	  for(int k=j; k<n&&grid[i][k]!='W'; ++k)
	    if(grid[i][k] == 'E')
	      ++rowKill;
	}

	// we need to recompute colKill for the current column as a wall has been encountered
	if(i==0 || grid[i-1][j]=='W') {
	  colKill[j] = 0;
	  for(int k=i; k<m&&grid[k][j]!='W'; ++k)
	    if(grid[k][j] == 'E')
	      ++colKill[j];
	}

	if(grid[i][j] == '0')
	  maxKilled = max(maxKilled, rowKill+colKill[j]);
      }
    }

    return maxKilled;
  }

};


// Runtime: O(mn)
// Space: O(mn)
class Solution2 {
public:
  int maxKilledEnemies(vector<vector<char>>& grid) {
    int nRows = grid.size();
    int nCols = nRows ? grid[0].size() : 0;
    int maxKilled = 0;
    vector<vector<int>> killGrid(nRows, vector<int>(nCols,0));  // number of enemies killed on the row only

    // row scan
    for(int i=0; i<nRows; ++i) {
      for(int l=0,r=0,nEnemy=0 ; r<=nCols; ++r) {
	if(r==nCols || grid[i][r]=='W') {
	  for(int j=l; j<r; ++j)
	    killGrid[i][j] = grid[i][j]=='0' ? nEnemy : 0;
	  l = r + 1;
	  nEnemy = 0;
	}
	else if(grid[i][r] == 'E')
	  ++nEnemy;

      }
    }

    // col scan
    for(int j=0; j<nCols; ++j) {
      for(int t=0,b=0,nEnemy=0; b<=nRows; ++b) {
	if(b==nRows || grid[b][j]=='W') {
	  for(int i=t; i<b; ++i)
	    if(grid[i][j] == '0')
	      maxKilled = max(maxKilled, nEnemy+killGrid[i][j]);
	  t = b + 1;
	  nEnemy = 0;
	}
	else if(grid[b][j] == 'E')
	  ++nEnemy;
      }
    }

    return maxKilled;
  }
};

int main()
{
  vector<vector<char>> grid = {{'0','E','0','0'}, {'E','0','W','E'}, {'0','E','0','0'}};
  //xxx printMatrix(grid);
  Solution sol;
  int maxKilled = sol.maxKilledEnemies(grid);
  cout << "maxKilled: " << maxKilled << endl;

  return 0;
}
