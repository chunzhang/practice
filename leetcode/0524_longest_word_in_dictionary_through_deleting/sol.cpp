/*
  Given a string and a string dictionary, find the longest string in the dictionary that can be formed by deleting some characters of the given string. If there are more than one possible results, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.

  Example 1:
  Input:
  s = "abpcplea", d = ["ale","apple","monkey","plea"]

  Output: 
  "apple"
  Example 2:
  Input:
  s = "abpcplea", d = ["a","b","c"]

  Output: 
  "a"
  Note:
  All the strings in the input will only contain lower-case letters.
  The size of the dictionary won't exceed 1,000.
  The length of all the strings in the input won't exceed 1,000.
*/

#include "../common/common.h"

using namespace std;

// First sorting, and then return the first matching string in sorted order search
class Solution {
public:
  string findLongestWord(string s, vector<string>& d) {
    auto comp = [](const string &s1, const string &s2) {
      return s1.size()!=s2.size() ? s1.size()>s2.size() : s1<s2;
    };
    set<string, decltype(comp)> dict(d.begin(), d.end(), comp);
        
    for(const string &sub : dict)
      if(isSub(s, sub))
	return sub;
    return "";
  }
    
private:
  // return T if sub can be formed by deleting characters from s
  bool isSub(const string &s, const string &sub) {
    int j = 0;
    for(int i=0; i<s.size()&&j<sub.size(); ++i) {
      if(s[i] == sub[j])
	++j;
    }
    return j==sub.size();
  }
};

int main()
{
  string s = "abpcplea";
  vector<string> d = {"ale","apple","monkey","plea"};
  Solution sol;
  string res = sol.findLongestWord(s, d);
  cout << "res: " << res << endl;

  return 0;
}

// Actually, no need to sort
// -- Just search each input word in a way similar to "find max"
class Solution {
public:
  string findLongestWord(string s, vector<string>& d) {
    string maxMatching = "";
    for(const string &sub : d) {
      if(isSub(s, sub)) {
	if(sub.size()>maxMatching.size() 
	   || sub.size()==maxMatching.size() && sub<maxMatching) {
	  maxMatching = sub;
	}
      }
    }
      
    return maxMatching;
  }
    
private:
  // return T if sub can be formed by deleting characters from s
  bool isSub(const string &s, const string &sub) {
    int j = 0;
    for(int i=0; i<s.size()&&j<sub.size(); ++i) {
      if(s[i] == sub[j])
	++j;
    }
    return j==sub.size();
  }
};
