/*
  You are asked to cut off all the trees in a forest for a golf event. The forest is represented as an m x n matrix. In this matrix:

  0 means the cell cannot be walked through.
  1 represents an empty cell that can be walked through.
  A number greater than 1 represents a tree in a cell that can be walked through, and this number is the tree's height.
  In one step, you can walk in any of the four directions: north, east, south, and west. If you are standing in a cell with a tree, you can choose whether to cut it off.

  You must cut off the trees in order from shortest to tallest. When you cut off a tree, the value at its cell becomes 1 (an empty cell).

  Starting from the point (0, 0), return the minimum steps you need to walk to cut off all the trees. If you cannot cut off all the trees, return -1.

  You are guaranteed that no two trees have the same height, and there is at least one tree needs to be cut off.

 

  Example 1:


  Input: forest = [[1,2,3],[0,0,4],[7,6,5]]
  Output: 6
  Explanation: Following the path above allows you to cut off the trees from shortest to tallest in 6 steps.
  Example 2:


  Input: forest = [[1,2,3],[0,0,0],[7,6,5]]
  Output: -1
  Explanation: The trees in the bottom row cannot be accessed as the middle row is blocked.
  Example 3:

  Input: forest = [[2,3,4],[0,0,5],[8,7,6]]
  Output: 6
  Explanation: You can follow the same path as Example 1 to cut off all the trees.
  Note that you can cut off the first tree at (0, 0) before making any steps.
 

  Constraints:

  m == forest.length
  n == forest[i].length
  1 <= m, n <= 50
  0 <= forest[i][j] <= 10^9
*/

// BFS
// time complexity: O((M*N)^2)
// space complexity: O(M*N)
class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {
        _M = forest.size();
        _N = forest[0].size();
        
        // sort tress sorted by height
        map<int,pair<int,int>> trees;  
        for(int i=0; i<_M; ++i) {
            for(int j=0; j<_N; ++j) {
                if(forest[i][j] > 1) {
                    trees[forest[i][j]] = {i,j};
                }
            }
        }
        
        int ans = 0;
        pair<int,int> from = {0,0};
        for(auto it=trees.begin(); it!=trees.end(); ++it) {
            int steps = bfs(forest, from, it->second);
            if(steps == -1)
                return -1;
            ans += steps;
            from = it->second;
        }
        
        return ans;
    }
    
private:
    int _M;
    int _N;
    const int DIR[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
    
    int bfs(const vector<vector<int>> &forest, const pair<int,int> &from, const pair<int,int> &to) {
        if(from == to)
            return 0;
        
        queue<pair<int,int>> q;
        vector<vector<int>> visited(_M, vector<int>(_N,0));
        q.push(from);
        visited[from.first][from.second] = 1;
        int steps = 0;
        while(!q.empty()) {
            ++steps;
            int sz = q.size();
            while(sz--) {
                int i = q.front().first;
                int j = q.front().second;
                q.pop();
                for(int k=0; k<4; ++k) {
                    int ni = i + DIR[k][0];
                    int nj = j + DIR[k][1];
                    if(ni<0 || ni>=_M || nj<0 || nj>=_N || forest[ni][nj]==0 || visited[ni][nj])
                        continue;
                    if(ni==to.first && nj==to.second)
                        return steps;
                    q.push({ni,nj});
                    visited[ni][nj] = 1;
                }
            }
        }
        
        return -1;
    }
};


// ref impl from HuaHua
// same BFS, using tuple
class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {    
        m_ = forest.size();
        n_ = forest[0].size();
        
        // {height, x, y}
        vector<tuple<int,int,int>> trees;
        for (int y = 0; y < m_; ++y)
            for (int x = 0; x < n_; ++x)
                if (forest[y][x] > 1)
                    trees.emplace_back(forest[y][x], x, y);
        
        // sort trees by height
        sort(trees.begin(), trees.end());
        
        int sx = 0;
        int sy = 0;
        
        int total_steps = 0;
        
        // Move from current position to next tree to cut
        for (int i = 0; i < trees.size(); ++i) {
            int tx = get<1>(trees[i]);
            int ty = get<2>(trees[i]);
            
            int steps = BFS(forest, sx, sy, tx, ty);
            if (steps == INT_MAX) return -1;
            
            // Cut the tree, not necessary
            forest[ty][tx] = 1;
            
            total_steps += steps;
            
            sx = tx;
            sy = ty;
        }
        
        return total_steps;
        
    }    
private:
    // min steps to go from (sx,sy) to (tx,ty) based on current map
    // INT_MAX means not reachable
    int BFS(const vector<vector<int>>& forest, 
            int sx, int sy, 
            int tx, int ty) {
        
        static int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        auto visited = vector<vector<int>>(m_, vector<int>(n_, 0));
        
        // {x, y}
        queue<pair<int,int>> q;
        q.emplace(sx, sy);
        
        int steps = 0;
        while (!q.empty()) {
            int new_nodes = q.size();
            while (new_nodes--) {
                auto node = q.front();
                q.pop();
                const int cx = node.first;
                const int cy = node.second;
                
                // Found the shortest path
                if (cx == tx && cy == ty) 
                    return steps;
                
                for (int i = 0; i < 4; ++i) {
                    const int x = cx + dirs[i][0];
                    const int y = cy + dirs[i][1];
                    
                    // Out of bound or unwalkable
                    if (x < 0 || x == n_ 
                        || y < 0 || y == m_
                        || !forest[y][x]
                        || visited[y][x]) continue;
                    
                    // Mark x, y as visited
                    visited[y][x] = 1;                    
                    q.emplace(x, y);                
                }
            }
            ++steps;
        }
        
        // Impossible to reach
        return INT_MAX;
    }
    
    int m_;
    int n_;
};
