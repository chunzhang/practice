#include "../common/common.h"

using namespace std;

class Solution {
public:
  // Idea 2: use number of alphabets as key to identify anagrams
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;
    vector<int> counts(26, 0);
    for(auto &s : strs) {
      // counting number of 'a', 'b', ...
      for(auto &n : counts)
	n = 0;
      for(auto c : s)
	++counts[c-'a'];
      // convert counts to string to be used hash key
      ostringstream oss;
      for(auto n : counts)
	oss << n << "#";
      auto &vec = groups[oss.str()];
      vec.push_back(s);
    }

    vector<vector<string>> res;
    for(auto &elem : groups)
      res.push_back(std::move(elem.second));
    return res;
  }
};


class Solution2 {
public:
  // Idea 1: two strings are anagram if their sorted versions are equivalent
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;
    for(int i=0; i<strs.size(); ++i) {
      string s = strs[i];
      sort(s.begin(), s.end());
      auto &vec = groups[s];
      vec.push_back(strs[i]);
    }

    vector<vector<string>> res;
    for(auto it=groups.begin(); it!=groups.end(); ++it)
      res.push_back(std::move(it->second));
    
    return res;
  }
};

int main(int argc, char *argv[])
{
  vector<string> strs;
  for(int i=1; i<argc; ++i)
    strs.push_back(argv[i]);

  Solution sol;
  auto res = sol.groupAnagrams(strs);
  printMatrix(res);

  return 0;
}
