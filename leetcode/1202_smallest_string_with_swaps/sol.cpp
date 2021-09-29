/*
  You are given a string s, and an array of pairs of indices in the string pairs where pairs[i] = [a, b] indicates 2 indices(0-indexed) of the string.

  You can swap the characters at any pair of indices in the given pairs any number of times.

  Return the lexicographically smallest string that s can be changed to after using the swaps.

 

  Example 1:

  Input: s = "dcab", pairs = [[0,3],[1,2]]
  Output: "bacd"
  Explaination: 
  Swap s[0] and s[3], s = "bcad"
  Swap s[1] and s[2], s = "bacd"
  Example 2:

  Input: s = "dcab", pairs = [[0,3],[1,2],[0,2]]
  Output: "abcd"
  Explaination: 
  Swap s[0] and s[3], s = "bcad"
  Swap s[0] and s[2], s = "acbd"
  Swap s[1] and s[2], s = "abcd"
  Example 3:

  Input: s = "cba", pairs = [[0,1],[1,2]]
  Output: "abc"
  Explaination: 
  Swap s[0] and s[1], s = "bca"
  Swap s[1] and s[2], s = "bac"
  Swap s[0] and s[1], s = "abc"
 

  Constraints:

  1 <= s.length <= 10^5
  0 <= pairs.length <= 10^5
  0 <= pairs[i][0], pairs[i][1] < s.length
  s only contains lower case English letters.
*/


// DFS
// time complexity: O(VlgV), i.e., worst case bounded by sorting
// -- one can use counting sort to make reduce it O(V)
// space complexity: O(V+E), i.e., to store the graph
class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        // build graph
        vector<vector<int>> g(s.size());
        for(auto &p : pairs) {
            g[p[0]].push_back(p[1]);
            g[p[1]].push_back(p[0]);
        }
        
        vector<int> visited(s.size(), 0);
        for(int cur=0; cur<s.size(); ++cur) {
            if(!visited[cur]) {
                vector<int> nodes;
                dfs(g, visited, nodes, cur);
                string sub;
                for(int idx : nodes)
                    sub.push_back(s[idx]);
                sort(sub.begin(), sub.end());
                sort(nodes.begin(), nodes.end());  // it's important to sort indexes as well
                for(int i=0; i<sub.size(); ++i)
                    s[nodes[i]] = sub[i];
            }
        }
        
        return s;
    }
    
private:
    void dfs(const vector<vector<int>> &g, vector<int> &visited, vector<int> &nodes/*result*/, int cur) {
        nodes.push_back(cur);
        visited[cur] = 1;
        for(int next : g[cur]) {
            if(!visited[next])
                dfs(g, visited, nodes, next);
        }
    }
};

// union-find
// time complexity: O(VlgV), i.e., worst case bounded by string sorting
// -- one can use counting sort to make reduce it O(V)
// space complexity: O(V)
class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        // build union
        build(s.size());
        
        // merge unions
        for(auto &p : pairs)
            merge(p[0], p[1]);
        
        // collect unions
        unordered_map<int,vector<int>> unions;
        for(int idx=0; idx<s.size(); ++idx)
            unions[getRoot(idx)].push_back(idx);
        
        // format new string
        for(auto entry : unions) {
            vector<int> &indexes = entry.second;
            string sub;
            for(int idx : indexes)
                sub.push_back(s[idx]);
            sort(sub.begin(), sub.end());
            // sort(indexes.begin(), indexes.end());  // by construction, it is already sorted
            for(int i=0; i<sub.size(); ++i)
                s[indexes[i]] = sub[i];
        }
        
        return s;
    }
    
private:
    vector<int> _parent;
    vector<int> _rank;
    void build(const int N) {
        _parent.resize(N, 0);
        for(int i=0; i<N; ++i)
            _parent[i] = i;
        _rank.resize(N, 1);
    }
    
    int getRoot(int idx) {
        if(_parent[idx] != idx)
            _parent[idx] = getRoot(_parent[idx]);
        return _parent[idx];
    }
    
    void merge(int idx1, int idx2) {
        int r1 = getRoot(idx1);
        int r2 = getRoot(idx2);
        if(r1 == r2)
            return;
        
        if(_rank[r1] < _rank[r2])
            _parent[r1] = r2;
        else if(_rank[r1] > _rank[r2])
            _parent[r2] = r1;
        else {
            _parent[r2] = r1;
            ++_rank[r1];
        }
    }
};


// ref from HuaHua -- DFS
class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        vector<vector<int>> g(s.length());
        for (const auto& e : pairs) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
 
        unordered_set<int> seen;
        vector<int> idx;
        string tmp;
        function<void(int)> dfs = [&](int cur) {
            if (seen.count(cur)) return;
            seen.insert(cur);
            idx.push_back(cur);
            tmp += s[cur];
            for (int nxt : g[cur]) dfs(nxt);
        };
 
        for (int i = 0; i < s.length(); ++i) {
            if (seen.count(i)) continue;
            idx.clear();
            tmp.clear();
            dfs(i);
            sort(begin(tmp), end(tmp));
            sort(begin(idx), end(idx));      
            for (int k = 0; k < idx.size(); ++k)
                s[idx[k]] = tmp[k];
        }
        return s;
    }
};


// ref from HuaHua -- union-find
class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.length();
        vector<int> p(n);    
        iota(begin(p), end(p), 0); // p = {0, 1, 2, ... n - 1}
    
        function<int(int)> find = [&](int x) {
            return p[x] == x ? x : p[x] = find(p[x]);
        };        
    
        for (const auto& e : pairs)
            p[find(e[0])] = find(e[1]); // union
    
        vector<vector<int>> idx(n);
        vector<string> ss(n);
    
        for (int i = 0; i < s.length(); ++i) {
            int id = find(i);      
            idx[id].push_back(i); // already sorted
            ss[id].push_back(s[i]);
        }
    
        for (int i = 0; i < n; ++i) {      
            sort(begin(ss[i]), end(ss[i]));
            for (int k = 0; k < idx[i].size(); ++k)
                s[idx[i][k]] = ss[i][k];
        }
    
        return s;
    }
};
