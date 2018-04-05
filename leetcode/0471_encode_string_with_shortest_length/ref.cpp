// Rigorous proof: Why condition "(s+s).find(s,1) < s.size()" is equivalent to substring repetition?
// https://leetcode.com/problems/encode-string-with-shortest-length/discuss/95601/Rigorous-proof:-Why-condition-%22(s+s).find(s1)-less-s.size()%22-is-equivalent-to-substring-repetition
/*
  1.5K
  VIEWS
  8
  zzg_zzm
  zzg_zzm
  392
  Last Edit: Mar 29, 2018, 10:01 AM

  Even though many of us use the following smart condition in code to check for substring repetition, I didn’t see a rigorous proof. So here is one.

  Why condition (s+s).find(s,1) < s.size() is equivalent to substring repetition?

  Proof: Let N = s.size() and L := (s+s).find(s,1), actually we can prove that the following 2 statements are equivalent:

  0 < L < N;
  N%L == 0 and s[i] == s[i%L] is true for any i in [0, N). (which means s.substr(0,L) is the repetitive substring)
  Consider function char f(int i) { return s[i%N]; }, obviously it has a period N.

  "1 => 2": From condition 1, we have for any i in [0,N)

  s[i] == (s+s)[i+L] == s[(i+L)%N],
  which means L is also a positive period of function f. Note that N == L*(N/L)+N%L, so we have
  f(i) == f(i+N) == f(i+L*(N/L)+N%L) == f(i+N%L),
  which means N%L is also a period of f. Note that N%L < L but L := (s+s).find(s,1) is the minimum positive period of function f, so we must have N%L == 0. Note that i == L*(i/L)+i%L, so we have
  s[i] == f(i) == f(L*(i/L)+i%L) == f(i%L) == s[i%L],
  so condition 2 is obtained.
  "2=>1": If condition 2 holds, for any i in [0,N), note that N%L == 0, we have

  (s+s)[i+L] == s[(i+L)%N] == s[((i+L)%N)%L] == s[(i+L)%L] == s[i],
  which means (s+s).substr(L,N) == s, so condition 1 is obtained.
*/

// O(N^3) DP
// https://leetcode.com/problems/encode-string-with-shortest-length/discuss/95605/Easy-to-understand-C++-O(n3)-solution
class Solution {
private:
  vector<vector<string>> dp;
public:
  string collapse(string& s, int i, int j) {
    string temp = s.substr(i, j - i + 1);
    auto pos = (temp+temp).find(temp, 1);
    if (pos >= temp.size()) {
      return temp;
    }
    return to_string(temp.size()/pos) + '['+ dp[i][i+pos-1]+']';
  }

  string encode(string s) {
    int n = s.size();
    dp = vector<vector<string>>(n, vector<string>(n, ""));
    for (int step = 1; step <= n; step++) {  //* length -- only depends on subproblems with a smaller length
      for (int i = 0; i + step - 1 < n; i++) {
	int j = i + step - 1;
	dp[i][j] = s.substr(i, step);
	for (int k = i; k < j; k++) {
	  auto left = dp[i][k];
	  auto right = dp[k + 1][j];
	  if (left.size() + right.size() < dp[i][j].size()) {
	    dp[i][j] = left + right;
	  }
	}
	string replace = collapse(s, i, j);
	if (replace.size() < dp[i][j].size()) {
	  dp[i][j] = replace;
	}
      }
    }
    return dp[0][n - 1];
  }
};

// DFS + memoization
// https://leetcode.com/problems/encode-string-with-shortest-length/discuss/95617/Short-C++-DFS+MEMORIZATION-26ms
class Solution {
  int numRepetition(string &s, string &t) {
    int cnt=0,i=0;
    while(i<s.length()) {
      if(s.substr(i,t.length())!=t) break;
      cnt++;
      i+=t.length();
    }
    return cnt;
  }
  string dfs(string s, unordered_map<string,string> &m) {
    if(s.length()<5) return s;
    if(m.count(s)) return m[s];
    string res = s;
    for(int i=0;i<s.length();i++) {
      string s1 = s.substr(0,i+1);
      int cnt = numRepetition(s,s1);
      string t;
      for(int k=1;k<=cnt;k++) {
	if(k==1) t=s1+dfs(s.substr(i+1),m);
	else t = to_string(k)+"["+dfs(s1,m)+"]"+dfs(s.substr(k*s1.length()),m);
	if(t.length()<res.length()) res=t;            
      }
    }
    m[s]=res;
    return res;        
  }
public:
  string encode(string s) {
    unordered_map<string,string> m;
    return dfs(s,m);
  }
};
