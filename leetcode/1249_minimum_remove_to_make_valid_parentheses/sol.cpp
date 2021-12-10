/*
Given a string s of '(' , ')' and lowercase English characters.

Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions ) so that the resulting parentheses string is valid and return any valid string.

Formally, a parentheses string is valid if and only if:

It is the empty string, contains only lowercase characters, or
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.
 

Example 1:

Input: s = "lee(t(c)o)de)"
Output: "lee(t(c)o)de"
Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.
Example 2:

Input: s = "a)b(c)d"
Output: "ab(c)d"
Example 3:

Input: s = "))(("
Output: ""
Explanation: An empty string is also valid.
Example 4:

Input: s = "(a(b(c)d)"
Output: "a(b(c)d)"
 

Constraints:

1 <= s.length <= 10^5
s[i] is either'(' , ')', or lowercase English letter.
*/


// scan left-->right to remove invalid ')', and then scan right-->left to remove invalid '('
// time complexity: O(N)
// space complexity: O(N)
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        string temp;
        scan(s, temp, '(', ')');
        reverse(temp.begin(), temp.end());
        string ans;
        scan(temp, ans, ')', '(');
        reverse(ans.begin(), ans.end());
        return ans;
    }
    
private:
    void scan(const string&s, string &ans, char open, char close) {
        int budget = 0;
        for(int i=0; i<s.size(); ++i) {
            ans.push_back(s[i]);
            if(s[i] == open)
                ++budget;
            else if(s[i] == close) {
                if(budget)
                    --budget;
                else
                    ans.pop_back();
            }
        }
    }
};


// same idea, a slightly different impl that records parentheses to be removed so as to build answer in the end
// no need to do any string reverse
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        vector<char> removed(s.size(), 0);
        
        // scan from left to right to remove invalid ')'
        int left = 0;
        for(int i=0; i<s.size(); ++i) {
            if(s[i] == '(') {
                ++left;
            }
            else if(s[i] == ')') {
                if(left)
                    --left;
                else
                   removed[i] = 1; 
            }
        }
        
        // scan from right to left to remove invalid '('
        int right = 0;
        for(int i=s.size()-1; i>=0; --i) {
            if(removed[i] == 1)
                continue;
            
            if(s[i] == ')')
                ++right;
            else if(s[i] == '(') {
                if(right)
                    --right;
                else
                    removed[i] = 1;
            }
        }
        
        // build answer
        string ans;
        for(int i=0; i<s.size(); ++i)
            if(removed[i] != 1)
                ans.push_back(s[i]);
        return ans;
    }
};
