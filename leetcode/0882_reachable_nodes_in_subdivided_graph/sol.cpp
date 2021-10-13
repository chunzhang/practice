/*
You are given an undirected graph (the "original graph") with n nodes labeled from 0 to n - 1. You decide to subdivide each edge in the graph into a chain of nodes, with the number of new nodes varying between each edge.

The graph is given as a 2D array of edges where edges[i] = [ui, vi, cnti] indicates that there is an edge between nodes ui and vi in the original graph, and cnti is the total number of new nodes that you will subdivide the edge into. Note that cnti == 0 means you will not subdivide the edge.

To subdivide the edge [ui, vi], replace it with (cnti + 1) new edges and cnti new nodes. The new nodes are x1, x2, ..., xcnti, and the new edges are [ui, x1], [x1, x2], [x2, x3], ..., [xcnti-1, xcnti], [xcnti, vi].

In this new graph, you want to know how many nodes are reachable from the node 0, where a node is reachable if the distance is maxMoves or less.

Given the original graph and maxMoves, return the number of nodes that are reachable from node 0 in the new graph.

 

Example 1:


Input: edges = [[0,1,10],[0,2,1],[1,2,2]], maxMoves = 6, n = 3
Output: 13
Explanation: The edge subdivisions are shown in the image above.
The nodes that are reachable are highlighted in yellow.
Example 2:

Input: edges = [[0,1,4],[1,2,6],[0,2,8],[1,3,1]], maxMoves = 10, n = 4
Output: 23
Example 3:

Input: edges = [[1,2,4],[1,4,5],[1,3,1],[2,3,4],[3,4,5]], maxMoves = 17, n = 5
Output: 1
Explanation: Node 0 is disconnected from the rest of the graph, so only node 0 is reachable.
 

Constraints:

0 <= edges.length <= min(n * (n - 1) / 2, 104)
edges[i].length == 3
0 <= ui < vi < n
There are no multiple edges in the graph.
0 <= cnti <= 104
0 <= maxMoves <= 109
1 <= n <= 3000
*/

// First, we compute shortest path from 0 to all other nodes
// -- the node also add to distance of 1
// -- we do not need to search nodes beyond maxMoves distance
// Then, we know the extra "subdividing" nodes that can be covered from each original nodes
// -- extraCover[i] = maxMoves-dist[i]
// -- by iterating each edge, the additional covered nodes is min(weight(u,v), extraCover[u]+extraCover[v]) for edge (u,v)
// This uses Dijkstra algorithm to find shortest path
// time complexity: O(ElgE)
// space complexity: O(V+E)
class Solution {
public:
    typedef pair<int,int> iPair ;
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        // build graph
        vector<vector<iPair>> g(n);
        for(auto &e : edges) {
            g[e[0]].push_back({e[1],e[2]});
            g[e[1]].push_back({e[0],e[2]});
        }
        
        // Dijkstra to compute shortest path from 0 to each node
        vector<int> dist(n, INT_MAX);
        priority_queue<iPair,vector<iPair>,greater<iPair>> pq;  // (distance, node-id) pair
        pq.push({0,0});  // source node
        dist[0] = 0;
        while(!pq.empty()) {
            iPair cur = pq.top();
            pq.pop();
            if(cur.first > dist[cur.second])  // all edge weights are positive ==> distance monotonically increase ==> this won't lead to shorter distance
                continue;
            for(auto &nei : g[cur.second]) {
                int d = cur.first + nei.second + 1;  // the neighbor node itself is also counted as one distance
                if(d<=maxMoves && d<dist[nei.first]) {
                    dist[nei.first] = d;
                    pq.push({d, nei.first});
                }
            }
        }
                
        // build answer
        int ans = 0;
        vector<int> extraCover(n, 0);  // additional subdividing nodes that can be coverd from each original node
        for(int i=0; i<n; ++i) {
            if(dist[i] <= maxMoves) {
                ++ans;  // original node is covered
                extraCover[i] = maxMoves-dist[i];
            }
        }
        for(auto &e : edges) {
            ans += min(e[2], extraCover[e[0]]+extraCover[e[1]]);
        }
        
        return ans;
    }
};


// BFS (i.e., using queue) to compute shortest path
class Solution {
public:
    typedef pair<int,int> iPair ;
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        // build graph
        vector<vector<iPair>> g(n);
        for(auto &e : edges) {
            g[e[0]].push_back({e[1],e[2]});
            g[e[1]].push_back({e[0],e[2]});
        }
        
        // Dijkstra to compute shortest path from 0 to each node
        vector<int> dist(n, INT_MAX);
        queue<iPair> q;  // (distance, node-id) pair
        q.push({0,0});  // source node
        dist[0] = 0;
        while(!q.empty()) {
            iPair cur = q.front();
            q.pop();
            if(cur.first > dist[cur.second])  // all edge weights are positive ==> distance monotonically increase ==> this won't lead to shorter distance
                continue;
            for(auto &nei : g[cur.second]) {
                int d = cur.first + nei.second + 1;  // the neighbor node itself is also counted as one distance
                if(d<=maxMoves && d<dist[nei.first]) {
                    dist[nei.first] = d;
                    q.push({d, nei.first});
                }
            }
        }
                
        // build answer
        int ans = 0;
        vector<int> extraCover(n, 0);  // additional subdividing nodes that can be coverd from each original node
        for(int i=0; i<n; ++i) {
            if(dist[i] <= maxMoves) {
                ++ans;  // original node is covered
                extraCover[i] = maxMoves-dist[i];
            }
        }
        for(auto &e : edges) {
            ans += min(e[2], extraCover[e[0]]+extraCover[e[1]]);
        }
        
        return ans;
    }
};
