/*
Equations are given in the format A / B = k, where A and B are variables represented as strings, and k is a real number (floating point number). Given some queries, return the answers. If the answer does not exist, return -1.0.

Example:
Given a / b = 2.0, b / c = 3.0. 
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? . 
return [6.0, 0.5, -1.0, 1.0, -1.0 ].

The input is: vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries , where equations.size() == values.size(), and the values are positive. This represents the equations. Return vector<double>.

According to the example above:

equations = [ ["a", "b"], ["b", "c"] ],
values = [2.0, 3.0],
queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ]. 
The input is always valid. You may assume that evaluating the queries will result in no division by zero and there is no contradiction.
*/

#include "../common/common.h"

using namespace std;

// Solution based on union-find
class Solution {
public:
  ~Solution() {
    for(auto elem : _sets) {
      delete elem.second;
    }
  }
  
  vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
    for(int i=0; i<equations.size(); ++i) {
      string v1 = equations[i].first;
      string v2 = equations[i].second;
      double ratio = values[i];
      bool found1 = (_sets.find(v1) != _sets.end());
      bool found2 = (_sets.find(v2) != _sets.end());
      if(!found1 && !found2) {
	Node *n1 = new Node();
	Node *n2 = new Node();
	n2->_val = 1.0;
	n1->_val = n2->_val * ratio;
	n1->_parent = n2;
	_sets[v1] = n1;
	_sets[v2] = n2;
      }
      else if(!found1) {
	Node *n1 = new Node();
	Node *n2 = _sets[v2];
	n1->_val = n2->_val * ratio;
	n1->_parent = n2;
	_sets[v1] = n1;
      }
      else if(!found2) {
	Node *n1 = _sets[v1];
	Node *n2 = new Node();
	n2->_val = n1->_val / ratio;
	n2->_parent = n1;
	_sets[v2] = n2;
      }
      else {
	makeUnion(_sets[v1], _sets[v2], ratio);
      }
    }

    vector<double> res;
    for(int i=0; i<queries.size(); ++i) {
      auto it1 = _sets.find(queries[i].first);
      Node *n1 = (it1!=_sets.end() ? it1->second : nullptr);
      auto it2 = _sets.find(queries[i].second);
      Node *n2 = (it2!=_sets.end() ? it2->second : nullptr);
      if(!n1 || !n2 || findParent(n1)!=findParent(n2)) {
	res.push_back(-1.0);
      }
      else {
	res.push_back(n1->_val / n2->_val);
      }
    }
    return res;
  }

private:
  struct Node {  // This can be easily extended
    Node() : _parent(this),
	     _val(0.0)
    {
      // Dummy
    }
    Node *_parent;
    double _val;
  };

  Node *findParent(Node *n) {
    if(n->_parent == n)
      return n;
    n->_parent = findParent(n->_parent);  // path compression on the fly
    return n->_parent;
  }

  void makeUnion(Node *n1, Node *n2, /*ratio between two sets*/double setRatio) {
    Node *p1 = findParent(n1);
    Node *p2 = findParent(n2);
    if(p1 != p2) {
      // Merge set1 into set2 (i.e., p2 being the overall root)
      // -- (val1*x)/(val2)=setRatio ==> x = (val2*setRatio)/(val1)
      // -- Actually, may need to merge set2 into set1 if val1 is 0!!!
      double x = (n2->_val * setRatio) / (n1->_val);
      // now update all elements in set1
      for(auto elem : _sets) {  // should this be heavy duty, we may maintain another container for set-->elem mapping
	if(findParent(elem.second) == p1) {
	  elem.second->_val *= x;
	}
      }
      p1->_parent = p2;
    }
  }

  unordered_map<string, Node*> _sets;
    
};

// A better DFS solution -- actually, we only need to pass "ratio" instead of the absolute inferred variable value in the DFS search function
class Solution3 {
public:
  vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
    // 1. build graph
    for(int i=0; i<equations.size(); ++i) {
      string v1 = equations[i].first;
      string v2 = equations[i].second;
      double ratio = values[i];
      m_graph[v1].insert(make_pair(v2, ratio));
      if(ratio != 0)
	m_graph[v2].insert(make_pair(v1, 1/ratio));
    }

    // 2. DFS search for each query
    vector<double> res;
    for(int i=0; i<queries.size(); ++i) {
      string from = queries[i].first;
      string target = queries[i].second;
      if(m_graph.find(from) == m_graph.end()) {
	res.push_back(-1.0);
	continue;
      }

      if(from == target) {
	res.push_back(1.0);
	continue;
      }
      
      auto it = m_graph[from].begin();
      visited.clear();
      visited.insert(from);
      auto ret = search(from, target, 1.0);  // starting ratio is 1.0 as x/x=1.0
      if(ret.first)  // found path
	res.push_back(ret.second);
      else
	res.push_back(-1.0);
    }
    
    return res;    
  }

  // DFS search
  // -- recursively propagate ratio only
  // -- return True if the target is found
  pair<bool,double> search(const std::string &from, const std::string &target, double ratio) {
    for(auto neig : m_graph[from]) {
      if(visited.find(neig.first) != visited.end())
	continue;
      visited.insert(neig.first);

      if(neig.first == target) {
	return make_pair(true, ratio*neig.second);
      }
      
      auto ret = search(neig.first, target, ratio*neig.second);
      if(ret.first)
	return make_pair(true, ret.second);
    }

    return make_pair(false, 0.0);
  }


private:
  unordered_map<string, map<string,double>> m_graph;  // this is directed graph
  unordered_set<string> visited;
};

class Solution2 {
public:
  vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
    // 1. build graph
    for(int i=0; i<equations.size(); ++i) {
      string v1 = equations[i].first;
      string v2 = equations[i].second;
      double ratio = values[i];
      m_graph[v1].insert(make_pair(v2, ratio));
      if(ratio != 0)
	m_graph[v2].insert(make_pair(v1, 1/ratio));
    }

    // 2. DFS search for each query
    vector<double> res;
    for(int i=0; i<queries.size(); ++i) {
      string from = queries[i].first;
      string target = queries[i].second;
      if(m_graph.find(from) == m_graph.end()) {
	res.push_back(-1.0);
	continue;
      }

      if(from == target) {
	res.push_back(1.0);
	continue;
      }
      
      auto it = m_graph[from].begin();
      double fromVal = it->second;  // assume a value for the query starting node
      double targetVal = 0.0;
      visited.clear();
      visited.insert(from);
      if(search(from, fromVal, target, targetVal))  // found path
	res.push_back(fromVal/targetVal);
      else
	res.push_back(-1.0);
    }
    
    return res;    
  }

  // DFS search -- return True if the target is found
  bool search(const std::string &from, double fromVal, const std::string &target, double &targetVal) {
    for(auto neig : m_graph[from]) {
      if(visited.find(neig.first) != visited.end())
	continue;
      visited.insert(neig.first);
      if(neig.first == target) {
	targetVal = fromVal / neig.second;
	return true;
      }

      if(search(neig.first, fromVal/neig.second, target, targetVal))
	 return true;
    }

    return false;
  }


private:
  unordered_map<string, map<string,double>> m_graph;  // this is directed graph
  unordered_set<string> visited;
};


// This DOES NOT work as the query nodes may come from differen clusters!
class SolutionWrong {
public:
  vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {

    // 1. build graph
    for(int i=0; i<equations.size(); ++i) {
      string v1 = equations[i].first;
      string v2 = equations[i].second;
      m_graph[v1].insert(v2);
      m_graph[v2].insert(v1);
      m_equations[v1+"/"+v2] = values[i];
    }

    // 2. graph traversal
    for(auto it=m_graph.begin(); it!=m_graph.end(); ++it) {
      if(m_vars.find(it->first) != m_vars.end())
	continue;
      bfs(it->first);
    }

    // 3. compute results
    vector<double> res;
    for(int i=0; i<queries.size(); ++i) {
      auto it1 = m_vars.find(queries[i].first);
      auto it2 = m_vars.find(queries[i].second);
      if(it1==m_vars.end() || it2==m_vars.end())
	res.push_back(-1.0);
      else
	res.push_back(it1->second / it2->second);
    }
    
    return res;    
  }

  void bfs(string var) {
    queue<string> q;
    q.push(var);
    while(!q.empty()) {
      string nd = q.front();
      q.pop();
      for(auto neig : m_graph[nd]) {
	if(m_vars.find(neig) == m_vars.end()) {
	  inferVal(nd, neig);
	  q.push(neig);
	}
      }
    }
  }

  void inferVal(string v1, string v2) {
    string eq = v1 + "/" + v2;
    if(m_equations.find(eq) == m_equations.end()) {
      swap(v1, v2);
      eq = v1 + "/" + v2;
    }
    double val = m_equations[eq];
    bool found1 = (m_vars.find(v1)!=m_vars.end());
    bool found2 = (m_vars.find(v2)!=m_vars.end());
    if(!found1 && !found2) {
      m_vars[v2] = 1.0;
      m_vars[v1] = 1.0 * val;
    }
    else if(found1 && !found2) {
      m_vars[v2] = m_vars[v1] / val;
    }
    else if(!found1 && found2) {
      m_vars[v1] = m_vars[v2] * val;
    }
    else {
      // no need to recompute as the input has no contradiction
    }
  }

private:
  map<string, set<string>> m_graph;
  map<string, double> m_equations;
  map<string, double> m_vars;
};

int main()
{
  vector<pair<string, string>> equations = { {"a", "b"}, {"c", "d"}, {"b", "c"} };
  vector<double> values = {2.0, 3.0, 7.0};
  vector<pair<string, string>> queries = { {"a", "d"} /*{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}*/ };

  Solution sol;
  auto res = sol.calcEquation(equations, values, queries);
  printVector(res);

  return 0;
}
