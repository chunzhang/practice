// De Bruijn sequence C++
// https://leetcode.com/problems/cracking-the-safe/discuss/110260/De-Bruijn-sequence-C++
/*
  From wiki: De Bruijn sequence
  "a de Bruijn sequence of order n on a size-k alphabet A is a cyclic sequence in which every possible length-n string on A occurs exactly once as a substring".

  The De Brujin sequence has length k^n. See the proof from the link.

  “The de Bruijn sequences can be constructed by taking a Hamiltonian path of an n-dimensional de Bruijn graph over k symbols (or equivalently, an Eulerian cycle of an (n − 1)-dimensional de Bruijn graph).”

  Use Hierholzer’s Algorithm to construct the Eulerian circuit.
  I read @dietpepsi 's post about this problem.
*/
class Solution {
  int n, k, v;
  vector<vector<bool> > visited;
  string sequence;
public:
  string crackSafe(int n, int k) {
    if (k == 1) return string(n, '0');
    this->n = n;
    this->k = k;
    v = 1;
    for (int i = 0; i < n -1; ++i) v *= k;
    visited.resize(v, vector<bool>(k, false));
    dfs(0);
    return sequence + sequence.substr(0, n - 1);
  }
    
  void dfs(int u) {
    for (int i = 0; i < k; ++i) {
      if (!visited[u][i]) {
	visited[u][i] = true;
	dfs((u * k + i) % v);
	sequence.push_back('0' + i);
      }
    }
  }
};

// C++, greedy loop from backward with explaination
// https://leetcode.com/problems/cracking-the-safe/discuss/112966/C++-greedy-loop-from-backward-with-explaination
/*
  Taking n = 2,k= 2 as example, we start with “00”, let string prev = last n-1 digits (prev = ‘0’), and create an new string by appending a new digit from k-1 to 0 respectively. in this case we first check string ‘01’.
*/
string crackSafe(int n, int k) {
  string ans = string(n, '0');
  unordered_set<string> visited;
  visited.insert(ans);
        
  for(int i = 0;i<pow(k,n);i++){
    string prev = ans.substr(ans.size()-n+1,n-1);
    for(int j = k-1;j>=0;j--){
      string now = prev + to_string(j);
      if(!visited.count(now)){
	visited.insert(now);
	ans += to_string(j);
	break;
      }
    }
  }
  return ans;
}
