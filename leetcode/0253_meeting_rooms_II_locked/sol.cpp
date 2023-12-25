/*
Google/Facebook/TikTok


Given an array of meeting time intervals intervals where intervals[i] = [starti, endi], return the minimum number of conference rooms required.

Example 1:

Input: intervals = [[0,30],[5,10],[15,20]]
Output: 2
Example 2:

Input: intervals = [[7,10],[2,4]]
Output: 1
 

Constraints:

1 <= intervals.length <= 104
0 <= starti < endi <= 106
*/

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
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const vector<int> &i1, const vector<int> &i2) {
            return i1[0] < i2[0];  // sort by meeting start point
        });
        
        priority_queue<int, vector<int>, greater<int>> rooms;  // keep track of first meeting to end
        for(auto &v : intervals) {
            if(!rooms.empty() && v[0]>=rooms.top())  // a meeting has already ended
                rooms.pop();
            rooms.push(v[1]);
        }

        return rooms.size();
    }
};

// a different impl with min-heap that stores interval: more to show the usage of customized sorting function
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const vector<int> &i1, const vector<int> &i2) {
            return i1[0] < i2[0];  // sort by meeting start point
        });
        auto comp = [](const vector<int> &i1, const vector<int> &i2) {
            return i1[1] > i2[1];
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> rooms(comp);
        for(auto &v : intervals) {
            if(!rooms.empty() && v[0]>=rooms.top()[1])  // a meeting has already ended
                rooms.pop();
            rooms.push(v);
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
