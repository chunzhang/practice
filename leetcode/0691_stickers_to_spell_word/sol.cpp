/*
We are given n different types of stickers. Each sticker has a lowercase English word on it.

You would like to spell out the given string target by cutting individual letters from your collection of stickers and rearranging them. You can use each sticker more than once if you want, and you have infinite quantities of each sticker.

Return the minimum number of stickers that you need to spell out target. If the task is impossible, return -1.

Note: In all test cases, all words were chosen randomly from the 1000 most common US English words, and target was chosen as a concatenation of two random words.

 

Example 1:

Input: stickers = ["with","example","science"], target = "thehat"
Output: 3
Explanation:
We can use 2 "with" stickers, and 1 "example" sticker.
After cutting and rearrange the letters of those stickers, we can form the target "thehat".
Also, this is the minimum number of stickers necessary to form the target string.
Example 2:

Input: stickers = ["notice","possible"], target = "basicbasic"
Output: -1
Explanation:
We cannot form the target "basicbasic" from cutting letters from the given stickers.
 

Constraints:

n == stickers.length
1 <= n <= 50
1 <= stickers[i].length <= 10
1 <= target.length <= 15
stickers[i] and target consist of lowercase English letters.
*/

// DFS + memoization (same as DP+memoization)
class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        // idea is to use DFS + memoization to solve the problem (can also be interpreted as DP+memoization)
        vector<vector<int>> sc(stickers.size(), vector<int>(26,0));  // counting characters for each sticker
        for(int i=0; i<stickers.size(); ++i)
            for(char c : stickers[i])
                ++sc[i][c-'a'];

        sort(target.begin(), target.end());  // note the order of characters in target is indifferent, so always keep it in sorted order to simply the coding
        unordered_map<string,int> mem;  // memorize result
        mem[""] = 0;

        // now perform DFS with memoization
        return dfs(sc, mem, target);
    }

    int dfs(const vector<vector<int>> &sc, unordered_map<string,int> &mem, string target) {
        if(target.empty())
            return 0;

        auto it = mem.find(target);
        if(it != mem.end())
            return it->second;

        // build target character counting
        vector<int> tc(26,0);
        for(char c : target)
            ++tc[c-'a'];

        // try each sticker
        int ans = INT_MAX;
        for(int i=0; i<sc.size(); ++i) {
            if(!sc[i][target[0]-'a'])  // this is to make sure current sticker at least covers one character of the target
                continue;

            // select current sticker
            string nextTarget;
            for(int j=0; j<26; ++j) {
                if(tc[j]-sc[i][j]>0)
                    nextTarget += string(tc[j]-sc[i][j], 'a'+j);  // build new target string in sorted order
            }
            int ansNext = dfs(sc, mem, nextTarget);
            if(ansNext != -1)
                ans = min(ans, ansNext+1);
        }

        if(ans == INT_MAX)
            ans = -1;
        
        mem[target] = ans;
        return ans;
    }
};


// my initial DFS solution -- TLE
class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        // idea is to use DFS with pruning to solve the knapsack problem
        vector<int> targetCount(26, 0);  // counting target characters
        for(char c : target)
            ++targetCount[c-'a'];
        vector<vector<int>> stickerCount(stickers.size(), vector<int>(26,0));
        for(int i=0; i<stickers.size(); ++i) {
            for(char c : stickers[i])
                ++stickerCount[i][c-'a'];
        }

        // first, exclude unsolvable problem: target has a character does not appear in any of the stickers
        for(char c : target) {
            bool found = false;
            for(int i=0; i<stickerCount.size(); ++i) {
                if(stickerCount[i][c-'a']) {
                    found = true;
                    break;
                }
            }
            if(!found)
                return -1;
        }

        // then, do DFS with pruning
        int minSelected = INT_MAX;
        dfs(stickerCount, targetCount, minSelected, 0);
        return minSelected;
    }

    void dfs(const vector<vector<int>> &stickerCount, vector<int> &targetCount, int &minSelected, int nSelected/*num selected stickers*/) {
        if(nSelected >= minSelected)  // cannot reach a better solution in current branch
            return;

        // whether a valid solution is found
        bool foundSolution = true;
        for(int count : targetCount) {
            if(count > 0) {  // found uncovered character in target
                foundSolution = false;
                break;
            }
        }
        if(foundSolution) {
            minSelected = nSelected;
        }

        // try next sticker to use
        for(int i=0; i<stickerCount.size(); ++i) {
            // select the i-th sticker
            bool help = false;  // whether select sticker i helps cover more characters of target
            for(int j=0; j<26; ++j) {
                if(stickerCount[i][j] && targetCount[j]>0)
                    help = true;
                targetCount[j] -= stickerCount[i][j];
            }

            if(help)
                dfs(stickerCount, targetCount, minSelected, nSelected+1);

            // unselect the i-th sticker
            for(int j=0; j<26; ++j)
                targetCount[j] += stickerCount[i][j];
        }
    }
};
