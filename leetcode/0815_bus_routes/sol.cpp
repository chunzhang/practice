/*
  We have a list of bus routes. Each routes[i] is a bus route that the i-th bus repeats forever. For example if routes[0] = [1, 5, 7], this means that the first bus (0-th indexed) travels in the sequence 1->5->7->1->5->7->1->... forever.

  We start at bus stop S (initially not on a bus), and we want to go to bus stop T. Travelling by buses only, what is the least number of buses we must take to reach our destination? Return -1 if it is not possible.

  Example:
  Input: 
  routes = [[1, 2, 7], [3, 6, 7]]
  S = 1
  T = 6
  Output: 2
  Explanation: 
  The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
  Note:

  1 <= routes.length <= 500.
  1 <= routes[i].length <= 500.
  0 <= routes[i][j] < 10 ^ 6.
*/

// My idea
// -- Each bus becomes a node
// -- Perform BFS from all buses containing S until any bus containing T
class Solution {
public:
  int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
    if(S == T)
      return 0;
    vector<int> dist(routes.size(), 0);  // distance and visited flag
    unordered_map<int, vector<int>> station2Bus;  // station to bus mapping
    queue<int> q;  // BFS queue
    unordered_set<int> dest; // buses containing destination
    for(int bus=0; bus<routes.size(); ++bus) {
      bool hasS = false;
      bool hasT = false;
      for(int i=0; i<routes[bus].size(); ++i) {
	int station = routes[bus][i];
	station2Bus[station].push_back(bus);
	if(station == S) {
	  hasS = true;
	  q.push(bus);
	  dist[bus] = 1;
	}
	if(station == T) {
	  hasT = true;
	  dest.insert(bus);
	}
      }
      if(hasS && hasT)
	return 1;
    }
        
    while(!q.empty()) {
      int bus = q.front();
      q.pop();
      int nextDist = dist[bus] + 1;

      // Search all neighbors
      for(int station : routes[bus]) {
	for(int nextBus : station2Bus[station]) {
	  if(dist[nextBus])  // already visited
	    continue;
	  if(dest.count(nextBus))  // found!
	    return nextDist;
	  else { 
	    q.push(nextBus);
	    dist[nextBus] = nextDist;
	  }
	}
      }
    }
        
    return -1;  // No such route exists!
  }
};
