/*
Apple/Facebook/Amazon/Bloomberg/Nvidia/Google/Uber/Adobe/Microsoft
  
Given a string s, sort it in decreasing order based on the frequency of the characters. The frequency of a character is the number of times it appears in the string.

Return the sorted string. If there are multiple answers, return any of them.

Example 1:

Input: s = "tree"
Output: "eert"
Explanation: 'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.

Example 2:

Input: s = "cccaaa"
Output: "aaaccc"
Explanation: Both 'c' and 'a' appear three times, so both "cccaaa" and "aaaccc" are valid answers.
Note that "cacaca" is incorrect, as the same characters must be together.

Example 3:

Input: s = "Aabb"
Output: "bbAa"
Explanation: "bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.
 
Constraints:

1 <= s.length <= 5 * 10^5
s consists of uppercase and lowercase English letters and digits.
*/

// customized sort by frequency (not using hash map)
// alternatively, one can just use vector<pair<int,int>> to sort {character, freq} pair
class Solution {
public:
    string frequencySort(string s) {
        vector<int> count(128, 0);
        for(char c : s)
            ++count[c];
        vector<char> characters(128,0);
        for(char c=0; c<characters.size(); ++c)
            characters[c] = c;
        // sort by frequency
        sort(characters.begin(), characters.end(), [&](const char c1, const char c2) {return count[c1]>count[c2];});
        string ans;
        for(char c : characters) {
            if(!count[c])
                break;
            ans += string(count[c], c);
        }
        return ans;
    }
};


// using multi-map
class Solution {
public:
    string frequencySort(string s) {
        vector<int> count(128, 0);
        for(char c : s)
            ++count[c];
        // use map for sorting
        multimap<int,char,greater<int>> sorted;
        //multimap<int,char,greater<int>> sorted( (greater<int>()) );  // also valid -- note use of additional parantheses to avoid compilier ambuiguity
        for(char c=0; c<count.size(); ++c)
            if(count[c])
                sorted.emplace(count[c],c);
        // build answer
        string ans;
        for(auto &kv : sorted)  // this is not iterator; instead using reference to avoid copy
            ans += string(kv.first, kv.second);
        return ans;
    }
};
