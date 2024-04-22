/*
Google/Apple

You are given an array of strings words. Each element of words consists of two lowercase English letters.

Create the longest possible palindrome by selecting some elements from words and concatenating them in any order. Each element can be selected at most once.

Return the length of the longest palindrome that you can create. If it is impossible to create any palindrome, return 0.

A palindrome is a string that reads the same forward and backward.

Example 1:

Input: words = ["lc","cl","gg"]
Output: 6
Explanation: One longest palindrome is "lc" + "gg" + "cl" = "lcggcl", of length 6.
Note that "clgglc" is another longest palindrome that can be created.

Example 2:

Input: words = ["ab","ty","yt","lc","cl","ab"]
Output: 8
Explanation: One longest palindrome is "ty" + "lc" + "cl" + "yt" = "tylcclyt", of length 8.
Note that "lcyttycl" is another longest palindrome that can be created.

Example 3:

Input: words = ["cc","ll","xx"]
Output: 2
Explanation: One longest palindrome is "cc", of length 2.
Note that "ll" is another longest palindrome that can be created, and so is "xx".
 
Constraints:

1 <= words.length <= 10^5
words[i].length == 2
words[i] consists of lowercase English letters.
*/

// greedy:
// -- 1) for word with same letters, e.g., "xx", the even amount can be used, and only one of the odd part can be used
// -- 2) for word like "xy", search for occurrence of "yx" and they can be added together
// time: O(N)
// space: O(N) due to hash table used
class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        unordered_map<string,int> wordCount;
        for(auto &w : words) {
            ++wordCount[w];
        }

        int ans = 0;
        bool mid = false;  // a single word with two same letters can be put in the middle
        for(auto &kv : wordCount) {
            if(!kv.second)  // the word may have already been used
                continue;

            string w1 = kv.first;
            if(w1[0] == w1[1]) {
                ans += 4*(kv.second/2);
                if(kv.second % 2)
                    mid = true;
                kv.second = 0;  // not necessary
            }
            else {
                string w2 = kv.first;
                swap(w2[0], w2[1]);
                auto it2 = wordCount.find(w2);
                if(it2 != wordCount.end()) {
                    int count = min(kv.second, it2->second);
                    ans += 4*count;
                    kv.second -= count;
                    it2->second -= count;
                }
            }
        }

        if(mid)
            ans += 2;
        return ans;
    }
};

// a slightly different and cleaner implementation (no update to the hash table needed)
class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        unordered_map<string,int> wordCount;
        for(auto &w : words) {
            ++wordCount[w];
        }

        int ans = 0;
        bool mid = false;  // a single word with two same letters can be put in the middle
        for(auto &kv : wordCount) {
            string w2(kv.first.rbegin(), kv.first.rend());
            //if(!wordCount.count(w2))
            //    continue;
            if(w2[0] == w2[1]) {
                ans += 4*(kv.second/2);
                if(kv.second % 2)
                    mid = true;
            }
            else {
                if(wordCount.count(w2))
                    ans += 2*min(kv.second, wordCount[w2]/*this could invalidate iterators*/);  // reverse word would be counted in the future iterations
            }
        }

        if(mid)
            ans += 2;
        return ans;
    }
};


// ref sol: use 2-D vector to store count of all two letter words
class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        int ans=0;
        vector<vector<int>> count(26,vector<int>(26));
        for(string w:words)
        {
            int i=w[0]-'a';
            int j=w[1]-'a';
            if(count[j][i])
            {
                ans+=4;
                count[j][i]--;  // cancel out with an existing reversed word
            }
            else
                count[i][j]++;
        }
        for(int i=0;i<26;i++)
        {
            if(count[i][i])
                return ans+2;  // only one can be counted, so return directly
        }
        return ans;
    }
};
