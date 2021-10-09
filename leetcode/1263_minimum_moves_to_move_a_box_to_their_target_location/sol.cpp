/*
  A storekeeper is a game in which the player pushes boxes around in a warehouse trying to get them to target locations.

  The game is represented by an m x n grid of characters grid where each element is a wall, floor, or box.

  Your task is to move the box 'B' to the target position 'T' under the following rules:

  The character 'S' represents the player. The player can move up, down, left, right in grid if it is a floor (empty cell).
  The character '.' represents the floor which means a free cell to walk.
  The character '#' represents the wall which means an obstacle (impossible to walk there).
  There is only one box 'B' and one target cell 'T' in the grid.
  The box can be moved to an adjacent free cell by standing next to the box and then moving in the direction of the box. This is a push.
  The player cannot walk through the box.
  Return the minimum number of pushes to move the box to the target. If there is no way to reach the target, return -1.

 

  Example 1:


  Input: grid = [["#","#","#","#","#","#"],
  ["#","T","#","#","#","#"],
  ["#",".",".","B",".","#"],
  ["#",".","#","#",".","#"],
  ["#",".",".",".","S","#"],
  ["#","#","#","#","#","#"]]
  Output: 3
  Explanation: We return only the number of times the box is pushed.
  Example 2:

  Input: grid = [["#","#","#","#","#","#"],
  ["#","T","#","#","#","#"],
  ["#",".",".","B",".","#"],
  ["#","#","#","#",".","#"],
  ["#",".",".",".","S","#"],
  ["#","#","#","#","#","#"]]
  Output: -1
  Example 3:

  Input: grid = [["#","#","#","#","#","#"],
  ["#","T",".",".","#","#"],
  ["#",".","#","B",".","#"],
  ["#",".",".",".",".","#"],
  ["#",".",".",".","S","#"],
  ["#","#","#","#","#","#"]]
  Output: 5
  Explanation:  push the box down, left, left, up and up.
  Example 4:

  Input: grid = [["#","#","#","#","#","#","#"],
  ["#","S","#",".","B","T","#"],
  ["#","#","#","#","#","#","#"]]
  Output: -1
 

  Constraints:

  m == grid.length
  n == grid[i].length
  1 <= m, n <= 20
  grid contains only characters '.', '#', 'S', 'T', or 'B'.
  There is only one character 'S', 'B', and 'T' in the grid.
*/


// BFS to find shortest path
// need to keep track of current location of both the box and the player
// time complexity: O((M*N)^2)
// space complexity: O(M*N)
class Solution {
public:
    int minPushBox(vector<vector<char>>& grid) {
        _M = grid.size();
        _N = grid[0].size();
        pair<int,int> origBox;  // original box location
        pair<int,int> origPlayer;   // original player location
        for(int i=0; i<_M; ++i) {
            for(int j=0; j<_N; ++j) {
                if(grid[i][j] == 'B')
                    origBox = {i,j};
                if(grid[i][j] == 'S')
                    origPlayer = {i,j};
            }
        }
        
        // BFS to find shortest path
        queue<pair<pair<int,int>,pair<int,int>>> q;  // keep track of both box and player location
        vector<vector<int>> visited(_M*_N, vector<int>(_M*_N,0));
        q.push({origBox,origPlayer});
        visited[origBox.first*_N+origBox.second][origPlayer.first*_N+origPlayer.second];
        int level = 0;
        while(!q.empty()) {
            int sz = q.size();
            while(sz--) {
                auto node = q.front();
                q.pop();
                pair<int,int> &curBox = node.first;
                pair<int,int> &curPlayer = node.second;
                for(auto &d : _dir) {
                    pair<int,int> nextBox = {curBox.first+d.first, curBox.second+d.second};
                    if(nextBox.first<0 || nextBox.first>=_M || nextBox.second<0 || nextBox.second>=_N || grid[nextBox.first][nextBox.second]=='#')  // invalid box location
                        continue;
                    pair<int,int> nextPlayer = {curBox.first-d.first, curBox.second-d.second};  // player needs to be at this location to push the box to the given next box location
                    if(nextPlayer.first<0 || nextPlayer.first>=_M || nextPlayer.second<0 || nextPlayer.second>=_N || grid[nextPlayer.first][nextPlayer.second]=='#')  // invalid player location
                        continue;
                    if(visited[nextBox.first*_N+nextBox.second][nextPlayer.first*_N+nextPlayer.second] || !canMovePlayer(grid, curBox, curPlayer, nextPlayer))  // player can't reach the push location
                        continue;
                    if(grid[nextBox.first][nextBox.second] == 'T')  // box reach destination
                        return level+1;
                    q.push({nextBox,nextPlayer});
                    visited[nextBox.first*_N+nextBox.second][nextPlayer.first*_N+nextPlayer.second] = 1;
                }
            }
            ++level;
        }
                
        return -1;
    }

private:
    const vector<pair<int,int>> _dir = {{0,1},{0,-1},{1,0},{-1,0}};
    int _M;
    int _N;
    
    // whether the player can move from curPlayer position to nextPlayer position
    bool canMovePlayer(vector<vector<char>> &grid, const pair<int,int> &curBox, const pair<int,int> &curPlayer, const pair<int,int> &nextPlayer) {
        if(curPlayer == nextPlayer)
            return true;
                
        // still use BFS
        queue<pair<int,int>> q;
        vector<int> visited(_M*_N, 0);
        q.push(curPlayer);
        visited[curPlayer.first*_N+curPlayer.second] = 1;
        while(!q.empty()) {
            pair<int,int> cur = q.front();
            q.pop();
            for(auto &d : _dir) {
                pair<int,int> next = {cur.first+d.first, cur.second+d.second};
                if(next.first<0 || next.first>=_M || next.second<0 || next.second>=_N || grid[next.first][next.second]=='#' || next==curBox)  // note player cannot go over box
                    continue;
                if(visited[next.first*_N+next.second])
                    continue;
                if(next == nextPlayer)  // find path
                    return true;
                q.push(next);
                visited[next.first*_N+next.second] = 1;
            }
        }
        return false;
    }
};


// ref impl from HuaHua: BFS
struct Node {
    int bx;
    int by;
    int px;
    int py;
 
    int key() const { return ((by * 20 + bx) << 16) | (py * 20 + px); }
};
 
class Solution {
public:
    int minPushBox(vector<vector<char>>& grid) {
        const int n = grid.size();
        const int m = grid[0].size();
        Node start;
        Node end;
 
        for (int y = 0; y < n; ++y)
            for (int x = 0; x < m; ++x)
                if (grid[y][x] == 'B') {
                    start.bx = x;
                    start.by = y;
                } else if (grid[y][x] == 'S') {
                    start.px = x;
                    start.py = y;
                } else if (grid[y][x] == 'T') {
                    end.bx = x;
                    end.by = y;
                }

        // DFS to search if player can reach (tx,ty)
        auto hasPath = [&](const Node& cur, int tx, int ty) {
            vector<int> seen(m*n);
            function<bool(int, int)> dfs = [&](int x, int y) {
                if (x < 0 || x >= m || y < 0 || y >= n || grid[y][x] == '#')
                    return false;
                if (x == cur.bx && y == cur.by) return false;
                int key = y * m + x;
                if (seen[key]) return false;
                seen[key] = 1;
                if (x == tx && y == ty) return true;
                return dfs(x + 1, y) || dfs(x - 1, y) || dfs(x, y + 1) || dfs(x, y - 1);
            };
 
            return dfs(cur.px, cur.py);
        };

        // whether it's valid to move box to the given direction
        auto canPush = [&](const Node& cur, int dx, int dy, Node* nxt) {
            const int bx = cur.bx + dx;
            const int by = cur.by + dy;
            if (bx < 0 || bx >= m || by < 0 || by >= n || grid[by][bx] == '#')
                return false;
            if (!hasPath(cur, cur.bx - dx, cur.by - dy)) return false;
            nxt->bx = bx;
            nxt->by = by;
            nxt->px = cur.bx;
            nxt->py = cur.by;
            return true;
        };

        // BFS to find shortest path
        const vector<int> dirs{0, -1, 0, 1, 0};
        unordered_set<int> seen;
        queue<Node> q;
        q.push(start);
        seen.push(start.key());
        int steps = 0;
        while (q.size()) {
            int size = q.size();
            while (size--) {
                Node cur = q.front();
                q.pop();
                for (int i = 0; i < 4; ++i) {
                    Node nxt;
                    if (!canPush(cur, dirs[i], dirs[i + 1], &nxt) ||
                        seen.count(nxt.key()))
                        continue;
                    if (nxt.bx == end.bx && nxt.by == end.by) return steps + 1;
                    seen.insert(nxt.key());
                    q.push(nxt);
                }
            }
            ++steps;
        }
        return -1;
    }
};


// ref impl from HuaHua: A*
struct Node {
    int bx;
    int by;
    int px;
    int py;
    int h;  // heuristic function for A*
    int g;  // history function for A*
 
    int key() const {
        return ((by * m + bx) << 2) | ((bx - px) + 1) | ((by - py) + 1) >> 1;
    }
    int f() const { return g + h; }  // cost function for A*
    bool operator< (const Node& o) const {  // so node with lowest cost appear on top of the priority queue
        return f() > o.f();
    }
  
    static int m;
};
 
int Node::m;
 
class Solution {
public:
    int minPushBox(vector<vector<char>>& grid) {
        const vector<int> dirs{0, -1, 0, 1, 0};
        const int n = grid.size();
        const int m = Node::m = grid[0].size();
        Node start;
        Node end;
 
        for (int y = 0; y < n; ++y)
            for (int x = 0; x < m; ++x)
                if (grid[y][x] == 'B') {
                    start.bx = x;
                    start.by = y;
                } else if (grid[y][x] == 'S') {
                    start.px = x;
                    start.py = y;
                } else if (grid[y][x] == 'T') {
                    end.bx = x;
                    end.by = y;
                }
    
        auto isValid = [&](int x, int y) {
            return !(x < 0 || x >= m || y < 0 || y >= n || grid[y][x] == '#');
        };

        // BFS to search if player can reach (tx,ty)
        auto hasPath = [&](const Node& cur, int tx, int ty) {
            if (!isValid(tx, ty)) return false;
            vector<int> seen(m*n);
            queue<int> q;
            q.push(cur.py * m + cur.px);
            seen[cur.py * m + cur.px] = 1;
            while (q.size()) {
                int x = q.front() % m;
                int y = q.front() / m;
                q.pop();
                for (int i = 0; i < 4; ++i) {
                    int nx = x + dirs[i];
                    int ny = y + dirs[i + 1];
                    if (!isValid(nx, ny)) continue;
                    if (nx == cur.bx && ny == cur.by) continue;
                    if (nx == tx && ny == ty) return true;
                    if (seen[ny * m  + nx]++) continue;          
                    q.push(ny * m + nx);
                }
            }
            return false;
        };

        // whether it's valid to move box to the given direction
        auto canPush = [&](const Node& cur, int dx, int dy, Node* nxt) {
            nxt->bx = cur.bx + dx;
            nxt->by = cur.by + dy;
            nxt->px = cur.bx;
            nxt->py = cur.by;
            nxt->g = cur.g + 1;
            nxt->h = abs(nxt->bx - end.bx) + abs(nxt->by - end.by);
            if (!isValid(nxt->bx, nxt->by)) return false;
            return hasPath(cur, cur.bx - dx, cur.by - dy);
        };

        // A*
        vector<int> seen(m*n*4);
        priority_queue<Node> q;  // A* uses priority queue
        start.g = 0;
        start.h = abs(start.bx - end.bx) + abs(start.by - end.by);
        q.push(start);
        while (q.size()) {   
            Node cur = q.top();
            q.pop();
            for (int i = 0; i < 4; ++i) {
                Node nxt;
                if (!canPush(cur, dirs[i], dirs[i + 1], &nxt) || seen[nxt.key()]++) continue;        
                if (nxt.bx == end.bx && nxt.by == end.by) return nxt.g;        
                q.push(nxt);
            }
        }
        return -1;
    }
};
