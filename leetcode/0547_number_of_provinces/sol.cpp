/*
There are n cities. Some of them are connected, while some are not. If city a is connected directly with city b, and city b is connected directly with city c, then city a is connected indirectly with city c.

A province is a group of directly or indirectly connected cities and no other cities outside of the group.

You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.

Return the total number of provinces.

 

Example 1:


Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
Output: 2
Example 2:


Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
Output: 3
 

Constraints:

1 <= n <= 200
n == isConnected.length
n == isConnected[i].length
isConnected[i][j] is 1 or 0.
isConnected[i][i] == 1
isConnected[i][j] == isConnected[j][i]
*/


// DFS to find connected components
// time complexity: O(N^2)
// space complexity: O(N)
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        const int N = isConnected.size();
        vector<int> visited(N, 0);
        int ans = 0;
        for(int i=0; i<N; ++i) {
            if(!visited[i]) {
                dfs(isConnected, visited, i);
                ++ans;
            }
        }
        
        return ans;
    }
    
private:
    void dfs(const vector<vector<int>> &g, vector<int> &visited, int i) {
        visited[i] = 1;
        for(int j=0; j<g[i].size(); ++j) {
            if(g[i][j] && !visited[j])
                dfs(g, visited, j);
        }
    }
};
