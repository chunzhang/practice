/*
  You are given an array routes representing bus routes where routes[i] is a bus route that the ith bus repeats forever.

  For example, if routes[0] = [1, 5, 7], this means that the 0th bus travels in the sequence 1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 -> ... forever.
  You will start at the bus stop source (You are not on any bus initially), and you want to go to the bus stop target. You can travel between bus stops by buses only.

  Return the least number of buses you must take to travel from source to target. Return -1 if it is not possible.

 

  Example 1:

  Input: routes = [[1,2,7],[3,6,7]], source = 1, target = 6
  Output: 2
  Explanation: The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
  Example 2:

  Input: routes = [[7,12],[4,5,15],[6],[15,19],[9,12,13]], source = 15, target = 12
  Output: -1
 

  Constraints:

  1 <= routes.length <= 500.
  1 <= routes[i].length <= 10^5
  All the values of routes[i] are unique.
  sum(routes[i].length) <= 10^5
  0 <= routes[i][j] < 10^6
  0 <= source, target < 10^6
*/

// BFS to find shortest path, i.e., build graph explicitly
// time complexity: O(N*M), where N is number of buses, M is average number of stops each bus take
// space complexity: O(N*M+N^2)
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if(source == target)
            return 0;
        
        // build graph: node-->bus, edge-->two bus share a common stop
        vector<vector<int>> g(routes.size());
        unordered_map<int,vector<int>> stop2bus;  // stop --> bus
        vector<int> from;  // start bus node
        unordered_set<int> to;    // end bus node
        for(int bus=0; bus<routes.size(); ++bus) {
            for(int stop : routes[bus]) {
                if(stop == source)
                    from.push_back(bus);
                if(stop == target)
                    to.insert(bus);
                auto &buses = stop2bus[stop];
                // add to graph
                for(int b : buses) {
                    g[b].push_back(bus);
                    g[bus].push_back(b);
                }
                buses.push_back(bus);
            }
        }
        
        // BFS
        queue<int> q;
        vector<int> visited(routes.size(), 0);
        for(int bus : from) {
            q.push(bus);
            visited[bus] = 1;
        }
        int nBus = 1;
        while(!q.empty()) {
            int sz = q.size();
            while(sz--) {
                int bus = q.front();
                q.pop();
                if(to.find(bus) != to.end())
                    return nBus;
                for(int nb : g[bus]) {
                    if(!visited[nb]) {
                        q.push(nb);
                        visited[nb] = 1;
                    }
                }
            }
            ++nBus;
        }
        
        return -1;
    }
    
};


// BFS to find shortest path, i.e., w/o building the graph explicitly
// time complexity: O(N*M)
// space complexity: O(N*M)
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if(source == target)  // important corner casse
            return 0;
        
        // we don't build graph explicitly; instead, we build stop-->bus mapping so the connecting buses can be searched on the fly
        unordered_map<int,vector<int>> stop2bus;
        vector<int> from;  // starting bus
        unordered_set<int> to;    // ending bus
        for(int bus=0; bus<routes.size(); ++bus) {
            for(int stop : routes[bus]) {
                stop2bus[stop].push_back(bus);
                if(stop == source)
                    from.push_back(bus);
                if(stop == target)
                    to.insert(bus);
            }
        }
        
        // BFS
        queue<int> q;
        vector<int> visited(routes.size(), 0);
        for(int bus : from) {
            q.push(bus);
            visited[bus] = 1;
        }
        int nBus = 1;
        while(!q.empty()) {
            int sz = q.size();
            while(sz--) {
                int bus = q.front();
                q.pop();
                if(to.find(bus) != to.end())
                    return nBus;
                for(int stop : routes[bus]) {  // since we didn't build the graph explicitly, we need to search connecting buses on the fly
                    for(int nb : stop2bus[stop]) {
                        if(!visited[nb]) {
                            q.push(nb);
                            visited[nb] = 1;
                        }
                    }
                }
            }
            ++nBus;
        }
        
        return -1;
    }
    
};


// official ref impl (in Java)
import java.awt.Point;

class Solution {
    public int numBusesToDestination(int[][] routes, int S, int T) {
        if (S==T) return 0;
        int N = routes.length;

        List<List<Integer>> graph = new ArrayList();
        for (int i = 0; i < N; ++i) {
            Arrays.sort(routes[i]);
            graph.add(new ArrayList());
        }
        Set<Integer> seen = new HashSet();
        Set<Integer> targets = new HashSet();
        Queue<Point> queue = new ArrayDeque();

        // Build the graph.  Two buses are connected if
        // they share at least one bus stop.
        for (int i = 0; i < N; ++i)
            for (int j = i+1; j < N; ++j)
                if (intersect(routes[i], routes[j])) {
                    graph.get(i).add(j);
                    graph.get(j).add(i);
                }

        // Initialize seen, queue, targets.
        // seen represents whether a node has ever been enqueued to queue.
        // queue handles our breadth first search.
        // targets is the set of goal states we have.
        for (int i = 0; i < N; ++i) {
            if (Arrays.binarySearch(routes[i], S) >= 0) {
                seen.add(i);
                queue.offer(new Point(i, 0));
            }
            if (Arrays.binarySearch(routes[i], T) >= 0)
                targets.add(i);
        }

        while (!queue.isEmpty()) {
            Point info = queue.poll();
            int node = info.x, depth = info.y;
            if (targets.contains(node)) return depth+1;
            for (Integer nei: graph.get(node)) {
                if (!seen.contains(nei)) {
                    seen.add(nei);
                    queue.offer(new Point(nei, depth+1));
                }
            }
        }

        return -1;
    }

    public boolean intersect(int[] A, int[] B) {
        int i = 0, j = 0;
        while (i < A.length && j < B.length) {
            if (A[i] == B[j]) return true;
            if (A[i] < B[j]) i++; else j++;
        }
        return false;
    }
};



// ref impl from HuaHua
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
        if (S == T) return 0;
    
        unordered_map<int, vector<int>> m;
        for (int i = 0; i < routes.size(); ++i)
            for (const int stop : routes[i])
                m[stop].push_back(i);
    
        vector<int> visited(routes.size(), 0);
        queue<int> q;
        q.push(S);
        int buses = 0;
    
        while (!q.empty()) {
            int size = q.size();      
            ++buses;
            while (size--) {
                int curr = q.front(); q.pop();        
                for (const int bus : m[curr]) {
                    if (visited[bus]) continue;          
                    visited[bus] = 1;
                    for (int stop : routes[bus]) {
                        if (stop == T) return buses;            
                        q.push(stop);
                    }
                }        
            }      
        }
        return -1;
    }
};


    
