/*
  Write a function to generate the generalized abbreviations of a word.

  Example:
  Given word = "word", return the following list (order does not matter):
  ["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]
*/

// Bit manipulation
// Use binary representation where each bit means whether character at this index is abbreviated
class Solution {
public:
  vector<string> generateAbbreviations(string word) {
    int len = word.size();
    vector<string> ans(0x1<<len);
        
    // enumerate all binary representations for a given word size
    for(unsigned n=0; n<ans.size(); ++n) {
      int count = 0;  // number of continues 1's so far
      string abbr;
      for(int i=len-1; i>=0; --i) {
	if((n&(0x1<<i)) == 0) {  // Note == has higher predence than &
	  if(count)
	    abbr += to_string(count);
	  abbr.push_back(word[len-i-1]);
	  count = 0;
	}
	else {
	  ++count;
	}
      }
      if(count)
	abbr += to_string(count);  // for trailing ones
      ans[n] = abbr;
    }
    return ans;
  }
};

// My DFS/backtracking solution
class Solution {
public:
  vector<string> generateAbbreviations(string word) {
    vector<string> ans;
    string str;
    dfs(ans, word, str, 0, 0);
    return ans;
  }
    
private:
  void dfs(vector<string> &ans, const string &word, string &str, int count, int cur) {
    if(cur == word.size()) {
      ans.push_back(count?str+to_string(count):str);
      return;
    }
        
    // Case that abbreviates current character
    dfs(ans, word, str, count+1, cur+1);
        
    // Case that does not abbreviate current character
    int orgLen = str.size();
    if(count)
      str += to_string(count);
    str.push_back(word[cur]);
    dfs(ans, word, str, 0, cur+1);
    str.resize(orgLen);  // Backtracking
  }
};
