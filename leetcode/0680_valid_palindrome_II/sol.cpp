/*
Given a string s, return true if the s can be palindrome after deleting at most one character from it.

 

Example 1:

Input: s = "aba"
Output: true
Example 2:

Input: s = "abca"
Output: true
Explanation: You could delete the character 'c'.
Example 3:

Input: s = "abc"
Output: false
 

Constraints:

1 <= s.length <= 105
s consists of lowercase English letters.
*/

class Solution {
public:
    bool validPalindrome(string s) {
        // after encountering an unmatched pair, try remove either one and then do a strict palindrome check
        for(int i=0,j=s.size()-1; i<=j; ++i,--j) {
            if(s[i] != s[j])
                return validPalindromeStrict(s,i,j-1) || validPalindromeStrict(s,i+1,j);
        }
        return true;
    }

    bool validPalindromeStrict(const string &s, int i, int j) {
        while(i<=j) {
            if(s[i] != s[j])
                return false;
            ++i;
            --j;
        }
        return true;
    }

};
