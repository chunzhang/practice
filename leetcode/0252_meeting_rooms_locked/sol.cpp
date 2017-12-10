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

class Solution {
public:
  bool canAttendMeetings(vector<Interval>& intervals) {
    std::sort(intervals.begin(),
	      intervals.end(),
	      [](const Interval &i1, const Interval &i2) {
		return i1.start < i2.start;
	      });
    for(int i=1; i<intervals.size(); ++i) {
      if(intervals[i].start < intervals[i-1].end)
	return false;
    }

    return true;
  }
};

int main(int argc, char *argv[])
{
  vector<Interval> intervals = makeIntervals(argc, argv);
  printIntervals(intervals);
  Solution sol;
  bool res = sol.canAttendMeetings(intervals);
  cout << "res: " << res << endl;

  return 0;
}
