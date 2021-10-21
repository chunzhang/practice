/*
There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections forming a network where connections[i] = [ai, bi] represents a connection between servers ai and bi. Any server can reach other servers directly or indirectly through the network.

A critical connection is a connection that, if removed, will make some servers unable to reach some other server.

Return all critical connections in the network in any order.

 

Example 1:


Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
Output: [[1,3]]
Explanation: [[3,1]] is also accepted.
Example 2:

Input: n = 2, connections = [[0,1]]
Output: [[0,1]]
 

Constraints:

2 <= n <= 10^5
n - 1 <= connections.length <= 10^5
0 <= ai, bi <= n - 1
ai != bi
There are no repeated connections.
*/


// Tarjan's algorithm
// -- Any edge that is NOT part of the cycle is CRITICAL ==> remove it breaks the graph into two components
// -- For each node, we compute:
// ---- id: the discover time of the node during DFS
// ---- low: the lowest node id that can be reached during DFS
// -- If id[u]<low[v], then the edge (u,v) is CRITICAL ==> not part of cycle
// ---- Note the original graph is strongly connected
// -- Do not traverse back, i.e., u-->v, we should not traver v-->u again
// time and space complexity: O(V+E)
class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        // Use Tarjan's algorithm
        vector<vector<int>> g(n);
        vector<int> id(n, -1);
        vector<int> low(n, INT_MAX);
        for(auto &e : connections) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        
        vector<vector<int>> ans;
        tarjan(g, id, low, 0, -1/*dummy parent of starting node*/, ans);
        
        return ans;
    }
    
private:
    void tarjan(const vector<vector<int>> &g, vector<int> &id, vector<int> &low, int u/*current node*/, int p/*parent node*/, vector<vector<int>> &ans) {
        static int nextId = 0;
        if(id[u] == -1) {
            id[u] = nextId++;
            low[u] = id[u];
        }
        
        for(int v : g[u]) {
            if(v == p)  // do not trace back to where it comes from
                continue;
            
            if(id[v] == -1) {  // v is not discovered yet
                tarjan(g, id, low, v, u, ans);  // DFS
            }
            
            if(id[u] < low[v])  // this is the key: if v does not go back to a node <= id[u], then the edge (u,v) is not part of the loop
                ans.push_back({u,v});

            low[u] = min(low[u], low[v]);
            

        }
    }
};


// Tarjan: a different impl (from HuaHua)
// I think this version is better, as it simply returns the "lowest node id" during current traversal
class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        // Use Tarjan's algorithm
        vector<vector<int>> g(n);
        vector<int> id(n, -1);
        for(auto &e : connections) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        
        vector<vector<int>> ans;
        tarjan(g, id, 0, -1/*dummy parent of starting node*/, ans);
        
        return ans;
    }
    
private:
    // return the lowest node ID that can be reached during DFS
    int tarjan(const vector<vector<int>> &g, vector<int> &id, int u/*current node*/, int p/*parent node*/, vector<vector<int>> &ans) {
        static int nextId = 0;
        id[u] = nextId++;
        int min_u = id[u];
        
        for(int v : g[u]) {
            if(v == p)  // do not trace back to where it comes from
                continue;
            
            if(id[v] == -1) {  // first time discover
                int min_v = tarjan(g, id, v, u, ans);
                min_u = min(min_u, min_v);
                if(id[u] < min_v)
                    ans.push_back({u,v});
            }   
            else {
                min_u = min(min_u, id[v]);
            }
        }
        
        return min_u;
    }
};


// Just another impl
class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        // Use Tarjan's algorithm
        vector<vector<int>> g(n);
        vector<int> id(n, -1);
        for(auto &e : connections) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        
        vector<vector<int>> ans;
        tarjan(g, id, 0, -1/*dummy parent of starting node*/, ans);
        
        return ans;
    }
    
private:
    // return the lowest node ID that can be reached during DFS
    int tarjan(const vector<vector<int>> &g, vector<int> &id, int u/*current node*/, int p/*parent node*/, vector<vector<int>> &ans) {
        static int nextId = 0;
        if(id[u] != -1)
            return id[u];
        
        id[u] = nextId++;
        int min_u = id[u];
        
        for(int v : g[u]) {
            if(v == p)  // do not trace back to where it comes from
                continue;
            
            bool firstTime = id[v]==-1;
            int min_v = tarjan(g, id, v, u, ans);
            min_u = min(min_u, min_v);
            if(firstTime && id[u]<min_v)  // if the edge is not first time visited, we shall not add it
                ans.push_back({u,v});
        }
        
        return min_u;
    }
};
