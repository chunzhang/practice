/*
There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
Return the ordering of courses you should take to finish all courses. If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.

 

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1].
Example 2:

Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].
Example 3:

Input: numCourses = 1, prerequisites = []
Output: [0]
 

Constraints:

1 <= numCourses <= 2000
0 <= prerequisites.length <= numCourses * (numCourses - 1)
prerequisites[i].length == 2
0 <= ai, bi < numCourses
ai != bi
All the pairs [ai, bi] are distinct.
*/


// topo-sort using DFS
// time complexity: O(V+E)
// space complexity: O(V)
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // build graph
        vector<vector<int>> g(numCourses);
        for(auto &req : prerequisites) {
            g[req[1]].push_back(req[0]);
        }
        
        vector<int> ans;
        vector<STATUS> visited(numCourses, NONE);
        for(int cur=0; cur<numCourses; ++cur) {
            if(visited[cur]==NONE && dfs(g,visited,ans,cur))
                return {};
        }
        
        reverse(ans.begin(), ans.end());
        return ans;
    }
        
private:
    enum STATUS{NONE,VISITING,VISITED};
    // return true if DFS detects loop
    bool dfs(const vector<vector<int>> &g, vector<STATUS> &visited, vector<int> &ans, int cur) {
        visited[cur] = VISITING;
        for(int next : g[cur]) {
            if(visited[next] == VISITING)  // loop detected
                return true;
            if(visited[next] == VISITED)
                continue;
            if(dfs(g, visited, ans, next))
                return true;
        }
        
        visited[cur] = VISITED;
        ans.push_back(cur);
        return false;
    }
        
};


// topo-sort with BFS
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // build graph
        vector<vector<int>> g(numCourses);
        vector<int> nInputs(numCourses, 0);  // number of inputs of each graph node
        for(auto &req : prerequisites) {
            g[req[1]].push_back(req[0]);
            ++nInputs[req[0]];
        }
        
        // BFS
        queue<int> q;
        vector<int> ans;
        for(int cur=0; cur<numCourses; ++cur) {
            if(nInputs[cur] == 0)
                q.push(cur);
        }
        while(!q.empty()) {
            int cur = q.front();
            q.pop();
            ans.push_back(cur);
            for(int next : g[cur]) {
                if(--nInputs[next] == 0)
                    q.push(next);
            }
        }
        
        return ans.size()==numCourses?ans:vector<int>();
    }
        
};
