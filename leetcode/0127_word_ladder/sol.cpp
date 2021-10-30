/*
A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:

Every adjacent pair of words differs by a single letter.
Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
sk == endWord
Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.

 

Example 1:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.
Example 2:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: 0
Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.
 

Constraints:

1 <= beginWord.length <= 10
endWord.length == beginWord.length
1 <= wordList.length <= 5000
wordList[i].length == beginWord.length
beginWord, endWord, and wordList[i] consist of lowercase English letters.
beginWord != endWord
All the words in wordList are unique.
*/


// BFS: one-directional w/o building the graph
// time complexity: O(N*26*L), N is number of words, L is length of a word
// space complexity: O(N*L)
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // BFS w/o explicitly build the graph
        unordered_set<string> dict(wordList.begin(), wordList.end());  // unvisited words
        if(!dict.count(endWord))
            return 0;
        
        // BFS
        queue<string> q;
        q.push(beginWord);
        dict.erase(beginWord);
        int nWords = 1;
        while(!q.empty()) {
            int sz = q.size();
            while(sz--) {
                string word = q.front();
                q.pop();
                // enumerate all variants of current word
                for(int i=0; i<word.size(); ++i) {
                    char c = word[i];
                    for(char c2='a'; c2<='z'; ++c2) {
                        word[i] = c2;
                        if(word == endWord)
                            return nWords+1;
                        if(dict.count(word)) {
                            q.push(word);
                            dict.erase(word);  // same as mark as visited
                        }
                    }
                    word[i] = c;
                }
            }
            ++nWords;
        }
        
        return 0;
    }
};


// BFS: bi-directional w/o building the graph
// time complexity: still O(N*L), but has const factor reduced compared to one-directional BFS
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // bi-directional BFS w/o explicitly build the graph
        unordered_set<string> dict(wordList.begin(), wordList.end());  // unvisited words
        if(!dict.count(endWord))
            return 0;
        
        // bi-directional BFS
        unordered_set<string> q1, q2;  // frontiers from two ends
        q1.emplace(beginWord);
        dict.erase(beginWord);
        q2.emplace(endWord);
        dict.erase(endWord);
        int nWords = 1;
        while(!q1.empty() && !q2.empty()) {
            // heuristic: always expand the smaller frontier
            if(q1.size() > q2.size())
                q1.swap(q2);
            
            unordered_set<string> q;  // next frontier
            for(string word : q1) {
                // enumerate all variants of current word
                for(int i=0; i<word.size(); ++i) {
                    char c = word[i];
                    for(char c2='a'; c2<='z'; ++c2) {
                        word[i] = c2;
                       if(q2.count(word))
                           return nWords+1;
                        if(dict.count(word)) {
                            q.emplace(word);
                            dict.erase(word);  // same as to mark as visited
                        }
                    }
                    word[i] = c;
                }
            }
            q1.swap(q);
            
            ++nWords;
        }
        
        
        return 0;
    }
};


// BFS: one directional with graph explicitly built
// time complexity: O(L*N^2), i.e., build graph
// space complexity: O(N^2), i.e., for graph
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
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
            return 0;
                
        // BFS
        queue<int> q;
        vector<int> visited(N, 0);
        q.push(start);
        visited[start] = 1;
        int nWords = 1;
        while(!q.empty()) {
            int sz = q.size();
            while(sz--) {
                int cur = q.front();
                q.pop();
                for(int next : g[cur]) {
                    if(next == end)
                        return nWords+1;
                    if(!visited[next]) {
                        q.push(next);
                        visited[next] = 1;
                    }
                }
            }
            ++nWords;
        }
        
        return 0;
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
