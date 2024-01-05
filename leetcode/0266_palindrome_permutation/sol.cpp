/*
Facebook/Google/Uber

Given a string s, return true if a permutation of the string could form a 
palindrome and false otherwise.

Example 1:

Input: s = "code"
Output: false

Example 2:

Input: s = "aab"
Output: true

Example 3:

Input: s = "carerac"
Output: true
 

Constraints:

1 <= s.length <= 5000
s consists of only lowercase English letters.
*/

// at most one character with odd count
class Solution {
public:
    bool canPermutePalindrome(string s) {
        vector<int> counts(26,0);
        for(char c : s)
            ++counts[c-'a'];
        int cnt = 0;
        for(int n : counts)
            if(n%2)
                ++cnt;

        return cnt<=1;
    }
};


// bit manipulation for counting
class Solution {
public:
    bool canPermutePalindrome(string s) {
        // count by bit manipulation
        unsigned count = 0;
        for(char c : s)
            count ^= (0x1<<(c-'a'));

        // count number of 1's
        int nOnes = 0;
        for(int i=0; i<26; ++i)
            if((count>>i)&0x1)
                ++nOnes;
        return nOnes<=1;
    }
};
