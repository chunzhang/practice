/*
  Given a string s, find the length of the longest substring without repeating characters.

 

  Example 1:

  Input: s = "abcabcbb"
  Output: 3
  Explanation: The answer is "abc", with the length of 3.
  Example 2:

  Input: s = "bbbbb"
  Output: 1
  Explanation: The answer is "b", with the length of 1.
  Example 3:

  Input: s = "pwwkew"
  Output: 3
  Explanation: The answer is "wke", with the length of 3.
  Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
  Example 4:

  Input: s = ""
  Output: 0
 

  Constraints:

  0 <= s.length <= 5 * 104
  s consists of English letters, digits, symbols and spaces.
*/

// two pointers
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> counts(256, 0);
        int ans = 0;
        for(int inti=0,j=0; j<s.size(); ++j) {  // for substring ends at j
            counts[s[j]]++;
            while(counts[s[j]] > 1) {
                counts[s[i++]]--;
            }
            
            ans = max(ans, j-i+1);
        }
        
        return ans;
    }
};


// two pointers: another impl
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> counts(256, 0);
        int ans = 0;
        for(int i=0,j=0; j<s.size(); ++i) {  // for substring starts at i
            for(; j<s.size()&&counts[s[j]]==0; ++j)
                counts[s[j]]++;
            ans = max(ans, j-i);
            counts[s[i]]--;
        }
        
        return ans;
    }
};

// remember index of char appeared last time
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
