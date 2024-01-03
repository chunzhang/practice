/*
Bloomberg/Facebook/TikTok

You are given a string s and an integer k, a k duplicate removal consists of choosing k adjacent and equal letters from s and removing them, causing the left and the right side of the deleted substring to concatenate together.

We repeatedly make k duplicate removals on s until we no longer can.

Return the final string after all such duplicate removals have been made. It is guaranteed that the answer is unique.

 

Example 1:

Input: s = "abcd", k = 2
Output: "abcd"
Explanation: There's nothing to delete.
Example 2:

Input: s = "deeedbbcccbdaa", k = 3
Output: "aa"
Explanation: 
First delete "eee" and "ccc", get "ddbbbdaa"
Then delete "bbb", get "dddaa"
Finally delete "ddd", get "aa"
Example 3:

Input: s = "pbbcggttciiippooaais", k = 2
Output: "ps"
 

Constraints:

1 <= s.length <= 10^5
2 <= k <= 10^4
s only contains lowercase English letters.
*/


// use a stack to store the characters, when there are k same characters, delete them.
// O(N) we iterate through the string only once, and there's const stack operations for each char
class Solution {
public:
    string removeDuplicates(string s, int k) {
        // use vector as a stack to store current character and it's count
        vector<pair<char,int>> st;
        for(char c : s) {
            if(st.empty() || c!=st.back().first)
                st.emplace_back(c,1);
            else {
                ++st.back().second;
                if(st.back().second == k)  // string reduction on the fly
                    st.pop_back();
            }
        }

        // rebuild answer string
        string ans;
        for(auto &p : st)
            ans += string(p.second, p.first);
        return ans;
    }
};


// brute-force solution by simulating the process: TLE
// O(N^2/k)
class Solution {
public:
    string removeDuplicates(string s, int k) {
        while(removeOnce(s,k))
            ;
        return s;
    }

private:
    bool removeOnce(string &s, int k) {
        string res;
        for(int i=0; i<s.size(); ) {
            int j = i+1;
            while(j<s.size() && s[j]==s[i])
                ++j;
            res += s.substr(i, (j-i)%k);
            i = j;
        }

        bool changed = res.size()<s.size();
        s.swap(res);
        return changed;  // some removal happen
    }
};
