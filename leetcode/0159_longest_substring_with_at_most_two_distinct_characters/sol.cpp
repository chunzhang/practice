/*
  Given a string, find the length of the longest substring T that contains at most 2 distinct characters.

  For example, Given s = “eceba”,

  T is "ece" which its length is 3.
*/

#include "../common/common.h"

using namespace std;

class Solution {
public:
  int lengthOfLongestSubstringTwoDistinct(string s) {
    int maxLen = 0;
    unordered_map<char, int> chMap;
    int count = 0;
    for(int i=0,j=0; j<s.size(); ++j) {
      if(chMap[s[j]]++ == 0)
	++count;
      
      // move i to make the string valid again
      while(count > 2) {
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

// Here's one solution specific for "two distinct characters"
// -- https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/discuss/49687/
// -- Can't be extended to "k distinct characters:
/*
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        // xy....x yyyyy z
        // xy....y xxxxx z
        // i     j       k
        // i start of the 2-char substring
        // j the last position other than the last char in the substring
        // k current position to check
        // e.g. let's say current substring is as above.
        // Now we find a new char 'z' at position k. We can only keep s[k-1] and s[k] for the new substring.
        // So we need to scan from the tail until we hit a char other than s[k-1] at position j.
        // And we need to abandon all chars <= j.
        // Also, we could imagine there is always a new char after the end of string.
        // So we need to do an extra check s.size() - i.
        const int N = s.size();
        int i = 0, j = -1, max_len = 0;
        for (int k = 1; k < N; ++k) {
            if (s[k] == s[k-1]) continue;
            if (j > -1 && s[k] != s[j]) {
                max_len = max(max_len, k - i);
                i = j + 1;
            }
            j = k - 1;
        }
        return max(max_len, (int)s.size() - i);
    }
};
*/

int main(int argc, char *argv[])
{
  string s = argv[1];
  Solution sol;
  int maxLen = sol.lengthOfLongestSubstringTwoDistinct(s);
  cout << "maxLen: " << maxLen << endl;

  return 0;
}
