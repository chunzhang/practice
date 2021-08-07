/*
You are given an array of words where each word consists of lowercase English letters.

wordA is a predecessor of wordB if and only if we can insert exactly one letter anywhere in wordA without changing the order of the other characters to make it equal to wordB.

For example, "abc" is a predecessor of "abac", while "cba" is not a predecessor of "bcad".
A word chain is a sequence of words [word1, word2, ..., wordk] with k >= 1, where word1 is a predecessor of word2, word2 is a predecessor of word3, and so on. A single word is trivially a word chain with k == 1.

Return the length of the longest possible word chain with words chosen from the given list of words.

 

Example 1:

Input: words = ["a","b","ba","bca","bda","bdca"]
Output: 4
Explanation: One of the longest word chains is ["a","ba","bda","bdca"].
Example 2:

Input: words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]
Output: 5
Explanation: All the words can be put in a word chain ["xb", "xbc", "cxbc", "pcxbc", "pcxbcf"].
Example 3:

Input: words = ["abcd","dbqca"]
Output: 1
Explanation: The trivial word chain ["abcd"] is one of the longest word chains.
["abcd","dbqca"] is not a valid word chain because the ordering of the letters is changed.
 

Constraints:

1 <= words.length <= 1000
1 <= words[i].length <= 16
words[i] only consists of lowercase English letters.
*/

// Bottom-up DP
// Time complexity is O(NlgN+N*N*L), where N is number of words, L is length of a word
class Solution {
public:
    int longestStrChain(vector<string>& words) {
        // sort words by length, O(NlgN)
        sort(words.begin(), words.end(), [](const string &s1, const string &s2){return s1.size()<s2.size();});
        
        // dp(i): max length of chain that ends at word i
        // use similar bottom-up DP as of "Longest Increasing Subsequence (leetcode 300)"
        int ans = 1;
        vector<int> dp(words.size(), 1);
        for(int i=1; i<words.size(); ++i) {  // O(N)
            if(words[i].size() == 1)
                continue;
            for(int j=i-1; j>=0; --j) {  // note words is sorted string length, O(N)
                if(words[j].size() < words[i].size()-1)
                    break;
                if(isPredecessor(words[j], words[i])) {  // O(L)
                    dp[i] = max(dp[i], dp[j]+1);
                }
            }
            ans = max(ans, dp[i]);
        }
        
        return ans;
    }
    
private:
    // Whether s1 is predecessor of s2
    bool isPredecessor(const string &s1, const string &s2) {
        if(s1.size() != s2.size()-1)
            return false;
        
        int diff = 0;
        for(int i=0,j=0; i<s1.size()&&j<s2.size(); ) {
            if(s1[i]!=s2[j]) {
                if(++diff > 1)
                    return false;
                ++j;
            }
            else {
                ++i;
                ++j;
            }
        }
        
        return true;
    }
};

// Official DP with memorization
// Idea is to compute predecessor by deleting character from word one at a time, since L is much smaller than N, time complexity will be better
// Time complexity: O(N*L*L), N is the recursion depth, and L^2 to compute all predecessors of a word
class Solution {
private:

    int dfs(unordered_set<string> &words, unordered_map<string, int> &memo, string currentWord) {
        // If the word is encountered previously we just return its value present in the map (memoization).
        if (memo.find(currentWord) != memo.end()) {
            return memo[currentWord];
        }
        // This stores the maximum length of word sequence possible with the 'currentWord' as the
        int maxLength = 1;

        // creating all possible strings taking out one character at a time from the `currentWord`
        for (int i = 0; i < currentWord.length(); i++) {
            string newWord = currentWord.substr(0, i) + currentWord.substr(i + 1);
            // If the new word formed is present in the list, we do a dfs search with this newWord.
            if (words.find(newWord) != words.end()) {
                int currentLength = 1 + dfs(words, memo, newWord);
                maxLength = max(maxLength, currentLength);
            }
        }
        memo[currentWord] = maxLength;

        return maxLength;
    }

public :
    int longestStrChain(vector<string> &words) {
        unordered_map<string, int> memo;
        unordered_set<string> wordsPresent;
        for (const string &word : words) {
            wordsPresent.insert(word);
        }
        int ans = 0;
        for (const string &word : words) {
            ans = max(ans, dfs(wordsPresent, memo, word));
        }
        return ans;
    }
};

// Official bottom-up DP
// Time complexity is O(NlogN+N*L*L), NlgN for sorting, N of outer loop to iterate through all words, and L^2 to compute all possible predecessors of a word
class Solution {
public :

    int longestStrChain(vector<string> &words) {
        unordered_map<string, int> dp;

        // Sorting the list in terms of the word length.
        std::sort(words.begin(), words.end(), [](const std::string &word1, const std::string &word2) {
            return word1.size() < word2.size();
        });

        int longestWordSequenceLength = 1;

        for (const string &word : words) {
            int presentLength = 1;
            // Find all possible predecessors for the current word by removing one letter at a time.
            for (int i = 0; i < word.length(); i++) {
                string predecessor = word.substr(0, i) + word.substr(i + 1, word.length() + 1);
                if (dp.find(predecessor) != dp.end()) {
                    int previousLength = dp[predecessor];
                    presentLength = max(presentLength, previousLength + 1);
                }
            }
            dp[word] = presentLength;
            longestWordSequenceLength = max(longestWordSequenceLength, presentLength);
        }
        return longestWordSequenceLength;
    }
};
