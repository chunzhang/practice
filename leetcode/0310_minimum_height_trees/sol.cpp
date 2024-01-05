/*
Facebook/Citadel/Amazon

A tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.

Given a tree of n nodes labelled from 0 to n - 1, and an array of n - 1 edges where edges[i] = [ai, bi] indicates that there is an undirected edge between the two nodes ai and bi in the tree, you can choose any node of the tree as the root. When you select a node x as the root, the result tree has height h. Among all possible rooted trees, those with minimum height (i.e. min(h))  are called minimum height trees (MHTs).

Return a list of all MHTs' root labels. You can return the answer in any order.

The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.

 

Example 1:

Input: n = 4, edges = [[1,0],[1,2],[1,3]]
Output: [1]
Explanation: As shown, the height of the tree is 1 when the root is the node with label 1 which is the only MHT.

Example 2:

Input: n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
Output: [3,4]
 

Constraints:

1 <= n <= 2 * 10^4
edges.length == n - 1
0 <= ai, bi < n
ai != bi
All the pairs (ai, bi) are distinct.
The given input is guaranteed to be a tree and there will be no repeated edges.
*/


// Two pass BFS
// 1. first BFS from any root node ==> nodes in last level are end points of longest path in the tree;
//    one can actually prove there's only one unique longest path in any tree
// 2. so, we select any one node in the last level, then do a second BFS from it;
//    this second BFS gives the longest path, so the middle layer node is the root of the min height tree;
//    note there can be one or two such root nodes, depends on whether the longest path is odd or even
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        // build graph
        vector<vector<int>> g(n);
        for(auto &e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        // BFS from any root
        vector<vector<int>> levelNodes;
        queue<pair<int,int>> q;  // {current node, parent node} pair
        q.emplace(0,-1);  // starting from arbitary root, say 0
        bfs(g,q,levelNodes);

        // the last level contains node in longest path
        // so, starting from it with another BFS to find middle nodes
        q.emplace(levelNodes.back()[0],-1);
        levelNodes.clear();
        bfs(g,q,levelNodes);

        vector<int> ans;
        int levels = levelNodes.size();
        ans.push_back(levelNodes[levels/2][0]);
        if(levels%2 == 0)
            ans.push_back(levelNodes[levels/2-1][0]);

        return ans;
    }

private:
    void bfs(const vector<vector<int>> &g, queue<pair<int,int>> &q, vector<vector<int>> &levelNodes) {
        while(!q.empty()) {
            levelNodes.push_back(vector<int>());
            int sz = q.size();
            while(sz--) {
                auto node = q.front();
                q.pop();
                levelNodes.back().push_back(node.first);
                for(int next : g[node.first]) {
                    if(next != node.second)  // avoid going back to parent since g is undirected
                        q.emplace(next,node.first);
                }
            }
        }
    }
};


// better solution
// since we already know there're at most 2 possible roots (i.e., centroid of the tree), we can design an algorithm
// to do topo-sort like node trimming. Specifically, trim leaf nodes until reaching centroid. Note a node becomes a leaf
// when it has only degree=1
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if(n == 1)
            return {0};

        // since we know there're at most two valid roots (they're actually centroid of the tree graph),
        // we want to design a topo-sort like algorithm to trim leaves layer by layer until there're <=2
        // nodes left

        // build graph
        vector<vector<int>> g(n);
        vector<int> degree(n,0);
        for(auto &e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
            degree[e[0]]++;
            degree[e[1]]++;
        }

        // BFS based topo sort
        vector<int> curLeaves;
        vector<int> nextLeaves;
        for(int node=0; node<n; ++node)
            if(degree[node] == 1)
                curLeaves.push_back(node);
        while(n > 2) {  // remaining nodes
            for(int node : curLeaves) {  // must trim entire layer as a whole!
                --degree[node];
                for(int next : g[node])
                    if(--degree[next] == 1)  // can go negative, but it doesn't matter
                        nextLeaves.push_back(next);
            }
            n -= curLeaves.size();
            curLeaves.swap(nextLeaves);
            nextLeaves.clear();
        }

        // construct answer
        return curLeaves;
    }
};
