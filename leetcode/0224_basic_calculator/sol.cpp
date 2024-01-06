/*
Facebook/Microsoft/TikTok

Given a string s representing a valid expression, implement a basic calculator to evaluate it, and return the result of the evaluation.

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

 

Example 1:

Input: s = "1 + 1"
Output: 2

Example 2:

Input: s = " 2-1 + 2 "
Output: 3

Example 3:

Input: s = "(1+(4+5+2)-3)+(6+8)"
Output: 23
 

Constraints:

1 <= s.length <= 3 * 10^5
s consists of digits, '+', '-', '(', ')', and ' '.
s represents a valid expression.
'+' is not used as a unary operation (i.e., "+1" and "+(2 + 3)" is invalid).
'-' could be used as a unary operation (i.e., "-1" and "-(2 + 3)" is valid).
There will be no two consecutive operators in the input.
Every number and running calculation will fit in a signed 32-bit integer.
*/

// my newer solution -- key is to remember the current operator, which will be '+' to start with
class Solution {
public:
    int calculate(string s) {
        int cur = 0;
        return cal(s,cur);
    }

private:
    int cal(const string &s, int &cur) {
        int ans = 0;
        char op = '+';  // current operator: always start with '+'
        while(cur < s.size()) {
            if(isdigit(s[cur])) {
                int num = 0;
                while(cur<s.size() && isdigit(s[cur])) {
                    num = num*10 + (s[cur++]-'0');  // have to use bracket to avoid integer overflow
                }
                ans += (op=='+')?num:(-num);
                --cur;  // because we increment cur at the end of each loop
            }
            else if(s[cur]=='+' || s[cur]=='-'){
                op = s[cur];
            }
            else if(s[cur] == '(') {
                int num = cal(s,++cur);  // need to increment cur to bypass '('
                ans += op=='+'?num:(-num);
            }
            else if(s[cur] == ')') {  // don't increment cur as it'll be incremented in the caller
                return ans;
            }
            ++cur;
        }
        return ans;
    }
};


// recursive call when seeing '(', returns when seeing ')'
// time complexity: O(N)
class Solution {
public:
    int calculate(string s) {
        int idx = 0;
        return calRec(s, idx);
    }
    
private:
    long getNum(const string &s, int &idx) {
        while(idx<s.size() && s[idx]==' ')
            ++idx;
        long num = 0;
        while(isdigit(s[idx])) {
            num = num*10 + s[idx++] - '0';
        }
        return num;
    }
    
    long calRec(const string &s, int &idx) {
        long val = 0;
        char op = '+';
        while(idx < s.size()) {
            if(s[idx] == ' ') {
                ++idx;
                continue;
            }
            
            if(s[idx]=='+' || s[idx]=='-') {
                op = s[idx++];
                continue;
            }

            // find second operand
            long curNum = 0;
            if(s[idx] == '(') {
                ++idx;
                curNum = calRec(s, idx);
            }
            else if(s[idx] == ')') {
                ++idx;
                return val;
            }
            else {
                curNum = getNum(s, idx);
            }
            
            if(op == '+')
                val += curNum;
            else if(op == '-')
                val -= curNum;
        }
        
        return val;
    }
};
