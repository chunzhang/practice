/*
Given a string s and a list of strings dict, you need to add a closed pair of bold tag <b> and </b> to wrap the substrings in s that exist in dict. If two such substrings overlap, you need to wrap them together by only one pair of closed bold tag. Also, if two substrings wrapped by bold tags are consecutive, you need to combine them.
Example 1:
Input: 
s = "abcxyz123"
dict = ["abc","123"]
Output:
"<b>abc</b>xyz<b>123</b>"
Example 2:
Input: 
s = "aaabbcc"
dict = ["aaa","aab","bc"]
Output:
"<b>aaabbc</b>c"
Note:
The given dict won't contain duplicates, and its length won't exceed 100.
All the strings in input have length in range [1, 1000].
*/

#include "../common/common.h"

using namespace std;

// Substring search + merge interval
class Solution {
public:
  string addBoldTag(string s, vector<string>& dict) {
    // 1. Build intervals for all matched substrings in the dict
    vector<pair<int,int>> intervals;
    for(const string &word : dict) {
      int cur = -1;
      while((cur=s.find(word,cur+1)) != string::npos) {
	intervals.push_back(make_pair(cur, cur+word.size()-1));
      }
    }
        
    if(intervals.empty())
      return s;

    // 2. Sort intervals
    sort(intervals.begin(), intervals.end());  // default sort is good enough
        
    // 3. Merge intervals
    vector<pair<int,int>> mergedIntervals;
    int start = intervals[0].first;
    int end = intervals[0].second;
    for(int i=1; i<intervals.size(); ++i) {
      if(intervals[i].first > end + 1) {
	mergedIntervals.push_back(make_pair(start, end));
	start = intervals[i].first;
	end = intervals[i].second;
      }
      else {
	end = max(end, intervals[i].second);
      }
    }
    mergedIntervals.push_back(make_pair(start,end));  // Don't forget this last interval
        
    string res;
    int cur = 0;
    for(auto interval : mergedIntervals) {
      int start = interval.first;
      int end = interval.second;
      res += (s.substr(cur,start-cur));
      res += "<b>" + s.substr(start, end-start+1) + "</b>";
      cur = end + 1;
    }
    res += s.substr(cur);  // Don't forget remaining substring
    return res;
  }
};


// KMP + boolean array
class Solution {
public:
  string addBoldTag(string s, vector<string>& dict) {
    vector<int> bold(s.size()+2, 0);  // bold[i]==1 if s[i] shall be bold
    for(const string &word : dict) {
      int cur = -1;
      while((cur=s.find(word,cur+1)) != string::npos) {
	for(int i=cur; i<cur+word.size(); ++i) {
	  bold[i+1] = 1;
	}
      }
    }
        
    string res;
    // note bold is has one dummy entry at both the beginning and the end
    for(int i=1; i<s.size()+1; ++i) {
      if(bold[i] && !bold[i-1])
	res += "<b>";
      res.push_back(s[i-1]);
      if(bold[i] && !bold[i+1])
	res += "</b>";
    }
    return res;
  }
};

// Brute-force search + boolean array
class Solution {
public:
  string addBoldTag(string s, vector<string>& dict) {
    vector<int> bold(s.size()+2, 0);  // bold[i]==1 if s[i] shall be bold
    int end = 0;
    for(int i=0; i<s.size(); ++i) {
      for(const string &word : dict) {
	if(s.substr(i,word.size()) == word)
	  end = max(end, i+(int)word.size());
      }
      if(end > i)
	bold[i+1] = 1;
    }
        
    string res;
    // note bold is has one dummy entry at both the beginning and the end
    for(int i=1; i<s.size()+1; ++i) {
      if(bold[i] && !bold[i-1])
	res += "<b>";
      res.push_back(s[i-1]);
      if(bold[i] && !bold[i+1])
	res += "</b>";
    }
    return res;
  }
};
