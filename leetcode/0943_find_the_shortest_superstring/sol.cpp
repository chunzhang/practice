/*
  Given an array of strings words, return the smallest string that contains each string in words as a substring. If there are multiple valid strings of the smallest length, return any of them.

  You may assume that no string in words is a substring of another string in words.

 

  Example 1:

  Input: words = ["alex","loves","leetcode"]
  Output: "alexlovesleetcode"
  Explanation: All permutations of "alex","loves","leetcode" would also be accepted.
  Example 2:

  Input: words = ["catg","ctaagt","gcta","ttca","atgcatc"]
  Output: "gctaagttcatgcatc"
 

  Constraints:

  1 <= words.length <= 12
  1 <= words[i].length <= 20
  words[i] consists of lowercase English letters.
  All the strings of words are unique.
*/

// DP based on Hamiltonian path
// PUSH style
// O(N*N*2^N) time complexity, O(N*2^N) space complexity
class Solution {
public:
    string shortestSuperstring(vector<string>& words) {
        const int N = words.size();
        
        // cost[i][j]: cost of word[i] followed by word[j]
        vector<vector<int>> cost(N, vector<int>(N,INT_MAX/2));
        for(int i=0; i<N; ++i) {
            for(int j=0; j<N; ++j) {
                if(i == j)
                    continue;
                cost[i][j] = calCost(words[i], words[j]);
            }
        }
        
        // dp[s][j]: shortest string to reach state s that ends with words[j]
        // -- s is a bitmap of currently words, i.e., 0101==>words[0] and words[2] are used
        // dp[s|(1<<j)][j] = min{dp[s][i]+cost[i][j]}, i.e., words[j] follows word[i]  ==> PUSH style
        int NS = 0x1<<N;  // number of states
        vector<vector<int>> dp(NS, vector<int>(N, INT_MAX/2));
        vector<vector<int>> p(NS, vector<int>(N, -1));  // to remember path to build final answer
        for(int i=0; i<N; ++i) {
            dp[0x1<<i][i] = words[i].size();  // base case, only one word is used
        }
        
        // push style
        for(int s=0; s<NS; ++s) {
            for(int i=0; i<N; ++i) {
                if((s&(1<<i)) == 0)  // invalid state
                    continue;
                for(int j=0; j<N; ++j) {
                    if(s&(1<<j))  // j is already used, skip
                        continue;
                    if(dp[s|(1<<j)][j] > dp[s][i]+cost[i][j]) {
                        dp[s|(1<<j)][j] = dp[s][i]+cost[i][j];
                        p[s|(1<<j)][j] = i;
                    }
                }
            }
        }
        
        return buildAns(words, dp, p, cost);
    }
    
private:
    // cost of w1 followed by w2
    int calCost(const string &w1, const string &w2) {
        const int l1 = w1.size();
        const int l2 = w2.size();
        int overlap = min(l1,l2) - 1;  // assumption: w1 and w2 is not substring of each other
        while(overlap) {
            if(w1.substr(l1-overlap) == w2.substr(0,overlap))
                break;
            else
                --overlap;
        }
        return l2 - overlap;
    }
    
    // build answer from dp array
    string buildAns(const vector<string> &words, const vector<vector<int>> &dp, const vector<vector<int>> &p, const vector<vector<int>> &cost) {
        const int NS = dp.size();
        auto it = min_element(dp[NS-1].begin(), dp[NS-1].end());
        int s = NS - 1;  // starting state
        int j = distance(dp[NS-1].begin(), it);
        string ans;
        while(s) {
            int i = p[s][j];    // previous string
            if(i == -1)
                ans = words[j] + ans;
            else
                ans = words[j].substr(words[j].size()-cost[i][j]) + ans;
            s = s&(~(0x1<<j));  // previous state, i.e., unset j-th bit
            j = i;
        }
               
        return ans;
    }
};


// DP PULL style
class Solution {
public:
    string shortestSuperstring(vector<string>& words) {
        const int N = words.size();
        
        // cost[i][j]: cost of word[i] followed by word[j]
        vector<vector<int>> cost(N, vector<int>(N,INT_MAX/2));
        for(int i=0; i<N; ++i) {
            for(int j=0; j<N; ++j) {
                if(i == j)
                    continue;
                cost[i][j] = calCost(words[i], words[j]);
            }
        }
        
        // dp[s][j]: shortest string to reach state s that ends with words[j]
        // -- s is a bitmap of currently words, i.e., 0101==>words[0] and words[2] are used
        // dp[s][j] = min{dp[s&(~(0x1<<j))][i]+cost[i][j]}, i.e., words[j] follows word[i] ==> PULL style
        int NS = 0x1<<N;  // number of states
        vector<vector<int>> dp(NS, vector<int>(N, INT_MAX/2));
        vector<vector<int>> p(NS, vector<int>(N));  // to remember path to build final answer
        for(int i=0; i<N; ++i) {
            dp[0x1<<i][i] = words[i].size();  // base case, only one word is used
        }
        for(int s=1; s<NS; ++s) {
            for(int j=0; j<N; ++j) {
                if((s&(0x1<<j)) == 0)  // invalid, s does not contain j, but it needs to end with words[j]
                    continue;
                int ps = s & (~(0x1<<j));  // previous state, i.e., unset j-th bit; also note that ps<=s, so the bottom-up build works
                for(int i=0; i<N; ++i) {
                    if((ps&(0x1<<i)) == 0)  // invalid, ps does not contain i, but it needs to end with words[i]
                        continue;
                    if(dp[ps][i]+cost[i][j] < dp[s][j]) {
                        dp[s][j] = dp[ps][i] + cost[i][j];
                        p[s][j] = i;
                    }
                }
            }
        }
        
        return buildAns(words, dp, p, cost);
    }
    
private:
    // cost of w1 followed by w2
    int calCost(const string &w1, const string &w2) {
        const int l1 = w1.size();
        const int l2 = w2.size();
        int overlap = min(l1,l2) - 1;  // assumption: w1 and w2 is not substring of each other
        while(overlap) {
            if(w1.substr(l1-overlap) == w2.substr(0,overlap))
                break;
            else
                --overlap;
        }
        return l2 - overlap;
    }
    
    // build answer from dp array
    string buildAns(const vector<string> &words, const vector<vector<int>> &dp, const vector<vector<int>> &p, const vector<vector<int>> &cost) {
        const int NS = dp.size();
        auto it = min_element(dp[NS-1].begin(), dp[NS-1].end());
        int state = NS - 1;
        int i;
        int j = distance(dp[NS-1].begin(), it);
        stack<int> path;  // dp array store string usage in reverse order, so we use stack to reverse it back
        while(state) {
            path.push(j);
            int i = p[state][j];    // previous string
            state = state&(~(0x1<<j));  // previous state, i.e., unset j-th bit
            j = i;
        }
        
        i = path.top();
        path.pop();
        string ans = words[i];
        while(!path.empty()) {
            j = path.top();
            path.pop();
            ans += words[j].substr(words[j].size()-cost[i][j]);
            i = j;
        }
        
        return ans;
    }
};


// Brute force DFS+pruning from HuaHua
class Solution {
public:
    string shortestSuperstring(vector<string>& A) {    
        const int n = A.size();
        g_ = vector<vector<int>>(n, vector<int>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                g_[i][j] = A[j].length();
                for (int k = 1; k <= min(A[i].length(), A[j].length()); ++k)
                    if (A[i].substr(A[i].size() - k) == A[j].substr(0, k))            
                        g_[i][j] = A[j].length() - k;
            }
        vector<int> path(n);
        best_len_ = INT_MAX;
        dfs(A, 0, 0, 0, path);    
        string ans = A[best_path_[0]];
        for (int k = 1; k < best_path_.size(); ++k) {
            int i = best_path_[k - 1];
            int j = best_path_[k];
            ans += A[j].substr(A[j].length() - g_[i][j]);
        }
        return ans;
    }
private:
    vector<vector<int>> g_;
    vector<int> best_path_;
    int best_len_;
    void dfs(const vector<string>& A, int d, int used, int cur_len, vector<int>& path) {
        if (cur_len >= best_len_) return;
        if (d == A.size()) {
            best_len_ = cur_len;
            best_path_ = path;
            return;
        }
    
        for (int i = 0; i < A.size(); ++i) {
            if (used & (1 << i)) continue;      
            path[d] = i;
            dfs(A,
                d + 1, 
                used | (1 << i),
                d == 0 ? A[i].length() : cur_len + g_[path[d - 1]][i],
                path);
        }
    }
};


// official solution (in Java)
/*
We have to put the words into a row, where each word may overlap the previous word. This is because no word is contained in any word.

Also, it is sufficient to try to maximize the total overlap of the words.

Say we have put some words down in our row, ending with word A[i]. Now say we put down word A[j] as the next word, where word j hasn't been put down yet. The overlap increases by overlap(A[i], A[j]).

We can use dynamic programming to leverage this recursion. Let dp(mask, i) be the total overlap after putting some words down (represented by a bitmask mask), for which A[i] was the last word put down. Then, the key recursion is dp(mask ^ (1<<j), j) = max(overlap(A[i], A[j]) + dp(mask, i)), where the jth bit is not set in mask, and i ranges over all bits set in mask.

Of course, this only tells us what the maximum overlap is for each set of words. We also need to remember each choice along the way (ie. the specific i that made dp(mask ^ (1<<j), j) achieve a minimum) so that we can reconstruct the answer.

Algorithm

Our algorithm has 3 main components:

Precompute overlap(A[i], A[j]) for all possible i, j.
Calculate dp[mask][i], keeping track of the "parent" i for each j as described above.
Reconstruct the answer using parent information.
Please see the implementation for more details about each section.
*/
class Solution {
    public String shortestSuperstring(String[] A) {
        int N = A.length;

        // Populate overlaps
        int[][] overlaps = new int[N][N];
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) if (i != j) {
                int m = Math.min(A[i].length(), A[j].length());
                for (int k = m; k >= 0; --k)
                    if (A[i].endsWith(A[j].substring(0, k))) {
                        overlaps[i][j] = k;
                        break;
                    }
            }

        // dp[mask][i] = most overlap with mask, ending with ith element
        int[][] dp = new int[1<<N][N];
        int[][] parent = new int[1<<N][N];
        for (int mask = 0; mask < (1<<N); ++mask) {
            Arrays.fill(parent[mask], -1);

            for (int bit = 0; bit < N; ++bit) if (((mask >> bit) & 1) > 0) {
                // Let's try to find dp[mask][bit].  Previously, we had
                // a collection of items represented by pmask.
                int pmask = mask ^ (1 << bit);
                if (pmask == 0) continue;
                for (int i = 0; i < N; ++i) if (((pmask >> i) & 1) > 0) {
                    // For each bit i in pmask, calculate the value
                    // if we ended with word i, then added word 'bit'.
                    int val = dp[pmask][i] + overlaps[i][bit];
                    if (val > dp[mask][bit]) {
                        dp[mask][bit] = val;
                        parent[mask][bit] = i;
                    }
                }
            }
        }

        // # Answer will have length sum(len(A[i]) for i) - max(dp[-1])
        // Reconstruct answer, first as a sequence 'perm' representing
        // the indices of each word from left to right.

        int[] perm = new int[N];
        boolean[] seen = new boolean[N];
        int t = 0;
        int mask = (1 << N) - 1;

        // p: the last element of perm (last word written left to right)
        int p = 0;
        for (int j = 0; j < N; ++j)
            if (dp[(1<<N) - 1][j] > dp[(1<<N) - 1][p])
                p = j;

        // Follow parents down backwards path that retains maximum overlap
        while (p != -1) {
            perm[t++] = p;
            seen[p] = true;
            int p2 = parent[mask][p];
            mask ^= 1 << p;
            p = p2;
        }

        // Reverse perm
        for (int i = 0; i < t/2; ++i) {
            int v = perm[i];
            perm[i] = perm[t-1-i];
            perm[t-1-i] = v;
        }

        // Fill in remaining words not yet added
        for (int i = 0; i < N; ++i) if (!seen[i])
            perm[t++] = i;

        // Reconstruct final answer given perm
        StringBuilder ans = new StringBuilder(A[perm[0]]);
        for (int i = 1; i < N; ++i) {
            int overlap = overlaps[perm[i-1]][perm[i]];
            ans.append(A[perm[i]].substring(overlap));
        }

        return ans.toString();
    }
};
