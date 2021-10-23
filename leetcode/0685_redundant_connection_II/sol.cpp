/*
  In this problem, a rooted tree is a directed graph such that, there is exactly one node (the root) for which all other nodes are descendants of this node, plus every node has exactly one parent, except for the root node which has no parents.

  The given input is a directed graph that started as a rooted tree with n nodes (with distinct values from 1 to n), with one additional directed edge added. The added edge has two different vertices chosen from 1 to n, and was not an edge that already existed.

  The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [ui, vi] that represents a directed edge connecting nodes ui and vi, where ui is a parent of child vi.

  Return an edge that can be removed so that the resulting graph is a rooted tree of n nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array.

 

  Example 1:


  Input: edges = [[1,2],[1,3],[2,3]]
  Output: [2,3]
  Example 2:


  Input: edges = [[1,2],[2,3],[3,4],[4,1],[1,5]]
  Output: [4,1]
 

  Constraints:

  n == edges.length
  3 <= n <= 1000
  edges[i].length == 2
  1 <= ui, vi <= n
  ui != vi
*/


// union-find
// time complexity: O(N)
class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        // Case 1: if each node has only one parent ==> same as undirected graph
        // Case 2: if one node has two parents, i.e., both e1 and e2 come to that node
        // -- Case 2.1: if there is NO cycle, return e1 or e2 whichever comes later from the inputs
        // -- Case 2.2: if there is A cycle, then return e1 or e2 whichever constitutes the cycle
        const int N = edges.size();


        // First iteration over edges, check whether there’s any node with two parents
        // If so, mark them as e1 and e2, and remove e2 from the graph (for preparing union-find)
        vector<int> parent(N+1, 0);  // since node ID starts from 1, we use 0 to denote no-parent
        vector<int> e1;
        vector<int> e2;
        for(auto &e : edges) {
            int u = e[0];
            int v = e[1];
            if(parent[v] != 0) {  // found node with multiple parents ==> we know e1 and e2
                e1 = {parent[v], v};
                e2 = e;
                
                // it's important to remove e2
                e[0] = -1;
                e[1] = -1;
            }
            else
                parent[v] = u;
        }
        
        // Second iteration over edges, detect whether there’s an edge that need to merge same component
        // If so, either we hit case-1, or we hit case-2.2 for e1
        UnionFind uf(N+1);
        for(auto &e : edges) {
            if(e[0]==-1 || e[1]==-1)  // the edge is already deleted
                continue;

            // if e1 does not exist, we hit case-1 here;
            // otherwise, we hit case 2.2 here that e1 builds the cycle
            if(!uf.merge(e[0], e[1]))
                return e1.empty()?e:e1;
        }
        
        return e2;  // either case 2.1 that e2 comes later, or case 2.2 that e2 builds the cycle (which isn't detected by union-find as e2 is already deleted)
    }
    
private:
    class UnionFind {
    public:
        UnionFind(const int N) : _root(N), _rank(N,1) {
            iota(_root.begin(), _root.end(), 0);
        }
        
        int getRoot(int n) {
            if(_root[n] != n)
                _root[n] = getRoot(_root[n]);
            return _root[n];
        }
        
        bool merge(int n1, int n2) {
            int r1 = getRoot(n1);
            int r2 = getRoot(n2);
            if(r1 == r2)
                return false;
            
            if(_rank[r1] < _rank[r2])
                _root[r1] = r2;
            else if(_rank[r1] > _rank[r2])
                _root[r2] = r1;
            else {
                _root[r2] = r1;
                _rank[r1]++;
            }
            
            return true;
        }
        
    private:
        vector<int> _root;
        vector<int> _rank;
    };
};


// Not using union-find (ref impl from HuaHua)
// similar idea, but do DFS cycle detection instead of using union-find
class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        
        vector<int> parents(edges.size() + 1, 0);        
        
        vector<int> ans1;
        vector<int> ans2;        
        
        bool dup_parents = false;
        
        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            
            // A node has two parents
            if (parents[v] > 0) {
                ans1 = {parents[v], v};
                ans2 = edge;
                dup_parents = true;
                // Delete the later edge
                edge[0] = edge[1] = -1;
            } else {            
                parents[v] = u;
            }
        }
        
        // Reset parents
        parents = vector<int>(edges.size() + 1, 0);
        
        for(const auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            
            // Invalid edge (we deleted in step 1)
            if (u < 0 || v < 0) continue;
            
            parents[v] = u;
            
            if (cycle(v, parents))
                return dup_parents ? ans1 : edge;
        }
        
        return ans2;
    }    
private:
    bool cycle(int v, const vector<int>& parents) {
        int u = parents[v];        
        while (u) {
            if (u == v) return true;            
            u = parents[u];
        }
        return false;
    }
};
