/*
Facebook/TikTok/Bloomberg

Given a string s consisting only of characters a, b and c.

Return the number of substrings containing at least one occurrence of all these characters a, b and c.

 

Example 1:

Input: s = "abcabc"
Output: 10
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again). 
Example 2:

Input: s = "aaacb"
Output: 3
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "aaacb", "aacb" and "acb". 
Example 3:

Input: s = "abc"
Output: 1
 

Constraints:

3 <= s.length <= 5 x 10^4
s only consists of a, b or c characters.
*/


// O(N) with two pointers
class Solution {
public:
    int numberOfSubstrings(string s) {
        vector<int> count(3,0);  // counts of 'a','b','c'
        int nCh = 0; // number of unique character in current window

        // use two pointers for window [i,j)
        int ans = 0;
        int i = 0;
        int j = 0;
        for(; j<s.size(); ) {
            if(nCh == 3) {  // valid window: add answer and move left pointer
                ans += s.size()-j+1;  // all substring [i, j), [i,j+1) ... are valid
                int c = s[i++] - 'a';
                if(--count[c] == 0)
                    --nCh;
            }
            else {  // invalid window: move right pointer
                int c = s[j++] - 'a';
                if(++count[c] == 1)
                    ++nCh;
            }
        }
        
        while(nCh == 3) {  // since we exit loop when j==s.size(), don't forget remaining answers by moving left pointer
            ++ans;
            int c = s[i++] - 'a';
            if(--count[c] == 0)
                --nCh;
        }

        return ans;
    }
};


// a slightly different implementation
class Solution {
public:
    int numberOfSubstrings(string s) {
        vector<int> count(3,0);  // counts of 'a','b','c'
        int nCh = 0; // number of unique character in current window

        // use two pointers for window [i,j)
        int ans = 0;
        for(int i=0,j=0; j<=s.size(); ) {
            if(nCh == 3) {  // valid window: add answer and move left pointer
                ans += s.size()-j+1;  // all substring [i, j), [i,j+1) ... are valid
                int c = s[i++] - 'a';
                if(--count[c] == 0)
                    --nCh;
            }
            else {  // invalid window: move right pointer
                if(j < s.size()) {
                    int c = s[j] - 'a';
                    if(++count[c] == 1)
                        ++nCh;
                }
                ++j;
            }
        }
        
        return ans;
    }
};
