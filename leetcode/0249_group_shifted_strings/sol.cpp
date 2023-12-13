/*
  Given a string, we can "shift" each of its letter to its successive letter, for example: "abc" -> "bcd". We can keep "shifting" which forms the sequence:

  "abc" -> "bcd" -> ... -> "xyz"
  Given a list of strings which contains only lowercase alphabets, group all strings that belong to the same shifting sequence.

  For example, given: ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"], 
  A solution is:

  [
  ["abc","bcd","xyz"],
  ["az","ba"],
  ["acef"],
  ["a","z"]
  ]
*/

#include "../common/common.h"

using namespace std;


// For a string s of length n, we encode its shifting feature as "s[1] - s[0], s[2] - s[1], ..., s[n - 1] - s[n - 2]"
// -- Such encoding uniquely identifies different groups
class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        unordered_map<string,vector<string>> groups;
        for(const string &s : strings)
            groups[encode(s)].push_back(s);
        
        vector<vector<string>> res;
        for(auto &item : groups)
            res.push_back(item.second);

        return res;
    }

private:
    // encode the string: s[i]-s[i-1] ==> character a--z
    // string from the same shifted group must have the same encoding
    string encode(const string &s) {
        string code = "";  // this covers the len=1 string
        for(int i=0; i<s.size()-1; ++i) {
            code.append(1, (s[i+1]-s[i]+26)%26+'a');
        }
        return code;
    }
};


// Enumerate all shifted strings for each input string
class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        unordered_map<string,int> dict;
        for(const string &word : strings)
            dict[word] += 1;
        
        vector<vector<string>> res;
        for(auto item : dict) {
            if(item.second) {
                string word = item.first;
                vector<string> group;
                for(int i=0; i<26; ++i) {  // compute and search all shifted strings from word
                    auto it = dict.find(word);
                    if(it != dict.end()) {
                        while(it->second) {
                            group.push_back(word);
                            --it->second;
                        }
                    }
                    for(int j=0; j<word.size(); ++j) {
                        word[j] += 1;
                        if(word[j] > 'z')  // this is important
                            word[j] -= 26;
                    }
                }
                res.push_back(group);
            }
        }
        
        return res;
    }
};


// brute-force O(N^2) search
class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        vector<int> selected(strings.size(), 0);
        vector<vector<string>> res;
        for(int i=0; i<strings.size(); ++i) {
            if(selected[i])
                continue;
            vector<string> group;
            group.push_back(strings[i]);
            selected[i] = 1;
            for(int j=i+1; j<strings.size(); ++j) {
                if(selected[j])
                    continue;
                if(isShiftedString(strings[i], strings[j])) {
                    group.push_back(strings[j]);
                    selected[j] = 1;
                }
            }
            res.push_back(group);
        }
        return res;
    }

private:
    bool isShiftedString(const string &s1, const string &s2) {
        if(s1.size() != s2.size())
            return false;

        int delta = s1[0] - s2[0];
        if(delta < 0)
            delta += 26;
        for(int i=1; i<s1.size(); ++i) {
            int d = s1[i] - s2[i];
            if(d < 0)
                d += 26;
            if(d != delta)
                return false;
        }

        return true;
    }
};


// reference solution: covert each string to it's signature (e.g., the string that starts with 'a')
// -- strings from the same shifted group must have same signature
class Solution {
public:
    char shiftLetter(char letter, int shift) {
        return (letter - shift + 26) % 26 + 'a';
    }
    
    // Create a hash value
    string getHash(string& s) {
        // Calculate the number of shifts to make the first character to be 'a'
        int shift = s[0];
        string hashKey;
        
        for (char letter : s) {
            hashKey += shiftLetter(letter, shift);
        }
        
        return hashKey;
    }
    
    vector<vector<string>> groupStrings(vector<string>& strings) {
        unordered_map<string, vector<string>> mapHashToList;
        
        // Create a hash_value (hashKey) for each string and append the string
        // to the list of hash values i.e. mapHashToList["abc"] = ["abc", "bcd"]
        for (string str : strings) {
            string hashKey = getHash(str);
            mapHashToList[hashKey].push_back(str);
        }
        
        // Iterate over the map, and add the values to groups
        vector<vector<string>> groups;
        for (auto it : mapHashToList) {
            groups.push_back(it.second);
        }
        
        return groups;
    }
};
