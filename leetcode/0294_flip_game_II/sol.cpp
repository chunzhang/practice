/*
  You are playing the following Flip Game with your friend: Given a string that contains only these two characters: + and -, you and your friend take turns to flip two consecutive "++" into "--". The game ends when a person can no longer make a move and therefore the other person will be the winner.

  Write a function to determine if the starting player can guarantee a win.

  For example, given s = "++++", return true. The starting player can guarantee a win by flipping the middle "++" to become "+--+".

  Follow up:
  Derive your algorithm's runtime complexity.
*/

// DFS + memoization
class Solution {
public:
  bool canWin(string s) {
    unordered_map<string,bool> mem;  // memoization
    return dfs(s, mem);
  }
    
private:
  bool dfs(string &s, unordered_map<string,bool> &mem) {
    auto it = mem.find(s);
    if(it != mem.end())
      return it->second;
        
    for(int i=0; i+1<s.size(); ++i) {
      if(s[i]=='+' && s[i+1]=='+') {
	s[i] = '-';
	s[i+1] = '-';
	bool oppWin = dfs(s,mem);
	s[i] = '+';
	s[i+1] = '+';
	if(!oppWin) {
	  mem[s] = true;
	  return true;
	}
      }
    }
        
    mem[s] = false;
    return false;
  }
};
