/*
  You are given a m x n 2D grid initialized with these three possible values.

  -1 - A wall or an obstacle.
  0 - A gate.
  INF - Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
  Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

  For example, given the 2D grid:
  INF  -1  0  INF
  INF INF INF  -1
  INF  -1 INF  -1
  0  -1 INF INF
  After running your function, the 2D grid should be:
  3  -1   0   1
  2   2   1  -1
  1  -1   2  -1
  0  -1   3   4
*/

// BFS from all gates
class Solution {
public:
  void wallsAndGates(vector<vector<int>>& rooms) {
    if(rooms.empty())
      return;
        
    int m = rooms.size();
    int n = rooms[0].size();
    queue<pair<int,int>> q;   // current level
    for(int i=0; i<m; ++i)    // starting from all gates at the same time!
      for(int j=0; j<n; ++j)
	if(rooms[i][j] == 0) {
	  q.push(make_pair(i,j));
	}
    vector<pair<int,int>> directions = {{-1,0}, {0,1}, {1,0}, {0,-1}};
    while(!q.empty()) {
      int x = q.front().first;
      int y = q.front().second;
      q.pop();
      for(auto dir : directions) {
	int xx = x + dir.first;
	int yy = y + dir.second;
	if(xx>=0 && xx<m && yy>=0 && yy<n && rooms[xx][yy]==INT_MAX) {
	  rooms[xx][yy] = rooms[x][y] + 1;
	  q.push(make_pair(xx,yy));
	}
      }
    }
                
    return;
  }
    
};
