/*
Given a reference of a node in a connected undirected graph.

Return a deep copy (clone) of the graph.

Each node in the graph contains a value (int) and a list (List[Node]) of its neighbors.

class Node {
    public int val;
    public List<Node> neighbors;
}
 

Test case format:

For simplicity, each node's value is the same as the node's index (1-indexed). For example, the first node with val == 1, the second node with val == 2, and so on. The graph is represented in the test case using an adjacency list.

An adjacency list is a collection of unordered lists used to represent a finite graph. Each list describes the set of neighbors of a node in the graph.

The given node will always be the first node with val = 1. You must return the copy of the given node as a reference to the cloned graph.

 

Example 1:


Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
Output: [[2,4],[1,3],[2,4],[1,3]]
Explanation: There are 4 nodes in the graph.
1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
Example 2:


Input: adjList = [[]]
Output: [[]]
Explanation: Note that the input contains one empty list. The graph consists of only one node with val = 1 and it does not have any neighbors.
Example 3:

Input: adjList = []
Output: []
Explanation: This an empty graph, it does not have any nodes.
Example 4:


Input: adjList = [[2],[1]]
Output: [[2],[1]]
 

Constraints:

The number of nodes in the graph is in the range [0, 100].
1 <= Node.val <= 100
Node.val is unique for each node.
There are no repeated edges and no self-loops in the graph.
The Graph is connected and all nodes can be visited starting from the given node.
*/

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/


// DFS -- impl 1
// time complexity: O(V+E)
// space complexity: O(V)
class Solution {
public:
    Node* cloneGraph(Node* node) {
        if(!node)
            return nullptr;
        
        // DFS
        Node *cloneNode = new Node(node->val);
        _nodes[node] = cloneNode;
        for(Node *nei : node->neighbors) {
            auto it = _nodes.find(nei);
            Node *cloneNei = it!=_nodes.end()?it->second:cloneGraph(nei);
            cloneNode->neighbors.push_back(cloneNei);
        }
        
        return cloneNode;
    }
    
private:
    unordered_map<Node*, Node*> _nodes;  // mapping to cloned nodes; also used as visited marking
};


// DFS -- impl 2
class Solution {
public:
    Node* cloneGraph(Node* node) {
        if(!node)
            return nullptr;
        
        // DFS
        auto it = _nodes.find(node);
        if(it!=_nodes.end())
            return it->second;
        
        Node *cloneNode = new Node(node->val);
        _nodes[node] = cloneNode;
        for(Node *nei : node->neighbors) {
            Node *cloneNei = cloneGraph(nei);
            cloneNode->neighbors.push_back(cloneNei);
        }
        
        return cloneNode;
    }
    
private:
    unordered_map<Node*, Node*> _nodes;  // mapping to cloned nodes; also used as visited marking
};


// BFS -- impl 1
// time complexity: O(V+E)
// space complexity: O(V)
class Solution {
public:
    Node* cloneGraph(Node* node) {
        // BFS
        queue<Node*> q;
        if(node) {
            q.push(node);
            _nodes[node] = new Node(node->val);
        }
        while(q.size()) {
            Node *n = q.front();
            q.pop();
            Node *nc = _nodes[n];
            for(Node *nei : n->neighbors) {  // unvisited
                Node *neic = nullptr;
                auto it = _nodes.find(nei);
                if(it == _nodes.end()) {
                    q.push(nei);
                    neic = new Node(nei->val);
                    _nodes[nei] = neic;
                }
                else
                    neic = it->second;
                nc->neighbors.push_back(neic);
            }
        }
        
        return _nodes[node];
    }
    
private:
    unordered_map<Node*, Node*> _nodes;  // mapping to cloned nodes; also used as visited marking
};


// BFS -- impl 2
class Solution {
public:
    Node* cloneGraph(Node* node) {
        // BFS
        queue<Node*> q;
        if(node) {
            q.push(node);
            _nodes[node] = new Node(node->val);
        }
        while(q.size()) {
            Node *n = q.front();
            q.pop();
            for(Node *nei : n->neighbors) {
                if(_nodes.find(nei) == _nodes.end()) {  // unvisited
                    q.push(nei);
                    _nodes[nei] = new Node(nei->val);
                }
                _nodes[n]->neighbors.push_back(_nodes[nei]);
            }
        }
        
        return _nodes[node];
    }
    
private:
    unordered_map<Node*, Node*> _nodes;  // mapping to cloned nodes; also used as visited marking
};
