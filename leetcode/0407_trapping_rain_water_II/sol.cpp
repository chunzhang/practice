/*
  Given an m x n matrix of positive integers representing the height of each unit cell in a 2D elevation map, compute the volume of water it is able to trap after raining.

  Note:
  Both m and n are less than 110. The height of each unit cell is greater than 0 and is less than 20,000.

  Example:

  Given the following 3x6 height map:
  [
  [1,4,3,1,3,2],
  [3,2,1,3,2,4],
  [2,3,3,2,3,1]
  ]

  Return 4.

  The above image represents the elevation map [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]] before the rain.


  After the rain, water is trapped between the blocks. The total volume of water trapped is 4.
*/

// Use priority queue to keep the currnet boundary

class Solution {
public:
  struct Bar {
    Bar(int height, int row, int column) : h(height),
					   r(row),
					   c(column)
    {
      // Dummy                                          
    }
    int h;  // height
    int r;  // row index
    int c;  // column index
  };
    
public:
  int trapRainWater(vector<vector<int>>& heightMap) {
    if(heightMap.empty())
      return 0;
    int m = heightMap.size();     // num of rows
    int n = heightMap[0].size();  // num of cols
    int sinkHeight = 0;  // this is the "sink's height", i.e., water inside the current boundary would flow into such sink
    auto comp = [](const Bar& e1, const Bar &e2) {return e1.h>e2.h;};
    priority_queue<Bar, vector<Bar>, decltype(comp)> pq(comp);
    int water = 0;  // trapped water
    vector<vector<int>> visited(m, vector<int>(n,0));
        
    // 1. build initial boundary
    for(int i=0; i<m; ++i)
      for(int j=0; j<n; ++j)
	if(i==0 || i==m-1 || j==0 || j==n-1)
	  if(!visited[i][j]) {
	    pq.push(Bar(heightMap[i][j], i, j));
	    visited[i][j] = 1;
	  }
        
    // 2. move boundary towards inside
    vector<pair<int,int>> dir = {{-1,0}, {0,1}, {1,0}, {0,-1}};  // search directions
    while(!pq.empty()) {
      Bar cur = pq.top();
      pq.pop();
      if(cur.h > sinkHeight)  // sink's height can only increase when we encounter a new boundary bar with bigger height
	sinkHeight = cur.h;
      for(auto d : dir) {
	int x = cur.r + d.first;
	int y = cur.c + d.second;
	if(x<0 || x>=m || y<0 || y>=n || visited[x][y])
	  continue;
	visited[x][y] = 1;
	Bar next(heightMap[x][y], x, y);
	if(next.h < sinkHeight)
	  water += sinkHeight-next.h;
	pq.push(next);
      }
    }
        
    return water;
  }
};
