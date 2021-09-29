/*
You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.

Return the size of the largest island in grid after applying this operation.

An island is a 4-directionally connected group of 1s.

 

Example 1:

Input: grid = [[1,0],[0,1]]
Output: 3
Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
Example 2:

Input: grid = [[1,1],[1,0]]
Output: 4
Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 4.
Example 3:

Input: grid = [[1,1],[1,1]]
Output: 4
Explanation: Can't change any 0 to 1, only one island with area = 4.
 

Constraints:

n == grid.length
n == grid[i].length
1 <= n <= 500
grid[i][j] is either 0 or 1.

*/


// Use DFS to collect island size
// time complexity: O(M*N)
// space complexity: O(M*N)
class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        _M = grid.size();
        _N = grid[0].size();
        _parent.resize(_M*_N, -1);  // -1 means it does not belong to any island
        _size[-1] = 0;
        
        // dfs
        for(int i=0; i<_M; ++i)
            for(int j=0; j<_N; ++j)
                if(grid[i][j] == 1)
                    dfs(grid, i, j, i*_N+j/*pid*/);
        
        vector<pair<int,int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};
        int ans = 0;
        for(auto &entry : _size)
            ans = max(ans, entry.second);  // grid could be all ones

        // try flip 0-->1 and calculate max island area
        for(int i=0; i<_M; ++i) {
            for(int j=0; j<_N; ++j) {
                if(_parent[i*_N+j] == -1) {  // originally zero
                    int size = 1;
                    vector<int> toMerge;  // to avoid duplicates, use vector is faster than unordered_map, since there're at most four directions
                    for(auto &d : dir) {
                        int ni = i + d.first;
                        int nj = j + d.second;
                        if(ni>=0 && ni<_M && nj>=0 && nj<_N) {
                            int pid = _parent[ni*_N+nj];
                            if(pid!=-1 && find(toMerge.begin(), toMerge.end(), pid)==toMerge.end())
                                toMerge.push_back(pid);
                        }
                    }
                    for(int pid : toMerge)
                        size += _size[pid];
                    ans = max(ans,size);
                }
            }
        }
        
        return ans;
    }
    
private:
    int _M;
    int _N;
    vector<int> _parent;  // parent set id, i.e., pid
    unordered_map<int,int> _size;  // pid-->island size mapping

    void dfs(vector<vector<int>> &grid, int i, int j, int pid) {
        _parent[i*_N+j] = pid;
        _size[pid]++;
        grid[i][j] = 0;
        if(i+1<_M && grid[i+1][j]==1)
            dfs(grid, i+1, j, pid);
        if(i-1>=0 && grid[i-1][j]==1)
            dfs(grid, i-1, j, pid);
        if(j+1<_N && grid[i][j+1]==1)
            dfs(grid, i, j+1, pid);
        if(j-1>=0 && grid[i][j-1]==1)
            dfs(grid, i, j-1, pid);
    }
};


// union-find
// time complexity: O(M*N)
// space complexity: O(M*N)
class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        _M = grid.size();
        _N = grid[0].size();
        vector<pair<int,int>> dir = {{0,1},{0,-1},{1,0},{-1,0}};
        
        // build unions
        build(grid);
        
        // merge unions
        for(int i=0; i<_M; ++i)
            for(int j=0; j<_N; ++j)
                if(grid[i][j] == 1)
                    for(auto &d : dir) {
                        int ni = i + d.first;
                        int nj = j + d.second;
                        if(ni>=0 && ni<_M && nj>=0 && nj<_N && grid[ni][nj]==1)
                            merge(i*_N+j, ni*_N+nj);
                    }
        
        // collect union size
        unordered_map<int,int> islands;
        for(int i=0; i<_M; ++i)
            for(int j=0; j<_N; ++j)
                if(grid[i][j] == 1)
                    ++islands[getParent(i*_N+j)];
        
        // base answer
        int ans = 0;
        for(auto &entry : islands) {
            ans = max(ans, entry.second);
        }
        
        // try flip 0-->1
        for(int i=0; i<_M; ++i) {
            for(int j=0; j<_N; ++j) {
                if(grid[i][j] == 0) {  // originally zero
                    int size = 1;
                    vector<int> toMerge;
                    for(auto &d : dir) {
                        int ni = i + d.first;
                        int nj = j + d.second;
                        if(ni>=0 && ni<_M && nj>=0 && nj<_N) {
                            int pid = getParent(ni*_N+nj);
                            if(pid!=-1 && find(toMerge.begin(), toMerge.end(), pid)==toMerge.end())
                                toMerge.push_back(pid);
                        }
                    }
                    for(int pid : toMerge)
                        size += islands[pid];
                    ans = max(ans,size);
                }
            }
        }
        
        return ans;
    }
    
private:
    int _M;
    int _N;
    vector<int> _parent;  // for union-find
    vector<int> _rank;
    
    void build(const vector<vector<int>> &grid) {
        _parent.resize(_M*_N, -1);
        _rank.resize(_M*_N, 0);
        for(int i=0; i<_M; ++i)
            for(int j=0; j<_N; ++j)
                if(grid[i][j] == 1) {
                    int idx = i*_N+j;
                    _parent[idx] = idx;
                    _rank[idx] = 1;
                }
    }
    
    int getParent(int idx) {
        if(_parent[idx]!=-1 && _parent[idx]!=idx)
            _parent[idx] = getParent(_parent[idx]);
        
        return _parent[idx];
    }
    
    void merge(int idx1, int idx2) {
        int p1 = getParent(idx1);
        int p2 = getParent(idx2);
        if(p1 == p2)
            return;
        
        if(_rank[p1] < _rank[p2])
            _parent[p1] = p2;
        else if(_rank[p1] > _rank[p2])
            _parent[p2] = p1;
        else {
            _parent[p2] = p1;
            _rank[p1]++;
        }
    }
};
