/*
  You are given an m x n grid rooms initialized with these three possible values.

  -1 A wall or an obstacle.
  0 A gate.
  INF Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
  Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

 

  Example 1:


  Input: rooms = [[2147483647,-1,0,2147483647],[2147483647,2147483647,2147483647,-1],[2147483647,-1,2147483647,-1],[0,-1,2147483647,2147483647]]
  Output: [[3,-1,0,1],[2,2,1,-1],[1,-1,2,-1],[0,-1,3,4]]
  Example 2:

  Input: rooms = [[-1]]
  Output: [[-1]]
  Example 3:

  Input: rooms = [[2147483647]]
  Output: [[2147483647]]
  Example 4:

  Input: rooms = [[0]]
  Output: [[0]]
 

  Constraints:

  m == rooms.length
  n == rooms[i].length
  1 <= m, n <= 250
  rooms[i][j] is -1, 0, or 231 - 1.
*/


// BFS from all gates
// time complexity: O(M*N)
class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        const int M = rooms.size();
        const int N = rooms[0].size();
        const int DIR[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
        
        // BFS
        queue<pair<int,int>> q;
        for(int i=0; i<M; ++i)
            for(int j=0; j<N; ++j)
                if(rooms[i][j] == 0)
                    q.push({i,j});
        int steps = 0;
        while(!q.empty()) {
            ++steps;
            int sz = q.size();
            while(sz--) {
                pair<int,int> cur = q.front();
                q.pop();
                for(int d=0; d<4; ++d) {
                    int ni = cur.first + DIR[d][0];
                    int nj = cur.second + DIR[d][1];
                    if(ni<0 || ni>=M || nj<0 || nj>=N || rooms[ni][nj]!=INT_MAX)
                        continue;
                    rooms[ni][nj] = steps;
                    q.push({ni,nj});
                }
            }
        }
    }
};
