/*
Salesforce/Facebook/Snowflake

You have a graph of n nodes labeled from 0 to n - 1. You are given an integer n and a list of edges where edges[i] = [ai, bi] indicates that there is an undirected edge between nodes ai and bi in the graph.

Return true if the edges of the given graph make up a valid tree, and false otherwise.

Example 1:

Input: n = 5, edges = [[0,1],[0,2],[0,3],[1,4]]
Output: true

Example 2:

Input: n = 5, edges = [[0,1],[1,2],[2,3],[1,3],[1,4]]
Output: false

Constraints:

1 <= n <= 2000
0 <= edges.length <= 5000
edges[i].length == 2
0 <= ai, bi < n
ai != bi
There are no self-loops or repeated edges.
*/

// sol1: BFS
// time: O(N)
class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if(edges.size() != n-1)
            return false;

        // build undirected graph
        vector<vector<int>> g(n);
        for(auto &e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        // BFS to detect loop
        vector<int> visited(n,0);
        queue<pair<int,int>> q;  // {node,parent} pair
        q.push({0,-1});  // select node-0 as the root (if this is a tree, any node can be the tree root)
        visited[0] = 1;
        int nVisited = 1;
        while(!q.empty()) {
            auto cur = q.front();
            q.pop();
            for(int next : g[cur.first]) {
                if(next == cur.second)  // do not go back as this is undirected graph
                    continue;
                if(visited[next])  // loop detected
                    return false;
                visited[next] = 1;
                ++nVisited;
                q.push({next,cur.first});
            }
        }

        return nVisited==n;
    }
};


// sol2: union-find
// time: O(N)
class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if(edges.size() != n-1)
            return false;

        // based on union-find: for a valid tree, each edge would
        // uniquely connect two sub-trees
        vector<int> parent(n);  // root of the union-find set
        for(int i=0; i<parent.size(); ++i)
            parent[i] = i;
        for(auto &e : edges) {
            int r1 = find(parent, e[0]);
            int r2 = find(parent, e[1]);
            if(r1 == r2)  // found loop: nodes belonging to the same tree are merged again
                return false;
            parent[r1] = r2;  // union (without ranking)
        }

        return true;
    }

private:
    int find(vector<int> &parent, int node) {  // same as get tree root
        if(parent[node] != node)
            parent[node] = find(parent, parent[node]);  // path compression
        return parent[node];
    }
};
