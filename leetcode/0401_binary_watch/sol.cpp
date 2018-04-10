/*
  A binary watch has 4 LEDs on the top which represent the hours (0-11), and the 6 LEDs on the bottom represent the minutes (0-59).

  Each LED represents a zero or one, with the least significant bit on the right.


  For example, the above binary watch reads "3:25".

  Given a non-negative integer n which represents the number of LEDs that are currently on, return all possible times the watch could represent.

  Example:

  Input: n = 1
  Return: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
  Note:
  The order of output does not matter.
  The hour must not contain a leading zero, for example "01:00" is not valid, it should be "1:00".
  The minute must be consist of two digits and may contain a leading zero, for example "10:2" is not valid, it should be "10:02".
*/

// Enumerate all possible numLedsHours + numLedsMinutes combination
class Solution {
public:
  vector<string> readBinaryWatch(int num) {
    // 1. count how many leds are on for each hour and minute number
    unordered_map<int, vector<string>> h;
    for(int n=0; n<12; ++n) {
      h[numLeds(n)].push_back(to_string(n));
    }
    unordered_map<int, vector<string>> m;
    for(int n=0; n<60; ++n) {
      m[numLeds(n)].push_back(n<10?"0"+to_string(n):to_string(n));
    }
        
    // 2. enumerate all possible times
    vector<string> ans;
    for(int hn=0; hn<=num&&hn<=3; ++hn) // num leds for hour
      for(string hh : h[hn])                
	for(string mm : m[num-hn]) {
	  ans.push_back(hh + ":" + mm);
	}
        
    return ans;
  }
    
private:
  int numLeds(int n) {
    int num = 0;
    while(n) {
      if(n & 0x1)
	++num;
      n >>= 0x1;
    }
    return num;
  }
};

// Enumerate all times
class Solution {
public:
  vector<string> readBinaryWatch(int num) {
    vector<string> ans;
    for(int hh=0; hh<12; ++hh)
      for(int mm=0; mm<60; ++mm)
	if(numLeds((hh<<6)|mm) == num)  // trick to merge number and count bits
	  ans.push_back(to_string(hh) + (mm<10?":0":":") + to_string(mm));
        
    return ans;
  }
    
private:
  int numLeds(int n) {
    int num = 0;
    while(n) {
      if(n & 0x1)
	++num;
      n >>= 0x1;
    }
    return num;
  }
};

// DFS/backtracking
class Solution {
public:
  vector<string> readBinaryWatch(int num) {
    vector<string> ans;
    vector<int> hourBits = {1, 2, 4, 8};
    vector<int> minBits = {1, 2, 4, 8, 16, 32};
    dfs(ans, hourBits, minBits, 0, 0, num, 0);
    return ans;
  }
    
private:
  void dfs(vector<string> &ans, 
	   vector<int> &hourBits, 
	   vector<int> &minBits, 
	   int hh,       // current hour
	   int mm,       // current minute
	   int num,      // num Leds left to pick
	   int start)    // start position to pick next led bit
  {
    if(num == 0) {
      ans.push_back(to_string(hh) + (mm<10?":0":":") + to_string(mm));
      return;
    }
        
    // Select one bit at each dfs recursion
    // -- Note each bit can be selected only once, which is the reason we need to maintain "start"
    for(int i=start; i<hourBits.size()+minBits.size(); ++i) {
      if(i<hourBits.size()) {
	hh += hourBits[i];
	if(hh < 12)
	  dfs(ans, hourBits, minBits, hh, mm, num-1, i+1);
	hh -= hourBits[i];
      }
      else {
	mm += minBits[i-hourBits.size()];
	if(mm < 60)
	  dfs(ans, hourBits, minBits, hh, mm, num-1, i+1);
	mm -= minBits[i-hourBits.size()];
      }
    }
        
  }
};
