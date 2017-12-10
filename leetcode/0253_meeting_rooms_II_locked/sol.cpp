/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

#include "../common/common.h"

using namespace std;

// Use a min-heap to keep track of the meeting that ends earliest
class Solution1 {
public:
  int minMeetingRooms(vector<Interval>& intervals) {
    std::sort(intervals.begin(),
	      intervals.end(),
	      [](const Interval &i1, const Interval &i2) {
		return i1.start < i2.start;
	      });
    auto comp = [](const Interval &i1, const Interval &i2) { return i1.end > i2.end; };
    priority_queue<Interval, vector<Interval>, decltype(comp)> rooms(comp);
    if(!intervals.empty())
      rooms.push(intervals[0]);
    for(int i=1; i<intervals.size(); ++i) {
      if(intervals[i].start >= rooms.top().end)  // we can reuse the room for the meeting that has already ended
	rooms.pop();
      rooms.push(intervals[i]);
    }

    return rooms.size();
  }
};

// Solution based on line-scan
// -- Whenever sees an interval start, ++room
// -- Whenever sees an interval end, --roon
class Solution2 {
public:
  int minMeetingRooms(vector<Interval>& intervals) {
    int maxRoom = 0;
    int room = 0;
    priority_queue<int, vector<int>, greater<int>> starts;
    priority_queue<int, vector<int>, greater<int>> ends;
    for(const auto &interval : intervals) {
      starts.push(interval.start);
      ends.push(interval.end);
    }

    while(!starts.empty()) {
      while(!ends.empty() && ends.top()<=starts.top()) {
	--room;
	ends.pop();
      }
      ++room;
      if(room > maxRoom)
	maxRoom = room;
      starts.pop();
    }

    return maxRoom;
  }

};

// Line-scan: use a map to keep track of start/end points
class Solution3 {
public:
  int minMeetingRooms(vector<Interval>& intervals) {
    map<int, int> deltas;
    int room = 0;
    int maxRoom = 0;
    for(const auto &interval : intervals) {
      deltas[interval.start] += 1;  // whenever a meeting starts, we take one room
      deltas[interval.end] -= 1;    // whenever a meeting ends, we release a room
    }

    for(const auto &delta : deltas) {
      room += delta.second;
      maxRoom = max(room, maxRoom);
    }

    return maxRoom;
  }

};

// Line-scan: use a vector to keep track of start/end points
class Solution {
public:
  int minMeetingRooms(vector<Interval>& intervals) {
    vector<pair<int,int>> deltas;
    for(const auto &interval : intervals) {
      deltas.push_back(make_pair(interval.start, 1));
      deltas.push_back(make_pair(interval.end, -1));
    }
    sort(deltas.begin(), deltas.end());  // use default pair sort: -1 comes before 1
    int room = 0;
    int maxRoom = 0;
    for(const auto &delta : deltas) {
      room += delta.second;
      maxRoom = max(room, maxRoom);
    }

    return maxRoom;
  }

};

int main(int argc, char *argv[])
{
  auto intervals = makeIntervals(argc, argv);
  printIntervals(intervals);
  Solution sol;
  int res = sol.minMeetingRooms(intervals);
  cout << "res: " << res << endl;

  return 0;
}
