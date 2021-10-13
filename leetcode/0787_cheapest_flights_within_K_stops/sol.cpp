/*
There are n cities connected by some number of flights. You are given an array flights where flights[i] = [fromi, toi, pricei] indicates that there is a flight from city fromi to city toi with cost pricei.

You are also given three integers src, dst, and k, return the cheapest price from src to dst with at most k stops. If there is no such route, return -1.

 

Example 1:


Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 1
Output: 200
Explanation: The graph is shown.
The cheapest price from city 0 to city 2 with at most 1 stop costs 200, as marked red in the picture.
Example 2:


Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 0
Output: 500
Explanation: The graph is shown.
The cheapest price from city 0 to city 2 with at most 0 stop costs 500, as marked blue in the picture.
 

Constraints:

1 <= n <= 100
0 <= flights.length <= (n * (n - 1) / 2)
flights[i].length == 3
0 <= fromi, toi < n
fromi != toi
1 <= pricei <= 104
There will not be any multiple flights between two cities.
0 <= src, dst, k < n
src != dst
*/

// BFS -- fastest
// time complexity: O(V^K) or O(E*K)???
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // build graph
        vector<vector<pair<int,int>>> g(n);
        for(auto &f : flights)
            g[f[0]].push_back({f[1],f[2]});
        
        // BFS
        vector<int> dist(n, INT_MAX);
        queue<pair<int,int>> q;
        dist[src] = 0;
        q.push({src,0});  // current node and cost so far
        while(!q.empty() && k>=0) {
            int sz = q.size();
            while(sz--) {  // expand to next level
                pair<int,int> cur = q.front();
                q.pop();
                for(auto &f : g[cur.first]) {
                    int next = f.first;
                    int d = cur.second + f.second;
                    if(d < dist[next]) {
                        dist[next] = d;
                        q.push({next,d});  // important pruning: note level monotonically increase during BFS
                    }
                }
            }
            --k;
        }
        
        return dist[dst]==INT_MAX?-1:dist[dst];
    }
};


// Bellman-Ford: DP -- also fast
// dp(j,k): min cost to arrive j-th city taking up to k flights
// dp(j,k) = min{dp(i,k-1)+weight(i,j)} for all edge (i,j)
// -- K stops ==> K+1 flights ==> answer is dp(dst,K+1)
// time complexity: O(K*E)
// space complexity: O(K*V) --> can be reduced to O(V)
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        const int MAX_COST = (K+2)*1e4;
        vector<vector<int>> dp(n, vector(K+2, MAX_COST));  // at most K+1 flights for K stops
        for(int k=0; k<K+2; ++k) 
            dp[src][k] = 0;
        for(int k=1; k<=K+1; ++k) {  // at most K+1 flights for K stops
            for(auto &f : flights) {
                int i = f[0];
                int j = f[1];
                int w = f[2];
                dp[j][k] = min(dp[j][k], dp[i][k-1]+w);
            }
        }
        
        return dp[dst][K+1]==MAX_COST?-1:dp[dst][K+1];            
    }
};

// Dijkstra  -- can pass
// time complexity: O(ElgE)
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // build graph
        vector<vector<pair<int,int>>> g(n);
        for(auto &f : flights)
            g[f[0]].push_back({f[1],f[2]});
        
        vector<vector<int>> dist(n, vector<int>(k+1,INT_MAX));  // min distance to each node with k stops
        function<bool(const Node&,const Node&)> comp = [](const Node &n1, const Node &n2) {
            return n1._dist > n2._dist;
        };
        priority_queue<Node, vector<Node>, decltype(comp)> pq(comp);
        pq.emplace(0, src, 0);
        dist[src][0] = 0;
        while(!pq.empty()) {
            Node cur = pq.top();
            pq.pop();
            for(auto &f : g[cur._id]) {
                int next = f.first;
                int w = f.second;
                int stops = cur._stops + (next==dst?0:1);
                if(stops > k)  // too many stops needed
                    continue;
                int d = cur._dist + w;
                if(d < dist[next][stops]) {
                    dist[next][stops] = d;
                    pq.emplace(d,next,stops);
                }
            }
        }
        
        int ans = *min_element(dist[dst].begin(), dist[dst].end());
        return ans==INT_MAX?-1:ans;
    }
private:
    struct Node {
        Node(int d, int id, int s) : _dist(d), _id(id), _stops(s) {}
        int _dist;
        int _id;
        int _stops;
    };
};


// DFS -- TLE
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // build graph
        vector<vector<pair<int,int>>> g(n);
        for(auto &f : flights)
            g[f[0]].push_back({f[1],f[2]});
        
        // DFS
        vector<int> visited(n, 0);
        int ans = INT_MAX;
        dfs(g, visited, src, dst, k, 0, ans);

        return ans==INT_MAX?-1:ans;
    }
    
    
private:
    // assume cur node is on valid path and is already calculated
    void dfs(const vector<vector<pair<int,int>>> &g, vector<int> &visited, int cur, int dst, int k, int d, int &ans) {
        if(cur == dst) {
            ans = d;
            return;
        }
        
        if(k < 0)
            return;
        
        for(auto &f : g[cur]) {
            if(visited[f.first])
                continue;
            if(d+f.second >= ans)
                continue;
            visited[f.first] = 1;
            dfs(g, visited, f.first, dst, k-1, d+f.second, ans);
            visited[f.first] = 0;
        }
    }
};


// DFS another impl -- TLE
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // build graph
        vector<vector<pair<int,int>>> g(n);
        for(auto &f : flights)
            g[f[0]].push_back({f[1],f[2]});
        
        // DFS
        vector<vector<int>> dist(n, vector<int>(k+1, INT_MAX));
        vector<int> visited(n, 0);
        dfs(g, dist, dst, k, src, 0, 0, visited);

        int ans = *min_element(dist[dst].begin(), dist[dst].end());
        return ans==INT_MAX?-1:ans;
    }
    
    
private:
    // assume cur node is on valid path and is already calculated
    void dfs(const vector<vector<pair<int,int>>> &g, vector<vector<int>> &dist, const int dst, const int k, int cur, int stops, int d, vector<int> &visited) {
        if(cur == dst) {
            --stops;
            dist[cur][stops] = min(dist[cur][stops], d);
            return;
        }
        
        if(visited[cur] || stops>k || d>=dist[cur][stops])
            return;
        
        visited[cur] = 1;
        dist[cur][stops] = d;
        for(auto &f : g[cur]) {
            dfs(g, dist, dst, k, f.first, stops+1, d+f.second, visited);
        }
        visited[cur] = 0;
    }
};
