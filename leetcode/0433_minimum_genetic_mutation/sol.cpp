/*
  A gene string can be represented by an 8-character long string, with choices from 'A', 'C', 'G', and 'T'.

  Suppose we need to investigate a mutation from a gene string start to a gene string end where one mutation is defined as one single character changed in the gene string.

  For example, "AACCGGTT" --> "AACCGGTA" is one mutation.
  There is also a gene bank bank that records all the valid gene mutations. A gene must be in bank to make it a valid gene string.

  Given the two gene strings start and end and the gene bank bank, return the minimum number of mutations needed to mutate from start to end. If there is no such a mutation, return -1.

  Note that the starting point is assumed to be valid, so it might not be included in the bank.

 

  Example 1:

  Input: start = "AACCGGTT", end = "AACCGGTA", bank = ["AACCGGTA"]
  Output: 1
  Example 2:

  Input: start = "AACCGGTT", end = "AAACGGTA", bank = ["AACCGGTA","AACCGCTA","AAACGGTA"]
  Output: 2
  Example 3:

  Input: start = "AAAAACCC", end = "AACCCCCC", bank = ["AAAACCCC","AAACCCCC","AACCCCCC"]
  Output: 3
 

  Constraints:

  start.length == 8
  end.length == 8
  0 <= bank.length <= 10
  bank[i].length == 8
  start, end, and bank[i] consist of only the characters ['A', 'C', 'G', 'T'].
*/

// BFS
// time and space complexity: O(N^2): for building graph
class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        if(start == end)
            return 0;
        
        // build graph
        bank.push_back(start);
        vector<vector<int>> g(bank.size());
        int from = bank.size() - 1;
        int to = -1;
        for(int i=0; i<bank.size()-1; ++i) {
            if(bank[i] == end)
                to = i;
            for(int j=i+1; j<bank.size(); ++j) {
                int diff = 0;
                for(int k=0; k<8; ++k)
                    if(bank[i][k] != bank[j][k])
                        ++diff;
                if(diff == 1) {
                    g[i].push_back(j);
                    g[j].push_back(i);
                }
            }
        }
        
        // BFS
        int level = 0;
        vector<int> visited(bank.size(), 0);
        queue<int> q;
        q.push(from);
        visited[from] = 1;
        while(!q.empty()) {
            int sz = q.size();
            while(sz--) {
                int node = q.front();
                q.pop();
                if(node == to)
                    return level;
                for(int nei : g[node])
                    if(!visited[nei]) {
                        q.push(nei);
                        visited[nei] = 1;
                    }
            }
            ++level;
        }
        
        return -1;  // no mutation path
    }
};


// BFS w/o building graph (ref impl from HuaHua)
// time complexity: O(N^2)
// space complexity: O(N)
class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {    
        queue<string> q;
        q.push(start);
    
        unordered_set<string> visited;
        visited.insert(start);
    
        int mutations = 0;
        while (!q.empty()) {
            size_t size = q.size();
            while (size--) {
                string curr = std::move(q.front()); q.pop();
                if (curr == end) return mutations;
                for (const string& gene : bank) {
                    if (visited.count(gene) || !validMutation(curr, gene)) continue;
                    visited.insert(gene);
                    q.push(gene);
                }
            }
            ++mutations;
        }    
        return -1;
    }
private:
    bool validMutation(const string& s1, const string& s2) {
        int count = 0;
        for (int i = 0; i < s1.length(); ++i)
            if (s1[i] != s2[i] && count++) return false;
        return true;
    }
};
