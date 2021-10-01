/*
There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
Return true if you can finish all courses. Otherwise, return false.

 

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So it is possible.
Example 2:

Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.
 

Constraints:

1 <= numCourses <= 105
0 <= prerequisites.length <= 5000
prerequisites[i].length == 2
0 <= ai, bi < numCourses
All the pairs prerequisites[i] are unique.
*/


// topo-sorting with DFS
// time complexity: O(V+E)
// space complexity: O(V)
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> g(numCourses);
        for(auto &req : prerequisites)
            g[req[1]].push_back(req[0]);
        
        // topo-sort with DFS
        vector<STATUS> visited(numCourses, NONE);
        for(int cur=0; cur<numCourses; ++cur)
            if(dfs(g, visited, cur))
                return false;
        
        return true;
    }
    
private:
    enum STATUS{NONE, VISITING, VISITED};  // traversal status
    // return true if DFS detects loop
    bool dfs(const vector<vector<int>> &g, vector<STATUS> &visited, int cur) {
        if(visited[cur] == VISITING)
            return true;
        
        if(visited[cur] == VISITED)
            return false;
        
        visited[cur] = VISITING;
        for(int next : g[cur]) {
            if(dfs(g, visited, next))
                return true;
        }
        visited[cur] = VISITED;
        return false;
    }
};


// topo-sorting impl2
// faster by pre-checking next node status ==> one less level of recursion
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> g(numCourses);
        for(auto &req : prerequisites)
            g[req[1]].push_back(req[0]);
        
        // topo-sort with DFS
        vector<STATUS> visited(numCourses, NONE);
        for(int cur=0; cur<numCourses; ++cur) {
            if(visited[cur] != NONE)
                continue;
            if(dfs(g, visited, cur))
                return false;
        }
        
        return true;
    }
    
private:
    enum STATUS{NONE, VISITING, VISITED};  // traversal status
    // return true if DFS detects loop
    bool dfs(const vector<vector<int>> &g, vector<STATUS> &visited, int cur) {
        visited[cur] = VISITING;
        for(int next : g[cur]) {
            if(visited[next] == VISITING)
                return true;
            else if(visited[next] == VISITED)
                continue;
            
            if(dfs(g, visited, next))
                return true;
        }
        visited[cur] = VISITED;
        return false;
    }
};


// topo-sorting with BFS
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> g(numCourses);
        vector<int> nInputs(numCourses, 0);  // number of inputs of each graph node
        for(auto &req : prerequisites) {
            g[req[1]].push_back(req[0]);
            ++nInputs[req[0]];
        }
        
        // BFS
        queue<int> q;
        int count = 0;  // number node with valid topo-order
        for(int cur=0; cur<numCourses; ++cur) {
            if(nInputs[cur] == 0)
                q.push(cur);
        }
        while(!q.empty()) {
            int cur = q.front();
            q.pop();
            ++count;
            for(int next : g[cur]) {
                if(--nInputs[next] == 0)
                    q.push(next);
            }
        }
                
        return count==numCourses;
    }
    
};


// brute-force: for every node, try a fresh DFS to detect loop
// time complexity: O(V^2)
// space complexity: O(V)
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> g(numCourses);
        for(auto &req : prerequisites)
            g[req[1]].push_back(req[0]);
        
        for(int cur=0; cur<numCourses; ++cur) {
            vector<int> visited(numCourses, 0);
            if(dfs(g, visited, cur))
                return false;
        }
        
        return true;
    }
    
private:
    // return true if DFS detects loop
    bool dfs(const vector<vector<int>> &g, vector<int> &visited, int cur) {
        visited[cur] = 1;  // mark visiting
        for(int next : g[cur]) {
            if(visited[next]==2)  // already visited
                continue;
            if(visited[next]==1 || dfs(g,visited,next))
                return true;
        }
        visited[cur] = 2;  // mark visited
        
        return false;
    }
};


// brute-force: ref impl from HuaHua
class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        
        graph_.clear();
        
        for(const auto& p : prerequisites)
            graph_[p.first].insert(p.second);
        
        for (int i = 0; i < numCourses; ++i) {
            vector<int> visited(numCourses, 0);
            if (cycle(i, i, visited)) return false;
        }
        
        return true;
    }
    
private:
    unordered_map<int, unordered_set<int>> graph_;
    
    bool cycle(int start, int curr, vector<int>& visited) {        
        if (curr == start && visited[start]) return true;
        if (!graph_.count(curr)) return false;
        
        for (const int next : graph_.at(curr)) {
            if (visited[next]) continue;
            visited[next] = true;
            if (cycle(start, next, visited)) return true;
        }
        return false;
    }
};
