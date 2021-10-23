/*
  There are n computers numbered from 0 to n-1 connected by ethernet cables connections forming a network where connections[i] = [a, b] represents a connection between computers a and b. Any computer can reach any other computer directly or indirectly through the network.

  Given an initial computer network connections. You can extract certain cables between two directly connected computers, and place them between any pair of disconnected computers to make them directly connected. Return the minimum number of times you need to do this in order to make all the computers connected. If it's not possible, return -1. 

 

  Example 1:



  Input: n = 4, connections = [[0,1],[0,2],[1,2]]
  Output: 1
  Explanation: Remove cable between computer 1 and 2 and place between computers 1 and 3.
  Example 2:



  Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]
  Output: 2
  Example 3:

  Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]
  Output: -1
  Explanation: There are not enough cables.
  Example 4:

  Input: n = 5, connections = [[0,1],[0,2],[3,4],[2,3]]
  Output: 0
 

  Constraints:

  1 <= n <= 10^5
  1 <= connections.length <= min(n*(n-1)/2, 10^5)
  connections[i].length == 2
  0 <= connections[i][0], connections[i][1] < n
  connections[i][0] != connections[i][1]
  There are no repeated connections.
  No two computers are connected by more than one cable.
*/

// Union-Find
class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        UnionFind uf(n);
        int redundant = 0;  // redundant connections that can be used
        for(auto &e : connections) {
            if(!uf.merge(e[0], e[1]))
                ++redundant;
        }
        
        int needed = uf._nSets - 1;
        return needed<=redundant?needed:-1;
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
        
        // return false if they already belong to the same set
        bool merge(int n1, int n2) {
            int r1 = getRoot(n1);
            int r2 = getRoot(n2);
            if(r1 == r2)
                return false;
            
            if(_rank[r1] < _rank[r2])  // merge by rank
                _parent[r1] = r2;
            else if(_rank[r1] > _rank[r2])
                _parent[r2] = r1;
            else {
                _parent[r2] = r1;
                _rank[r1]++;
            }
            
            --_nSets;
            return true;
        }
    };

};


// ref impl from HuaHua: union-find
class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        if (connections.size() < n - 1)  // this is interesting
            return -1;
        vector<int> p(n);
        iota(begin(p), end(p), 0);  // useful API
    
        function<int(int)> find = [&](int x) {
            return p[x] == x ? x : p[x] = find(p[x]);
        };
    
        for (const auto& c : connections)
            p[find(c[0])] = find(c[1]);    
    
        unordered_set<int> s;
        for (int i = 0; i < n; ++i)
            s.insert(find(i));
    
        return s.size() - 1;        
    }
};

// ref impl from HuaHua: DFS
class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        if (connections.size() < n - 1) return -1;
        vector<vector<int>> g(n);
        for (const auto& c : connections) {
            g[c[0]].push_back(c[1]);
            g[c[1]].push_back(c[0]);
        }
        vector<int> seen(n);
        int count = 0;
        function<void(int)> dfs = [&](int cur) {
            for (int nxt : g[cur])
                if (!seen[nxt]++) dfs(nxt);      
        };
        for (int i = 0; i < n; ++i)
            if (!seen[i]++ && ++count)
                dfs(i);        
        return count - 1;
    }
};
