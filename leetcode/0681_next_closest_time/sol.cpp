/*
  Given a time represented in the format "HH:MM", form the next closest time by reusing the current digits. There is no limit on how many times a digit can be reused.

  You may assume the given input string is always valid. For example, "01:34", "12:09" are all valid. "1:34", "12:9" are all invalid.

  Example 1:

  Input: "19:34"
  Output: "19:39"
  Explanation: The next closest time choosing from digits 1, 9, 3, 4, is 19:39, which occurs 5 minutes later.  It is not 19:33, because this occurs 23 hours and 59 minutes later.
  Example 2:

  Input: "23:59"
  Output: "22:22"
  Explanation: The next closest time choosing from digits 2, 3, 5, 9, is 22:22. It may be assumed that the returned time is next day's time since it is smaller than the input time numerically.
*/

#include "../common/common.h"
#include <iomanip>

using namespace std;

// This is another version of enumerations based approach -- use modular to compute time delta
class Solution {
public:
  string nextClosestTime(string time) {
    int startTime = atoi(time.substr(0,2).c_str())*60 + atoi(time.substr(3).c_str());
    set<int> digs;
    for(char c : time)
      if(c != ':')
	digs.insert(c-'0');

    int closestTime = startTime;
    int minDelta = numeric_limits<int>::max();
    for(int hh1 : digs)
      for(int hh2 : digs)
	for(int mm1 : digs)
	  for(int mm2 : digs) {
	    int hh = hh1*10 + hh2;
	    int mm = mm1*10 + mm2;
	    if(hh>23 || mm>59)
	      continue;
	    int curTime = hh*60 + mm;
	    int delta = (curTime-startTime) % 1440;
	    if(delta < 0)
	      delta += 1440;
	    //xxx cout << hh << ":" << mm << " minus " << startTime/60 << ":" << startTime%60 << " is " << delta << " minutes" << endl; 
	    if(delta>0 && delta<minDelta) {
	      closestTime = curTime;
	      minDelta = delta;
	    }
	  }

    int hh = closestTime / 60;
    int mm = closestTime % 60;
    ostringstream oss;
    oss << setw(2) << setfill('0') << hh << ":" << setw(2) << setfill('0') << mm;
    return oss.str();
  }

};


// This is simulation based approach
// simulate the clock going forward by one minute. Each time it moves forward, if all the digits are allowed, then return the current time.
class Solution3 {
public:
  string nextClosestTime(string time) {
    int startTime = atoi(time.substr(0,2).c_str())*60 + atoi(time.substr(3).c_str());
    set<int> digs;
    for(char c : time)
      if(c != ':')
	digs.insert(c-'0');

    for(int i=1; i<1440/* 24*60 minutes */; ++i) {
      int simTime = (startTime+i)%1440;;
      int hh = simTime / 60;
      int mm = simTime % 60;
      vector<int> simDigs = {hh/10, hh%10, mm/10, mm%10};
      bool valid = true;
      for(int d : simDigs)
	if(digs.find(d) == digs.end()) {
	  valid = false;
	  break;
	}
      if(valid) {
	ostringstream oss;
	oss << simDigs[0] << simDigs[1] << ":" << simDigs[2] << simDigs[3];
	return oss.str();
      }
    }

    // cannot reach here..., but still return something
    return time;
  }

};

// This is my first implementation of enumeration-based solution
class Solution2 {
public:
  string nextClosestTime(string time) {
    vector<int> digs(4,0);
    digs[0] = time[0]-'0';
    digs[1] = time[1]-'0';
    digs[2] = time[3]-'0';
    digs[3] = time[4]-'0';
    int hh = digs[0]*10 + digs[1];
    int mm = digs[2]*10 + digs[3];
    int hhC = hh;
    int mmC = mm;
    int minDelta = numeric_limits<int>::max();

    // enumerate all possible times to find the closest
    for(int h1 : digs)
      for(int h2 : digs)
	for(int m1 : digs)
	  for(int m2 : digs) {
	    int hhTemp = h1*10 + h2;
	    int mmTemp = m1*10 + m2;
	    if(hhTemp>23 || mmTemp>59)
	      continue;
	    int delta = calDelta(hhTemp, mmTemp, hh, mm);
	    if(delta>0 && delta<minDelta) {
	      hhC = hhTemp;
	      mmC = mmTemp;
	      minDelta = delta;
	    }
	  }

    ostringstream oss;
    oss << setw(2) << setfill('0') << hhC << ":" << setw(2) << setfill('0') << mmC;
    return oss.str();
  }

  int calDelta(int hh1, int mm1, int hh2, int mm2) {
    if(hh1<hh2 || (hh1==hh2 && mm1<mm2))
      hh1 += 24;
    int delta = hh1*60+mm1 - (hh2*60+mm2);
    //xxx cout << hh1 << ":" << mm1 << " minus " << hh2 << ":" << mm2 << " is " << delta << " minutes" << endl; 
    return delta;
  }
};

int main(int argc, char *argv[])
{
  string time = argv[1];
  Solution sol;
  string res = sol.nextClosestTime(time);
  cout << time << " --> " << res << endl;

  return 0;
}
