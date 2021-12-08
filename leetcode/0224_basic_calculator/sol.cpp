/*
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
