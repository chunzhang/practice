/*
We can represent a sentence as an array of words, for example, the sentence "I am happy with leetcode" can be represented as arr = ["I","am",happy","with","leetcode"].

Given two sentences sentence1 and sentence2 each represented as a string array and given an array of string pairs similarPairs where similarPairs[i] = [xi, yi] indicates that the two words xi and yi are similar.

Return true if sentence1 and sentence2 are similar, or false if they are not similar.

Two sentences are similar if:

They have the same length (i.e., the same number of words)
sentence1[i] and sentence2[i] are similar.
Notice that a word is always similar to itself, also notice that the similarity relation is transitive. For example, if the words a and b are similar, and the words b and c are similar, then a and c are similar.

 

Example 1:

Input: sentence1 = ["great","acting","skills"], sentence2 = ["fine","drama","talent"], similarPairs = [["great","good"],["fine","good"],["drama","acting"],["skills","talent"]]
Output: true
Explanation: The two sentences have the same length and each word i of sentence1 is also similar to the corresponding word in sentence2.
Example 2:

Input: sentence1 = ["I","love","leetcode"], sentence2 = ["I","love","onepiece"], similarPairs = [["manga","onepiece"],["platform","anime"],["leetcode","platform"],["anime","manga"]]
Output: true
Explanation: "leetcode" --> "platform" --> "anime" --> "manga" --> "onepiece".
Since "leetcode is similar to "onepiece" and the first two words are the same, the two sentences are similar.
Example 3:

Input: sentence1 = ["I","love","leetcode"], sentence2 = ["I","love","onepiece"], similarPairs = [["manga","hunterXhunter"],["platform","anime"],["leetcode","platform"],["anime","manga"]]
Output: false
Explanation: "leetcode" is not similar to "onepiece".
 

Constraints:

1 <= sentence1.length, sentence2.length <= 1000
1 <= sentence1[i].length, sentence2[i].length <= 20
sentence1[i] and sentence2[i] consist of lower-case and upper-case English letters.
0 <= similarPairs.length <= 2000
similarPairs[i].length == 2
1 <= xi.length, yi.length <= 20
xi and yi consist of English letters.
*/

#include "../common/common.h"

using namespace std;


// union-find: use unordered_map to keep track of parent
class Solution {
public:
    bool areSentencesSimilarTwo(vector<string>& sentence1, vector<string>& sentence2, vector<vector<string>>& similarPairs) {
        if(sentence1.size() != sentence2.size())
            return false;
        
        // union find
        unordered_map<string,string> _parent;
        function<string(const string&)> getParent = [&](const string &s) {
            auto it = _parent.find(s);
            if(it == _parent.end()) {
                _parent[s] = s;
                return s;
            }

            if(it->second != s) {
                it->second = getParent(it->second);
            }
            return _parent[s];
        };
        function<void(const string&,const string&)> merge = [&](const string &s1, const string &s2) {
            _parent[getParent(s1)] = getParent(s2);
        };
        
        for(auto &v : similarPairs)
            merge(v[0], v[1]);
        for(int i=0; i<sentence1.size(); ++i) {
            if(sentence1[i]!=sentence2[i] && getParent(sentence1[i])!=getParent(sentence2[i]))
                return false;
        }
        return true;
    }    
};

// union-find: use vector<int> to keep track of parent
class Solution {
public:
    bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<pair<string, string>> pairs) {
        if(words1.size() != words2.size())
            return false;

        // 1. make unions
        _sets.resize(pairs.size()*2);
        for(int i=0; i<_sets.size(); ++i)
            _sets[i] = i;
    
        int id = 0;
        for(int i=0; i<pairs.size(); ++i) {
            string w1 = pairs[i].first;
            string w2 = pairs[i].second;
            if(_words.find(w1) == _words.end()) {
                _words[w1] = id++;
            }
            if(_words.find(w2) == _words.end()) {
                _words[w2] = id++;
            }
            makeUnion(_words[w1], _words[w2]);
        }

        // 2. checking
        for(int i=0; i<words1.size(); ++i) {
            string w1 = words1[i];
            string w2 = words2[i];
            if(w1 == w2)
                continue;
            if(_words.find(w1)==_words.end() || _words.find(w2)==_words.end())
                return false;
            if(findParent(_words[w1]) != findParent(_words[w2]))
                return false;
        }

        return true;
    }

private:
    int findParent(int id) {
        if(_sets[id] != id)
            _sets[id] = findParent(_sets[id]);  // path compression on the fly
        return _sets[id];
    }

    void makeUnion(int id1, int id2) {
        _sets[findParent(id1)] = findParent(id2);
    }
  
    unordered_map<string, int> _words;  // each word in the "pairs" is assigned a unique ID
    vector<int> _sets;  // parent of each word ID, -1 means the word doesn't exist
};

// The DFS based solution
class Solution {
public:
    bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<pair<string, string>> pairs) {
        if(words1.size() != words2.size())
            return false;
    
        // 1. build graph
        for(int i=0; i<pairs.size(); ++i) {
            _graph[pairs[i].first].insert(pairs[i].second);
            _graph[pairs[i].second].insert(pairs[i].first);
        }

        // 2. checking
        for(int i=0; i<words1.size(); ++i) {
            if(words1[i] == words2[i])
                continue;
            if(_graph.find(words1[i])==_graph.end() || _graph.find(words2[i])==_graph.end())
                return false;

            _visited.clear();
            if(!dfs(words1[i], words2[i]))
                return false;
        }

        return true;
    }

    bool dfs(const string &from, const string &target) {
        _visited.insert(from);
        for(const string &neig : _graph[from]) {
            if(_visited.count(neig))
                continue;
            if(neig==target || dfs(neig,target))
                return true;
        }
        return false;
    }

private:
    unordered_map<string, set<string>> _graph;
    unordered_set<string> _visited;
};


// ref impl from HuaHua: DFS with coloring
class Solution {
public:
    bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<pair<string, string>>& pairs) {
        if (words1.size() != words2.size()) return false;
        
        g_.clear();
        ids_.clear();
        
        for (const auto& p : pairs) {
            g_[p.first].insert(p.second);
            g_[p.second].insert(p.first);
        }        
        
        int id = 0;
        
        for (const auto& p : pairs) {
            if(!ids_.count(p.first)) dfs(p.first, ++id);
            if(!ids_.count(p.second)) dfs(p.second, ++id);
        }
        
        for (int i = 0; i < words1.size(); ++i) {
            if (words1[i] == words2[i]) continue;
            auto it1 = ids_.find(words1[i]);
            auto it2 = ids_.find(words2[i]);
            if (it1 == ids_.end() || it2 == ids_.end()) return false;
            if (it1->second != it2->second) return false;
        }
        
        return true;
    }
private:
    bool dfs(const string& curr, int id) {
        ids_[curr] = id;  // assign color
        for (const auto& next : g_[curr]) {
            if (ids_.count(next)) continue;
            if (dfs(next, id)) return true;
        }
        return false;
    }
    
    unordered_map<string, int> ids_;
    unordered_map<string, unordered_set<string>> g_;
};
