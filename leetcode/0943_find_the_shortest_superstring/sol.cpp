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
