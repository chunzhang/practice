/*
Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

 

Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1
Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] is '0' or '1'.
*/

// BFS
// time complexity: O(M*N)
// space complexity: O(min(M,N)) -- max size of frontier
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int ans = 0;
        for(int i=0; i<grid.size(); ++i) {
            for(int j=0; j<grid[0].size(); ++j)
                if(grid[i][j] == '1') {
                    ++ans;
                    bfs(grid, i, j);
                }
        }
        
        return ans;
    }
    
private:
    vector<vector<int>> _dir = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    void bfs(vector<vector<char>> &grid, int i, int j) {
        const int M = grid.size();
        const int N = grid[0].size();
        queue<pair<int,int>> q;
        q.push({i,j});
        grid[i][j] = '0';
        while(q.size()) {
            auto node = q.front();
            q.pop();
            for(auto &dir : _dir) {
                int ni = node.first + dir[0];
                int nj = node.second + dir[1];
                if(ni>=0 && ni<M && nj>=0 && nj<N && grid[ni][nj]=='1') {
                    q.push({ni,nj});
                    grid[ni][nj] = '0';  // must mark visisted when node is added to the queue
                }
            }
        }
    }
};


// DFS
// time complexity: O(M*N)
// space complexity: O(M*N)  -- max recursion depth
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        _M = grid.size();
        _N = grid[0].size();
        int ans = 0;
        for(int i=0; i<grid.size(); ++i) {
            for(int j=0; j<grid[0].size(); ++j)
                if(grid[i][j] == '1') {
                    ++ans;
                    dfs(grid, i, j);
                }
        }
        
        return ans;
    }
    
private:
    vector<vector<int>> _dir = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    int _M;
    int _N;
    void dfs(vector<vector<char>> &grid, int i, int j) {
        if(i<0 || i>=_M || j<0 || j>=_N || grid[i][j] == '0')
            return;
        
        grid[i][j] = '0';
        for(auto &d : _dir) {
            dfs(grid, i+d[0], j+d[1]);
        }
    }
};


// Union find
// -- O(1) amortized time using path compression + ranking
// -- Ref: https://www.geeksforgeeks.org/union-find-algorithm-set-2-union-by-rank/
// time complexity: O(M*N)
// space complexity: O(M*N)
class UnionFind
{
public:
    UnionFind(const vector<vector<char>> &grid) {
        int m = grid.size();
        int n = m ? grid[0].size() : 0;
        _parent.resize(m*n);
        _rank.resize(m*n);
        _numSets = 0;
        for(int i=0; i<m; ++i) {
            for(int j=0; j<n; ++j) {
                int idx = i*n + j;  // 2D --> 1D index
                if(grid[i][j] == '1') {
                    _parent[idx] = idx;
                    _rank[idx] = 0;
                    ++_numSets;
                }
                else {
                    _parent[idx] = -1;
                    _rank[idx] = -1;
                }
            }
        }
    }

    int findRoot(int idx) {
        if(_parent[idx] == -1)
            return -1;
        if(_parent[idx] != idx)  // not root of the set, keep searching upward
            _parent[idx] = findRoot(_parent[idx]);  // path compression: shorten path to root when called
        return _parent[idx];
    }

    // Rank based set union
    void merge(int idx1, int idx2) {
        int root1 = findRoot(idx1);
        int root2 = findRoot(idx2);
        if(root1 == root2)  // already belongs to the same set, no-op
            return;
        if(_rank[root1] > _rank[root2]) {
            _parent[root2] = root1;
        }
        else if(_rank[root1] < _rank[root2]) {
            _parent[root1] = root2;
        }
        else {
            _parent[root2] = root1;
            ++_rank[root1];
        }
        --_numSets;
    }

    int numSets() const {
        return _numSets;
    }
  
private:
    vector<int> _parent;  // grid index --> root, parent[i]==-1 if the grid is '0', parent[i]==i if the grid is root
    vector<int> _rank;    // grid index --> rank
    int _numSets;          // number of disjoint sets
};


class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        UnionFind uf(grid);
        int m = grid.size();
        int n = m ? grid[0].size() : 0;
        for(int i=0; i<m; ++i) {
            for(int j=0; j<n; ++j) {
                if(grid[i][j] == '1') {
                    int idx1 = i*n + j;
                    // NOTE: only need to merge to the right and to the down
                    if(j+1<n && grid[i][j+1]=='1')
                        uf.merge(idx1, i*n+j+1);
                    if(i+1<m && grid[i+1][j]=='1')
                        uf.merge(idx1, (i+1)*n+j);
                }
            }
        }

        return uf.numSets();
    }
};

int main()
{
    //vector<vector<char>> grid = {{'1','1','1','1','0'}, {'1','1','0','1','0'}, {'1','1','0','0','0'}, {'0','0','0','0','0'}};
    vector<vector<char>> grid = {{'1','1','0','0','0'}, {'1','1','0','0','0'}, {'0','0','1','0','0'}, {'0','0','0','1','1'}};
    Solution sol;
    int num = sol.numIslands(grid);
    cout << "num: " << num << endl;

    return 0;
}
