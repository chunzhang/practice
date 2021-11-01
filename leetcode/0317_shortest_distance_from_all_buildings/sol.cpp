/*
You are given an m x n grid grid of values 0, 1, or 2, where:

each 0 marks an empty land that you can pass by freely,
each 1 marks a building that you cannot pass through, and
each 2 marks an obstacle that you cannot pass through.
You want to build a house on an empty land that reaches all buildings in the shortest total travel distance. You can only move up, down, left, and right.

Return the shortest travel distance for such a house. If it is not possible to build such a house according to the above rules, return -1.

The total travel distance is the sum of the distances between the houses of the friends and the meeting point.

The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.

 

Example 1:


Input: grid = [[1,0,2,0,1],[0,0,0,0,0],[0,0,1,0,0]]
Output: 7
Explanation: Given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2).
The point (1,2) is an ideal empty land to build a house, as the total travel distance of 3+3+1=7 is minimal.
So return 7.
Example 2:

Input: grid = [[1,0]]
Output: 1
Example 3:

Input: grid = [[1]]
Output: -1
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 50
grid[i][j] is either 0, 1, or 2.
There will be at least one building in the grid.
*/


// BFS from 1-grid
// -- most optimal, reuse grid as visited flag
// -- each iteration from a building, change reachable land from 0 --> -1 --> -2 -->...
// time complexity: O((M*N)^2)
// space complexity: O(M*N)
class Solution {
public:
    int shortestDistance(vector<vector<int>>& grid) {
        _M = grid.size();
        _N = grid[0].size();
        
        vector<vector<int>> dist(_M, vector<int>(_N,0));    // total dist to all reachable buildings from an empty land
        int nBuildings = 0;
        for(int i=0; i<_M; ++i) {
            for(int j=0; j<_N; ++j) {
                if(grid[i][j] == 1) {
                    bfs(grid, -nBuildings, i, j, dist);
                    ++nBuildings;
                }
            }
        }
        
        // build answer
        int ans = INT_MAX;
        for(int i=0; i<_M; ++i)
            for(int j=0; j<_N; ++j)
                if(grid[i][j]==-nBuildings)
                    ans = min(ans, dist[i][j]);

        return ans==INT_MAX?-1:ans;
    }
    
private:
    int _M;
    int _N;
    const int DIR[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
    
    // BFS search from a building to all its reachable empty lands
    // on every call, we change the reachable cell value from 0 to -1 to -2 to ... ==> also used as visited flag
    void bfs(vector<vector<int>> &grid, const int flag/*target cell value that needs to */, int i, int j, vector<vector<int>> &dist/*total dist of an empty land*/) {
        int newFlag = flag - 1;
        queue<pair<int,int>> q;
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
                    if(ni<0 || ni>=_M || nj<0 || nj>=_N || grid[ni][nj]!=flag || grid[ni][nj]==newFlag)
                        continue;
                    
                    // reach an newly found empty land
                    dist[ni][nj] += steps;
                    q.push({ni,nj});
                    grid[ni][nj] = newFlag;
                }
            }
        }
    }
};

// BFS from 1-grid
// -- for each 0-grid, keep track of total distance and number of reachable buildings
// time complexity: O((M*N)^2)
// space complexity: O(M*N)
class Solution {
public:
    int shortestDistance(vector<vector<int>>& grid) {
        _M = grid.size();
        _N = grid[0].size();
        
        vector<vector<int>> dist(_M, vector<int>(_N,0));    // total dist to all reachable buildings from an empty land
        vector<vector<int>> total(_M, vector<int>(_N, 0));  // total number of reachable buildings from an empty land
        int nBuildings = 0;
        for(int i=0; i<_M; ++i) {
            for(int j=0; j<_N; ++j) {
                if(grid[i][j] == 1) {
                    ++nBuildings;
                    bfs(grid, nBuildings, i, j, dist, total);
                }
            }
        }
        
        // build answer
        int ans = INT_MAX;
        for(int i=0; i<_M; ++i)
            for(int j=0; j<_N; ++j)
                if(grid[i][j]==0 && total[i][j]==nBuildings)
                    ans = min(ans, dist[i][j]);

        return ans==INT_MAX?-1:ans;
    }
    
private:
    int _M;
    int _N;
    const int DIR[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
    
    // BFS search from a building to all its reachable empty lands
    void bfs(const vector<vector<int>> &grid, const int nBuildings, int i, int j, vector<vector<int>> &dist/*total dist of an empty land*/, vector<vector<int>> &total/*total reachable buildings of an empty land*/) {
        vector<vector<int>> visited(_M, vector<int>(_N,0));
        queue<pair<int,int>> q;
        q.push({i,j});
        visited[i][j] = 1;
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
                    if(ni<0 || ni>=_M || nj<0 || nj>=_N || grid[ni][nj]>0 || visited[ni][nj])
                        continue;
                    if(total[ni][nj] != nBuildings-1)  // the land is not reachable to all buildings so far, so any path expanded from it cannot reach all buildings
                        continue;
                    
                    // reach an newly found empty land
                    dist[ni][nj] += steps;
                    ++total[ni][nj];
                    q.push({ni,nj});
                    visited[ni][nj] = 1;
                }
            }
        }
    }
};


// BFS start from 0-grid -- almost TLE since there're many more 0s than 1s
// time complexity: O((M*N)^2)
// space complexity: O(M*N)
class Solution {
public:
    int shortestDistance(vector<vector<int>>& grid) {
        _M = grid.size();
        _N = grid[0].size();
        
        int total = 0;
        for(int i=0; i<_M; ++i)
            for(int j=0; j<_N; ++j)
                if(grid[i][j] == 1)
                    ++total;

        // BFS from all 0-grid
        int ans = INT_MAX;
        for(int i=0; i<_M; ++i) {
            for(int j=0; j<_N; ++j) {
                if(grid[i][j] == 0) {
                    int dist = bfs(grid, i, j, total);
                    if(dist != -1)
                        ans = min(ans, dist);
                }
            }
        }

        return ans==INT_MAX?-1:ans;
    }
    
private:
    int _M;
    int _N;
    const int DIR[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
    
    int bfs(vector<vector<int>> &grid, int i, int j, int total/*total number of houses to reach*/) {
        vector<vector<int>> visited(_M, vector<int>(_N,0));
        queue<pair<int,int>> q;
        q.push({i,j});
        visited[i][j] = 1;
        int dist = 0;
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
                    if(ni<0 || ni>=_M || nj<0 || nj>=_N || grid[ni][nj]==2 || visited[ni][nj])
                        continue;

                    visited[ni][nj] = 1;
                    if(grid[ni][nj] == 1) {
                        dist += steps;
                        if(--total == 0)
                            return dist;
                    }
                    else {
                        q.push({ni,nj});
                    }
                }
            }
        }
        
        // IMPORTANT: not all buildings are reachable, so we mark visited 0-grids as 2 so they won't be traversed again
        // without doing this, it will TLE
        for(int i=0; i<_M; ++i)
            for(int j=0; j<_N; ++j)
                if(grid[i][j]==0 && visited[i][j])
                    grid[i][j] = 2;
        return -1;
    }
};
