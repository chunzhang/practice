/*
Facebook/Cruise Automation

Given a string s, return all the palindromic permutations (without duplicates) of it.

You may return the answer in any order. If s has no palindromic permutation, return an empty list.

Example 1:

Input: s = "aabb"
Output: ["abba","baab"]

Example 2:

Input: s = "abc"
Output: []
 

Constraints:

1 <= s.length <= 16
s consists of only lowercase English letters.
*/


// sol1: DFS to build half of the palindrome
// time: O(N/2 + 1)!
class Solution {
public:
    vector<string> generatePalindromes(string s) {
        vector<int> count(128, 0);
        for(char c : s)
            ++count[c];
        vector<string> ans;
        string cur;
        dfs(ans, cur, s.size(), count);
        return ans;
    }

private:
    void dfs(vector<string> &ans, string &cur/*half of the palindrome*/, int left, vector<int> &count) {
        if(left <= 1) {  // found valid palindrome
            string temp = cur;
            reverse(temp.begin(), temp.end());
            if(left == 0) {
                ans.push_back(cur+temp);
            }
            else {
                for(char c='a'; c<='z'; ++c)
                    if(count[c]) {
                        ans.push_back(cur+string(1,c)+temp);
                        break;
                    }
            }
            return;
        }

        for(char c='a'; c<='z'; ++c) {
            if(count[c] >= 2) {
                cur.push_back(c);
                count[c] -= 2;
                dfs(ans, cur, left-2, count);
                cur.pop_back();
                count[c] += 2;
            }
        }
    }
};


// sol2: build half of the palindrome, and then find all permutations of it
// time: O(N/2 + 1)!
class Solution {
public:
    vector<string> generatePalindromes(string s) {
        vector<int> count(128, 0);
        for(char c : s)
            ++count[c];

        // 1. build half of the palindrome (if exists)
        string half;
        bool odd = false;
        char mid;  // middle character (at most one exists)
        for(char c='a'; c<='z'; ++c) {
            if(count[c]%2) {  // detect odd characters
                if(odd)
                    return {};  // multiple odd character exists -- no solution
                odd = true;
                mid = c;
            }
            half += string(count[c]/2, c);
        }

        // 2. build all permutations of the half palindrome
        vector<string> ans = move(allPermutations(half));  // use move semantics
        for(string &p : ans) {
            string temp = p;
            reverse(temp.begin(),temp.end());
            if(odd)
                p.push_back(mid);
            p += temp;
        }

        return ans;
    }

private:
    // find all permutations
    vector<string> allPermutations(string &s) {
        vector<string> perms;
        string orig = s;
        do {
            perms.push_back(s);
            next_permutation(s.begin(), s.end());  // next permutation > s -- will not generate duplicated ones
        } while(s != orig);
        return perms;
    }
};
