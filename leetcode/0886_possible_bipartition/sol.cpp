/*
We want to split a group of n people (labeled from 1 to n) into two groups of any size. Each person may dislike some other people, and they should not go into the same group.

Given the integer n and the array dislikes where dislikes[i] = [ai, bi] indicates that the person labeled ai does not like the person labeled bi, return true if it is possible to split everyone into two groups in this way.

 

Example 1:

Input: n = 4, dislikes = [[1,2],[1,3],[2,4]]
Output: true
Explanation: group1 [1,4] and group2 [2,3].
Example 2:

Input: n = 3, dislikes = [[1,2],[1,3],[2,3]]
Output: false
Example 3:

Input: n = 5, dislikes = [[1,2],[2,3],[3,4],[4,5],[1,5]]
Output: false
 

Constraints:

1 <= n <= 2000
0 <= dislikes.length <= 10^4
dislikes[i].length == 2
1 <= dislikes[i][j] <= n
ai < bi
All the pairs of dislikes are unique.
*/


// DFS by coloring nodes
class Solution {
public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        // same as determine whether a graph is bipartite
        vector<vector<int>> g(n+1);
        for(auto &v : dislikes) {
            g[v[0]].push_back(v[1]);
            g[v[1]].push_back(v[0]);
        }
        
        // DFS
        vector<int> color(n+1, -1);
        for(int cur=1; cur<=n; ++cur)
            if(color[cur]==-1 && !dfs(g,color,cur,0))
                return false;
        return true;
    }
    
private:
    bool dfs(const vector<vector<int>> &g, vector<int> &color, int cur, int c) {
        color[cur] = c;
        int nc = c^0x1;
        for(int next : g[cur]) {
            if(color[next]==c || color[next]==-1&&!dfs(g,color,next,nc))
                return false;
        }
        
        return true;
    }
};


// BFS -- see solution of 0785
