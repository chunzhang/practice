/*
  There is a directed graph of n nodes with each node labeled from 0 to n - 1. The graph is represented by a 0-indexed 2D integer array graph where graph[i] is an integer array of nodes adjacent to node i, meaning there is an edge from node i to each node in graph[i].

  A node is a terminal node if there are no outgoing edges. A node is a safe node if every possible path starting from that node leads to a terminal node.

  Return an array containing all the safe nodes of the graph. The answer should be sorted in ascending order.

 

  Example 1:

  Illustration of graph
  Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
  Output: [2,4,5,6]
  Explanation: The given graph is shown above.
  Nodes 5 and 6 are terminal nodes as there are no outgoing edges from either of them.
  Every path starting at nodes 2, 4, 5, and 6 all lead to either node 5 or 6.
  Example 2:

  Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
  Output: [4]
  Explanation:
  Only node 4 is a terminal node, and every path starting at node 4 leads to node 4.
 

  Constraints:

  n == graph.length
  1 <= n <= 10^4
  0 <= graph[i].length <= n
  0 <= graph[i][j] <= n - 1
  graph[i] is sorted in a strictly increasing order.
  The graph may contain self-loops.
  The number of edges in the graph will be in the range [1, 4 * 10^4].
*/


// A very clean solution based on topo-sorting
// Key idea: nodes involved in loop will stay in VISITING status
class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& g) {
        vector<STATUS> visited(g.size(), NONE);
        vector<int> ans;
        for(int cur=0; cur<g.size(); ++cur) {
            if(!dfs(g,visited,cur))
                ans.push_back(cur);
        }
        
        return ans;
    }
    
private:
    enum STATUS{NONE,VISITING,VISITED};
    
    // return true if DFS detects loop
    // Key idea: nodes involved in loop will stay in VISITING status
    bool dfs(const vector<vector<int>> &g, vector<STATUS> &visited, int cur) {
        if(visited[cur] != NONE)
            return visited[cur]==VISITING;
        
        visited[cur] = VISITING;
        for(int next : g[cur]) {
            if(visited[next] == VISITED)
                continue;
            if(visited[next]==VISITING || dfs(g,visited,next))
                return true;
        }
        
        visited[cur] = VISITED;
        return false;
    }
};


// topo-sorting with BFS on reversed graph
// terminal nodes become starting nodes in reversed graph
// if a node eventually only reaches terminal nodes, it will be found by BFS topo-sort from reversed graph
class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        vector<vector<int>> rgraph(graph.size());  // reversed graph
        vector<short> safe(graph.size(), 0);   // whether a node is safe
        vector<int> nInputs(graph.size(), 0);  // number of node inputs in reversed graph
        
        // build reversed graph
        for(int i=0; i<graph.size(); ++i) {
            for(int j : graph[i]) {
                rgraph[j].push_back(i);
                ++nInputs[i];
            }
        }
        
        // topo-sort with BFS
        queue<int> q;
        for(int cur=0; cur<rgraph.size(); ++cur) {
            if(nInputs[cur] == 0)
                q.push(cur);
        }
        while(!q.empty()) {
            int cur = q.front();
            q.pop();
            safe[cur] = 1;
            for(int next : rgraph[cur]) {
                if(--nInputs[next] == 0)
                    q.push(next);
            }
        }
        
        vector<int> ans;
        for(int i=0; i<safe.size(); ++i)
            if(safe[i])
                ans.push_back(i);
        return ans;
    }
};

// my initial impl for DFS topo-sort
class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& g) {
        vector<STATUS> visited(g.size(), NONE);
        vector<int> safe(g.size(), 1);
        for(int cur=0; cur<g.size(); ++cur) {
            if(visited[cur] == NONE)
                dfs(g,visited,safe,cur);
        }
        
        vector<int> ans;
        for(int node=0; node<safe.size(); ++node)
            if(safe[node])
                ans.push_back(node);
        
        return ans;
    }
    
private:
    enum STATUS{NONE,VISITING,VISITED};
    // return true if DFS detects loop
    bool dfs(const vector<vector<int>> &g, vector<STATUS> &visited, vector<int> &safe, int cur) {
        visited[cur] = VISITING;
        bool loop = false;
        for(int next : g[cur]) {
            if(visited[next] == VISITING) {
                loop = true;
            }
            else if(visited[next] == VISITED) {
                if(!safe[next])
                    loop = true;
            }
            else {
                loop = dfs(g,visited,safe,next);
            }
            
            if(loop)
                break;
        }
        
        visited[cur] = VISITED;
        if(loop)
            safe[cur] = 0;
        return loop;
    }
};


// ref impl from HuaHua
class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {    
        vector<State> states(graph.size(), UNKNOWN);
        vector<int> ans;
        for (int i = 0; i < graph.size(); ++i)      
            if (dfs(graph, i, states) == SAFE)
                ans.push_back(i);
        return ans;
    }
private:
    enum State {UNKNOWN, VISITING, SAFE, UNSAFE};
    State dfs(const vector<vector<int>>& g, int cur, vector<State>& states) {
        if (states[cur] == VISITING)
            return states[cur] = UNSAFE;
        if (states[cur] != UNKNOWN)
            return states[cur];
        states[cur] = VISITING;
        for (int next : g[cur])
            if (dfs(g, next, states) == UNSAFE) 
                return states[cur] = UNSAFE;
        return states[cur] = SAFE;
    }
};
