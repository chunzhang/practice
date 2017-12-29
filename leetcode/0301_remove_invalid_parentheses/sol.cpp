#include "../common/common.h"

using namespace std;

// This is the less efficient BFS solution
class Solution {
public:
  vector<string> removeInvalidParentheses(string s) {
    vector<string> res;
    set<string> curLv;
    curLv.insert(s);
    while(!curLv.empty()) {
      bool found = false;
      set<string> nextLv;
      for(const string& ns : curLv) {
	if(isValid(ns)) {
	  found = true;
	  res.push_back(ns);
	}

	if(!found) {
	  for(int i=0; i<ns.size(); ++i) {
	    if(ns[i]=='(' || ns[i]==')')
	      nextLv.insert(ns.substr(0, i)+ns.substr(i+1));
	  }
	}
      }
      if(found)
	break;
      curLv.swap(nextLv);
    }

    return res;
  }

  bool isValid(const string &s) {  // note empty string is also valid
    int count = 0;
    for(char c : s) {
      if(c == '(')
	++count;
      else if(c == ')')
	--count;
      if(count < 0)
	break;
    }
    return count==0;
  }
};

// This is the DFS solution
// https://leetcode.com/problems/remove-invalid-parentheses/discuss/75027/
class Solution2 {
public:
  vector<string> removeInvalidParentheses(string s) {
    vector<string> results;
    search(results, s, 0, 0, 0, '(', ')');
    return results;
  }

  void search(vector<string> &results, const string &s, int count, int cur, int start, char left, char right) {
    for( ; cur<s.size(); ++cur) {
      if(s[cur] == left)
	++count;
      else if(s[cur] == right)
	--count;

      if(count < 0) {  // found invalid matching
	/*	while(s[start] != right)
	  ++start;
	*/
	for(int j=start; j<=cur; ++j) {
	  if(s[j]==right && (j==start || s[j-1]!=s[j])) {  // use same technique as "combination sum II" to remove duplicates!!!
	    string ns = s.substr(0,j) + s.substr(j+1);
	    search(results, ns, count+1, cur, j, left, right);
	  }
	}
	return;  // current s is not valid, so simply exit
      }
    }

    if(count > 0) {  // only possible after first round (i.e., left to right scan)
      string ns = s;
      reverse(ns.begin(), ns.end());
      search(results, ns, 0, 0, 0, ')', '(');
    }
    else if(count == 0) {  // found valid solution
      string ns = s;
      if(left == ')')  // becomes valid after second round (i.e., right to left scan)
	reverse(ns.begin(), ns.end());
      results.push_back(ns);
    }
  }
};

int main(int argc, char *argv[])
{
  string s = argv[1];
  cout << "input: " << s << endl;
  Solution sol;
  auto results = sol.removeInvalidParentheses(s);
  cout << "output: " << results.size() << endl;
  printVector(results);

  return 0;
}
