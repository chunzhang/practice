/*
You have an undirected, connected graph of n nodes labeled from 0 to n - 1. You are given an array graph where graph[i] is a list of all the nodes connected with node i by an edge.

Return the length of the shortest path that visits every node. You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.

 

Example 1:


Input: graph = [[1,2,3],[0],[0],[0]]
Output: 4
Explanation: One possible path is [1,0,2,0,3]
Example 2:


Input: graph = [[1],[0,2,4],[1,3,4],[2],[1,2]]
Output: 4
Explanation: One possible path is [0,1,4,2,3]
 

Constraints:

n == graph.length
1 <= n <= 12
0 <= graph[i].length < n
graph[i] does not contain i.
If graph[a] contains b, then graph[b] contains a.
The input graph is always connected.
*/


// BFS
// time and space complexity: O(N*2^N)
class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        // BFS on state s(n, visited), where n is the current node, and visited is binary repr of all visited nodes so far
        // -- can compress state into one binary integer representation
        // -- total number of states: n*2^n
        const int N = graph.size();
        const int allVisited = (0x1<<N) - 1;
        if(N == 1)
            return 0;
        
        // initialize BFS: every node can be a starting point
        // use 16-bit integer to encode state: highest 4-bit==>node ID, lowest bits: graph visited status
        queue<unsigned short> q;
        vector<unsigned short> visited((0x1<<(N+4)), 0);
        for(unsigned short n=0; n<N; ++n) {
            int state = (n<<N) | (0x1<<n);
            q.push(state);
            visited[state] = 1;
        }
        
        // BFS
        int steps = 0;
        while(!q.empty()) {
            int sz = q.size();
            while(sz--) {
                unsigned short cur = q.front() >> N;  // current node ID
                unsigned short v = q.front() & allVisited;  // current graph visited status
                q.pop();
                for(unsigned short next : graph[cur]) {   // next node ID
                    unsigned short nv = v | (0x1<<next);  // next graph visited status
                    if(nv == allVisited)
                        return steps+1;
                    int nextState = (next<<N) | nv;
                    if(visited[nextState])
                        continue;
                    q.push(nextState);
                    visited[nextState] = 1;
                }
            }
            
            ++steps;
        }
        
        return -1;
    }
};
