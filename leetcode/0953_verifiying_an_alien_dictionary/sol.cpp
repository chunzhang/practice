/*
Facebook/Uber/TikTok

In an alien language, surprisingly, they also use English lowercase letters, but possibly in a different order. The order of the alphabet is some permutation of lowercase letters.

Given a sequence of words written in the alien language, and the order of the alphabet, return true if and only if the given words are sorted lexicographically in this alien language.

 

Example 1:

Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
Output: true
Explanation: As 'h' comes before 'l' in this language, then the sequence is sorted.
Example 2:

Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
Output: false
Explanation: As 'd' comes after 'l' in this language, then words[0] > words[1], hence the sequence is unsorted.
Example 3:

Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
Output: false
Explanation: The first three characters "app" match, and the second string is shorter (in size.) According to lexicographical rules "apple" > "app", because 'l' > '∅', where '∅' is defined as the blank character which is less than any other character (More info).
 

Constraints:

1 <= words.length <= 100
1 <= words[i].length <= 20
order.length == 26
All characters in words[i] and order are English lowercase letters.

*/


// impl 1
class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        vector<int> od(128, -1);  // char --> int order
        for(int i=0; i<order.size(); ++i)
            od[order[i]] = i;

        for(int i=0; i<words.size()-1; ++i) {
            const string &w1 = words[i];
            const string &w2 = words[i+1];
            bool found = false;
            for(int j=0; j<min(w1.size(),w2.size()); ++j) {
                if(od[w1[j]] > od[w2[j]])
                    return false;
                else if(od[w1[j]] < od[w2[j]]) {
                    found = true;
                    break;
                }
            }
            if(!found && w1.size()>w2.size())
                return false;
        }

        return true;
    }
};

// impl 2: w/o using found flag
class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        vector<int> od(128, -1);  // char --> int order
        for(int i=0; i<order.size(); ++i)
            od[order[i]] = i;

        for(int i=0; i<words.size()-1; ++i) {
            const string &w1 = words[i];
            const string &w2 = words[i+1];
            int j = 0;
            int sz = min(w1.size(), w2.size());
            for(; j<sz; ++j) {
                if(od[w1[j]] > od[w2[j]])
                    return false;
                else if(od[w1[j]] < od[w2[j]])
                    break;
            }
            if(j==sz && w1.size()>w2.size())  // loop is not ended from break
                return false;
        }

        return true;
    }
};
