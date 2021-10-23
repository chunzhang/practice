/*
  An n x n grid is composed of 1 x 1 squares where each 1 x 1 square consists of a '/', '\', or blank space ' '. These characters divide the square into contiguous regions.

  Given the grid grid represented as a string array, return the number of regions.

  Note that backslash characters are escaped, so a '\' is represented as '\\'.

 

  Example 1:


  Input: grid = [" /","/ "]
  Output: 2
  Example 2:


  Input: grid = [" /","  "]
  Output: 1
  Example 3:


  Input: grid = ["\\/","/\\"]
  Output: 4
  Explanation: (Recall that because \ characters are escaped, "\\/" refers to \/, and "/\\" refers to /\.)
  Example 4:


  Input: grid = ["/\\","\\/"]
  Output: 5
  Explanation: (Recall that because \ characters are escaped, "\\/" refers to \/, and "/\\" refers to /\.)
  Example 5:


  Input: grid = ["//","/ "]
  Output: 3
 

  Constraints:

  n == grid.length
  n == grid[i].length
  1 <= n <= 30
  grid[i][j] is either '/', '\', or ' '.
*/

// Merge sub-grid regions with union-find
// Divide each grid into four sub-grids: 0--up, 1--right, 2--bottom, 3--left
// Then, we can use disjoint-set to merge sub-grids
class Solution {
public:
    int regionsBySlashes(vector<string>& grid) {
        const int N = grid.size();
        UnionFind uf(N*N*4);  // each grid is divided into four sub-grids: 0--up, 1--right, 2--bottom, 3--left
        for(int i=0; i<N; ++i) {
            for(int j=0; j<N; ++j) {
                int curIdx = (i*N+j)*4;
                // intra-grid merge
                if(grid[i][j] == ' ') {
                    uf.merge(curIdx, curIdx+1);
                    uf.merge(curIdx, curIdx+2);
                    uf.merge(curIdx, curIdx+3);
                }
                else if(grid[i][j] == '/') {
                    uf.merge(curIdx, curIdx+3);
                    uf.merge(curIdx+1, curIdx+2);
                }
                else {
                    uf.merge(curIdx, curIdx+1);
                    uf.merge(curIdx+2, curIdx+3);
                }
                
                // inter-grid merge: only need to merge right and down
                if(j<N-1)
                    uf.merge(curIdx+1, curIdx+4+3);  // merge right
                if(i<N-1)
                    uf.merge(curIdx+2, curIdx+4*N+0);  // merge down
            }
        }
        
        return uf._nSets;
    }

private:
    struct UnionFind {
        vector<int> _parent;
        vector<int> _rank;
        int _nSets;   // number of disjoint sets
        
        UnionFind(const int sz) : _parent(sz), _rank(sz,1), _nSets(sz) {
            for(int n=0; n<sz; ++n)
                _parent[n] = n;
        }
        
        int getRoot(int n) {
            if(_parent[n] != n)
                _parent[n] = getRoot(_parent[n]);  // path compression
            return _parent[n];
        }
        
        void merge(int n1, int n2) {
            int r1 = getRoot(n1);
            int r2 = getRoot(n2);
            if(r1 == r2)
                return;
            
            if(_rank[r1] < _rank[r2])  // merge by rank
                _parent[r1] = r2;
            else if(_rank[r1] > _rank[r2])
                _parent[r2] = r1;
            else {
                _parent[r2] = r1;
                _rank[r1]++;
            }
            
            --_nSets;
        }
    };
};


// Use Euler's formula
// union-find: whenever two nodes belonging to the same component are merged, it creates a new region
class Solution {  
public:
    int regionsBySlashes(vector<string>& grid) {
        int n = grid.size();
        p_ = vector<int>((n + 1) * (n + 1));     
        // All vertices on the boundaries are merged into root(0).    
        for (int r = 0; r < n + 1; ++r)
            for (int c = 0; c < n + 1; ++c)
                p_[getIndex(n, r, c)] = (r == 0 || r == n || c == 0 || c == n) ? 0 : getIndex(n, r, c);
    
        int f = 1;    
        for (int r = 0; r < n; ++r)
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] == ' ') continue;
                // A new face will created if two vertices are already in the same group.        
                if (grid[r][c] == '/') {
                    f += merge(getIndex(n, r, c + 1),
                               getIndex(n, r + 1, c));
                } else {
                    f += merge(getIndex(n, r, c),
                               getIndex(n, r + 1, c + 1));
                }
            }    
        return f;
    }
private:
    vector<int> p_;  
  
    int getIndex(int n, int r, int c) { return r * (n + 1) + c; }  
      
    int find(int x) {
        if (p_[x] != x) p_[x] = find(p_[x]);
        return p_[x];
    }
  
    int merge(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return 1;
        p_[ry] = rx;
        return 0;
    }
};


// Pixelation: divide each grid into 3x3 sub-grids
// Then DFS search of connected components
class Solution {
public:
    int regionsBySlashes(vector<string>& grid) {
        const int n = grid.size();
        vector<vector<int>> g(n * 3, vector<int>(n * 3));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '/') {
                    g[i * 3 + 0][j * 3 + 2] = 1;
                    g[i * 3 + 1][j * 3 + 1] = 1;
                    g[i * 3 + 2][j * 3 + 0] = 1;
                } else if (grid[i][j] == '\\') {
                    g[i * 3 + 0][j * 3 + 0] = 1;
                    g[i * 3 + 1][j * 3 + 1] = 1;
                    g[i * 3 + 2][j * 3 + 2] = 1;
                }
            }
        int ans = 0;
        for (int i = 0; i < 3 * n; ++i)
            for (int j = 0; j < 3 * n; ++j) {
                if (g[i][j]) continue;
                visit(g, j, i, n * 3);
                ++ans;
            }
        return ans;
    }
private:
    void visit(vector<vector<int>>& g, int x, int y, int n) {
        if (x < 0 || x >= n || y < 0 || y >= n) return;
        if (g[y][x]) return;
        g[y][x] = 1;
        visit(g, x + 1, y, n);
        visit(g, x, y + 1, n);
        visit(g, x - 1, y, n);
        visit(g, x, y - 1, n);
    }
};
