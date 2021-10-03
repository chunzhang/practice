/*
Two strings X and Y are similar if we can swap two letters (in different positions) of X, so that it equals Y. Also two strings X and Y are similar if they are equal.

For example, "tars" and "rats" are similar (swapping at positions 0 and 2), and "rats" and "arts" are similar, but "star" is not similar to "tars", "rats", or "arts".

Together, these form two connected groups by similarity: {"tars", "rats", "arts"} and {"star"}.  Notice that "tars" and "arts" are in the same group even though they are not similar.  Formally, each group is such that a word is in the group if and only if it is similar to at least one other word in the group.

We are given a list strs of strings where every string in strs is an anagram of every other string in strs. How many groups are there?

 

Example 1:

Input: strs = ["tars","rats","arts","star"]
Output: 2
Example 2:

Input: strs = ["omv","ovm"]
Output: 1
 

Constraints:

1 <= strs.length <= 300
1 <= strs[i].length <= 300
strs[i] consists of lowercase letters only.
All words in strs have the same length and are anagrams of each other.
*/


// DFS -- find connected components
// time complexity: O(L*N^2)+O(N+E), where L is string length, N is number of strings, and E is number of edgies (worst case =O(N^2))
class Solution {
public:
    int numSimilarGroups(vector<string>& strs) {
        vector<vector<int>> g(strs.size());
        
        // build graph
        for(int i=0; i<strs.size()-1; ++i) {
            for(int j=i+1; j<strs.size(); ++j) {
                if(isSimilar(strs[i], strs[j])) {
                    g[i].push_back(j);
                    g[j].push_back(i);
                }
            }
        }
        
        // DFS
        int ans = 0;
        vector<short> visited(strs.size(), 0);
        for(int i=0; i<strs.size(); ++i) {
            if(!visited[i]) {
                ++ans;
                dfs(g, visited, i);
            }
        }
        
        return ans;
    }
    
private:
    bool isSimilar(const string &s1, const string &s2) {
        int count = 0;
        for(int i=0; i<s1.size(); ++i)
            if(s1[i] != s2[i])
                if(++count > 2)
                    return false;
        return true;
    }
    
    void dfs(const vector<vector<int>> &g, vector<short> &visited, int cur) {
        visited[cur] = 1;
        for(int next : g[cur]) {
            if(!visited[next])
                dfs(g, visited, next);
        }
    }
};


// union-find
// time complexity: O(L*N^2), where L is string length, N is number of strings
class Solution {
public:
    int numSimilarGroups(vector<string>& strs) {
        // union-find
        build(strs.size());
        
        // build graph
        for(int i=0; i<strs.size()-1; ++i) {
            for(int j=i+1; j<strs.size(); ++j) {
                if(isSimilar(strs[i], strs[j])) {
                    merge(i, j);
                }
            }
        }
        
        return _size;
    }
    
private:
    bool isSimilar(const string &s1, const string &s2) {
        int count = 0;
        for(int i=0; i<s1.size(); ++i)
            if(s1[i] != s2[i])
                if(++count > 2)
                    return false;
        return true;
    }
    
    // for union-find
    vector<int> _parent;
    vector<int> _rank;
    int _size;
    void build(int size) {
        _parent = vector<int>(size, 0);
        for(int i=0; i<size; ++i)
            _parent[i] = i;
        _rank = vector<int>(size, 1);
        _size = size;
    }
    
    int getParent(int n) {
        if(_parent[n] != n)
            _parent[n] = getParent(_parent[n]);
        return _parent[n];
    }
    
    void merge(int n1, int n2) {
        int p1 = getParent(n1);
        int p2 = getParent(n2);
        if(p1 == p2)
            return;
        
        if(_rank[p1] < _rank[p2])
            _parent[p1] = p2;
        else if(_rank[p1] > _rank[p2])
            _parent[p2] = p1;
        else {
            _parent[p2] = p1;
            ++_rank[p1];
        }
        
        --_size;
    }

};
