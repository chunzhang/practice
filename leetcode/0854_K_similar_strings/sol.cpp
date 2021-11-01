/*
Strings s1 and s2 are k-similar (for some non-negative integer k) if we can swap the positions of two letters in s1 exactly k times so that the resulting string equals s2.

Given two anagrams s1 and s2, return the smallest k for which s1 and s2 are k-similar.

 

Example 1:

Input: s1 = "ab", s2 = "ba"
Output: 1
Example 2:

Input: s1 = "abc", s2 = "bca"
Output: 2
Example 3:

Input: s1 = "abac", s2 = "baca"
Output: 2
Example 4:

Input: s1 = "aabc", s2 = "abca"
Output: 2
 

Constraints:

1 <= s1.length <= 20
s2.length == s1.length
s1 and s2 contain only lowercase letters from the set {'a', 'b', 'c', 'd', 'e', 'f'}.
s2 is an anagram of s1.
*/


// BFS: strong pruning with greedy strategy
// time complexity: O(N!) -- loose bound
class Solution {
public:
    int kSimilarity(string s1, string s2) {
        if(s1 == s2)
            return 0;
        
        // BFS
        queue<string> q;
        unordered_set<string> visited;
        q.push(s1);
        visited.emplace(s1);
        int steps = 0;
        while(!q.empty()) {
            ++steps;
            int sz = q.size();
            while(sz--) {
                string s = q.front();
                q.pop();
                
                int i = 0;
                while(s[i]==s2[i])  // find first i s.t. s[i]!=s2[i], which is the character to be swapped
                    ++i;
                for(int j=i+1; j<s.size(); ++j) {
                    if(s[j]==s2[i] && s[j]!=s2[j]) {  // strong pruning greedily: try to swap to make i-th character matched, and does not make j-th character unmatched
                        swap(s[i], s[j]);
                        if(s == s2)
                            return steps;
                        if(!visited.count(s)) {
                            q.push(s);
                            visited.emplace(s);
                        }
                        swap(s[i],s[j]);
                    }
                }
                
            }
        }
        
        return -1;  // should not reach here
    }
};
