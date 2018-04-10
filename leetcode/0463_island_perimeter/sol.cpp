/*
  You are given a map in form of a two-dimensional integer grid where 1 represents land and 0 represents water. Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells). The island doesn't have "lakes" (water inside that isn't connected to the water around the island). One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.

  Example:

  [[0,1,0,0],
  [1,1,1,0],
  [0,1,0,0],
  [1,1,0,0]]

  Answer: 16
  Explanation: The perimeter is the 16 yellow stripes in the image below:
*/


// Straightforward solution
// Check neighbors of all land grid. If the neighbor is 
// water grid or boundary, perimenter+=1
class Solution {
public:
  int islandPerimeter(vector<vector<int>>& grid) {
    int ans = 0;
    int m = grid.size();
    int n = m ? grid[0].size() : 0;
        
    for(int i=0; i<m; ++i) {
      for(int j=0; j<n; ++j) {
	if(grid[i][j] == 0)
	  continue;
	if(i==0 || grid[i-1][j]==0)
	  ++ans;
	if(i==m-1 || grid[i+1][j]==0)
	  ++ans;
	if(j==0 || grid[i][j-1]==0)
	  ++ans;
	if(j==n-1 || grid[i][j+1]==0)
	  ++ans;
      }
    }
        
    return ans;
  }
};

// A faster solution
// perimenter = numLands*4 - numNeighbors*2
// -- Note numNeighbors shall not be double counted. As such, we 
//    only search neighbors in right and down direction
class Solution {
public:
  int islandPerimeter(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = m ? grid[0].size() : 0;
    int ans = 0;
    int numLands = 0;
    int numNeighbors = 0;
    for(int i=0; i<m; ++i)
      for(int j=0; j<n; ++j)
	if(grid[i][j] == 1) {
	  ++numLands;
	  // search neighbors in only right and down diection to avoid double counting
	  if(j!=n-1 && grid[i][j+1]==1)
	    ++numNeighbors;
	  if(i!=m-1 && grid[i+1][j]==1)
	    ++numNeighbors;
	}
    return numLands*4 - numNeighbors*2;
  }
};
