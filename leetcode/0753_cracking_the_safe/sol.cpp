/*
  There is a box protected by a password. The password is n digits, where each letter can be one of the first k digits 0, 1, ..., k-1.

  You can keep inputting the password, the password will automatically be matched against the last n digits entered.

  For example, assuming the password is "345", I can open it when I type "012345", but I enter a total of 6 digits.

  Please return any string of minimum length that is guaranteed to open the box after the entire string is inputted.

  Example 1:
  Input: n = 1, k = 2
  Output: "01"
  Note: "10" will be accepted too.
  Example 2:
  Input: n = 2, k = 2
  Output: "00110"
  Note: "01100", "10011", "11001" will be accepted too.
  Note:
  n will be in the range [1, 4].
  k will be in the range [1, 10].
  k^n will be at most 4096.
*/

// Theorem is that next password can always reuse previous (n-1) digits so as to get the min length -- De Bruijin sequence
// -- Thus, the min length is fixed as (k^n+n-1)
// According to this theorem, we convert this problem to a graph DFS search with backtracking
// -- Each node is a valid password (e.g., for n=2, k=2, there're four nodes 00, 01, 10, 11)
// -- Goal is to find a path that vistits each node exactly once (i.e., Hamiltonian path). There can be many such paths, but
//    any one is correct answer
// -- Since the graph is symmetric, we can start from any node (e.g., 00 for example)
// -- We backtrack whenenver visiting the node a second time
class Solution {
public:
  string crackSafe(int n, int k) {
    int tot = pow(k, n);  // total number of passwords (i.e., nodes)
    unordered_set<string> visited;
    string seq;  // result
    for(int i=0; i<n; ++i)
      seq.push_back('0');
    visited.insert(seq);
        
    // The "if" is not necessary since such path must exist, but still good to have it for "good coding style" purpose
    if(dfs(seq, visited, n, k, tot))
      return seq;
    return "";
  }
    
private:
  bool dfs(string &seq, unordered_set<string> &visited, int n, int k, int tot) {
    if(visited.size() == tot)  // find the wanted path!
      return true;
        
    string prefix = seq.substr(seq.size() - n + 1);  // last n-1 digits
    for(int i=0; i<k; ++i) {
      char c = '0' + i;
      string node = prefix + c;   // next node (i.e., password)
      if(!visited.count(node)) {  // make sure node is visited exactly once
	visited.insert(node);
	seq.push_back(c);
	if(dfs(seq, visited, n, k, tot))
	  return true;
	else {  // Backtracking
	  visited.erase(node);
	  seq.pop_back();
	}
      }
    }
        
    return false;  // cannot lead to valid solution --> return fail so can backtrack one level up
  }
};
