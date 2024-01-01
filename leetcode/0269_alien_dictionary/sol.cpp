/*
Facebook/Google/TikTok

There is a new alien language that uses the English alphabet. However, the order of the letters is unknown to you.

You are given a list of strings words from the alien language's dictionary. Now it is claimed that the strings in words are 
sorted lexicographically
 by the rules of this new language.

If this claim is incorrect, and the given arrangement of string in words cannot correspond to any order of letters, return "".

Otherwise, return a string of the unique letters in the new alien language sorted in lexicographically increasing order by the new language's rules. If there are multiple solutions, return any of them.

 

Example 1:

Input: words = ["wrt","wrf","er","ett","rftt"]
Output: "wertf"
Example 2:

Input: words = ["z","x"]
Output: "zx"
Example 3:

Input: words = ["z","x","z"]
Output: ""
Explanation: The order is invalid, so return "".
 

Constraints:

1 <= words.length <= 100
1 <= words[i].length <= 100
words[i] consists of only lowercase English letters.
*/


// improved solution for topo-sort: only build graph from words[i] and words[i+1]
class Solution {
public:
    string alienOrder(vector<string>& words) {
        unordered_map<char,int> inputs;  // in degrees
        for(const string &w : words) {
            for(char c : w)
                inputs[c] = 0;
        }

        // build directed graph: x<y ==> x-->y
        unordered_map<char,unordered_set<char>> g;
        for(int i=0; i<words.size()-1; ++i) {  // NOTE: only need to compare words[i] with words[i+1]
            string w1 = words[i];
            string w2 = words[i+1];
            bool found = false;
            for(int k=0; k<w1.size()&&k<w2.size(); ++k) {
                if(w1[k] != w2[k]) {
                    auto &loads = g[w1[k]];
                    auto it = loads.find(w2[k]);
                    if(it == loads.end()) {
                        loads.insert(w2[k]);
                        ++inputs[w2[k]];
                    }
                    found = true;
                    break;
                }
            }
            if(!found && w1.size()>w2.size()) {    // avoid invalid sorting: ["ab", "a"]
                cout << w1 << ", " << w2 << endl;
                return "";
            }
        }

        // topo sort by BFS
        queue<char> q;
        for(auto it=inputs.begin(); it!=inputs.end(); ++it) {
            if(it->second == 0)
                q.push(it->first);
        }

        string ans = "";
        while(!q.empty()) {
            char c = q.front();
            q.pop();
            ans.push_back(c);
            for(char cc : g[c]) {
                if(--inputs[cc] == 0)
                    q.push(cc);
            }
        }

        return ans.size()==inputs.size() ? ans : "";
    }
};


// topo-sort
class Solution {
public:
    string alienOrder(vector<string>& words) {
        // build directed graph: x<y ==> x-->y
        unordered_map<char,unordered_set<char>> g;
        for(int i=0; i<words.size(); ++i) {
            string w1 = words[i];
            for(int j=i+1; j<words.size(); ++j) {
                string w2 = words[j];
                bool found = false;
                for(int k=0; k<w1.size()&&k<w2.size(); ++k) {
                    if(w1[k] != w2[k]) {
                        g[w1[k]].insert(w2[k]);
                        found = true;
                        break;
                    }
                }
                if(!found && w1.size()>w2.size()) {
                     cout << w1 << ", " << w2 << endl;
                    return "";
                }
            }
        }

        // topo sort by BFS
        unordered_map<char,int> inputs;
        for(const string &w : words) {
            for(char c : w)
                inputs[c] = 0;
        }
        for(auto it=g.begin(); it!=g.end(); ++it) {
            for(char c : it->second)
                ++inputs[c];
        }

        queue<char> q;
        for(auto it=inputs.begin(); it!=inputs.end(); ++it) {
            if(it->second == 0) {
                q.push(it->first);
            }
        }

        string ans = "";
        while(!q.empty()) {
            char c = q.front();
            q.pop();
            ans.push_back(c);
            for(char cc : g[c]) {
                if(--inputs[cc] == 0)
                    q.push(cc);
            }
        }

        for(auto it=inputs.begin(); it!=inputs.end(); ++it)
            if(it->second)
                return "";

        return ans;
    }
};
