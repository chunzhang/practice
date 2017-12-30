/*
Given a string, find the length of the longest substring T that contains at most k distinct characters.

For example, Given s = “eceba” and k = 2,

T is "ece" which its length is 3.
*/

#include "../common/common.h"

using namespace std;

// Follow up: the interviewer may say that the string is given as a steam. In this situation, we can’t maintain a “left pointer” as the classical O(n) hashmap solution.
// The solution is to maintain characters with their "leftmost last occurrence"
// -- O(NlgK) complexity
class Solution {
public:
  int lengthOfLongestSubstringKDistinct(string s, int k) {
    if(k <= 0)
      return 0;
    int maxLen = 0;
    unordered_map<char, int> chMap;  // to keep track of left-most last occurence index of characters in the substring window
    map<int, char> lastOcc;  // to keep sorted order of last occurence (can be replaced with a priority-queue as well)
    for(int i=0, j=0; j<s.size(); ++j) {
      char c = s[j];
      auto it = chMap.find(c);  // whether the current character is already in the substring window
      if(it==chMap.end() && chMap.size()==k) {  // need to move i to fix invalid substring
	auto it2 = lastOcc.begin();  // character with "left-most last occurence" is the one to be removed from the window
	i = it2->first + 1;
	chMap.erase(it2->second);
	lastOcc.erase(it2);
      }
      else if(it != chMap.end()) {  // need to update lastOcc index of existing character as it appears again as the current character
	lastOcc.erase(it->second);
      }

      chMap[c] = j;
      lastOcc[j] = c;
      maxLen = max(maxLen, j-i+1);
    }

    return maxLen;
  }

};

class Solution2 {
public:
  int lengthOfLongestSubstringKDistinct(string s, int k) {
    int maxLen = 0;
    unordered_map<char, int> chMap;
    int count = 0;
    for(int i=0,j=0; j<s.size(); ++j) {
      if(chMap[s[j]]++ == 0)
	++count;
      
      // move i to make the string valid again
      while(count > k) {
	auto it = chMap.find(s[i++]);
	it->second -= 1;
	if(it->second == 0)
	  --count;
      }
      
      // invariant: here we have a valid substring s[i,...,j]
      maxLen = max(maxLen, j-i+1);
    }

    return maxLen;
  }
};

int main(int argc, char *argv[])
{
  string s = argv[1];
  int k = atoi(argv[2]);
  Solution sol;
  int maxLen = sol.lengthOfLongestSubstringKDistinct(s,k);
  cout << "maxLen: " << maxLen << endl;

  return 0;
}
