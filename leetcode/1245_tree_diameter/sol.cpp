/*
Facebook/Google

The diameter of a tree is the number of edges in the longest path in that tree.

There is an undirected tree of n nodes labeled from 0 to n - 1. You are given a 2D array edges where edges.length == n - 1 and edges[i] = [ai, bi] indicates that there is an undirected edge between nodes ai and bi in the tree.

Return the diameter of the tree.

Example 1:
Input: edges = [[0,1],[0,2]]
Output: 2
Explanation: The longest path of the tree is the path 1 - 0 - 2.

Example 2:

Input: edges = [[0,1],[1,2],[2,3],[1,4],[4,5]]
Output: 4
Explanation: The longest path of the tree is the path 3 - 2 - 1 - 4 - 5.
 

Constraints:

n == edges.length + 1
1 <= n <= 10^4
0 <= ai, bi < n
ai != bi
*/

// 1. in a complete tree, any node is root
// 2. need to pass parent node to avoid traversing back
class Solution {
public:
    int treeDiameter(vector<vector<int>>& edges) {
        // build tree graph
        vector<vector<int>> g(edges.size()+1);
        for(auto &e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        search(g, 0, -1);  // in a complete tree, any node is root!
        return m_ans;
    }

private:
    int search(const vector<vector<int>> &g, int node, int parent) {
        int max1 = 0;
        int max2 = 0;
        for(int c : g[node]) {
            if(c == parent)  // important to not go back since g is undirected
                continue;
            int d = search(g, c, node);
            if(d > max1)
                swap(max1,d);
            max2 = max(max2,d);
        }
        m_ans = max(m_ans, max1+max2);
        return max(max1,max2) + 1;
    }

private:
    int m_ans = INT_MIN;
};


// ref sol with two BFS (in Java)
// first BFS finds furthest node, which can be proven to be one end point of the longest path
// then do another BFS from that node to get the longest path
class Solution {

    public int treeDiameter(int[][] edges) {

        List<Set<Integer>> graph = new ArrayList<Set<Integer>>();
        for (int i = 0; i < edges.length + 1; ++i) {
            graph.add(new HashSet<Integer>());
        }

        for (int[] edge : edges) {
            Integer u = edge[0], v = edge[1];
            graph.get(u).add(v);
            graph.get(v).add(u);
        }

        // 1). find one of the farthest nodes
        // farthest_node, distance_1 = bfs(0)
        int[] nodeDistance = bfs(0, graph);
        // 2). find the other farthest node
        // and the distance between two farthest nodes
        // another_farthest_node, distance_2 = bfs(farthest_node)
        nodeDistance = bfs(nodeDistance[0], graph);

        return nodeDistance[1];
    }

    /**
     * return the farthest node from the 'start' node and the distance between them.
     */
    private int[] bfs(int start, List<Set<Integer>> graph) {
        boolean[] visited = new boolean[graph.size()];
        visited[start] = true;

        LinkedList<Integer> queue = new LinkedList<Integer>();
        queue.addLast(start);
        Integer lastNode = start, distance = -1;

        while (queue.size() > 0) {
            LinkedList<Integer> nextQueue = new LinkedList<Integer>();

            while (queue.size() > 0) {
                int nextNode = queue.removeFirst();
                for (Integer neighbor : graph.get(nextNode)) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        nextQueue.addLast(neighbor);
                        lastNode = neighbor;
                    }
                }
            }
            // increase the distance for each level of BFS traversal.
            distance += 1;
            queue = nextQueue;
        }

        return new int[] {lastNode, distance};
    }

}


// ref sol by identify centroid (in Java), refer to problem 0310 -- Minimum height tree
// if we could identify the centroid of a graph, then the distance from this centroid to any of its extreme peripheral nodes
// would be half of the diameter of the graph
class Solution {

    public int treeDiameter(int[][] edges) {

        // build the adjacency list representation of the graph.
        List<Set<Integer>> graph = new ArrayList<Set<Integer>>();
        for (int i = 0; i < edges.length + 1; ++i) {
            graph.add(new HashSet<Integer>());
        }
        for (int[] edge : edges) {
            Integer u = edge[0], v = edge[1];
            graph.get(u).add(v);
            graph.get(v).add(u);
        }

        // find the outer most nodes, i.e. leaf nodes
        LinkedList<Integer> leaves = new LinkedList<Integer>();
        for (int vertex = 0; vertex < graph.size(); ++vertex) {
            if (graph.get(vertex).size() == 1)
                leaves.add(vertex);
        }

        // "peel" the graph layer by layer,
        // until we have the centroids left.
        int layers = 0;
        int vertexLeft = edges.length + 1;
        while (vertexLeft > 2) {
            vertexLeft -= leaves.size();

            LinkedList<Integer> nextLeaves = new LinkedList<Integer>();

            for (int leaf : leaves) {
                // the only neighbor left on the leaf node.
                int neighbor = graph.get(leaf).iterator().next();
                graph.get(neighbor).remove(leaf);
                if (graph.get(neighbor).size() == 1)
                    nextLeaves.add(neighbor);
            }

            layers += 1;
            leaves = nextLeaves;
        }

        if (vertexLeft == 1)
            return layers * 2;
        else
            return layers * 2 + 1;
    }
}
