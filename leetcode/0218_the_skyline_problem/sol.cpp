#include "../common/common.h"

using namespace std;

class Solution2 {
public:
  vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
    vector<pair<int, int>> points;

    // sorted building start/end points for line scan
    map<int, vector<int>> steps;
    for(const auto & building : buildings) {
      steps[building[0]].push_back(building[2]);   // positive for building start
      steps[building[1]].push_back(-building[2]);  // negative for building end
    }

    int prevHeight = 0;
    map<int,int> heights;
    for(const auto &step : steps) {
      int x = step.first;
      int curHeight = prevHeight;
      for(int h : step.second) {
	if(h > 0) {
	  heights[h] += 1;
	  if(h > curHeight)
	    curHeight = h;
	}
	else if(h < 0) {
	  h = abs(h);
	  if(--heights[h] == 0)
	    heights.erase(h);
	  if(h == curHeight)
	    curHeight = heights.empty() ? 0 : heights.rbegin()->first;
	}
      }

      // here we make sure that at most one point would be inserted for all start/end edges with the same x
      if(curHeight != prevHeight) {
	points.push_back(make_pair(x, curHeight));
	prevHeight = curHeight;
      }
    }
    
    return points;
  }
};

// Idea is the same as line-scan, but this version is cleaner
class Solution3 {
public:
  vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
    vector<pair<int, int>> points;

    vector<pair<int, int>> edges;  // start/end points of buildings
    for(const auto &building : buildings) {
      edges.push_back(make_pair(building[0], -building[2]));   // negative for building start
      edges.push_back(make_pair(building[1], building[2]));    // positive for building end
    }
    sort(edges.begin(), edges.end());

    multiset<int> alive;  // sorted heights of all alive buildings, alive.rbegin() is the max-height so far
    alive.insert(0);      // this is for ground level

    // when x is the same, the order guarantees that the tallest building start is visited first, and the tallest building end is visited last
    // -- this is important for the below logic to work (considering we adds the point as long as preHeight!=curHeight)
    // -- if a point needs to be inserted for the tallest start, then all remaining start/end at the same x wouldn't insert any point
    // -- if a point needs to be inserted for the smaller end, then all remaining end at the same x wouldn't insert any point 
    for(const auto &edge : edges) {
      int preHeight = *alive.rbegin();
      if(edge.second < 0)
	alive.insert(-edge.second);
      else if(edge.second > 0)
	alive.erase(alive.find(edge.second));

      int curHeight = *alive.rbegin();
      if(curHeight != preHeight)
	points.push_back({edge.first, curHeight});
    }

    return points;
  }

};

// Solution based on height-map
// https://briangordon.github.io/2014/08/the-skyline-problem.html
class Solution {
public:
  vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
    vector<pair<int, int>> points;
    vector<int> hmap(10001, 0);
    set<int> edges;
    for(const auto &building : buildings) {
      edges.insert(building[0]);
      edges.insert(building[1]);
    }

    for(const auto &building : buildings) {  // for each rectangle
      for(int edge : edges) {
	if(edge>=building[0] && edge<building[1])  // not including right boundary since this is the falling edge
	  hmap[edge] = max(hmap[edge], building[2]);
      }
    }

    for(int edge : edges) {
      if(points.empty() || points.back().second!=hmap[edge])
	points.push_back({edge, hmap[edge]});
    }

    return points;
  }

};

int main()
{
  vector<vector<int>> buildings = { {2,9,10}, {3,7,15}, {5,12,12}, {15,20,10}, {19,24,8} };
  Solution sol;
  auto points = sol.getSkyline(buildings);
  for(const auto &p : points)
    cout << "(" << p.first << ", " << p.second << ")" << endl;

  return 0;
}
