/*
Facebook/Amazon/Adobe
  
Given two strings ransomNote and magazine, return true if ransomNote can be constructed by using the letters from magazine and false otherwise.

Each letter in magazine can only be used once in ransomNote.

Example 1:

Input: ransomNote = "a", magazine = "b"
Output: false

Example 2:

Input: ransomNote = "aa", magazine = "ab"
Output: false

Example 3:

Input: ransomNote = "aa", magazine = "aab"
Output: true
 

Constraints:

1 <= ransomNote.length, magazine.length <= 10^5
ransomNote and magazine consist of lowercase English letters.
*/

// counting characters: O(N)
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        vector<int> count(128,0);
        for(char c : magazine)
            ++count[c];
        for(char c : ransomNote)
            if(count[c]-- == 0)
                return false;
        return true;
    }
};
