/*
A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:

Every adjacent pair of words differs by a single letter.
Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
sk == endWord
Given two words, beginWord and endWord, and a dictionary wordList, return all the shortest transformation sequences from beginWord to endWord, or an empty list if no such sequence exists. Each sequence should be returned as a list of the words [beginWord, s1, s2, ..., sk].

 

Example 1:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: [["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]
Explanation: There are 2 shortest transformation sequences:
"hit" -> "hot" -> "dot" -> "dog" -> "cog"
"hit" -> "hot" -> "lot" -> "log" -> "cog"
Example 2:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: []
Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.
 

Constraints:

1 <= beginWord.length <= 5
endWord.length == beginWord.length
1 <= wordList.length <= 1000
wordList[i].length == beginWord.length
beginWord, endWord, and wordList[i] consist of lowercase English letters.
beginWord != endWord
All the words in wordList are unique.
*/

// BFS: one-directional w/o build graph
// -- in the end, build answer with DFS
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        // one-directional BFS w/o build the graph
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if(!dict.count(endWord))
            return {};
        
        // one-directional BFS
        unordered_map<string, vector<string>> p;  // we need to populate the parent of each word to build full path
        unordered_set<string> q;  // current level
        q.emplace(beginWord);
        dict.erase(beginWord);
        bool found = false;
        while(!q.empty() && !found) {
            unordered_set<string> nq;  // next level
            for(const string &cur : q) {
                string word = cur;
                // emunerate all variants of current word
                for(int i=0; i<word.size(); ++i) {
                    char c = word[i];
                    for(char c2='a'; c2<='z'; ++c2) {
                        word[i] = c2;
                        if(word == endWord)
                            found = true;
                        if(nq.count(word)) {  // word is found from current level --> record path
                            p[word].push_back(cur);
                        }
                        if(dict.count(word)) {  // word is found for the first time
                            nq.emplace(word);
                            dict.erase(word);
                            p[word].push_back(cur);
                        }
                    }
                    word[i] = c;
                }
            }
            q.swap(nq);
        }
        
        vector<vector<string>> ans;
        if(!found)
            return ans;
        vector<string> path;
        buildPath(p, endWord, path, ans);
        return ans;
    }
    
private:
    void buildPath(const unordered_map<string,vector<string>> &p, const string &cur, vector<string> &path, vector<vector<string>> &ans) {
        path.emplace_back(cur);
        auto it = p.find(cur);
        if(it == p.end())
            ans.emplace_back(path.rbegin(), path.rend());
        else 
            for(const string &next : it->second)
                 buildPath(p, next, path, ans);
        path.pop_back();
    }
};


// BFS: bi-directional w/o build graph
// -- need to keep track of search direction
// -- in the end, build answer with DFS
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        // bi-directional BFS w/o build the graph
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if(!dict.count(endWord))
            return {};
        
        // bi-directional BFS
        unordered_map<string, vector<string>> p;  // we need to populate the parent of each word to build full path
        unordered_set<string> q1, q2;  // current level
        q1.emplace(beginWord);
        dict.erase(beginWord);
        q2.emplace(endWord);
        dict.erase(endWord);
        bool found = false;
        int dir = 0;  // 0-->expand start to end, 1-->expand end to start
        while(!q1.empty() && !q2.empty() && !found) {
            if(q1.size() > q2.size()) {
                q1.swap(q2);
                dir ^= 0x1;  // flip direction
            }
            
            unordered_set<string> nq;  // next level
            for(const string &cur : q1) {
                string word = cur;
                // emunerate all variants of current word
                for(int i=0; i<word.size(); ++i) {
                    char c = word[i];
                    for(char c2='a'; c2<='z'; ++c2) {
                        word[i] = c2;
                        bool foundPath = q2.count(word);  // found valid path
                        bool discoverFromCurLevel = nq.count(word);   // word is discovered from current level
                        bool discoverFirstTime = dict.count(word);  // word is discovered for the first time
                        if(foundPath || discoverFromCurLevel || discoverFirstTime) {
                            if(foundPath)
                                found = true;
                            if(discoverFirstTime) {
                                nq.emplace(word);
                                dict.erase(word);
                            }
                            
                            // record parent
                            if(dir == 0)
                                p[word].push_back(cur);
                            else
                                p[cur].push_back(word);
                        }                        
                    }
                    word[i] = c;
                }
            }
            q1.swap(nq);
        }
        
        vector<vector<string>> ans;
        if(!found)
            return ans;
        vector<string> path;
        buildPath(p, beginWord, endWord, path, ans);
        return ans;
    }
    
private:
    void buildPath(const unordered_map<string,vector<string>> &p, const string &beginWord, const string &cur, vector<string> &path, vector<vector<string>> &ans) {
        path.emplace_back(cur);
        if(cur == beginWord)  // since we now traverse bi-directional, we have to check if the path starts with beginWord
            ans.emplace_back(path.rbegin(), path.rend());
        
        auto it = p.find(cur);
        if(it != p.end())
            for(const string &next : it->second)
                 buildPath(p, beginWord, next, path, ans);
        path.pop_back();
    }
};


// BFS: one-directional, explicitly build graph
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        if(find(wordList.begin(), wordList.end(), beginWord) == wordList.end())  // make sure we have beginWord
            wordList.push_back(beginWord);
        
        const int N = wordList.size();
        
        // build graph
        vector<vector<int>> g(N);
        int start = -1;
        int end = -1;
        for(int i=0; i<N; ++i) {
            if(wordList[i] == beginWord)
                start = i;
            else if(wordList[i] == endWord)
                end = i;
            for(int j=i+1; j<N; ++j) {
                if(canConnect(wordList[i], wordList[j])) {
                    g[i].push_back(j);
                    g[j].push_back(i);
                }
            }
        }
        
        if(end == -1)
            return vector<vector<string>>();
                
        // BFS
        vector<vector<int>> idxAns;
        queue<pair<int,vector<int>>> q;
        vector<int> visited(N, 0);
        q.push({start, vector<int>(1,start)});
        bool found = false;
        while(!q.empty() && !found) {
            int sz = q.size();
            while(sz--) {
                int cur = q.front().first;
                vector<int> path = q.front().second;
                q.pop();
                visited[cur] = 1;
                for(int next : g[cur]) {
                    if(!visited[next]) {
                        path.push_back(next);
                        q.push({next, path});
                        if(next == end) {
                            idxAns.push_back(path);
                            found = true;
                        }
                        path.pop_back();
                    }
                }
            }
        }
        
        // build answer with DFS
        vector<vector<string>> ans(idxAns.size());
        for(int i=0; i<idxAns.size(); ++i) {
            ans[i].resize(idxAns[i].size());
            for(int j=0; j<idxAns[i].size(); ++j) {
                ans[i][j] = wordList[idxAns[i][j]];
            }
        }
        return ans;
    }
    
private:
    // w1 and w2 is guaranteed to be of same length
    bool canConnect(const string &w1, const string &w2) {
        int count = 0;
        for(int i=0; i<w1.size(); ++i) {
            if(w1[i]!=w2[i] && ++count>1)
                return false;
        }
        return count==1;
    }
};
