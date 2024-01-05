/*
Facebook/Google/TikTok

There is a ball in a maze with empty spaces (represented as 0) and walls (represented as 1). The ball can go through the empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.

Given the m x n maze, the ball's start position and the destination, where start = [startrow, startcol] and destination = [destinationrow, destinationcol], return true if the ball can stop at the destination, otherwise return false.

You may assume that the borders of the maze are all walls (see examples).

 

Example 1:


Input: maze = [[0,0,1,0,0],[0,0,0,0,0],[0,0,0,1,0],[1,1,0,1,1],[0,0,0,0,0]], start = [0,4], destination = [4,4]
Output: true
Explanation: One possible way is : left -> down -> left -> down -> right -> down -> right.
Example 2:


Input: maze = [[0,0,1,0,0],[0,0,0,0,0],[0,0,0,1,0],[1,1,0,1,1],[0,0,0,0,0]], start = [0,4], destination = [3,2]
Output: false
Explanation: There is no way for the ball to stop at the destination. Notice that you can pass through the destination but you cannot stop there.
Example 3:

Input: maze = [[0,0,0,0,0],[1,1,0,0,1],[0,0,0,0,0],[0,1,0,0,1],[0,1,0,0,0]], start = [4,3], destination = [0,1]
Output: false
 

Constraints:

m == maze.length
n == maze[i].length
1 <= m, n <= 100
maze[i][j] is 0 or 1.
start.length == 2
destination.length == 2
0 <= start_row, destination_row <= m
0 <= start_col, destination_col <= n
Both the ball and the destination exist in an empty space, and they will not be in the same position initially.
The maze contains at least 2 empty spaces.
*/

// My DFS solution: next position is where the ball stops
// time: O(MN*(M+N)), i.e., each DFS we iterate four directions where each direction can be an O(M) or O(N) loop
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

// My BFS solution: next position is where the ball stops
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


// DFS solution by keeping track of directions (more complicated in implementation)
// time: O(5*MN)?
class Solution {
public:
    enum STATUS {Right=0, Down, Left, Up, Stop};  // must be defined first

    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        // DFS search with directions
        M = maze.size();
        N = maze[0].size();
        m_visited.resize(5, maze);
        return search(maze,start[0],start[1],destination[0],destination[1],Stop);
    }

private:
    bool search(const vector<vector<int>> &maze, int ci, int cj, int di, int dj, STATUS s) {
        m_visited[s][ci][cj] = 1;
        if(ci==di && cj==dj && s==Stop)
            return true;

        STATUS ns;
        int ni;
        int nj;
        if(s == Stop) {  // serach all four directions
            for(int i=Right; i<=Up; ++i) {  // use int as enum does not support ++
                ns = STATUS(i);  // note the type conversion here
                ni = ci + m_dir[ns].first;
                nj = cj + m_dir[ns].second;
                if(ni>=0 && ni<M && nj>=0 && nj<N && !maze[ni][nj] && !m_visited[ns][ni][nj])
                    if(search(maze,ni,nj,di,dj,ns))
                        return true;
            }
        }
        else {  // rolling with same direction
            ni = ci + m_dir[s].first;
            nj = cj + m_dir[s].second;
            if(ni>=0 && ni<M && nj>=0 && nj<N && !maze[ni][nj])
                ns = s;
            else {// hit border -- stop
                ns = Stop;
                ni = ci;
                nj = cj;
            }
            
            if(!m_visited[ns][ni][nj])
                return search(maze,ni,nj,di,dj,ns);
        }

        return false;
    }

private:
    int M;
    int N;
    const vector<pair<int,int>> m_dir = {{0,1},{1,0},{0,-1},{-1,0}};
    vector<vector<vector<int>>> m_visited;    
};
