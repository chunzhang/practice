/*
Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.

Note that the same word in the dictionary may be reused multiple times in the segmentation.

 

Example 1:

Input: s = "leetcode", wordDict = ["leet","code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".
Example 2:

Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
Note that you are allowed to reuse a dictionary word.
Example 3:

Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false
 

Constraints:

1 <= s.length <= 300
1 <= wordDict.length <= 1000
1 <= wordDict[i].length <= 20
s and wordDict[i] consist of only lowercase English letters.
All the strings of wordDict are unique.
*/

// DP solution: O(N^3) time complexity because sub-string extraction can take O(N)
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        // Define dp(i): whether s[i:] is breakable
        unordered_set<string> dict;
        int maxLen = 0;  // max lenght among all words in dictionary
        for(const string &w : wordDict) {
            dict.insert(w);
            maxLen = max(maxLen, (int)w.size());
        }
        
        const int N = s.size();
        vector<int> dp(N+1, 0);  // whether s[i:] is a breakable
        dp[N] = 1;  // padding, reach end ==> is a valid work break
        for(int i=N-1; i>=0; --i) {
            for(int len=1; len<=maxLen&&i+len<=N; ++len) {  // emurate all possible breaks
                if(dict.find(s.substr(i,len))!=dict.end() && dp[i+len]) {  // find a valid word break
                    dp[i] = 1;
                    break;
                }
            }
        }
        
        return dp[0];
    }
};

// An interesting view of BFS
// -- In my understanding, this is explicitly visualization of the DP recursion tree
/*
Another approach is to use Breadth-First-Search. Visualize the string as a tree where each node represents the prefix upto index endend. Two nodes are connected only if the substring between the indices linked with those nodes is also a valid string which is present in the dictionary. In order to form such a tree, we start with the first character of the given string (say ss) which acts as the root of the tree being formed and find every possible substring starting with that character which is a part of the dictionary. Further, the ending index (say ii) of every such substring is pushed at the back of a queue which will be used for Breadth First Search. Now, we pop an element out from the front of the queue and perform the same process considering the string s(i+1,end)s(i+1,end) to be the original string and the popped node as the root of the tree this time. This process is continued, for all the nodes appended in the queue during the course of the process. If we are able to obtain the last element of the given string as a node (leaf) of the tree, this implies that the given string can be partitioned into substrings which are all a part of the given dictionary.

The formation of the tree can be better understood with this example:
*/
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        set<string> word_set(wordDict.begin(), wordDict.end());
        queue<int> q;
        vector<bool> visited(s.length(), false);
        q.push(0);
        while (!q.empty()) {
            int start = q.front();
            q.pop();
            if (visited[start]) {
                continue;
            }
            for (int end = start + 1; end <= s.length(); end++) {
                if (word_set.find(s.substr(start, end - start)) !=
                    word_set.end()) {
                    q.push(end);
                    if (end == s.length()) {
                        return true;
                    }
                }
            }
            visited[start] = true;
        }
        return false;
    }
};
