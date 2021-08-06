/*
Given a string s and a dictionary of strings wordDict, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences in any order.

Note that the same word in the dictionary may be reused multiple times in the segmentation.

 

Example 1:

Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
Output: ["cats and dog","cat sand dog"]
Example 2:

Input: s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]
Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
Explanation: Note that you are allowed to reuse a dictionary word.
Example 3:

Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: []
 

Constraints:

1 <= s.length <= 20
1 <= wordDict.length <= 1000
1 <= wordDict[i].length <= 10
s and wordDict[i] consist of only lowercase English letters.
All the strings of wordDict are unique.
*/

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        // Define dp(i): whether s[i:] is breakable
        unordered_set<string> dict;
        int maxLen = 0;  // max lenght among all words in dictionary
        for(const string &w : wordDict) {
            dict.insert(w);
            maxLen = max(maxLen, (int)w.size());
        }
        
        const int N = s.size();
        vector<vector<int>> dp(N+1, vector<int>());  // whether s[i:] is a breakable; we store index to where the next word could start
        dp[N].push_back(-1);  // padding, reach end ==> is a valid work break
        for(int i=N-1; i>=0; --i) {
            for(int len=1; len<=maxLen&&i+len<=N; ++len) {  // emurate all possible breaks
                if(dict.find(s.substr(i,len))!=dict.end() && dp[i+len].size()) {  // find a valid word break
                    dp[i].push_back(i+len);  // store index to next word break
                }
            }
        }
        
        
        // DFS to collect results
        vector<string> res;
        string ans = "";
        dfs(s, dp, 0, res, ans);
        return res;
    }
    
private:
    void dfs(const string &s, const vector<vector<int>> &dp, int i, vector<string> &res, string &ans) {
        if(i == s.size()) {
            res.push_back(ans);
            return;
        }
        
        // For all next possible word break
        for(int next:dp[i]) {
            int len = next - i;
            string toAdd = (ans.empty()?"":" ") + s.substr(i, len);
            ans += toAdd;
            dfs(s, dp, i+len, res, ans);
            ans.resize(ans.size()-toAdd.size());  // recover
        }
    }
};
