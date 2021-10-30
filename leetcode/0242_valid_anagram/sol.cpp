/*
Given two strings s and t, return true if t is an anagram of s, and false otherwise.

 

Example 1:

Input: s = "anagram", t = "nagaram"
Output: true
Example 2:

Input: s = "rat", t = "car"
Output: false
 

Constraints:

1 <= s.length, t.length <= 5 * 104
s and t consist of lowercase English letters.
 

Follow up: What if the inputs contain Unicode characters? How would you adapt your solution to such a case?
*/


// count occurence of each letter
// time complexity: O(N)
// space complexity: O(1)
class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.size() != t.size())
            return false;
        int counts[128];
        memset(counts, 0, sizeof(counts));
        for(char c : s)
            ++counts[c];
        for(char c : t)
            if(!counts[c]--)
                return false;
        return true;
    }
};
