/*
  There are n cities numbered from 0 to n-1. Given the array edges where edges[i] = [fromi, toi, weighti] represents a bidirectional and weighted edge between cities fromi and toi, and given the integer distanceThreshold.

  Return the city with the smallest number of cities that are reachable through some path and whose distance is at most distanceThreshold, If there are multiple such cities, return the city with the greatest number.

  Notice that the distance of a path connecting cities i and j is equal to the sum of the edges' weights along that path.

 

  Example 1:


  Input: n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold = 4
  Output: 3
  Explanation: The figure above describes the graph. 
  The neighboring cities at a distanceThreshold = 4 for each city are:
  City 0 -> [City 1, City 2] 
  City 1 -> [City 0, City 2, City 3] 
  City 2 -> [City 0, City 1, City 3] 
  City 3 -> [City 1, City 2] 
  Cities 0 and 3 have 2 neighboring cities at a distanceThreshold = 4, but we have to return city 3 since it has the greatest number.
  Example 2:


  Input: n = 5, edges = [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]], distanceThreshold = 2
  Output: 0
  Explanation: The figure above describes the graph. 
  The neighboring cities at a distanceThreshold = 2 for each city are:
  City 0 -> [City 1] 
  City 1 -> [City 0, City 4] 
  City 2 -> [City 3, City 4] 
  City 3 -> [City 2, City 4]
  City 4 -> [City 1, City 2, City 3] 
  The city 0 has 1 neighboring city at a distanceThreshold = 2.
 

  Constraints:

  2 <= n <= 100
  1 <= edges.length <= n * (n - 1) / 2
  edges[i].length == 3
  0 <= fromi < toi < n
  1 <= weighti, distanceThreshold <= 10^4
  All pairs (fromi, toi) are distinct.
*/

// Floyd-Warshall to find all-pairs shortest path
// time complexity: O(V^3)
// space complexity: O(V^2)
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        // Floyd-Warshall to compute all-pairs shortest path
        vector<vector<int>> dist(n, vector<int>(n,1e9));
        for(auto &e : edges) {
            dist[e[0]][e[1]] = e[2];
            dist[e[1]][e[0]] = e[2];
        }
        for(int i=0; i<n; ++i)
            dist[i][i] = 0;

        for(int k=0; k<n; ++k)  // IMPORTANT: outer loop must iterate through k!!!
            for(int i=0; i<n; ++i)
                for(int j=0; j<n; ++j)
                    dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
        
        // build answer
        int minCity = INT_MAX;
        int ans = -1;
        for(int i=0; i<n; ++i) {
            int nNei = 0;
            for(int j=0; j<n; ++j)
                if(dist[i][j] <= distanceThreshold)
                    ++nNei;
            if(nNei <= minCity) {
                minCity = nNei;
                ans = i;
            }
        }
        return ans;
    }
};


// A very good implementation using Dijkstra (from HuaHua)
// time complexity: O(V*(V+E)lgV)
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int t) {
        vector<vector<pair<int, int>>> g(n);
        for (const auto& e : edges) {
            g[e[0]].emplace_back(e[1], e[2]);
            g[e[1]].emplace_back(e[0], e[2]);
        }
    
        // Returns the number of nodes within t from s.
        auto dijkstra = [&](int s) {  // Dijkstra itself takes O((V+E)lgV)
            vector<int> dist(n, INT_MAX / 2);
            set<pair<int, int>> q; // <dist, node>
            vector<set<pair<int, int>>::const_iterator> its(n);
            dist[s] = 0;
            for (int i = 0; i < n; ++i)
                its[i] = q.emplace(dist[i], i).first;
            while (!q.empty()) {
                auto it = cbegin(q);
                int d = it->first;
                int u = it->second;
                q.erase(it);        
                if (d > t) break; // pruning
                for (const auto& p : g[u]) {
                    int v = p.first;
                    int w = p.second;
                    if (dist[v] <= d + w) continue;
                    // Decrease key
                    q.erase(its[v]);
                    its[v] = q.emplace(dist[v] = d + w, v).first;
                }
            }
            return count_if(begin(dist), end(dist), [t](int d) { return d <= t; });
        };
    
        int ans = -1;
        int min_nb = INT_MAX;
        for (int i = 0; i < n; ++i) {
            int nb = dijkstra(i);
            if (nb <= min_nb) {
                min_nb = nb;
                ans = i;
            }
        }
    
        return ans;
    }
};
