/*
Given two equal-size strings s and t. In one step you can choose any character of t and replace it with another character.

Return the minimum number of steps to make t an anagram of s.

An Anagram of a string is a string that contains the same characters with a different (or the same) ordering.

 

Example 1:

Input: s = "bab", t = "aba"
Output: 1
Explanation: Replace the first 'a' in t with b, t = "bba" which is anagram of s.
Example 2:

Input: s = "leetcode", t = "practice"
Output: 5
Explanation: Replace 'p', 'r', 'a', 'i' and 'c' from t with proper characters to make t anagram of s.
Example 3:

Input: s = "anagram", t = "mangaar"
Output: 0
Explanation: "anagram" and "mangaar" are anagrams. 
Example 4:

Input: s = "xxyyzz", t = "xxyyzz"
Output: 0
Example 5:

Input: s = "friend", t = "family"
Output: 4
 

Constraints:

1 <= s.length <= 50000
s.length == t.length
s and t contain lower-case English letters only.
*/


// count sum of different letters
// time complexity: O(N)
// space complexity: O(1)
class Solution {
public:
    int minSteps(string s, string t) {
        int counts[128];
        memset(counts, 0, sizeof(counts));
        for(int i=0; i<s.size(); ++i) {
            ++counts[s[i]];
            --counts[t[i]];
        }
        
        int ans = 0;
        for(int i='a'; i<='z'; ++i)
            ans += abs(counts[i]);
        return ans/2;
    }
};


// a sightly different impl
class Solution {
public:
    int minSteps(string s, string t) {
       
        int n = s.size(), ans = 0;
        vector<int> arr(26,0);
        for(int i = 0; i < n; i++) {
            arr[s[i] - 'a']++;
            arr[t[i] - 'a']--;
        }
        for(int i : arr) if(i > 0) ans += i;
        return ans;
    }
};
