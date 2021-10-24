/*
Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.

A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.



 

Example 1:

Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
Example 2:

Input: digits = ""
Output: []
Example 3:

Input: digits = "2"
Output: ["a","b","c"]
 

Constraints:

0 <= digits.length <= 4
digits[i] is a digit in the range ['2', '9'].
*/


// DFS/backtracking
// time complexity: O(N*4^N), wehre N is the number of digits; totally 4^N combinations
// space complexity: O(N), which is the recursion depth
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if(digits.empty())
            return {};
        
        string cur;
        vector<string> ans;
        dfs(digits, 0, cur, ans);
        return ans;
    }
    
private:
    vector<string> _m = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    void dfs(const string &digits, int i, string &cur, vector<string> &ans) {
        const string &s = _m[digits[i]-'0'];
        for(char c : s) {
            cur.push_back(c);
            if(i == digits.size()-1)
                ans.push_back(cur);
            else
                dfs(digits, i+1, cur, ans);
            cur.pop_back();
        }
    }
};


// BFS
// time complexity: O(N*4^N)
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if(digits.empty())
            return {};
               
        // BFS
        vector<string> ans;
        ans.push_back("");  // this is important
        for(char d : digits) {
            const string &s = _m[d-'0'];
            vector<string> tmp;  // next level
            for(const string &cur : ans)
                for(char c : s)
                    tmp.emplace_back(cur+c);
            ans.swap(tmp);
        }
        
        return ans;
    }
    
private:
    vector<string> _m = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
};
