/*
In an n*n grid, there is a snake that spans 2 cells and starts moving from the top left corner at (0, 0) and (0, 1). The grid has empty cells represented by zeros and blocked cells represented by ones. The snake wants to reach the lower right corner at (n-1, n-2) and (n-1, n-1).

In one move the snake can:

- Move one cell to the right if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
- Move down one cell if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
- Rotate clockwise if it's in a horizontal position and the two cells under it are both empty. In that case the snake moves from (r, c) and (r, c+1) to (r, c) and (r+1, c).
- Rotate counterclockwise if it's in a vertical position and the two cells to its right are both empty. In that case the snake moves from (r, c) and (r+1, c) to (r, c) and (r, c+1).

Return the minimum number of moves to reach the target.

If there is no way to reach the target, return -1.

 

Example 1:



Input: grid = [[0,0,0,0,0,1],
               [1,1,0,0,1,0],
               [0,0,0,0,1,1],
               [0,0,1,0,1,0],
               [0,1,1,0,0,0],
               [0,1,1,0,0,0]]
Output: 11
Explanation:
One possible solution is [right, right, rotate clockwise, right, down, down, down, down, rotate counterclockwise, right, down].
Example 2:

Input: grid = [[0,0,1,1,1,1],
               [0,0,0,0,1,1],
               [1,1,0,0,0,1],
               [1,1,1,0,0,1],
               [1,1,1,0,0,1],
               [1,1,1,0,0,0]]
Output: 9
 

Constraints:

2 <= n <= 100
0 <= grid[i][j] <= 1
It is guaranteed that the snake starts at empty cells.
*/

// BFS solution
class Solution {
public:
    int minimumMoves(vector<vector<int>>& grid) {
        // BFS, each node is an (head_x, head_y, direction) tuple;
        // direction=0 --> horizontal, direction=1 --> vertical
        int n = grid.size();
        vector<vector<vector<int>>> visited(n, vector<vector<int>>(n, vector<int>(2,0)));
        queue<vector<int>> q;
        q.push({0,1,0});  // initial head at (0,1) with horizontal direction
        visited[0][1][0] = 1;
        int level = 0;
        while(!q.empty()) {
            int size = q.size();
            while(size--) {
                auto cur = q.front();
                q.pop();
                int x = cur[0];
                int y = cur[1];
                int dir = cur[2];
                
                if(x==n-1 && y==n-1 && !dir)  // find destination
                    return level;
            
                // move right
                if(y<n-1 && !grid[x][y+1] && (!dir || !grid[x-1][y+1])) {
                    if(!visited[x][y+1][dir]) {
                        q.push({x,y+1,dir});
                        visited[x][y+1][dir] = 1;
                    }
                }
            
                // move down
                if(x<n-1 && !grid[x+1][y] && (dir || !grid[x+1][y-1])) {
                    if(!visited[x+1][y][dir]) {
                        q.push({x+1,y,dir});
                        visited[x+1][y][dir] = 1;
                    }
                }    
            
                // rotate clockwise
                if(!dir && x<n-1 && !grid[x+1][y-1] && !grid[x+1][y]) {
                    if(!visited[x+1][y-1][1]) {
                        q.push({x+1,y-1,1});
                        visited[x+1][y-1][1] = 1;
                    }
                }
            
                // rotate counter-clockwise
                if(dir && y<n-1 && !grid[x][y+1] && !grid[x-1][y+1]) {
                    if(!visited[x-1][y+1][0]) {
                        q.push({x-1,y+1,0});
                        visited[x-1][y+1][0] = 1;
                    }
                }
            }
            ++level;
        }
        
        return -1;
    }
};
