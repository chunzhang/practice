/*
  You want to build a house on an empty land which reaches all buildings in the shortest amount of distance. You can only move up, down, left and right. You are given a 2D grid of values 0, 1 or 2, where:

  Each 0 marks an empty land which you can pass by freely.
  Each 1 marks a building which you cannot pass through.
  Each 2 marks an obstacle which you cannot pass through.
  For example, given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2):

  1 - 0 - 2 - 0 - 1
  |   |   |   |   |
  0 - 0 - 0 - 0 - 0
  |   |   |   |   |
  0 - 0 - 1 - 0 - 0
  The point (1,2) is an ideal empty land to build a house, as the total travel distance of 3+3+1=7 is minimal. So return 7.

  Note:
  There will be at least one building. If it is not possible to build such house according to the above rules, return -1.
*/

#include "../common/common.h"

using namespace std;

class Solution {
public:
  int shortestDistance(vector<vector<int>>& grid) {
    if(grid.empty())
      return -1;
        
    int m = grid.size();     // number of rows
    int n = grid[0].size();  // number of colss
    vector<pair<int,int>> dir = {{-1,0}, {0,1}, {1,0}, {0,-1}};  // four search directions
    int nBuilding = 0;  // number of buildings processed so far
    vector<vector<int>> nReach(m, vector<int>(n,0));     // For each 0-grid, how many buildings has reached it so far
    vector<vector<int>> distance(m, vector<int>(n, 0));  // For each 0-grid, total min-distance from all reachable buildings so far
    for(int i=0; i<m; ++i) {
      for(int j=0; j<n; ++j) {
	if(grid[i][j] != 1)
	  continue;
                
	// Assume number of buildings is less than number of empty land, so we
	// search from buildings to lands to save total number of searches
	++nBuilding;
                
	// We use BFS as by nature it computes shortest path from source to the frontier
	vector<vector<int>> visited(m, vector<int>(n,0));  // visit flag for BFS search
	int dist = 0;
	queue<pair<int,int>> qCur;   // current BFS frontier
	queue<pair<int,int>> qNext;  // next BFS frontier
	qCur.push(make_pair(i,j));  // starting point
	while(!qCur.empty()) {
	  int gi = qCur.front().first;  // current grid axis
	  int gj = qCur.front().second;
	  qCur.pop();
	  for(auto move : dir) {
	    int ii = gi + move.first;   // next grid to search
	    int jj = gj + move.second;
	    if(ii>=0 && ii<m && jj>=0 && jj<n   // valid grid
	       && grid[ii][jj]==0               // can only propagate through empty land
	       && !visited[ii][jj]              // first time discovered
	       && nReach[ii][jj]==nBuilding-1)  // no need to propagate through land that isn't reachable to all prevoius buildings -- this is an important pruning for improving runtime
	      {
		distance[ii][jj] += dist + 1;
		nReach[ii][jj] += 1;  // this land is reached from current building
		visited[ii][jj] = 1;
		qNext.push(make_pair(ii,jj));
	      }
	  }
                    
	  if(qCur.empty()) {  // current frontier is absorbed so switch to next frontier
	    ++dist;
	    swap(qCur, qNext);
	  }
	}  // End of BFS of current building               
      }
    }
        
    int minDist = INT_MAX;
    for(int i=0; i<m; ++i) {
      for(int j=0; j<n; ++j) {
	if(grid[i][j]==0 && nReach[i][j]==nBuilding) {
	  minDist = min(minDist, distance[i][j]);
	} 
      }
    }
        
    return minDist==INT_MAX ? -1 : minDist;
  }
};
