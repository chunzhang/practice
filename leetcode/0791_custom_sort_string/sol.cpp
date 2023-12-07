/*
You are given two strings order and s. All the characters of order are unique and were sorted in some custom order previously.

Permute the characters of s so that they match the order that order was sorted. More specifically, if a character x occurs before a character y in order, then x should occur before y in the permuted string.

Return any permutation of s that satisfies this property.

 

Example 1:

Input: order = "cba", s = "abcd"
Output: "cbad"
Explanation: 
"a", "b", "c" appear in order, so the order of "a", "b", "c" should be "c", "b", and "a". 
Since "d" does not appear in order, it can be at any position in the returned string. "dcba", "cdba", "cbda" are also valid outputs.
Example 2:

Input: order = "cbafg", s = "abcd"
Output: "cbad"
 

Constraints:

1 <= order.length <= 26
1 <= s.length <= 200
order and s consist of lowercase English letters.
All the characters of order are unique.
*/


// best solution: counting sort
class Solution {
public:
    string customSortString(string order, string s) {
        // use counting sort
        vector<int> counts(256, 0);
        for(char c : s)
          ++counts[c];

        string res;
        for(char c : order) {
          res.append(counts[c], c);
          counts[c] = 0;
        }

        for(char c='a'; c<='z'; ++c)
          res.append(counts[c], c);

        return res;
    }
};


// customized sorting with lambda
class Solution {
public:
    string customSortString(string order, string s) {
        vector<int> od(256,-1);
        for(int i=0; i<order.size(); ++i)
            od[order[i]] = i;

        sort(s.begin(), s.end(), [&](char c1, char c2) {
            return od[c1] < od[c2];
        });

        return s;
    }
};


// brute force solution
class Solution {
public:
    string customSortString(string order, string s) {
        // brute-force solution O(N*M)
        string res;
        for(char c1 : order)
          for(char c2 : s)
            if(c1 == c2)
              res.push_back(c1);

        for(char c : s)
          if(order.find(c) == string::npos)
            res.push_back(c);

        return res;
    }
};
