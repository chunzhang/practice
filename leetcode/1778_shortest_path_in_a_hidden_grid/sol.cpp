/*
Facebook

This is an interactive problem.

There is a robot in a hidden grid, and you are trying to get it from its starting cell to the target cell in this grid. The grid is of size m x n, and each cell in the grid is either empty or blocked. It is guaranteed that the starting cell and the target cell are different, and neither of them is blocked.

You want to find the minimum distance to the target cell. However, you do not know the grid's dimensions, the starting cell, nor the target cell. You are only allowed to ask queries to the GridMaster object.

Thr GridMaster class has the following functions:

boolean canMove(char direction) Returns true if the robot can move in that direction. Otherwise, it returns false.
void move(char direction) Moves the robot in that direction. If this move would move the robot to a blocked cell or off the grid, the move will be ignored, and the robot will remain in the same position.
boolean isTarget() Returns true if the robot is currently on the target cell. Otherwise, it returns false.
Note that direction in the above functions should be a character from {'U','D','L','R'}, representing the directions up, down, left, and right, respectively.

Return the minimum distance between the robot's initial starting cell and the target cell. If there is no valid path between the cells, return -1.

Custom testing:

The test input is read as a 2D matrix grid of size m x n where:

grid[i][j] == -1 indicates that the robot is in cell (i, j) (the starting cell).
grid[i][j] == 0 indicates that the cell (i, j) is blocked.
grid[i][j] == 1 indicates that the cell (i, j) is empty.
grid[i][j] == 2 indicates that the cell (i, j) is the target cell.
There is exactly one -1 and 2 in grid. Remember that you will not have this information in your code.

Example 1:

Input: grid = [[1,2],[-1,0]]
Output: 2
Explanation: One possible interaction is described below:
The robot is initially standing on cell (1, 0), denoted by the -1.
- master.canMove('U') returns true.
- master.canMove('D') returns false.
- master.canMove('L') returns false.
- master.canMove('R') returns false.
- master.move('U') moves the robot to the cell (0, 0).
- master.isTarget() returns false.
- master.canMove('U') returns false.
- master.canMove('D') returns true.
- master.canMove('L') returns false.
- master.canMove('R') returns true.
- master.move('R') moves the robot to the cell (0, 1).
- master.isTarget() returns true. 
We now know that the target is the cell (0, 1), and the shortest path to the target cell is 2.

Example 2:

Input: grid = [[0,0,-1],[1,1,1],[2,0,0]]
Output: 4
Explanation: The minimum distance between the robot and the target cell is 4.
Example 3:

Input: grid = [[-1,0],[0,2]]
Output: -1
Explanation: There is no path from the robot to the target cell.
 

Constraints:

1 <= n, m <= 500
m == grid.length
n == grid[i].length
grid[i][j] is either -1, 0, 1, or 2.
There is exactly one -1 in grid.
There is exactly one 2 in grid.
*/


/**
 * // This is the GridMaster's API interface.
 * // You should not implement it, or speculate about its implementation
 * class GridMaster {
 *   public:
 *     bool canMove(char direction);
 *     void move(char direction);
 *     boolean isTarget();
 * };
 */

// passing solution: first DFS to build grid, then BFS to get shortest path
class Solution {
public:
    int findShortestPath(GridMaster &master) {
        grid = vector<vector<short>>(1001, vector<short>(1001,-1));  // -1: unvisited, 0: empty, 1: blocked

        // first, perfrom DFS to build the grid
        // assume original location is in the center of the grid
        dfs(master, 500, 500);

        // DFS does not reach target, we can early exit here
        if(tx==-1 || ty==-1)
            return -1;

        // next, perfrom BFS to get shortest path
        int ans = 0;
        queue<pair<int,int>> q;
        q.emplace(500,500);
        grid[500][500] = 1;  // reuse as visited flat
        while(!q.empty()) {
            ++ans;
            int sz = q.size();
            while(sz--) {
                auto cur = q.front();
                q.pop();
                for(int d=0; d<dir.size(); ++d) {
                    int nx = cur.first + dirIdx[d].first;
                    int ny = cur.second + dirIdx[d].second;
                    if(nx==tx && ny==ty)  // find target
                        return ans;
                    if(!grid[nx][ny]) {  // find unvisited and unblocked grid
                        q.emplace(nx,ny);
                        grid[nx][ny] = 1;
                    }
                }
            }
        }

        return -1;
    }

private:
    void dfs(GridMaster &m, int cx, int cy) {
        if(m.isTarget()) {
            tx = cx;
            ty = cy;
        }

        for(int d=0; d<dir.size(); ++d) {
            int nx = cx + dirIdx[d].first;
            int ny = cy + dirIdx[d].second;
            if(grid[nx][ny] != -1)  // this grid is already visited
                continue;

            if(!m.canMove(dir[d])) {
                grid[nx][ny] = 1;  // this grid is blocked
                continue;
            }

            // need to visit next grid
            grid[nx][ny] = 0;  // this grid can be reached
            m.move(dir[d]);
            dfs(m, nx, ny);
            m.move(dir2[d]);  // move back
        }
    }

private:
    vector<char> dir = {'U', 'D', 'L', 'R'};
    vector<char> dir2 = {'D', 'U', 'R', 'L'};  // reverse direction
    vector<pair<int,int>> dirIdx = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    vector<vector<short>> grid;  // grid to be filled through DFS
    int tx = -1;  // target x
    int ty = -1;  // target y
};


// first DFS to build accessibility, then do BFS for shortest path
// -- still TLE (36/36 passed): this is likely due to implementation inefficiency (e.g., hash table) rather than algorithm complexity
class Solution {
public:
    struct MyHash {
        size_t operator()(const pair<int,int> &p) const {
            return p.first*31 + p.second;
        }
    };

    int findShortestPath(GridMaster &master) {
        // first, perform DFS to build grid accessibility (i.e., for a given grid what direction it can move further)
        pair<int,int> cur = {0,0};
        access[cur] = {0,0,0,0};
        dfs(master, cur);

        // next, perform BFS to calculate shortest path
        int ans = 0;
        unordered_set<pair<int,int>, MyHash> visited;
        visited.emplace(0,0);
        queue<pair<int,int>> q;
        q.emplace(0,0);
        while(!q.empty()) {
            ++ans;
            int sz = q.size();
            while(sz--) {
                auto cur = q.front();
                q.pop();
                for(int d=0; d<dir.size(); ++d) {
                    if(!access[cur][d])
                        continue;
                    pair<int,int> next = {cur.first+dirIdx[d].first, cur.second+dirIdx[d].second};
                    if(next == target)
                        return ans;
                    if(!visited.count(next)) {
                        visited.insert(next);
                        q.push(next);
                    }
                }
            }
        }

        return -1;
    }

private:
    void dfs(GridMaster &m, const pair<int,int> &cur) {
        if(m.isTarget())
            target = cur;

        vector<int> &canAccess = access[cur];
        for(int d=0; d<dir.size(); ++d) {
            if(!m.canMove(dir[d]))
                continue;
            canAccess[d] = 1;
            pair<int,int> next = {cur.first+dirIdx[d].first, cur.second+dirIdx[d].second};
            if(!access.count(next)) {
                access[next] = {0,0,0,0};
                m.move(dir[d]);
                dfs(m, next);
                m.move(dir2[d]);  // need to move back
            }
        }
    }

private:
    unordered_map<pair<int,int>, vector<int>, MyHash> access;
    pair<int,int> target = {INT_MAX,INT_MAX};
    vector<char> dir = {'U', 'D', 'L', 'R'};
    vector<char> dir2 = {'D', 'U', 'R', 'L'};  // reverse direction
    vector<pair<int,int>> dirIdx = {{-1,0}, {1,0}, {0,-1}, {0,1}};
};


// BFS -- memory limit exceeded
// copy GridMaster is too expensive
class Solution {
public:
    struct Node {
        int x;
        int y;
        GridMaster m;
        Node(int xx, int yy, GridMaster &mm) : x(xx), y(yy), m(mm) {

        }
    };

    int findShortestPath(GridMaster &master) {
        vector<char> dir = {'U', 'D', 'L', 'R'};
        vector<pair<int,int>> dirIdx = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        // BFS for shortest distance
        auto hash = [](const pair<int,int> &p) {return p.first*31+p.second;};
        unordered_set<pair<int,int>, decltype(hash)> visited;
        visited.emplace(0,0);  // make starting position the origin (0,0)
        queue<Node> q;
        q.emplace(0,0,master);
        int ans = 0;
        while(!q.empty()) {
            ++ans;
            int sz = q.size();
            while(sz--) {
                auto cur = q.front();
                q.pop();
                for(int d=0; d<dir.size(); ++d) {
                    int nx = cur.x + dirIdx[d].first;
                    int ny = cur.y + dirIdx[d].second;
                    if(cur.m.canMove(dir[d]) && !visited.count({nx,ny})) {
                        GridMaster nm = cur.m;
                        nm.move(dir[d]);
                        if(nm.isTarget())
                            return ans;
                        visited.emplace(nx,ny);
                        q.emplace(nx,ny,nm);
                    }                    
                }
            }
        }

        return -1;
    }
};


// DFS: allow revisit the node if a shorter distance is found
// TLE
class Solution {
public:
    struct MyHash {
        size_t operator()(const pair<int,int> &p) const {  // the function must be const
            return p.first*31 + p.second;
        }
    };

    int findShortestPath(GridMaster &master) {
        int ans = INT_MAX;
        pair<int,int> cur = {0,0};
        dist[cur] = 0;
        dfs(master, ans, cur);
        return ans==INT_MAX ? -1 : ans;
    }

private:
    void dfs(GridMaster &m, int &ans, const pair<int,int> &cur) {
        int curDist = dist[cur];

        if(m.isTarget()) {
            ans = min(ans, curDist);
            return;
        }

        for(int d=0; d<dir.size(); ++d) {
            if(!m.canMove(dir[d]))
                continue;
            pair<int,int> next = {cur.first+dirIdx[d].first, cur.second+dirIdx[d].second};
            if(!dist.count(next) || dist[next]>curDist+1) {
                dist[next] = curDist + 1;  // found better path
                m.move(dir[d]);
                dfs(m, ans, next);
                m.move(dir2[d]);  // need to move back
            }
        }
    }

private:
    unordered_map<pair<int,int>, int, MyHash> dist;
    vector<char> dir = {'U', 'D', 'L', 'R'};
    vector<char> dir2 = {'D', 'U', 'R', 'L'};  // reverse direction
    vector<pair<int,int>> dirIdx = {{-1,0}, {1,0}, {0,-1}, {0,1}};
};
