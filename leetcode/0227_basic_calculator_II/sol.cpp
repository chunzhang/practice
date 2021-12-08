/*
Given a string s which represents an expression, evaluate this expression and return its value. 

The integer division should truncate toward zero.

You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

 

Example 1:

Input: s = "3+2*2"
Output: 7
Example 2:

Input: s = " 3/2 "
Output: 1
Example 3:

Input: s = " 3+5 / 2 "
Output: 5
 

Constraints:

1 <= s.length <= 3 * 10^5
s consists of integers and operators ('+', '-', '*', '/') separated by some number of spaces.
s represents a valid expression.
All the integers in the expression are non-negative integers in the range [0, 2^31 - 1].
The answer is guaranteed to fit in a 32-bit integer.
*/


// handle higher prioirty '*' and '/' by remembering previous operand
// needs to handle white-spaces
// time complexity: O(N)
class Solution {
public:
    int calculate(string s) {
        int idx = 0;
        long num1 = getNum(s, idx);  // first operand
        long val = num1;  // current val of the expression
        while(idx < s.size()) {
            char op = getOp(s, idx);
            long num2 = getNum(s, idx);

            if(op == '+') {
                val += num2;
                num1 = num2;
            }
            else if(op == '-') {
                val -= num2;
                num1 = -num2;  // minus ==> add negative
            }
            else if(op == '*') {
                val = val - num1 + num1*num2;  // recover previous val, then add the multiplication to it
                num1 = num1*num2;
            }
            else if(op == '/') {
                val = val - num1 + num1/num2;
                num1 = num1/num2;
            }
        }
        
        return val;
    }
    
private:
    char getOp(const string &s, int &idx) {
        while(idx<s.size() && s[idx]==' ')
            ++idx;
        return idx<s.size()?s[idx++]:'N';  // 'N' means invalid operator, i.e., no more available
    }
    
    long getNum(const string &s, int &idx) {
        while(idx<s.size() && s[idx]==' ')
            ++idx;
        long num = 0;
        while(isdigit(s[idx])) {
            num = num*10 + s[idx++] - '0';
        }
        return num;
    }
};
