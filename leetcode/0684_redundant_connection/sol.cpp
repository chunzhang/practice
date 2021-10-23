/*
In this problem, a tree is an undirected graph that is connected and has no cycles.

You are given a graph that started as a tree with n nodes labeled from 1 to n, with one additional edge added. The added edge has two different vertices chosen from 1 to n, and was not an edge that already existed. The graph is represented as an array edges of length n where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the graph.

Return an edge that can be removed so that the resulting graph is a tree of n nodes. If there are multiple answers, return the answer that occurs last in the input.

 

Example 1:


Input: edges = [[1,2],[1,3],[2,3]]
Output: [2,3]
Example 2:


Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
Output: [1,4]
 

Constraints:

n == edges.length
3 <= n <= 1000
edges[i].length == 2
1 <= ai < bi <= edges.length
ai != bi
There are no repeated edges.
The given graph is connected.
*/

// Union-find
class DisjointSet {
public:
    DisjointSet(int n) {
        for(int i=0; i<=n; ++i) {
            _parent.push_back(i);
            _rank.push_back(0);
        }
    }
    
    int find(int x) {
        if(_parent[x] != x)
            _parent[x] = find(_parent[x]);  // path compression
        return _parent[x];
    }
    
    bool merge(int x, int y) {
        int px = find(x);
        int py = find(y);
        if(px == py)  // already belong to same set, no union actually happens
            return false;
        
        // union by rank
        if(_rank[px] < _rank[py])
            _parent[px] = py;
        else if(_rank[px] > _rank[py])
            _parent[py] = px;
        else {
            _parent[px] = py;
            _rank[py]++;
        }
        return true;
    }
    
private:
    vector<int> _parent;  // node start from 1, and _parent[x]==x means x is the root
    vector<int> _rank;
    
};

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        DisjointSet ds(edges.size());
        for(auto e : edges) {
            if(!ds.merge(e[0], e[1]))
                return e;
        }
        
        return vector<int>();   // should not reach here
    }
};
