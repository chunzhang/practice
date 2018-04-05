/*
  Given a string, find the length of the longest substring without repeating characters.

  Examples:

  Given "abcabcbb", the answer is "abc", which the length is 3.

  Given "bbbbb", the answer is "b", with the length of 1.

  Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/

class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    int maxDist = 0;
    vector<int> lastIdx(256, -1);  // most recent index when a character appear
    for(int i=0,j=0; j<s.size(); ++j) {
      char c = s[j];
      if(lastIdx[c] != -1) {  // may have repeated characters, so move i when necessary
	i = max(i, lastIdx[c]+1);  // make sure i doesn't go back
      }
      lastIdx[c] = j;
      maxDist = max(maxDist, j-i+1);
    }
        
    return maxDist;
  }
};
