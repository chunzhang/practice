/*
  You are given an array of variable pairs equations and an array of real numbers values, where equations[i] = [Ai, Bi] and values[i] represent the equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a single variable.

  You are also given some queries, where queries[j] = [Cj, Dj] represents the jth query where you must find the answer for Cj / Dj = ?.

  Return the answers to all queries. If a single answer cannot be determined, return -1.0.

  Note: The input is always valid. You may assume that evaluating the queries will not result in division by zero and that there is no contradiction.

 

  Example 1:

  Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
  Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
  Explanation: 
  Given: a / b = 2.0, b / c = 3.0
  queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
  return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
  Example 2:

  Input: equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
  Output: [3.75000,0.40000,5.00000,0.20000]
  Example 3:

  Input: equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
  Output: [0.50000,2.00000,-1.00000,-1.00000]
 

  Constraints:

  1 <= equations.length <= 20
  equations[i].length == 2
  1 <= Ai.length, Bi.length <= 5
  values.length == equations.length
  0.0 < values[i] <= 20.0
  1 <= queries.length <= 20
  queries[i].length == 2
  1 <= Cj.length, Dj.length <= 5
  Ai, Bi, Cj, Dj consist of lower case English letters and digits.
*/

#include "../common/common.h"

using namespace std;

// DFS: do a fresh search for every query
// time complexity: O(E + Q*E), where E is the number of equations, Q is the number of queries
class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        for(int i=0; i<equations.size(); ++i) {
            _g[equations[i][0]].push_back({equations[i][1], values[i]});
            _g[equations[i][1]].push_back({equations[i][0], 1/values[i]});
        }
        
        vector<double> ans;
        for(auto &v : queries) {
            // DFS
            unordered_set<string> visited;
            if(_g.find(v[0])==_g.end() || _g.find(v[1])==_g.end())
                ans.push_back(-1.0);
            else{
                double res = dfs(v[0], v[1], visited, 1.0);
                ans.push_back(res);
            }
        }
        
        return ans;
    }
    
private:
    unordered_map<string, vector<pair<string,double>>> _g;  // graph
    double dfs(const string &cur, const string &dest, unordered_set<string> &visited, double val) {
        if(cur == dest)
            return val;
        
        visited.insert(cur);
        for(auto &edge : _g[cur]) {
            if(visited.find(edge.first) != visited.end())
                continue;
            double res = dfs(edge.first, dest, visited, val*edge.second);
            if(res != -1.0)
                return res;
        }
        
        return -1.0;  // not found
    }
};


// DFS: traversal only once to find connected components, and then assign value to each variable
// time complexity: O(E + Q), where E is the number of equations, Q is the number of queries
class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        for(int i=0; i<equations.size(); ++i) {
            _g[equations[i][0]].push_back({equations[i][1], values[i]});
            _g[equations[i][1]].push_back({equations[i][0], 1/values[i]});
        }

        // DFS to identify connected components and assign values
        for(auto &entry : _g) {
            if(_vals.find(entry.first) != _vals.end())  // already visited and assigned value
                continue;
            string cur = entry.first;
            dfs(cur, cur, 1.0);
        }
        
        
        vector<double> ans;
        for(auto &v : queries) {
            if(_g.find(v[0])==_g.end() || _g.find(v[1])==_g.end() || _parent[v[0]]!=_parent[v[1]])
                ans.push_back(-1.0);
            else{
                ans.push_back(_vals[v[0]]/_vals[v[1]]);
            }
        }
        
        return ans;
    }
    
private:
    unordered_map<string, vector<pair<string,double>>> _g;  // graph
    unordered_map<string, string> _parent;  // variable --> representative node of each connected component
    unordered_map<string, double> _vals;    // assigned value for each variable, also used as visited flag
    void dfs(const string &cur, const string &rep, double val) {
        _parent[cur] = rep;
        _vals[cur] = val;
        for(auto &edge : _g[cur]) {
            if(_vals.find(edge.first) != _vals.end())
                continue;
            dfs(edge.first, rep, val/edge.second);
        }
    }
    
};


// union-find
// time complexity: O(E^2+Q), i.e., we need to update variable value at each merge
class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // union-find
        for(int i=0; i<equations.size(); ++i) {
            if(_parent.find(equations[i][0]) == _parent.end())
                makeNew(equations[i][0]);
            if(_parent.find(equations[i][1]) == _parent.end())
                makeNew(equations[i][1]);
            merge(equations[i][0], equations[i][1], values[i]);
        }
        
        
        vector<double> ans;
        for(auto &v : queries) {
            if(_parent.find(v[0])==_parent.end() || _parent.find(v[1])==_parent.end() || getParent(v[0])!=getParent(v[1]))
                ans.push_back(-1.0);
            else {
                ans.push_back(_val[v[0]]/_val[v[1]]);
            }
        }
        
        return ans;
    }
    
private:
    unordered_map<string,string> _parent;
    unordered_map<string,double> _val;
    
    void makeNew(const string &var) {
        _parent[var] = var;
        _val[var] = 1.0;
    }
    
    string getParent(const string &var) {
        if(_parent[var] != var)
            _parent[var] = getParent(_parent[var]);  // path compression
        return _parent[var];
    }
    
    void merge(const string &v1, const string &v2, double ratio/*ratio=v1/v2*/) {
        const string p1 = getParent(v1);
        const string p2 = getParent(v2);
        if(p1 == p2)
            return;
        double factor = ratio*_val[v2]/_val[v1];  // this is highly important
        for(auto &entry : _val) {
            if(getParent(entry.first) == p1) {
                _val[entry.first] *= factor;
            }
        }
        _parent[p2] = p1;
    }
};


// DFS: ref impl from HuaHua
// time complexity: O(E+Q*E)
class Solution {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        // g[A][B] = k -> A / B = k
        unordered_map<string, unordered_map<string, double>> g;        
        for (int i = 0; i < equations.size(); ++i) {
            const string& A = equations[i].first;
            const string& B = equations[i].second;
            const double k = values[i];
            g[A][B] = k;
            g[B][A] = 1.0 / k;
        }
        
        vector<double> ans;
        for (const auto& pair : queries) {
            const string& X = pair.first;
            const string& Y = pair.second;
            if (!g.count(X) || !g.count(Y)) {
                ans.push_back(-1.0);
                continue;
            }
            unordered_set<string> visited;            
            ans.push_back(divide(X, Y, g, visited));
        }
        return ans;
    }
private:
    // get result of A / B
    double divide(const string& A, const string& B, 
                  unordered_map<string, unordered_map<string, double>>& g,
                  unordered_set<string>& visited) {        
        if (A == B) return 1.0;
        visited.insert(A);
        for (const auto& pair : g[A]) {
            const string& C = pair.first;
            if (visited.count(C)) continue;
            double d = divide(C, B, g, visited); // d = C / B
            // A / B = C / B * A / C
            if (d > 0) return d * g[A][C];
        }        
        return -1.0;
    }
};


// union-find: ref impl from HuaHua
// time complexity: O(E+Q)
class Solution {
public:
    vector<double> calcEquation(const vector<pair<string, string>>& equations, vector<double>& values, const vector<pair<string, string>>& queries) {
        // parents["A"] = {"B", 2.0} -> A = 2.0 * B
        // parents["B"] = {"C", 3.0} -> B = 3.0 * C
        unordered_map<string, pair<string, double>> parents;
 
        for (int i = 0; i < equations.size(); ++i) {
            const string& A = equations[i].first;
            const string& B = equations[i].second;
            const double k = values[i];
            // Neighter is in the forrest
            if (!parents.count(A) && !parents.count(B)) {
                parents[A] = {B, k};
                parents[B] = {B, 1.0};
            } else if (!parents.count(A)) {
                parents[A] = {B, k};
            } else if (!parents.count(B)) {
                parents[B] = {A, 1.0 / k};
            } else {
                auto& rA = find(A, parents);
                auto& rB = find(B, parents);      
                parents[rA.first] = {rB.first, k / rA.second * rB.second};
            }    
        }
 
        vector<double> ans;
        for (const auto& pair : queries) {
            const string& X = pair.first;
            const string& Y = pair.second;
            if (!parents.count(X) || !parents.count(Y)) {
                ans.push_back(-1.0);
                continue;
            }
            auto& rX = find(X, parents); // {rX, X / rX}
            auto& rY = find(Y, parents); // {rY, Y / rY}
            if (rX.first != rY.first)
                ans.push_back(-1.0);
            else // X / Y = (X / rX / (Y / rY))
                ans.push_back(rX.second / rY.second);
        }
        return ans;
    }
private:
    pair<string, double>& find(const string& C, unordered_map<string, pair<string, double>>& parents) {
        if (C != parents[C].first) {
            const auto& p = find(parents[C].first, parents);
            parents[C].first = p.first;
            parents[C].second *= p.second;
        }
        return parents[C];
    }
};
