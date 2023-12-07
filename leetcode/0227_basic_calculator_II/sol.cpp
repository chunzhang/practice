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


// my other solution
class Solution {
public:
    int calculate(string s) {
        while(s.back() == ' ')
            s.pop_back();
        int cur = 0;
        vector<int> nums;
        vector<char> ops;
        nums.push_back(getNum(s,cur));
        while(cur<s.size()) {  // first evaluate '*', '/'
            ops.push_back(getOp(s,cur));
            nums.push_back(getNum(s,cur));
            if(ops.back()=='*' || ops.back()=='/') {
                int num2 = nums.back();
                nums.pop_back();
                int num1 = nums.back();
                nums.pop_back();
                nums.push_back((ops.back()=='*')?(num1*num2):(num1/num2));
                ops.pop_back();
            }
        }

        // now calculate '+', '-' from left to right
        int val = nums[0];
        for(int i=0; i<ops.size(); ++i) {
            if(ops[i] == '+')
                val += nums[i+1];
            else
                val -= nums[i+1];
        }
        return val;
    }

    int getNum(const string &s, int &cur) {
        while(cur<s.size() && s[cur]==' ')
            ++cur;

        int pos = cur;
        while(cur<s.size() && isdigit(s[cur]))
            ++cur;

        return stoi(s.substr(pos, cur-pos));
    }

    char getOp(const string &s, int &cur) {
        while(cur<s.size() && s[cur]== ' ')
            ++cur;
        return s[cur++];
    }
};


// reference solution 1
class Solution {
public:
    int calculate(string s) {
        int len = s.length();
        if (len == 0) return 0;
        stack<int> stack;
        int currentNumber = 0;
        char operation = '+';
        for (int i = 0; i < len; i++) {
            char currentChar = s[i];
            if (isdigit(currentChar)) {
                currentNumber = (currentNumber * 10) + (currentChar - '0');
            }
            if (!isdigit(currentChar) && !iswspace(currentChar) || i == len - 1) {
                if (operation == '-') {
                    stack.push(-currentNumber);
                } else if (operation == '+') {
                    stack.push(currentNumber);
                } else if (operation == '*') {
                    int stackTop = stack.top();
                    stack.pop();
                    stack.push(stackTop * currentNumber);
                } else if (operation == '/') {
                    int stackTop = stack.top();
                    stack.pop();
                    stack.push(stackTop / currentNumber);
                }
                operation = currentChar;
                currentNumber = 0;
            }
        }
        int result = 0;
        while (stack.size() != 0) {
            result += stack.top();
            stack.pop();
        }
        return result;
    }
};


// reference solution 2
class Solution {
public:
    int calculate(string s) {
        int length = s.length();
        if (length == 0) return 0;
        int currentNumber = 0, lastNumber = 0, result = 0;
        char sign = '+';
        for (int i = 0; i < length; i++) {
            char currentChar = s[i];
            if (isdigit(currentChar)) {
                currentNumber = (currentNumber * 10) + (currentChar - '0');
            }
            if (!isdigit(currentChar) && !iswspace(currentChar) || i == length - 1) {
                if (sign == '+' || sign == '-') {
                    result += lastNumber;
                    lastNumber = (sign == '+') ? currentNumber : -currentNumber;
                } else if (sign == '*') {
                    lastNumber = lastNumber * currentNumber;
                } else if (sign == '/') {
                    lastNumber = lastNumber / currentNumber;
                }
                sign = currentChar;
                currentNumber = 0;
            }
        }
        result += lastNumber;
        return result;  
    }
};
