/*
  There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.

  Given the ball's start position, the destination and the maze, determine whether the ball could stop at the destination.

  The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space. You may assume that the borders of the maze are all walls. The start and destination coordinates are represented by row and column indexes.

  Example 1

  Input 1: a maze represented by a 2D array

  0 0 1 0 0
  0 0 0 0 0
  0 0 0 1 0
  1 1 0 1 1
  0 0 0 0 0

  Input 2: start coordinate (rowStart, colStart) = (0, 4)
  Input 3: destination coordinate (rowDest, colDest) = (4, 4)

  Output: true
  Explanation: One possible way is : left -> down -> left -> down -> right -> down -> right.

  Example 2

  Input 1: a maze represented by a 2D array

  0 0 1 0 0
  0 0 0 0 0
  0 0 0 1 0
  1 1 0 1 1
  0 0 0 0 0

  Input 2: start coordinate (rowStart, colStart) = (0, 4)
  Input 3: destination coordinate (rowDest, colDest) = (3, 2)

  Output: false
  Explanation: There is no way for the ball to stop at the destination.

  Note:
  There is only one ball and one destination in the maze.
  Both the ball and the destination exist on an empty space, and they will not be at the same position initially.
  The given maze does not contain border (like the red rectangle in the example pictures), but you could assume the border of the maze are all walls.
  The maze contains at least 2 empty spaces, and both the width and height of the maze won't exceed 100.
*/

// My DFS solution
class Solution {
public:
  bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    if(maze.empty())
      return false;
        
    int m = maze.size();
    int n = maze[0].size();
    vector<vector<int>> visited(m, vector<int>(n, 0));
    return dfs(maze, visited, m, n, start[0], start[1], destination[0], destination[1]);
  }
    
private:
  bool dfs(vector<vector<int>> &maze, vector<vector<int>> &visited, int m, int n, int x, int y, int dx, int dy) {
    static vector<pair<int,int>> directions = {{-1,0}, {0,1}, {1,0}, {0,-1}};

    if(x==dx && y==dy)  // reach destination
      return true;
        
    for(auto dir : directions) {
      int xx = x + dir.first;
      int yy = y + dir.second;
      while(xx>=0 && xx<m && yy>=0 && yy<n && maze[xx][yy]!=1) {
	xx += dir.first;
	yy += dir.second;
      }
      xx -= dir.first;   // move back to last valid position
      yy -= dir.second;
            
      if(!visited[xx][yy]) {
	visited[xx][yy] = 1;
	if(dfs(maze, visited, m, n, xx, yy, dx, dy))
	  return true;
      }
    }
        
    return false;
  }
};

// My BFS solution
class Solution {
public:
  bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    if(maze.empty())
      return false;
        
    int m = maze.size();
    int n = maze[0].size();
    vector<vector<int>> visited(m, vector<int>(n, 0));
    queue<pair<int,int>> q;
    q.push(make_pair(start[0], start[1]));
    visited[start[0]][start[1]] = 1;
    vector<pair<int,int>> directions = {{-1,0}, {0,1}, {1,0}, {0,-1}};
    while(!q.empty()) {
      int x = q.front().first;
      int y = q.front().second;
      q.pop();
      if(x==destination[0] && y==destination[1])
	return true;
            
      for(auto dir : directions) {
	int xx = x + dir.first;
	int yy = y + dir.second;
	while(xx>=0 && xx<m && yy>=0 && yy<n && maze[xx][yy]!=1) {
	  xx += dir.first;
	  yy += dir.second;
	}
	xx -= dir.first;   // move back to last valid position
	yy -= dir.second;
	if(!visited[xx][yy]) {
	  visited[xx][yy] = 1;
	  q.push(make_pair(xx,yy));
	}
      }
    }
        
    return false;
  }
    
};
