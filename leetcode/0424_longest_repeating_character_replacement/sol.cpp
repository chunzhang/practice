/*
TikTok/Google/Facebook/Amazon/Adobe/Apple/Uber/Bloomberg/Yandex/Turing

You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most k times.

Return the length of the longest substring containing the same letter you can get after performing the above operations.

Example 1:

Input: s = "ABAB", k = 2
Output: 4
Explanation: Replace the two 'A's with two 'B's or vice versa.

Example 2:

Input: s = "AABABBA", k = 1
Output: 4
Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
There may exists other ways to achieve this answer too.
 

Constraints:

1 <= s.length <= 10^5
s consists of only uppercase English letters.
0 <= k <= s.length
*/


// sol 1: my first idea is to use two pointers (by trying all 26 possible repeating strings "AAA...", "BBB...", ..., "ZZZ...")
// time: O(26*N)
lass Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> count(128,0);
        for(char c : s)
            ++count[c];

        int ans = 0;
        for(char c='A'; c<='Z'; ++c)
            if(count[c])  // skip any unused character
                ans = max(ans, longestWithChar(s,k,c));
        return ans;
    }

private:
    // longest repeating string of character c
    int longestWithChar(const string &s, int k, char c) {
        int ans = 0;
        // use two pointers to form largest window [i,j)
        for(int i=0,j=0; j<s.size(); ) {
            // first, move j to form max [i,j)
            while(j<s.size()) {
                if(s[j] != c) {
                    if(k == 0)
                        break;
                    --k;
                }
                ++j;
            }

            ans = max(ans, j-i);

            // second, move i so k becomes positive again
            while(i<j && s[i]==c)
                ++i;
            ++i;
            ++k;
        }

        return ans;
    }
};


// sol 2: keep maxFreq of chars appeared in window [i,j]
// -- for such window, greedily flip all non-maxFreq chars will be the best we can do
// -- if j-i+1-maxFreq>k, this window is invalid so need to increment i
// -- otherwise, keep increment j
class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> count(128,0);
        int ans = 0;
        // for any valid [i,j) window
        for(int i=0,j=0,maxFreq=0; j<s.size(); ++j) {
            // now make the windows [i,j], i.e., include j
            maxFreq = max(maxFreq, ++count[s[j]]);  
            // greedy: for any window, char of maxFreq will be selected (i.e., replace other characters)
            if(j-i+1-maxFreq > k) {  // if the windows is invalid, increase i as well
                --count[s[i++]];
                // note there's no need to update maxFreq
                // 1. if s[i] is not the maxFreq char, there's no need to update from first place
                // 2. even if s[i] is the maxFreq char, remove it (i.e., increment i) does not make the window valid;
                //    i.e., j-(i+1)+1-(maxFreq-1) == j-i+1-maxFreq !!!
            }
            ans = max(ans, j-i+1);
        }
        return ans;
    }
};
