/*
  Given a string, we can "shift" each of its letter to its successive letter, for example: "abc" -> "bcd". We can keep "shifting" which forms the sequence:

  "abc" -> "bcd" -> ... -> "xyz"
  Given a list of strings which contains only lowercase alphabets, group all strings that belong to the same shifting sequence.

  For example, given: ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"], 
  A solution is:

  [
  ["abc","bcd","xyz"],
  ["az","ba"],
  ["acef"],
  ["a","z"]
  ]
*/

#include "../common/common.h"

using namespace std;

// For a string s of length n, we encode its shifting feature as "s[1] - s[0], s[2] - s[1], ..., s[n - 1] - s[n - 2],"
// -- Such encoding uniquely identifies different groups
class Solution {
public:
  vector<vector<string>> groupStrings(vector<string>& strings) {
    unordered_map<string, vector<string>> groups;
    for(const string &s : strings)
      groups[encode(s)].push_back(s);
        
    vector<vector<string>> res;
    for(auto g : groups)
      res.push_back(g.second);
    return res;
  }
    
private:
  string encode(const string &s) {
    string es;
    for(int i=1; i<s.size(); ++i) {
      int diff = s[i] - s[i-1];
      if(diff < 0)
	diff += 26;  // this is important
      es += 'a' + diff + '_';
    }
        
    return es;
  }
};

// My first try -- brute force solution
class Solution {
public:
  vector<vector<string>> groupStrings(vector<string>& strings) {
    unordered_map<string,int> dict;
    for(const string &word : strings)
      dict[word] += 1;
        
    vector<vector<string>> res;
    for(auto item : dict) {
      if(item.second) {
	string word = item.first;
	vector<string> group;
	for(int i=0; i<26; ++i) {  // compute and search all shifted strings from word
	  auto it = dict.find(word);
	  if(it != dict.end()) {
	    while(it->second) {
	      group.push_back(word);
	      --it->second;
	    }
	  }
	  for(int j=0; j<word.size(); ++j) {
	    word[j] += 1;
	    if(word[j] > 'z')  // this is important
	      word[j] -= 26;
	  }
	}
	res.push_back(group);
      }
    }
        
    return res;
  }
};
