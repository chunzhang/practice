/*
Consider a directed graph, with nodes labelled 0, 1, ..., n-1.  In this graph, each edge is either red or blue, and there could be self-edges or parallel edges.

Each [i, j] in red_edges denotes a red directed edge from node i to node j.  Similarly, each [i, j] in blue_edges denotes a blue directed edge from node i to node j.

Return an array answer of length n, where each answer[X] is the length of the shortest path from node 0 to node X such that the edge colors alternate along the path (or -1 if such a path doesn't exist).

 

Example 1:

Input: n = 3, red_edges = [[0,1],[1,2]], blue_edges = []
Output: [0,1,-1]
Example 2:

Input: n = 3, red_edges = [[0,1]], blue_edges = [[2,1]]
Output: [0,1,-1]
Example 3:

Input: n = 3, red_edges = [[1,0]], blue_edges = [[2,1]]
Output: [0,-1,-1]
Example 4:

Input: n = 3, red_edges = [[0,1]], blue_edges = [[1,2]]
Output: [0,1,2]
Example 5:

Input: n = 3, red_edges = [[0,1],[0,2]], blue_edges = [[1,0]]
Output: [0,1,1]
 

Constraints:

1 <= n <= 100
red_edges.length <= 400
blue_edges.length <= 400
red_edges[i].length == blue_edges[i].length == 2
0 <= red_edges[i][j], blue_edges[i][j] < n
*/


// BFS to find shortest path
// time and space complexity: O(V+E)
class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& red_edges, vector<vector<int>>& blue_edges) {
        // build graph
        vector<vector<int>> gr(n);
        vector<vector<int>> gb(n);
        for(auto &e : red_edges)
            gr[e[0]].push_back(e[1]);
        for(auto &e : blue_edges)
            gb[e[0]].push_back(e[1]);
        
        // BFS
        vector<int> ans(n, -1);
        vector<int> visited(2*n, 0);  // we need to differeniate by edge color arriving at the node
        queue<int> q;
        q.push((0<<1)|0);  // starting red, i.e., last bit
        visited[(0<<1)|0] = 1;
        q.push((0<<1)|1);  // starting blue, i.e., last bit
        visited[(0<<1)|1] = 1;
        int level = 0;
        while(!q.empty()) {
            int sz = q.size();
            while(sz--) {
                int cur = q.front();
                q.pop();
                int color = cur&0x1;  // arriving edge's color, i.e., denoted as last bit: red--0, blue--1
                int node = cur>>0x1;  // node id
                if(ans[node] == -1)
                    ans[node] = level;
                vector<vector<int>> &g = (color==0?gb:gr);
                for(int nei : g[node]) {
                    int next = (nei<<0x1) | (color==0?0x1:0x0);
                    if(!visited[next]) {
                        q.push(next);
                        visited[next] = 1;
                    }
                }
            }
            ++level;
        }
        
        return ans;
    }
};
